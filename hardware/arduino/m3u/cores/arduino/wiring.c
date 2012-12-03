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

#include "Arduino.h"
#include "Reset.h"
#include "delay.h"

#ifdef __cplusplus
extern "C" {
#endif

// FIXME [silabs]: stubbed file
uint32_t millis( void )
{
    return 0;
}

uint32_t micros( void )
{
    return 0;
}

void delay(uint32_t ms) {
    uint32 i;
    for (i = 0; i < ms; i++) {
        delayMicroseconds(1000);
    }
}

void delayMicroseconds(uint32_t us) {
    delay_us(us);
}

/*
 * Cortex-M3 Systick IT handler: MOVED TO MAIN DUE TO WEAK SYMBOL ISSUE NOT RESOLVED
 */
void SysTick_Handler( void )
{

}


#ifdef __cplusplus
}
#endif
