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

#ifndef _WIRING_INTERRUPTS_
#define _WIRING_INTERRUPTS_

#include "Arduino.h"


/**
 * The kind of transition on an external pin which should trigger an
 * interrupt.
 */
typedef enum ExtIntTriggerMode {
    RISING, /**< To trigger an interrupt when the pin transitions LOW
                 to HIGH */
    FALLING, /**< To trigger an interrupt when the pin transitions
                  HIGH to LOW */
    CHANGE /**< To trigger an interrupt when the pin transitions from
                LOW to HIGH or HIGH to LOW (i.e., when the pin
                changes). */
} ExtIntTriggerMode;

/**
 *  @brief Registers an interrupt handler on a pin.
 *
 *  The interrupt will be triggered on a given transition on the pin,
 *  as specified by the mode parameter.  The handler runs in interrupt
 *  context.  The new handler will replace whatever handler is
 *  currently registered for the pin, if any.
 *
 *  @param pin Pin number
 *  @param handler Function to run upon external interrupt trigger.
 *                 The handler should take no arguments, and have void
 *                 return type.
 *  @param mode Type of transition to trigger on, e.g. falling, rising, etc.
 *
 *  @sideeffect Registers a handler
 *  @see detachInterrupt()
 */
void attachInterrupt(uint8 pin, voidFuncPtr handler, ExtIntTriggerMode mode);

/**
 *  @brief Registers an interrupt handler on a pin.
 *
 *  The interrupt will be triggered on a given transition on the pin,
 *  as specified by the mode parameter.  The handler runs in interrupt
 *  context.  The new handler will replace whatever handler is
 *  currently registered for the pin, if any.
 *
 *  @param pin Pin number
 *  @param handler Static class member function to run upon external interrupt
 *                 trigger. The handler should take 1 argument and return void
 *  @param arg Argument that the handler will be passed when it's called. One
 *             use of this is to pass the specific instance of the class that
 *             will handle the interrupt.
 *  @param mode Type of transition to trigger on, e.g. falling, rising, etc.
 *
 *  @sideeffect Registers a handler
 *  @see detachInterrupt()
 */
void attachInterrupt(uint8 pin, voidArgumentFuncPtr handler, void *arg,
                     ExtIntTriggerMode mode);

/**
 * @brief Disable any registered external interrupt.
 * @param pin Maple pin number
 * @sideeffect unregisters external interrupt handler
 * @see attachInterrupt()
 */
void detachInterrupt(uint8 pin);


#endif /* _WIRING_INTERRUPTS_ */
