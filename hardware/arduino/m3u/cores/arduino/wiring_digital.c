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


void pinMode(uint32_t pin_num, uint32_t dwMode) {
    if (board_pin_invalid(pin_num)) {
        return;
    }

    WiringPinMode mode = dwMode;
    gpio_pin_mode outputMode;
    uint8_t pwm = false;
    const stm32_pin_info *gpio_pin = &PIN_MAP[pin_num];


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
    case PWM:
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
    uint32_t short_num = board_get_short_num(pin_num);
    if (short_num != pin_num) {
        if (pwm == true) {
            // High impedance main pin. Set PWM on secondary
            gpio_set_mode(gpio_pin->gpio_device, gpio_pin->gpio_bit, GPIO_DIGITAL_INPUT_PULLUP);
            gpio_pin = &PIN_MAP[short_num];
            gpio_set_mode(gpio_pin->gpio_device, gpio_pin->gpio_bit, outputMode);
        }
        else {
            // Disable PWM on secondary. Set primary pin function and return.
            const stm32_pin_info *short_pin = &PIN_MAP[short_num];
            gpio_set_af(short_pin->gpio_device, short_pin->gpio_bit, GPIOHD_FNCT_GPIO);
            timer_set_mode(short_pin->timer_device,
                    short_pin->timer_channel, TIMER_DISABLED);
            gpio_set_mode(short_pin->gpio_device, short_pin->gpio_bit, GPIO_DIGITAL_INPUT_PULLUP);
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

void digitalWrite(uint32_t pin, uint32_t val) {
    if (board_pin_invalid(pin)) {
        return;
    }
    gpio_write_bit(PIN_MAP[pin].gpio_device, PIN_MAP[pin].gpio_bit, val);
}

int digitalRead(uint32_t pin) {
    if (board_pin_invalid(pin)) {
        return;
    }

    return gpio_read_bit(PIN_MAP[pin].gpio_device, PIN_MAP[pin].gpio_bit) ?
            HIGH : LOW;
}

void togglePin(uint8 pin) {
    if (board_pin_invalid(pin)) {
        return;
    }
    gpio_toggle_bit(PIN_MAP[pin].gpio_device, PIN_MAP[pin].gpio_bit);
}


#ifdef __cplusplus
}
#endif

