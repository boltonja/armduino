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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "UARTClass.h"
#include <variant.h>
// Constructors ////////////////////////////////////////////////////////////////

UARTClass::UARTClass(struct usart_dev* dev, uint8_t* pBuff, uint16_t buffSize, uint8_t txPin, uint8_t rxPin)
{
    _dev = dev;
    _pBuff = pBuff;
    _buffSize = buffSize;
    _txPin = txPin;
    _rxPin = rxPin;
}

// Public Methods //////////////////////////////////////////////////////////////

void UARTClass::begin(const uint32_t baud)
{
    const stm32_pin_info *txi = &PIN_MAP[this->_txPin];
    const stm32_pin_info *rxi = &PIN_MAP[this->_rxPin];

    usart_config_gpios_async(this->_dev,
                             rxi->gpio_device, rxi->gpio_bit,
                             txi->gpio_device, txi->gpio_bit,
                             0);
    usart_init(this->_dev, _pBuff, _buffSize);
    usart_set_baud_rate(this->_dev, 0, baud);
    usart_enable(this->_dev);
}

void UARTClass::end( void )
{
    usart_disable(this->_dev);
}

int UARTClass::available( void )
{
    return usart_data_available(this->_dev);
}

int UARTClass::peek( void )
{
    return rb_peek(_dev->rb);

}

int UARTClass::read( void )
{
    // Block until a byte becomes available, to save user confusion.
    while (!this->available())
        ;
    return usart_getc(this->_dev);
}

void UARTClass::flush( void )
{
    usart_reset_rx(this->_dev);
}

size_t UARTClass::write( const uint8_t uc_data )
{
    usart_putc(this->_dev, uc_data);
}
