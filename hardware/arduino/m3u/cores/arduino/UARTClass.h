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

#ifndef _UART_CLASS_
#define _UART_CLASS_

#include "HardwareSerial.h"
#include "RingBuffer.h"

// Includes Atmel CMSIS
#include <chip.h>

class UARTClass : public HardwareSerial
{
  protected:
    uint8_t* _pBuff;
    uint16_t _buffSize;

  protected:
    struct usart_dev* _dev;
    uint8_t _txPin;
    uint8_t _rxPin;

  public:
    UARTClass(struct usart_dev* dev, uint8_t* pBuff, uint16_t buffSize, uint8_t tx_pin, uint8_t rx_pin);

    void begin(const uint32_t baud) ;
    void end(void) ;
    int available(void) ;
    int peek(void) ;
    int read(void) ;
    void flush(void) ;
    size_t write(const uint8_t c) ;

    void IrqHandler(void) ;

#if defined __GNUC__ /* GCC CS3 */
    using Print::write ; // pull in write(str) and write(buf, size) from Print
#elif defined __ICCARM__ /* IAR Ewarm 5.41+ */
//    virtual void write( const char *str ) ;
//    virtual void write( const uint8_t *buffer, size_t size ) ;
#endif

    operator bool() {return true;}; // UART always active
};

#endif // _UART_CLASS_
