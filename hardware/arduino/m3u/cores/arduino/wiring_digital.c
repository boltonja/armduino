/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

//fixme: silabs import timer_set_mode from other project
#define timer_set_mode(a,b,c) while (0) {}

#include "Arduino.h"
#include "gpio.h"
#ifdef __cplusplus
 extern "C" {
#endif
// FIXME [silabs]: timer_mode should be typedef'd in timer.h
 typedef enum timer_mode {
     /**
      * The timer stops counting, channel interrupts are detached, and
      * no state changes are output. */
     TIMER_DISABLED,

     /** PWM output. */
     TIMER_PWM,

     /* TIMER_PWM_CENTER_ALIGNED, TODO: Center-aligned PWM output mode. */

     /**
      * The timer counts from 0 to its reload value repeatedly; every
      * time the counter value reaches one of the channel compare
      * values, the corresponding interrupt is fired. */
     TIMER_OUTPUT_COMPARE,

     /* TIMER_INPUT_CAPTURE, TODO: In this mode, the timer can measure the
      *                            pulse lengths of input signals */
     /* TIMER_ONE_PULSE, TODO: In this mode, the timer can generate a single
      *                        pulse on a GPIO pin for a specified amount of
      *                        time. */
 } timer_mode;
 void pinMode( uint32_t pin_num, uint32_t dwMode ) {
     WiringPinMode mode = dwMode;
     gpio_pin_mode outputMode;
     uint8_t pwm = false;
     const stm32_pin_info *gpio_pin = &PIN_MAP[pin_num];


     if (pin_num >= BOARD_NR_GPIO_PINS) {
         return;
     }

     switch(mode) {
         case OUTPUT:
             outputMode = GPIO_DIGITAL_PP;
             break;
         case OUTPUT_OPEN_DRAIN:
             outputMode = GPIO_DIGITAL_OD;
             break;
         case INPUT:
         case INPUT_FLOATING:
         case INPUT_PULLDOWN:
         case INPUT_PULLUP:
             outputMode = GPIO_DIGITAL_INPUT_PULLUP;
             break;
         case INPUT_ANALOG:
             outputMode = GPIO_ANALOG;
             break;
         case PWM111:
             outputMode = GPIO_DIGITAL_PP;
             pwm = true;
             break;
         case PWM_OPEN_DRAIN:
             outputMode = GPIO_DIGITAL_OD;
             pwm = true;
             break;
         default:
             ASSERT(0);
             return;
     }

     // Shorted pin?
     uint32_t short_num = board_get_short_num(gpio_pin->gpio_device, gpio_pin->gpio_bit);
     if (short_num) {
         short_num -= 1;
         if (pwm == true) {
             // High impedance main pin. Set PWM on secondary
             gpio_set_mode(gpio_pin->gpio_device, gpio_pin->gpio_bit, GPIO_DIGITAL_INPUT_PULLUP);
             gpio_pin = &PIN_MAP_SHORTS[short_num];
             gpio_set_mode(gpio_pin->gpio_device, gpio_pin->gpio_bit, outputMode);
         }
         else {
             // Disable PWM on secondary. Set primary pin function and return.
             gpio_set_af(PIN_MAP_SHORTS[short_num].gpio_device, PIN_MAP_SHORTS[short_num].gpio_bit, GPIOHD_FNCT_GPIO);
             timer_set_mode(PIN_MAP_SHORTS[short_num].timer_device,
                     PIN_MAP_SHORTS[short_num].timer_channel, TIMER_DISABLED);
             gpio_set_mode(gpio_pin->gpio_device, gpio_pin->gpio_bit, outputMode);
             return;
         }
     }
     else {
         gpio_set_mode(gpio_pin->gpio_device, gpio_pin->gpio_bit, outputMode);
     }


     if (gpio_pin->timer_device != NULL) {
         /* Enable/disable timer channels if we're switching into or
          * out of PWM. */
         timer_set_mode(gpio_pin->timer_device,
                        gpio_pin->timer_channel,
                        pwm ? TIMER_PWM : TIMER_DISABLED);
     }

     // This only applies to PB4 pins
     if (gpio_get_type(gpio_pin->gpio_device) == GPIO_HIGHDRIVE) {
         gpio_set_af(gpio_pin->gpio_device, gpio_pin->gpio_bit, pwm ? GPIOHD_FNCT_EPCA0 : GPIOHD_FNCT_GPIO);
     }
 }

 void digitalWrite( uint32_t pin, uint32_t val ) {
     if (pin >= BOARD_NR_GPIO_PINS) {
         return;
     }

     gpio_write_bit(PIN_MAP[pin].gpio_device, PIN_MAP[pin].gpio_bit, val);
 }

int digitalRead(uint32_t pin) {
     if (pin >= BOARD_NR_GPIO_PINS) {
         return 0;
     }

     return gpio_read_bit(PIN_MAP[pin].gpio_device, PIN_MAP[pin].gpio_bit) ?
         HIGH : LOW;
 }

#ifdef __cplusplus
}
#endif

