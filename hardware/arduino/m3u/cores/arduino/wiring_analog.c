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

#ifdef __cplusplus
extern "C" {
#endif
// fixme [silabs]: tc type
typedef int Tc;
static int _readResolution = 10;
static int _writeResolution = 8;

void analogReadResolution(int res) {
    // FIXME [silabs]: stub function
}

void analogWriteResolution(int res) {
    // FIXME [silabs]: stub function
}

static inline uint32_t mapResolution(uint32_t value, uint32_t from, uint32_t to) {
    // FIXME [silabs]: stub function
}

eAnalogReference analog_reference = AR_DEFAULT;

void analogReference(eAnalogReference ulMode)
{
    // FIXME [silabs]: stub function
}

uint32_t analogRead(uint32_t ulPin)
{
    // FIXME [silabs]: stub function
	return 0;
}

static void TC_SetCMR_ChannelA(Tc *tc, uint32_t chan, uint32_t v)
{
    // FIXME [silabs]: stub function
}

static void TC_SetCMR_ChannelB(Tc *tc, uint32_t chan, uint32_t v)
{
    // FIXME [silabs]: stub function
}

static uint8_t PWMEnabled = 0;
static uint8_t pinEnabled[PINS_COUNT];
static uint8_t TCChanEnabled[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

void analogOutputInit(void) {
    // FIXME [silabs]: stub function
}

// Right now, PWM output only works on the pins with
// hardware support.  These are defined in the appropriate
// pins_*.c file.  For the rest of the pins, we default
// to digital output.
void analogWrite(uint32_t ulPin, uint32_t ulValue) {
    // FIXME [silabs]: stub function
}

#ifdef __cplusplus
}
#endif
