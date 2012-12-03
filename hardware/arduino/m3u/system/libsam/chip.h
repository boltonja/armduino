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

#ifndef _LIB_SAM_
#define _LIB_SAM_

/*
 * Core and peripherals registers definitions
 */
#include "sam.h"

/* Define attribute */
#if defined (  __GNUC__  ) /* GCC CS3 */
    #define WEAK __attribute__ ((weak))
#elif defined ( __ICCARM__ ) /* IAR Ewarm 5.41+ */
    #define WEAK __weak
#endif

/* Define NO_INIT attribute */
#if defined (  __GNUC__  )
    #define NO_INIT
#elif defined ( __ICCARM__ )
    #define NO_INIT __no_init
#endif

/*
 * Peripherals
 */
#include <libmaple/adc.h>
#include <libmaple/dac.h>
#include <libmaple/dma.h>
#include <libmaple/exti.h>
#include <libmaple/flash.h>
#include <libmaple/fsmc.h>
#include <libmaple/gpio.h>
#include <libmaple/i2c.h>
#include <libmaple/iwdg.h>
#include <libmaple/libmaple_types.h>
#include <libmaple/libmaple.h>
#include <libmaple/nvic.h>
#include <libmaple/pwr.h>
#include <libmaple/rcc.h>
#include <libmaple/ring_buffer.h>
#include <libmaple/scb.h>
#include <libmaple/spi.h>
#include <libmaple/stm32.h>
#include <libmaple/syscfg.h>
#include <libmaple/systick.h>
#include <libmaple/timer.h>
#include <libmaple/usart.h>
#include <libmaple/usb_cdcacm.h>
#include <libmaple/usb.h>
#include <libmaple/util.h>
#include <libmaple/xbar.h>


#endif /* _LIB_SAM_ */
