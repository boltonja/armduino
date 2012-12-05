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

#define ARDUINO_MAIN
#include "Arduino.h"

/*
 * Cortex-M3 Systick IT handler
 */
/*
extern void SysTick_Handler( void )
{
  // Increment tick count each ms
  TimeTick_Increment() ;
}
*/

void __init_hardware__(void);

/*
 * \brief Main entry point of Arduino application
 */
int main( void )
{
	init();

	delay(1);

	__init_hardware__();
#if defined(USBCON)
	//USBDevice.attach();
#endif

	setup();

	for (;;)
	{
		loop();
		//if (serialEventRun) serialEventRun();
	}

	return 0;
}

void __init_hardware__(void)
{
    HardwareTimer *timerArray[] = {&Timer1, &Timer2, &Timer3, &Timer4, &Timer5};
    // Set prescalers and overflows
    for (int i = 0; i < 5; i++) {
        timerArray[i]->pause();
        timerArray[i]->setPeriod(1000000 / PWM_FREQUENCY);
        timerArray[i]->resume();
    }

    // Set timer channels to PWM
    for (int i = 1; i <= 6; i++) timerArray[0]->setMode(i, TIMER_PWM);
    for (int i = 1; i <= 2; i++) timerArray[1]->setMode(i, TIMER_PWM);
    for (int i = 1; i <= 1; i++) timerArray[2]->setMode(i, TIMER_PWM);
    timerArray[3]->setMode(1, TIMER_PWM);
    timerArray[4]->setMode(1, TIMER_PWM);
}
