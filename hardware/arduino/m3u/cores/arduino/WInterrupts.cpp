/*
  Copyright (c) 2011-2012 Arduino.  All right reserved.

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

#include "WInterrupts.h"

static inline exti_trigger_mode exti_out_mode(ExtIntTriggerMode mode);

void attachInterrupt(uint8 pin, voidFuncPtr handler, ExtIntTriggerMode mode) {
    if (pin >= BOARD_NR_GPIO_PINS || !handler) {
        return;
    }

    exti_trigger_mode outMode = exti_out_mode(mode);

    exti_attach_interrupt((exti_num)(PIN_MAP[pin].gpio_bit),
                          (exti_cfg)PIN_MAP[pin].exti_triger,
                          handler,
                          outMode);
}

void attachInterrupt(uint8 pin, voidArgumentFuncPtr handler, void *arg,
                     ExtIntTriggerMode mode) {
    if (pin >= BOARD_NR_GPIO_PINS || !handler) {
        return;
    }

    exti_trigger_mode outMode = exti_out_mode(mode);

    exti_attach_callback((exti_num)(PIN_MAP[pin].gpio_bit),
                         (exti_cfg)PIN_MAP[pin].exti_triger,
                         handler,
                         arg,
                         outMode);
}

void detachInterrupt(uint8 pin) {
    if (pin >= BOARD_NR_GPIO_PINS) {
        return;
    }

    exti_detach_interrupt((exti_num)(PIN_MAP[pin].exti_triger));
}

static inline exti_trigger_mode exti_out_mode(ExtIntTriggerMode mode) {
    switch (mode) {
    case RISING:
        return EXTI_RISING;
    case FALLING:
        return EXTI_FALLING;
    case CHANGE:
        return EXTI_RISING_FALLING;
    }
    // Can't happen
    ASSERT(0);
    return (exti_trigger_mode)0;
}
