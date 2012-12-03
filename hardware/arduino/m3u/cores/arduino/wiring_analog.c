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

static int _readResolution = 12;
static int _writeResolution = 8;

void analogReadResolution(int res) {
    _readResolution = res;
}

void analogWriteResolution(int res) {
    // Limit to 16 bits otherwise conversion problems (see pwm res map below).
    if (res > 16) {
        res = 16;
    }
    _writeResolution = res;
}

static inline uint32_t mapResolution(uint32_t value, uint32_t from, uint32_t to) {
    if (from == to)
        return value;
    if (from > to)
        return value >> (from-to);
    else
        return value << (to-from);
}

eAnalogReference analog_reference = AR_DEFAULT;

void analogReference(eAnalogReference ulMode)
{
    //analog_reference = ulMode;
}

/* Unlike Wiring and Arduino, this assumes that the pin's mode is set
 * to INPUT_ANALOG. That's faster, but it does require some extra work
 * on the user's part. Not too much, we think ;). */
uint32_t analogRead(uint32_t pin)
{
    const adc_dev *dev = PIN_MAP[pin].adc_device;
    if (dev == NULL) {
        return 0;
    }
    uint32_t value = adc_read(dev, PIN_MAP[pin].adc_channel);

    // TODO [silabs]: find way to determine adc resolution. Make an analog class?
    return mapResolution(value, 12, _readResolution);
}


// Right now, PWM output only works on the pins with
// hardware support.  These are defined in the appropriate
// pins_*.c file.  For the rest of the pins, we default
// to digital output.
void analogWrite(uint32_t pin, uint32_t value) {

    const stm32_pin_info *gpio_pin = &PIN_MAP[pin];
    if (pin >= BOARD_NR_GPIO_PINS) {
        return;
    }

    // TODO [silabs]: add DAC here
    if (0) {
        return;
    }

    // PWM
    // Use shorted pins if possible. They have the EPCA module for the silabs board.
    uint32_t short_num = board_get_short_num(gpio_pin->gpio_device, gpio_pin->gpio_bit);
    gpio_pin = short_num ? &PIN_MAP_SHORTS[short_num - 1] : gpio_pin;
    if (gpio_pin->timer_device != NULL) {
        timer_dev *dev = gpio_pin->timer_device;
        uint8_t cc_channel = gpio_pin->timer_channel;
        timer_set_compare(dev, cc_channel, ((uint32_t)value * (uint32_t)timer_get_reload(dev)) / ((1 << _writeResolution) - 1));
        return;
    }

    // Digital Write
    pinMode(pin, OUTPUT);
    if (value < (_writeResolution / 2))
        digitalWrite(pin, LOW);
    else
        digitalWrite(pin, HIGH);
}

#ifdef __cplusplus
}
#endif
