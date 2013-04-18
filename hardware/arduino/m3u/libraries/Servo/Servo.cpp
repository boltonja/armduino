/*
 Servo.cpp - Interrupt driven Servo library for Arduino using 16 bit timers- Version 2
 Copyright (c) 2009 Michael Margolis.  All right reserved.
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 
 Modified 2013 by Steven Cooney to port Servo Library over to sim3u167 ACB chip.
 */

/* 
 
 A servo is activated by creating an instance of the Servo class passing the desired pin to the attach() method.
 The servos are pulsed in the background using the value most recently written using the write() method
 
 Note that analogWrite of PWM on pins associated with the timer are disabled when the first servo is attached.
 ONLY TIMER2 (PCA1) channel two is being used in this implementation. 
 Can change the timer and channel by changing the defaultTimer and defaultChannel.
 Can change the number of servos allowed by changing MAX_SERVOS.
 Interrupt takes the value of ticks in each servo to find the next time to interrupt. 
 It will interrupt the same number of times as there are servos.
 When updating the servo's ticks the update will be seen on the next period cycle.
 
 The methods are:
 
 Servo - Class for manipulating servo motors connected to Arduino pins.
 
 attach(pin )  - Attaches a servo motor to an i/o pin.
 attach(pin, min, max  ) - Attaches to a pin setting min and max values in microseconds
 default min is 544, max is 2400  
 
 write()     - Sets the servo angle in degrees.  (invalid angle that is valid as pulse in microseconds is treated as microseconds)
 writeMicroseconds() - Sets the servo pulse width in microseconds 
 read()      - Gets the last written servo pulse width as an angle between 0 and 180. 
 readMicroseconds()   - Gets the last written servo pulse width in microseconds. (was read_us() in first release)
 attached()  - Returns true if there is a servo attached. 
 detach()    - Stops an attached servos from pulsing its i/o pin. 
 
 
 
*/


#include <Arduino.h> 
#include <stdint.h>
#include "Servo.h"
#include <libmaple\timer.h>


// from wiring_constants.h
extern void __disable_irq(void);
extern void __enable_irq(void);



#define timer16_Sequence_t 1
#define defaultTimer TIMER2
#define defaultChannel 2
#define maxReload    65535

// clockCyclesPerTick = clock run at 2.5 Mhz
#define clockCyclesPerTick 25
#define usToTicks(_us)    ((clockCyclesPerTick* _us)/10)     // converts microseconds to tick by multiplying the seconds times the clock frequency
#define ticksToUs(_ticks) ((((unsigned)_ticks)*10)/ clockCyclesPerTick) // converts from ticks back to microseconds


#define TRIM_DURATION       2                               // compensation ticks to trim adjust for digitalWrite delays // 12 August 2009

//#define NBR_TIMERS        (MAX_SERVOS / SERVOS_PER_TIMER)

static servo_t servos[MAX_SERVOS];                          // static array of servo structures
static volatile int8_t Channel[_Nbr_16timers ];             // counter for the servo being pulsed for each timer (or -1 if refresh interval)
static uint8_t numActiveServos = 0;          // number of active servos


uint8_t ServoCount = 0;                                     // the total number of attached servos


// convenience macros
#define SERVO_INDEX_TO_TIMER(_servo_nbr) ((timer16_Sequence_t)(_servo_nbr / SERVOS_PER_TIMER)) // returns the timer controlling this servo
#define SERVO_INDEX_TO_CHANNEL(_servo_nbr) (_servo_nbr % SERVOS_PER_TIMER)       // returns the index of the servo on this timer
#define SERVO_INDEX(_timer,_channel)  ((_timer*SERVOS_PER_TIMER) + _channel)     // macro to access servo index by timer and channel
#define SERVO(_timer,_channel)  (servos[SERVO_INDEX(_timer,_channel)])            // macro to access servo class by timer and channel

#define SERVO_MIN() (MIN_PULSE_WIDTH - this->min * 4)  // minimum value in uS for this servo
#define SERVO_MAX() (MAX_PULSE_WIDTH - this->max * 4)  // maximum value in uS for this servo 


static void initISR(timer_dev *dev,uint8_t channel, uint16_t reloadValue);
volatile uint8_t servoNum    = 0;                // number of servos

/************ static functions common to all instances ***********************/
 static inline void interruptHandler(void){
    static uint8_t servoServiced = 0;                // which servo i am toggling in the interrupt
    static uint32_t ticksElapsed = 0;                // time elapsed since the biggining of the 20 ms period
    uint32_t newInterruptPeriod = 0;
    int i = 0;            
    static bool newPeriod = true;                    // true if this is the first interrupt in a new period    
    // update the ticks for any servo that got changed
    // set all servos high at beginning of each 20 ms period        
    if (newPeriod){            
        for (i = 0; i < servoNum; i += 1){
            digitalWrite(servos[i].Pin.nbr,HIGH);
            servos[i].ticks = servos[i].updatedTicks;
            servos[i].Pin.isActive = servos[i].Pin.isActiveUpdated;
            if (servos[i].Pin.isActive == false){
                servoServiced += 1;
            }
        }
        newPeriod = false;
    }
    
    i = 0;
    int pendingTicks = 10000;
    int repeats = 0;
    // find next servo that has the next closest time to interrupt
    for (i = 0; i < servoNum; i += 1){
        if ((servos[i].ticks < pendingTicks) && (servos[i].ticks > ticksElapsed) && (servos[i].Pin.isActive == true)){
            pendingTicks = servos[i].ticks;
        }
        if ((servos[i].ticks == ticksElapsed) && (servos[i].Pin.isActive == true)){
            servoServiced += 1;
            digitalWrite(servos[i].Pin.nbr,LOW);
        }
    }    

    // get new interrupt time until all servos are serviced
    if (servoServiced < servoNum){
        newInterruptPeriod = pendingTicks - ticksElapsed;
        ticksElapsed += newInterruptPeriod;
    }
    // once done wait until 20 ms period is done
    else{
        newInterruptPeriod = 50000 - ticksElapsed; 
        ticksElapsed = 0;
        servoServiced = 0;
        newPeriod = true;
    }
    initISR(defaultTimer, defaultChannel, newInterruptPeriod);
}

static void initISR(timer_dev *dev,uint8_t channel, uint16_t reloadValue){  
    timer_pause(dev);
    timer_set_prescaler(dev, 15);
    timer_set_reload(dev, reloadValue);
    timer_resume(dev);
    timer_set_compare(dev, channel, 1);
    timer_set_mode(dev, channel, TIMER_OUTPUT_COMPARE);
    timer_attach_interrupt(dev, channel, interruptHandler);
} 

static void finISR(timer_dev *dev, uint8_t channel){
    timer_detach_interrupt(dev, channel);
}

static boolean isTimerActive(timer_dev *timer){
    int index = 0;
    for (index = 0; index < SERVOS_PER_TIMER; index += 1){
        if (servos[index].Pin.isActiveUpdated == true){
            return true;
        }
    }
    return false;
}

/****************** end of static functions ******************************/

Servo::Servo(){
    if(ServoCount < MAX_SERVOS){
        this->servoIndex = ServoCount++;                    // assign a servo index to this instance
        servos[this->servoIndex].updatedTicks = usToTicks(DEFAULT_PULSE_WIDTH);   // store default values  - 12 Aug 2009
        servoNum += 1;
    }
    else{
        this->servoIndex = INVALID_SERVO;  // too many servos 
	}
}

uint8_t Servo::attach(int pin){
  return this->attach(pin, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
}

uint8_t Servo::attach(int pin, int min, int max){
    // only does function if the servo is not already attached
    if(servos[this->servoIndex].Pin.isActiveUpdated != true){ 
        if(this->servoIndex < MAX_SERVOS){
            pinMode(pin, OUTPUT);                                   // set servo pin to output
            servos[this->servoIndex].Pin.nbr = pin;  
            // todo min/max check: abs(min - MIN_PULSE_WIDTH) /4 < 128 
            this->min  = (MIN_PULSE_WIDTH - min) / 4;                //resolution of min/max is 4 uS
            this->max  = (MAX_PULSE_WIDTH - max) / 4; 
            // initialize the timer if it has not already been initialized 
            if(isTimerActive(defaultTimer) == false){
                initISR(defaultTimer, defaultChannel, maxReload);   
            } 
            servos[this->servoIndex].Pin.isActiveUpdated = true;  // this must be set after the check for isTimerActive
            numActiveServos += 1;
        } 
        return this-> servoIndex;
    }
}

void Servo::detach(){
    // only does function if servo is not already detached
    if (servos[this->servoIndex].Pin.isActiveUpdated == true){
        numActiveServos -= 1;
        servos[this->servoIndex].Pin.isActiveUpdated = false; 
        if(numActiveServos == 0){
            finISR(defaultTimer, defaultChannel);
        }
    }
}

void Servo::write(int value){  
    if(value < MIN_PULSE_WIDTH){  // treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds)
        if(value < 0) value = 0;
        if(value > 180) value = 180;
        value = map(value, 0, 180, 544, 2400);      
    }
    this->writeMicroseconds(value);
}

void Servo::writeMicroseconds(int value){
    // calculate and store the values for the given channel
    byte channel = this->servoIndex;
    if(channel < MAX_SERVOS){   // ensure channel is valid  
        if(value < 544){          // ensure pulse width is valid
            value = 544;
        }
        else if(value > 2400){
            value = 2400;
        }
    
        value = value - TRIM_DURATION;
        value = usToTicks(value);  // convert to ticks after compensating for interrupt overhead - 12 Aug 2009

        noInterrupts();
        servos[channel].updatedTicks = value;
        interrupts();
    } 
}

int Servo::read(){ // return the value as degrees
    return  map(this->readMicroseconds()+1, SERVO_MIN(), SERVO_MAX(), 0, 180);     
}

int Servo::readMicroseconds(){
    unsigned int pulsewidth;
    if(this->servoIndex != INVALID_SERVO ){
        pulsewidth = ticksToUs(servos[this->servoIndex].ticks) + TRIM_DURATION;   // 12 aug 2009
    }
    else{ 
        pulsewidth  = 0;
	}
    return pulsewidth;   
}

bool Servo::attached(){
    return servos[this->servoIndex].Pin.isActive;
}