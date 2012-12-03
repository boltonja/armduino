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
#include "USARTClass.h"

// Constructors ////////////////////////////////////////////////////////////////
#if 0
USARTClass::USARTClass( Usart* pUsart, IRQn_Type dwIrq, uint32_t dwId, RingBuffer* pRx_buffer )
{

}

// Public Methods //////////////////////////////////////////////////////////////

void USARTClass::begin( const uint32_t dwBaudRate )
{


}

void USARTClass::end( void )
{

}

int USARTClass::available( void )
{
  return (uint32_t)0;
}

int USARTClass::peek( void )
{
    return -1 ;
}

int USARTClass::read( void )
{

  return 0 ;
}

void USARTClass::flush( void )
{

}

size_t USARTClass::write( const uint8_t uc_data )
{

  return 1;
}

void USARTClass::IrqHandler( void )
{

}
#endif

