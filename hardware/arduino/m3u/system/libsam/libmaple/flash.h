/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file libmaple/include/libmaple/flash.h
 * @brief Flash support.
 */

#ifndef _LIBMAPLE_FLASH_H_
#define _LIBMAPLE_FLASH_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <libmaple/libmaple_types.h>



/* The series header must define:
 *
 * - FLASH_SAFE_WAIT_STATES, the smallest number of wait states that
 *   it is safe to use when SYSCLK is at its fastest documented rate
 *   and the MCU is powered at 3.3V (i.e. this doesn't consider
 *   overclocking or low voltage operation).
 *
 * - The following bit flags, for flash_enable_features():
 *
 *       -- FLASH_PREFETCH: prefetcher
 *       -- FLASH_ICACHE: instruction cache
 *       -- FLASH_DCACHE: data cache
 *
 *   See that function's Doxygen for more restrictions.
 */
#include <series/flash.h>

#ifdef __DOXYGEN__
/** Flash register map base pointer. */
#define FLASH_BASE
#endif

/*
 * Flash routines
 */
/**
 * @brief Enable Flash memory features
 *
 * If the target MCU doesn't provide a feature (e.g. instruction and
 * data caches on the STM32F1), the flag will be ignored. This allows
 * using these flags unconditionally, with the desired effect taking
 * place on targets that support them.
 *
 * @param feature_flags Bitwise OR of the following:
 *                      FLASH_PREFETCH (turns on prefetcher),
 *                      FLASH_ICACHE (turns on instruction cache),
 *                      FLASH_DCACHE (turns on data cache).
 */
static inline void flash_enable_features(uint32 feature_flags) {
    FLASH_BASE->CFGR |= feature_flags;
}

/**
 * @brief Set flash wait states
 *
 * Note that not all wait states are available on every MCU. See the
 * Flash programming manual for your MCU for restrictions on the
 * allowed value of wait_states for a given system clock (SYSCLK)
 * frequency.
 *
 * @param wait_states number of wait states (one of
 *                    FLASH_WAIT_STATE_0, FLASH_WAIT_STATE_1,
 *                    ..., FLASH_WAIT_STATE_7).
 */
static inline void flash_set_latency(uint32 ahb_freq) {
    uint32 spd_md = 3;
    if (ahb_freq <= 26000000) {
        spd_md = 0;
    }
    else if (ahb_freq <= 53000000) {
        spd_md = 1;
    }
    else if (ahb_freq <= 80000000) {
        spd_md = 2;
    }
    REG_SET_CLR(FLASH_BASE->CFGR, 0, FLASH_CFGR_SPMD_MASK);
    REG_SET_CLR(FLASH_BASE->CFGR, 1, spd_md << FLASH_CFGR_SPMD_BIT);
}

// Erase a page at address
void flash_erase_page(uint32 address);

// Writes 16 bits to flash
void flash_write_data(uint32 address, uint16 data[], int32 count);



/**
 * @brief Deprecated. Use flash_enable_features(FLASH_PREFETCH) instead.
 */
static inline void flash_enable_prefetch(void) {

}

#ifdef __cplusplus
}
#endif

#endif