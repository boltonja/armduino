/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following condition is met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

#ifndef _SAM_INCLUDED_
#define _SAM_INCLUDED_

#define part_is_defined(part) (defined(__ ## part ## __))

/* 
 * ----------------------------------------------------------------------------
 * SAM3 family 
 * ----------------------------------------------------------------------------
 */
// FIXME [silabs]:
#define SAM3U1C
/* SAM3U series */
#define SAM3U1 ( \
    part_is_defined( SAM3U1C ) || \
    part_is_defined( SAM3U1E ) )

/* Entire SAM3U series */
#define SAM3U_SERIES (SAM3U1 || SAM3U2 || SAM3U4)


/* 
 * ----------------------------------------------------------------------------
 * SAM4 family 
 * ----------------------------------------------------------------------------
 */


/* Entire SAM3 Family */
#define SAM3_SERIES ( SAM3N_SERIES || SAM3S_SERIES || SAM3SD8_SERIES || SAM3U_SERIES || SAM3XA_SERIES )

#define SAM ( SAM3_SERIES || SAM4_SERIES )

/* 
 * ----------------------------------------------------------------------------
 * Header inclusion 
 * ----------------------------------------------------------------------------
 */

#if SAM3_SERIES
#include "sam3.h"
#endif /* SAM3 */

#if SAM4_SERIES
#include "sam4.h"
#endif /* SAM4 */

#endif /* _SAM_INCLUDED_ */

