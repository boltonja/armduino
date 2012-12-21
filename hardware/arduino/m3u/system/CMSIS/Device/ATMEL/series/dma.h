/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2012 LeafLabs, LLC
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
 * @file libmaple/stm32f2/include/series/dma.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief STM32F2 DMA series header
 */

#ifndef _LIBMAPLE_SIM3U1_DMA_H_
#define _LIBMAPLE_SIM3U1_DMA_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dma_reg_map
{
   volatile uint32_t STATUS;    // Base Address + 0x0
   volatile uint32_t CONFIG;    // Base Address + 0x4
   volatile uint32_t BASEPTR;   // Base Address + 0x8
   volatile uint32_t ABASEPTR;  // Base Address + 0xC
   volatile uint32_t CHSTATUS;  // Base Address + 0x10
   volatile uint32_t CHSWRCN;   // Base Address + 0x14
   volatile uint32_t CHREQMSET; // Base Address + 0x20
   volatile uint32_t CHREQMCLR; // Base Address + 0x24
   volatile uint32_t CHENSET;   // Base Address + 0x28
   volatile uint32_t CHENCLR;   // Base Address + 0x2C
   volatile uint32_t CHALTSET;  // Base Address + 0x30
   volatile uint32_t CHALTCLR;  // Base Address + 0x34
   volatile uint32_t CHHPSET;   // Base Address + 0x38
   volatile uint32_t CHHPCLR;   // Base Address + 0x3C
   uint32_t          reserved0; // Base Address + 0x40
   uint32_t          reserved1; // Base Address + 0x44
   uint32_t          reserved2; // Base Address + 0x48
   volatile uint32_t BERRCLR;   // Base Address + 0x4C
} dma_reg_map;

#define DMA1_BASE (dma_reg_map*)0x40036000);

// Status
#define DMACTRL_STATUS_DMAENSTS_MASK                   0x00000001
#define DMACTRL_STATUS_STATE_MASK                      0x000000F0
#define DMACTRL_STATUS_NUMCHAN_MASK                    0x001F0000
#define DMACTRL_STATUS_DMAENSTS_BIT                    0  /* DMAENSTS<0>: DMA Enable Status.                */
#define DMACTRL_STATUS_STATE_BIT                       4  /* STATE<7:4>: State Machine State.               */
#define DMACTRL_STATUS_NUMCHAN_BIT                     16 /* NUMCHAN<20:16>: Number of Supported DMA Channels. */
#define DMACTRL_STATUS_DMAENSTS_NOT_SET                (0 << DMACTRL_STATUS_DMAENSTS_BIT)
#define DMACTRL_STATUS_DMAENSTS_SET                    (1 << DMACTRL_STATUS_DMAENSTS_BIT)
#define DMACTRL_STATUS_STATE_IDLE                      (0 << DMACTRL_STATUS_STATE_BIT)
#define DMACTRL_STATUS_STATE_READING_CHANNEL_CONFIG    (1 << DMACTRL_STATUS_STATE_BIT)
#define DMACTRL_STATUS_STATE_READING_SOURCE_POINTER    (2 << DMACTRL_STATUS_STATE_BIT)
#define DMACTRL_STATUS_STATE_READING_DEST_POINTER      (3 << DMACTRL_STATUS_STATE_BIT)
#define DMACTRL_STATUS_STATE_READING_SOURCE_DATA       (4 << DMACTRL_STATUS_STATE_BIT)
#define DMACTRL_STATUS_STATE_WRITING_DEST_DATA         (5 << DMACTRL_STATUS_STATE_BIT)
#define DMACTRL_STATUS_STATE_WAITING_DMA_REQ_CLEAR     (6 << DMACTRL_STATUS_STATE_BIT)
#define DMACTRL_STATUS_STATE_WRITING_CHANNEL_CONFIG    (7 << DMACTRL_STATUS_STATE_BIT)
#define DMACTRL_STATUS_STATE_STALLED                   (8 << DMACTRL_STATUS_STATE_BIT)
#define DMACTRL_STATUS_STATE_DONE                      (9 << DMACTRL_STATUS_STATE_BIT)
#define DMACTRL_STATUS_STATE_SCATTER_GATHER_TRANSITION (10 << DMACTRL_STATUS_STATE_BIT)

// Configure
#define DMACTRL_CFGR_DMAEN_MASK                        0x00000001
#define DMACTRL_CFGR_DMAEN_BIT                         0  /* DMAEN<0>: DMA Enable.                          */

// Base Pointer
#define DMACTRL_BASEPTR_MASK                           0xFFFFFFE0
#define DMACTRL_BASEPTR_BIT                            5  /* BASEPTR<31:5>: Control Base Pointer.           */


#define DMACTRL_ABASEPTR_MASK                          0xFFFFFFFF
#define DMACTRL_ABASEPTR_BIT                           0  /* ABASEPTR<31:0>: Alternate Control Base Pointer. */




// Channel Status
#define DMACTRL_CHSTATUS_CH0_MASK                      0x00000001
#define DMACTRL_CHSTATUS_CH1_MASK                      0x00000002
#define DMACTRL_CHSTATUS_CH2_MASK                      0x00000004
#define DMACTRL_CHSTATUS_CH3_MASK                      0x00000008
#define DMACTRL_CHSTATUS_CH4_MASK                      0x00000010
#define DMACTRL_CHSTATUS_CH5_MASK                      0x00000020
#define DMACTRL_CHSTATUS_CH6_MASK                      0x00000040
#define DMACTRL_CHSTATUS_CH7_MASK                      0x00000080
#define DMACTRL_CHSTATUS_CH8_MASK                      0x00000100
#define DMACTRL_CHSTATUS_CH9_MASK                      0x00000200
#define DMACTRL_CHSTATUS_CH10_MASK                     0x00000400
#define DMACTRL_CHSTATUS_CH11_MASK                     0x00000800
#define DMACTRL_CHSTATUS_CH12_MASK                     0x00001000
#define DMACTRL_CHSTATUS_CH13_MASK                     0x00002000
#define DMACTRL_CHSTATUS_CH14_MASK                     0x00004000
#define DMACTRL_CHSTATUS_CH15_MASK                     0x00008000
#define DMACTRL_CHSTATUS_CH16_MASK                     0x00010000
#define DMACTRL_CHSTATUS_CH17_MASK                     0x00020000
#define DMACTRL_CHSTATUS_CH18_MASK                     0x00040000
#define DMACTRL_CHSTATUS_CH19_MASK                     0x00080000
#define DMACTRL_CHSTATUS_CH20_MASK                     0x00100000
#define DMACTRL_CHSTATUS_CH21_MASK                     0x00200000
#define DMACTRL_CHSTATUS_CH22_MASK                     0x00400000
#define DMACTRL_CHSTATUS_CH23_MASK                     0x00800000
#define DMACTRL_CHSTATUS_CH24_MASK                     0x01000000
#define DMACTRL_CHSTATUS_CH25_MASK                     0x02000000
#define DMACTRL_CHSTATUS_CH26_MASK                     0x04000000
#define DMACTRL_CHSTATUS_CH27_MASK                     0x08000000
#define DMACTRL_CHSTATUS_CH28_MASK                     0x10000000
#define DMACTRL_CHSTATUS_CH29_MASK                     0x20000000
#define DMACTRL_CHSTATUS_CH30_MASK                     0x40000000
#define DMACTRL_CHSTATUS_CH31_MASK                     0x80000000
#define DMACTRL_CHSTATUS_CH0_BIT                       0  /* CH0<0>: Channel 0 Status.                      */
#define DMACTRL_CHSTATUS_CH1_BIT                       1  /* CH1<1>: Channel 1 Status.                      */
#define DMACTRL_CHSTATUS_CH2_BIT                       2  /* CH2<2>: Channel 2 Status.                      */
#define DMACTRL_CHSTATUS_CH3_BIT                       3  /* CH3<3>: Channel 3 Status.                      */
#define DMACTRL_CHSTATUS_CH4_BIT                       4  /* CH4<4>: Channel 4 Status.                      */
#define DMACTRL_CHSTATUS_CH5_BIT                       5  /* CH5<5>: Channel 5 Status.                      */
#define DMACTRL_CHSTATUS_CH6_BIT                       6  /* CH6<6>: Channel 6 Status.                      */
#define DMACTRL_CHSTATUS_CH7_BIT                       7  /* CH7<7>: Channel 7 Status.                      */
#define DMACTRL_CHSTATUS_CH8_BIT                       8  /* CH8<8>: Channel 8 Status.                      */
#define DMACTRL_CHSTATUS_CH9_BIT                       9  /* CH9<9>: Channel 9 Status.                      */
#define DMACTRL_CHSTATUS_CH10_BIT                      10 /* CH10<10>: Channel 10 Status.                   */
#define DMACTRL_CHSTATUS_CH11_BIT                      11 /* CH11<11>: Channel 11 Status.                   */
#define DMACTRL_CHSTATUS_CH12_BIT                      12 /* CH12<12>: Channel 12 Status.                   */
#define DMACTRL_CHSTATUS_CH13_BIT                      13 /* CH13<13>: Channel 13 Status.                   */
#define DMACTRL_CHSTATUS_CH14_BIT                      14 /* CH14<14>: Channel 14 Status.                   */
#define DMACTRL_CHSTATUS_CH15_BIT                      15 /* CH15<15>: Channel 15 Status.                   */
#define DMACTRL_CHSTATUS_CH16_BIT                      16
#define DMACTRL_CHSTATUS_CH17_BIT                      17
#define DMACTRL_CHSTATUS_CH18_BIT                      18
#define DMACTRL_CHSTATUS_CH19_BIT                      19
#define DMACTRL_CHSTATUS_CH20_BIT                      20
#define DMACTRL_CHSTATUS_CH21_BIT                      21
#define DMACTRL_CHSTATUS_CH22_BIT                      22
#define DMACTRL_CHSTATUS_CH23_BIT                      23
#define DMACTRL_CHSTATUS_CH24_BIT                      24
#define DMACTRL_CHSTATUS_CH25_BIT                      25
#define DMACTRL_CHSTATUS_CH26_BIT                      26
#define DMACTRL_CHSTATUS_CH27_BIT                      27
#define DMACTRL_CHSTATUS_CH28_BIT                      28
#define DMACTRL_CHSTATUS_CH29_BIT                      29
#define DMACTRL_CHSTATUS_CH30_BIT                      30
#define DMACTRL_CHSTATUS_CH31_BIT                      31
#define DMACTRL_CHSTATUS_CH0_NOT_WAITING               (0 << DMACTRL_CHSTATUS_CH0_BIT)
#define DMACTRL_CHSTATUS_CH0_WAITING                   (1 << DMACTRL_CHSTATUS_CH0_BIT)
#define DMACTRL_CHSTATUS_CH1_NOT_WAITING               (0 << DMACTRL_CHSTATUS_CH1_BIT)
#define DMACTRL_CHSTATUS_CH1_WAITING                   (1 << DMACTRL_CHSTATUS_CH1_BIT)
#define DMACTRL_CHSTATUS_CH2_NOT_WAITING               (0 << DMACTRL_CHSTATUS_CH2_BIT)
#define DMACTRL_CHSTATUS_CH2_WAITING                   (1 << DMACTRL_CHSTATUS_CH2_BIT)
#define DMACTRL_CHSTATUS_CH3_NOT_WAITING               (0 << DMACTRL_CHSTATUS_CH3_BIT)
#define DMACTRL_CHSTATUS_CH3_WAITING                   (1 << DMACTRL_CHSTATUS_CH3_BIT)
#define DMACTRL_CHSTATUS_CH4_NOT_WAITING               (0 << DMACTRL_CHSTATUS_CH4_BIT)
#define DMACTRL_CHSTATUS_CH4_WAITING                   (1 << DMACTRL_CHSTATUS_CH4_BIT)
#define DMACTRL_CHSTATUS_CH5_NOT_WAITING               (0 << DMACTRL_CHSTATUS_CH5_BIT)
#define DMACTRL_CHSTATUS_CH5_WAITING                   (1 << DMACTRL_CHSTATUS_CH5_BIT)
#define DMACTRL_CHSTATUS_CH6_NOT_WAITING               (0 << DMACTRL_CHSTATUS_CH6_BIT)
#define DMACTRL_CHSTATUS_CH6_WAITING                   (1 << DMACTRL_CHSTATUS_CH6_BIT)
#define DMACTRL_CHSTATUS_CH7_NOT_WAITING               (0 << DMACTRL_CHSTATUS_CH7_BIT)
#define DMACTRL_CHSTATUS_CH7_WAITING                   (1 << DMACTRL_CHSTATUS_CH7_BIT)
#define DMACTRL_CHSTATUS_CH8_NOT_WAITING               (0 << DMACTRL_CHSTATUS_CH8_BIT)
#define DMACTRL_CHSTATUS_CH8_WAITING                   (1 << DMACTRL_CHSTATUS_CH8_BIT)
#define DMACTRL_CHSTATUS_CH9_NOT_WAITING               (0 << DMACTRL_CHSTATUS_CH9_BIT)
#define DMACTRL_CHSTATUS_CH9_WAITING                   (1 << DMACTRL_CHSTATUS_CH9_BIT)
#define DMACTRL_CHSTATUS_CH10_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH10_BIT)
#define DMACTRL_CHSTATUS_CH10_WAITING                  (1 << DMACTRL_CHSTATUS_CH10_BIT)
#define DMACTRL_CHSTATUS_CH11_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH11_BIT)
#define DMACTRL_CHSTATUS_CH11_WAITING                  (1 << DMACTRL_CHSTATUS_CH11_BIT)
#define DMACTRL_CHSTATUS_CH12_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH12_BIT)
#define DMACTRL_CHSTATUS_CH12_WAITING                  (1 << DMACTRL_CHSTATUS_CH12_BIT)
#define DMACTRL_CHSTATUS_CH13_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH13_BIT)
#define DMACTRL_CHSTATUS_CH13_WAITING                  (1 << DMACTRL_CHSTATUS_CH13_BIT)
#define DMACTRL_CHSTATUS_CH14_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH14_BIT)
#define DMACTRL_CHSTATUS_CH14_WAITING                  (1 << DMACTRL_CHSTATUS_CH14_BIT)
#define DMACTRL_CHSTATUS_CH15_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH15_BIT)
#define DMACTRL_CHSTATUS_CH15_WAITING                  (1 << DMACTRL_CHSTATUS_CH15_BIT)
#define DMACTRL_CHSTATUS_CH16_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH16_BIT)
#define DMACTRL_CHSTATUS_CH16_WAITING                  (1 << DMACTRL_CHSTATUS_CH16_BIT)
#define DMACTRL_CHSTATUS_CH17_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH17_BIT)
#define DMACTRL_CHSTATUS_CH17_WAITING                  (1 << DMACTRL_CHSTATUS_CH17_BIT)
#define DMACTRL_CHSTATUS_CH18_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH18_BIT)
#define DMACTRL_CHSTATUS_CH18_WAITING                  (1 << DMACTRL_CHSTATUS_CH18_BIT)
#define DMACTRL_CHSTATUS_CH19_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH19_BIT)
#define DMACTRL_CHSTATUS_CH19_WAITING                  (1 << DMACTRL_CHSTATUS_CH19_BIT)
#define DMACTRL_CHSTATUS_CH20_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH20_BIT)
#define DMACTRL_CHSTATUS_CH20_WAITING                  (1 << DMACTRL_CHSTATUS_CH20_BIT)
#define DMACTRL_CHSTATUS_CH21_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH21_BIT)
#define DMACTRL_CHSTATUS_CH21_WAITING                  (1 << DMACTRL_CHSTATUS_CH21_BIT)
#define DMACTRL_CHSTATUS_CH22_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH22_BIT)
#define DMACTRL_CHSTATUS_CH22_WAITING                  (1 << DMACTRL_CHSTATUS_CH22_BIT)
#define DMACTRL_CHSTATUS_CH23_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH23_BIT)
#define DMACTRL_CHSTATUS_CH23_WAITING                  (1 << DMACTRL_CHSTATUS_CH23_BIT)
#define DMACTRL_CHSTATUS_CH24_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH24_BIT)
#define DMACTRL_CHSTATUS_CH24_WAITING                  (1 << DMACTRL_CHSTATUS_CH24_BIT)
#define DMACTRL_CHSTATUS_CH25_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH25_BIT)
#define DMACTRL_CHSTATUS_CH25_WAITING                  (1 << DMACTRL_CHSTATUS_CH25_BIT)
#define DMACTRL_CHSTATUS_CH26_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH26_BIT)
#define DMACTRL_CHSTATUS_CH26_WAITING                  (1 << DMACTRL_CHSTATUS_CH26_BIT)
#define DMACTRL_CHSTATUS_CH27_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH27_BIT)
#define DMACTRL_CHSTATUS_CH27_WAITING                  (1 << DMACTRL_CHSTATUS_CH27_BIT)
#define DMACTRL_CHSTATUS_CH28_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH28_BIT)
#define DMACTRL_CHSTATUS_CH28_WAITING                  (1 << DMACTRL_CHSTATUS_CH28_BIT)
#define DMACTRL_CHSTATUS_CH29_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH29_BIT)
#define DMACTRL_CHSTATUS_CH29_WAITING                  (1 << DMACTRL_CHSTATUS_CH29_BIT)
#define DMACTRL_CHSTATUS_CH30_NOT_WAITING              (0 << DMACTRL_CHSTATUS_CH30_BIT)
#define DMACTRL_CHSTATUS_CH30_WAITING                  (1 << DMACTRL_CHSTATUS_CH30_BIT)
#define DMACTRL_CHSTATUS_CH31_NOT_WAITING              (0U << DMACTRL_CHSTATUS_CH31_BIT)
#define DMACTRL_CHSTATUS_CH31_WAITING                  (1U << DMACTRL_CHSTATUS_CH31_BIT)



#define DMACTRL_CHSWRCN_CH0_MASK                       0x00000001
#define DMACTRL_CHSWRCN_CH1_MASK                       0x00000002
#define DMACTRL_CHSWRCN_CH2_MASK                       0x00000004
#define DMACTRL_CHSWRCN_CH3_MASK                       0x00000008
#define DMACTRL_CHSWRCN_CH4_MASK                       0x00000010
#define DMACTRL_CHSWRCN_CH5_MASK                       0x00000020
#define DMACTRL_CHSWRCN_CH6_MASK                       0x00000040
#define DMACTRL_CHSWRCN_CH7_MASK                       0x00000080
#define DMACTRL_CHSWRCN_CH8_MASK                       0x00000100
#define DMACTRL_CHSWRCN_CH9_MASK                       0x00000200
#define DMACTRL_CHSWRCN_CH10_MASK                      0x00000400
#define DMACTRL_CHSWRCN_CH11_MASK                      0x00000800
#define DMACTRL_CHSWRCN_CH12_MASK                      0x00001000
#define DMACTRL_CHSWRCN_CH13_MASK                      0x00002000
#define DMACTRL_CHSWRCN_CH14_MASK                      0x00004000
#define DMACTRL_CHSWRCN_CH15_MASK                      0x00008000
#define DMACTRL_CHSWRCN_CH16_MASK                      0x00010000
#define DMACTRL_CHSWRCN_CH17_MASK                      0x00020000
#define DMACTRL_CHSWRCN_CH18_MASK                      0x00040000
#define DMACTRL_CHSWRCN_CH19_MASK                      0x00080000
#define DMACTRL_CHSWRCN_CH20_MASK                      0x00100000
#define DMACTRL_CHSWRCN_CH21_MASK                      0x00200000
#define DMACTRL_CHSWRCN_CH22_MASK                      0x00400000
#define DMACTRL_CHSWRCN_CH23_MASK                      0x00800000
#define DMACTRL_CHSWRCN_CH24_MASK                      0x01000000
#define DMACTRL_CHSWRCN_CH25_MASK                      0x02000000
#define DMACTRL_CHSWRCN_CH26_MASK                      0x04000000
#define DMACTRL_CHSWRCN_CH27_MASK                      0x08000000
#define DMACTRL_CHSWRCN_CH28_MASK                      0x10000000
#define DMACTRL_CHSWRCN_CH29_MASK                      0x20000000
#define DMACTRL_CHSWRCN_CH30_MASK                      0x40000000
#define DMACTRL_CHSWRCN_CH31_MASK                      0x80000000
#define DMACTRL_CHSWRCN_CH0_BIT                        0  /* CH0<0>: Channel 0 Software Request.            */
#define DMACTRL_CHSWRCN_CH1_BIT                        1  /* CH1<1>: Channel 1 Software Request.            */
#define DMACTRL_CHSWRCN_CH2_BIT                        2  /* CH2<2>: Channel 2 Software Request.            */
#define DMACTRL_CHSWRCN_CH3_BIT                        3  /* CH3<3>: Channel 3 Software Request.            */
#define DMACTRL_CHSWRCN_CH4_BIT                        4  /* CH4<4>: Channel 4 Software Request.            */
#define DMACTRL_CHSWRCN_CH5_BIT                        5  /* CH5<5>: Channel 5 Software Request.            */
#define DMACTRL_CHSWRCN_CH6_BIT                        6  /* CH6<6>: Channel 6 Software Request.            */
#define DMACTRL_CHSWRCN_CH7_BIT                        7  /* CH7<7>: Channel 7 Software Request.            */
#define DMACTRL_CHSWRCN_CH8_BIT                        8  /* CH8<8>: Channel 8 Software Request.            */
#define DMACTRL_CHSWRCN_CH9_BIT                        9  /* CH9<9>: Channel 9 Software Request.            */
#define DMACTRL_CHSWRCN_CH10_BIT                       10 /* CH10<10>: Channel 10 Software Request.         */
#define DMACTRL_CHSWRCN_CH11_BIT                       11 /* CH11<11>: Channel 11 Software Request.         */
#define DMACTRL_CHSWRCN_CH12_BIT                       12 /* CH12<12>: Channel 12 Software Request.         */
#define DMACTRL_CHSWRCN_CH13_BIT                       13 /* CH13<13>: Channel 13 Software Request.         */
#define DMACTRL_CHSWRCN_CH14_BIT                       14 /* CH14<14>: Channel 14 Software Request.         */
#define DMACTRL_CHSWRCN_CH15_BIT                       15 /* CH15<15>: Channel 15 Software Request.         */
#define DMACTRL_CHSWRCN_CH16_BIT                       16
#define DMACTRL_CHSWRCN_CH17_BIT                       17
#define DMACTRL_CHSWRCN_CH18_BIT                       18
#define DMACTRL_CHSWRCN_CH19_BIT                       19
#define DMACTRL_CHSWRCN_CH20_BIT                       20
#define DMACTRL_CHSWRCN_CH21_BIT                       21
#define DMACTRL_CHSWRCN_CH22_BIT                       22
#define DMACTRL_CHSWRCN_CH23_BIT                       23
#define DMACTRL_CHSWRCN_CH24_BIT                       24
#define DMACTRL_CHSWRCN_CH25_BIT                       25
#define DMACTRL_CHSWRCN_CH26_BIT                       26
#define DMACTRL_CHSWRCN_CH27_BIT                       27
#define DMACTRL_CHSWRCN_CH28_BIT                       28
#define DMACTRL_CHSWRCN_CH29_BIT                       29
#define DMACTRL_CHSWRCN_CH30_BIT                       30
#define DMACTRL_CHSWRCN_CH31_BIT                       31
#define DMACTRL_CHSWRCN_CH0_DO_NOT_GENERATE_SW_REQ     (0 << DMACTRL_CHSWRCN_CH0_BIT)
#define DMACTRL_CHSWRCN_CH0_GENERATE_SW_REQ            (1 << DMACTRL_CHSWRCN_CH0_BIT)
#define DMACTRL_CHSWRCN_CH1_DO_NOT_GENERATE_SW_REQ     (0 << DMACTRL_CHSWRCN_CH1_BIT)
#define DMACTRL_CHSWRCN_CH1_GENERATE_SW_REQ            (1 << DMACTRL_CHSWRCN_CH1_BIT)
#define DMACTRL_CHSWRCN_CH2_DO_NOT_GENERATE_SW_REQ     (0 << DMACTRL_CHSWRCN_CH2_BIT)
#define DMACTRL_CHSWRCN_CH2_GENERATE_SW_REQ            (1 << DMACTRL_CHSWRCN_CH2_BIT)
#define DMACTRL_CHSWRCN_CH3_DO_NOT_GENERATE_SW_REQ     (0 << DMACTRL_CHSWRCN_CH3_BIT)
#define DMACTRL_CHSWRCN_CH3_GENERATE_SW_REQ            (1 << DMACTRL_CHSWRCN_CH3_BIT)
#define DMACTRL_CHSWRCN_CH4_DO_NOT_GENERATE_SW_REQ     (0 << DMACTRL_CHSWRCN_CH4_BIT)
#define DMACTRL_CHSWRCN_CH4_GENERATE_SW_REQ            (1 << DMACTRL_CHSWRCN_CH4_BIT)
#define DMACTRL_CHSWRCN_CH5_DO_NOT_GENERATE_SW_REQ     (0 << DMACTRL_CHSWRCN_CH5_BIT)
#define DMACTRL_CHSWRCN_CH5_GENERATE_SW_REQ            (1 << DMACTRL_CHSWRCN_CH5_BIT)
#define DMACTRL_CHSWRCN_CH6_DO_NOT_GENERATE_SW_REQ     (0 << DMACTRL_CHSWRCN_CH6_BIT)
#define DMACTRL_CHSWRCN_CH6_GENERATE_SW_REQ            (1 << DMACTRL_CHSWRCN_CH6_BIT)
#define DMACTRL_CHSWRCN_CH7_DO_NOT_GENERATE_SW_REQ     (0 << DMACTRL_CHSWRCN_CH7_BIT)
#define DMACTRL_CHSWRCN_CH7_GENERATE_SW_REQ            (1 << DMACTRL_CHSWRCN_CH7_BIT)
#define DMACTRL_CHSWRCN_CH8_DO_NOT_GENERATE_SW_REQ     (0 << DMACTRL_CHSWRCN_CH8_BIT)
#define DMACTRL_CHSWRCN_CH8_GENERATE_SW_REQ            (1 << DMACTRL_CHSWRCN_CH8_BIT)
#define DMACTRL_CHSWRCN_CH9_DO_NOT_GENERATE_SW_REQ     (0 << DMACTRL_CHSWRCN_CH9_BIT)
#define DMACTRL_CHSWRCN_CH9_GENERATE_SW_REQ            (1 << DMACTRL_CHSWRCN_CH9_BIT)
#define DMACTRL_CHSWRCN_CH10_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH10_BIT)
#define DMACTRL_CHSWRCN_CH10_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH10_BIT)
#define DMACTRL_CHSWRCN_CH11_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH11_BIT)
#define DMACTRL_CHSWRCN_CH11_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH11_BIT)
#define DMACTRL_CHSWRCN_CH12_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH12_BIT)
#define DMACTRL_CHSWRCN_CH12_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH12_BIT)
#define DMACTRL_CHSWRCN_CH13_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH13_BIT)
#define DMACTRL_CHSWRCN_CH13_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH13_BIT)
#define DMACTRL_CHSWRCN_CH14_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH14_BIT)
#define DMACTRL_CHSWRCN_CH14_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH14_BIT)
#define DMACTRL_CHSWRCN_CH15_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH15_BIT)
#define DMACTRL_CHSWRCN_CH15_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH15_BIT)
#define DMACTRL_CHSWRCN_CH16_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH16_BIT)
#define DMACTRL_CHSWRCN_CH16_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH16_BIT)
#define DMACTRL_CHSWRCN_CH17_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH17_BIT)
#define DMACTRL_CHSWRCN_CH17_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH17_BIT)
#define DMACTRL_CHSWRCN_CH18_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH18_BIT)
#define DMACTRL_CHSWRCN_CH18_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH18_BIT)
#define DMACTRL_CHSWRCN_CH19_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH19_BIT)
#define DMACTRL_CHSWRCN_CH19_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH19_BIT)
#define DMACTRL_CHSWRCN_CH20_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH20_BIT)
#define DMACTRL_CHSWRCN_CH20_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH20_BIT)
#define DMACTRL_CHSWRCN_CH21_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH21_BIT)
#define DMACTRL_CHSWRCN_CH21_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH21_BIT)
#define DMACTRL_CHSWRCN_CH22_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH22_BIT)
#define DMACTRL_CHSWRCN_CH22_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH22_BIT)
#define DMACTRL_CHSWRCN_CH23_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH23_BIT)
#define DMACTRL_CHSWRCN_CH23_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH23_BIT)
#define DMACTRL_CHSWRCN_CH24_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH24_BIT)
#define DMACTRL_CHSWRCN_CH24_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH24_BIT)
#define DMACTRL_CHSWRCN_CH25_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH25_BIT)
#define DMACTRL_CHSWRCN_CH25_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH25_BIT)
#define DMACTRL_CHSWRCN_CH26_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH26_BIT)
#define DMACTRL_CHSWRCN_CH26_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH26_BIT)
#define DMACTRL_CHSWRCN_CH27_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH27_BIT)
#define DMACTRL_CHSWRCN_CH27_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH27_BIT)
#define DMACTRL_CHSWRCN_CH28_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH28_BIT)
#define DMACTRL_CHSWRCN_CH28_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH28_BIT)
#define DMACTRL_CHSWRCN_CH29_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH29_BIT)
#define DMACTRL_CHSWRCN_CH29_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH29_BIT)
#define DMACTRL_CHSWRCN_CH30_DO_NOT_GENERATE_SW_REQ    (0 << DMACTRL_CHSWRCN_CH30_BIT)
#define DMACTRL_CHSWRCN_CH30_GENERATE_SW_REQ           (1 << DMACTRL_CHSWRCN_CH30_BIT)
#define DMACTRL_CHSWRCN_CH31_DO_NOT_GENERATE_SW_REQ    (0U << DMACTRL_CHSWRCN_CH31_BIT)
#define DMACTRL_CHSWRCN_CH31_GENERATE_SW_REQ           (1U << DMACTRL_CHSWRCN_CH31_BIT)



#define DMACTRL_CHREQMSET_CH0_MASK                     0x00000001
#define DMACTRL_CHREQMSET_CH1_MASK                     0x00000002
#define DMACTRL_CHREQMSET_CH2_MASK                     0x00000004
#define DMACTRL_CHREQMSET_CH3_MASK                     0x00000008
#define DMACTRL_CHREQMSET_CH4_MASK                     0x00000010
#define DMACTRL_CHREQMSET_CH5_MASK                     0x00000020
#define DMACTRL_CHREQMSET_CH6_MASK                     0x00000040
#define DMACTRL_CHREQMSET_CH7_MASK                     0x00000080
#define DMACTRL_CHREQMSET_CH8_MASK                     0x00000100
#define DMACTRL_CHREQMSET_CH9_MASK                     0x00000200
#define DMACTRL_CHREQMSET_CH10_MASK                    0x00000400
#define DMACTRL_CHREQMSET_CH11_MASK                    0x00000800
#define DMACTRL_CHREQMSET_CH12_MASK                    0x00001000
#define DMACTRL_CHREQMSET_CH13_MASK                    0x00002000
#define DMACTRL_CHREQMSET_CH14_MASK                    0x00004000
#define DMACTRL_CHREQMSET_CH15_MASK                    0x00008000
#define DMACTRL_CHREQMSET_CH16_MASK                    0x00010000
#define DMACTRL_CHREQMSET_CH17_MASK                    0x00020000
#define DMACTRL_CHREQMSET_CH18_MASK                    0x00040000
#define DMACTRL_CHREQMSET_CH19_MASK                    0x00080000
#define DMACTRL_CHREQMSET_CH20_MASK                    0x00100000
#define DMACTRL_CHREQMSET_CH21_MASK                    0x00200000
#define DMACTRL_CHREQMSET_CH22_MASK                    0x00400000
#define DMACTRL_CHREQMSET_CH23_MASK                    0x00800000
#define DMACTRL_CHREQMSET_CH24_MASK                    0x01000000
#define DMACTRL_CHREQMSET_CH25_MASK                    0x02000000
#define DMACTRL_CHREQMSET_CH26_MASK                    0x04000000
#define DMACTRL_CHREQMSET_CH27_MASK                    0x08000000
#define DMACTRL_CHREQMSET_CH28_MASK                    0x10000000
#define DMACTRL_CHREQMSET_CH29_MASK                    0x20000000
#define DMACTRL_CHREQMSET_CH30_MASK                    0x40000000
#define DMACTRL_CHREQMSET_CH31_MASK                    0x80000000
#define DMACTRL_CHREQMSET_CH0_BIT                      0  /* CH0<0>: Channel 0 Request Mask Enable.         */
#define DMACTRL_CHREQMSET_CH1_BIT                      1  /* CH1<1>: Channel 1 Request Mask Enable.         */
#define DMACTRL_CHREQMSET_CH2_BIT                      2  /* CH2<2>: Channel 2 Request Mask Enable.         */
#define DMACTRL_CHREQMSET_CH3_BIT                      3  /* CH3<3>: Channel 3 Request Mask Enable.         */
#define DMACTRL_CHREQMSET_CH4_BIT                      4  /* CH4<4>: Channel 4 Request Mask Enable.         */
#define DMACTRL_CHREQMSET_CH5_BIT                      5  /* CH5<5>: Channel 5 Request Mask Enable.         */
#define DMACTRL_CHREQMSET_CH6_BIT                      6  /* CH6<6>: Channel 6 Request Mask Enable.         */
#define DMACTRL_CHREQMSET_CH7_BIT                      7  /* CH7<7>: Channel 7 Request Mask Enable.         */
#define DMACTRL_CHREQMSET_CH8_BIT                      8  /* CH8<8>: Channel 8 Request Mask Enable.         */
#define DMACTRL_CHREQMSET_CH9_BIT                      9  /* CH9<9>: Channel 9 Request Mask Enable.         */
#define DMACTRL_CHREQMSET_CH10_BIT                     10 /* CH10<10>: Channel 10 Request Mask Enable.      */
#define DMACTRL_CHREQMSET_CH11_BIT                     11 /* CH11<11>: Channel 11 Request Mask Enable.      */
#define DMACTRL_CHREQMSET_CH12_BIT                     12 /* CH12<12>: Channel 12 Request Mask Enable.      */
#define DMACTRL_CHREQMSET_CH13_BIT                     13 /* CH13<13>: Channel 13 Request Mask Enable.      */
#define DMACTRL_CHREQMSET_CH14_BIT                     14 /* CH14<14>: Channel 14 Request Mask Enable.      */
#define DMACTRL_CHREQMSET_CH15_BIT                     15 /* CH15<15>: Channel 15 Request Mask Enable.      */
#define DMACTRL_CHREQMSET_CH16_BIT                     16
#define DMACTRL_CHREQMSET_CH17_BIT                     17
#define DMACTRL_CHREQMSET_CH18_BIT                     18
#define DMACTRL_CHREQMSET_CH19_BIT                     19
#define DMACTRL_CHREQMSET_CH20_BIT                     20
#define DMACTRL_CHREQMSET_CH21_BIT                     21
#define DMACTRL_CHREQMSET_CH22_BIT                     22
#define DMACTRL_CHREQMSET_CH23_BIT                     23
#define DMACTRL_CHREQMSET_CH24_BIT                     24
#define DMACTRL_CHREQMSET_CH25_BIT                     25
#define DMACTRL_CHREQMSET_CH26_BIT                     26
#define DMACTRL_CHREQMSET_CH27_BIT                     27
#define DMACTRL_CHREQMSET_CH28_BIT                     28
#define DMACTRL_CHREQMSET_CH29_BIT                     29
#define DMACTRL_CHREQMSET_CH30_BIT                     30
#define DMACTRL_CHREQMSET_CH31_BIT                     31
#define DMACTRL_CHREQMSET_CH0_EN                       (1 << DMACTRL_CHREQMSET_CH0_BIT)
#define DMACTRL_CHREQMSET_CH1_EN                       (1 << DMACTRL_CHREQMSET_CH1_BIT)
#define DMACTRL_CHREQMSET_CH2_EN                       (1 << DMACTRL_CHREQMSET_CH2_BIT)
#define DMACTRL_CHREQMSET_CH3_EN                       (1 << DMACTRL_CHREQMSET_CH3_BIT)
#define DMACTRL_CHREQMSET_CH4_EN                       (1 << DMACTRL_CHREQMSET_CH4_BIT)
#define DMACTRL_CHREQMSET_CH5_EN                       (1 << DMACTRL_CHREQMSET_CH5_BIT)
#define DMACTRL_CHREQMSET_CH6_EN                       (1 << DMACTRL_CHREQMSET_CH6_BIT)
#define DMACTRL_CHREQMSET_CH7_EN                       (1 << DMACTRL_CHREQMSET_CH7_BIT)
#define DMACTRL_CHREQMSET_CH8_EN                       (1 << DMACTRL_CHREQMSET_CH8_BIT)
#define DMACTRL_CHREQMSET_CH9_EN                       (1 << DMACTRL_CHREQMSET_CH9_BIT)
#define DMACTRL_CHREQMSET_CH10_EN                      (1 << DMACTRL_CHREQMSET_CH10_BIT)
#define DMACTRL_CHREQMSET_CH11_EN                      (1 << DMACTRL_CHREQMSET_CH11_BIT)
#define DMACTRL_CHREQMSET_CH12_EN                      (1 << DMACTRL_CHREQMSET_CH12_BIT)
#define DMACTRL_CHREQMSET_CH13_EN                      (1 << DMACTRL_CHREQMSET_CH13_BIT)
#define DMACTRL_CHREQMSET_CH14_EN                      (1 << DMACTRL_CHREQMSET_CH14_BIT)
#define DMACTRL_CHREQMSET_CH15_EN                      (1 << DMACTRL_CHREQMSET_CH15_BIT)
#define DMACTRL_CHREQMSET_CH16_EN                      (1 << DMACTRL_CHREQMSET_CH16_BIT)
#define DMACTRL_CHREQMSET_CH17_EN                      (1 << DMACTRL_CHREQMSET_CH17_BIT)
#define DMACTRL_CHREQMSET_CH18_EN                      (1 << DMACTRL_CHREQMSET_CH18_BIT)
#define DMACTRL_CHREQMSET_CH19_EN                      (1 << DMACTRL_CHREQMSET_CH19_BIT)
#define DMACTRL_CHREQMSET_CH20_EN                      (1 << DMACTRL_CHREQMSET_CH20_BIT)
#define DMACTRL_CHREQMSET_CH21_EN                      (1 << DMACTRL_CHREQMSET_CH21_BIT)
#define DMACTRL_CHREQMSET_CH22_EN                      (1 << DMACTRL_CHREQMSET_CH22_BIT)
#define DMACTRL_CHREQMSET_CH23_EN                      (1 << DMACTRL_CHREQMSET_CH23_BIT)
#define DMACTRL_CHREQMSET_CH24_EN                      (1 << DMACTRL_CHREQMSET_CH24_BIT)
#define DMACTRL_CHREQMSET_CH25_EN                      (1 << DMACTRL_CHREQMSET_CH25_BIT)
#define DMACTRL_CHREQMSET_CH26_EN                      (1 << DMACTRL_CHREQMSET_CH26_BIT)
#define DMACTRL_CHREQMSET_CH27_EN                      (1 << DMACTRL_CHREQMSET_CH27_BIT)
#define DMACTRL_CHREQMSET_CH28_EN                      (1 << DMACTRL_CHREQMSET_CH28_BIT)
#define DMACTRL_CHREQMSET_CH29_EN                      (1 << DMACTRL_CHREQMSET_CH29_BIT)
#define DMACTRL_CHREQMSET_CH30_EN                      (1 << DMACTRL_CHREQMSET_CH30_BIT)
#define DMACTRL_CHREQMSET_CH31_EN                      (1U << DMACTRL_CHREQMSET_CH31_BIT)


#define DMACTRL_CHREQMCLR_CH0_MASK                     0x00000001
#define DMACTRL_CHREQMCLR_CH1_MASK                     0x00000002
#define DMACTRL_CHREQMCLR_CH2_MASK                     0x00000004
#define DMACTRL_CHREQMCLR_CH3_MASK                     0x00000008
#define DMACTRL_CHREQMCLR_CH4_MASK                     0x00000010
#define DMACTRL_CHREQMCLR_CH5_MASK                     0x00000020
#define DMACTRL_CHREQMCLR_CH6_MASK                     0x00000040
#define DMACTRL_CHREQMCLR_CH7_MASK                     0x00000080
#define DMACTRL_CHREQMCLR_CH8_MASK                     0x00000100
#define DMACTRL_CHREQMCLR_CH9_MASK                     0x00000200
#define DMACTRL_CHREQMCLR_CH10_MASK                    0x00000400
#define DMACTRL_CHREQMCLR_CH11_MASK                    0x00000800
#define DMACTRL_CHREQMCLR_CH12_MASK                    0x00001000
#define DMACTRL_CHREQMCLR_CH13_MASK                    0x00002000
#define DMACTRL_CHREQMCLR_CH14_MASK                    0x00004000
#define DMACTRL_CHREQMCLR_CH15_MASK                    0x00008000
#define DMACTRL_CHREQMCLR_CH16_MASK                    0x00010000
#define DMACTRL_CHREQMCLR_CH17_MASK                    0x00020000
#define DMACTRL_CHREQMCLR_CH18_MASK                    0x00040000
#define DMACTRL_CHREQMCLR_CH19_MASK                    0x00080000
#define DMACTRL_CHREQMCLR_CH20_MASK                    0x00100000
#define DMACTRL_CHREQMCLR_CH21_MASK                    0x00200000
#define DMACTRL_CHREQMCLR_CH22_MASK                    0x00400000
#define DMACTRL_CHREQMCLR_CH23_MASK                    0x00800000
#define DMACTRL_CHREQMCLR_CH24_MASK                    0x01000000
#define DMACTRL_CHREQMCLR_CH25_MASK                    0x02000000
#define DMACTRL_CHREQMCLR_CH26_MASK                    0x04000000
#define DMACTRL_CHREQMCLR_CH27_MASK                    0x08000000
#define DMACTRL_CHREQMCLR_CH28_MASK                    0x10000000
#define DMACTRL_CHREQMCLR_CH29_MASK                    0x20000000
#define DMACTRL_CHREQMCLR_CH30_MASK                    0x40000000
#define DMACTRL_CHREQMCLR_CH31_MASK                    0x80000000
#define DMACTRL_CHREQMCLR_CH0_BIT                      0  /* CH0<0>: Channel 0 Request Mask Disable.        */
#define DMACTRL_CHREQMCLR_CH1_BIT                      1  /* CH1<1>: Channel 1 Request Mask Disable.        */
#define DMACTRL_CHREQMCLR_CH2_BIT                      2  /* CH2<2>: Channel 2 Request Mask Disable.        */
#define DMACTRL_CHREQMCLR_CH3_BIT                      3  /* CH3<3>: Channel 3 Request Mask Disable.        */
#define DMACTRL_CHREQMCLR_CH4_BIT                      4  /* CH4<4>: Channel 4 Request Mask Disable.        */
#define DMACTRL_CHREQMCLR_CH5_BIT                      5  /* CH5<5>: Channel 5 Request Mask Disable.        */
#define DMACTRL_CHREQMCLR_CH6_BIT                      6  /* CH6<6>: Channel 6 Request Mask Disable.        */
#define DMACTRL_CHREQMCLR_CH7_BIT                      7  /* CH7<7>: Channel 7 Request Mask Disable.        */
#define DMACTRL_CHREQMCLR_CH8_BIT                      8  /* CH8<8>: Channel 8 Request Mask Disable.        */
#define DMACTRL_CHREQMCLR_CH9_BIT                      9  /* CH9<9>: Channel 9 Request Mask Disable.        */
#define DMACTRL_CHREQMCLR_CH10_BIT                     10 /* CH10<10>: Channel 10 Request Mask Disable.     */
#define DMACTRL_CHREQMCLR_CH11_BIT                     11 /* CH11<11>: Channel 11 Request Mask Disable.     */
#define DMACTRL_CHREQMCLR_CH12_BIT                     12 /* CH12<12>: Channel 12 Request Mask Disable.     */
#define DMACTRL_CHREQMCLR_CH13_BIT                     13 /* CH13<13>: Channel 13 Request Mask Disable.     */
#define DMACTRL_CHREQMCLR_CH14_BIT                     14 /* CH14<14>: Channel 14 Request Mask Disable.     */
#define DMACTRL_CHREQMCLR_CH15_BIT                     15 /* CH15<15>: Channel 15 Request Mask Disable.     */
#define DMACTRL_CHREQMCLR_CH16_BIT                     16
#define DMACTRL_CHREQMCLR_CH17_BIT                     17
#define DMACTRL_CHREQMCLR_CH18_BIT                     18
#define DMACTRL_CHREQMCLR_CH19_BIT                     19
#define DMACTRL_CHREQMCLR_CH20_BIT                     20
#define DMACTRL_CHREQMCLR_CH21_BIT                     21
#define DMACTRL_CHREQMCLR_CH22_BIT                     22
#define DMACTRL_CHREQMCLR_CH23_BIT                     23
#define DMACTRL_CHREQMCLR_CH24_BIT                     24
#define DMACTRL_CHREQMCLR_CH25_BIT                     25
#define DMACTRL_CHREQMCLR_CH26_BIT                     26
#define DMACTRL_CHREQMCLR_CH27_BIT                     27
#define DMACTRL_CHREQMCLR_CH28_BIT                     28
#define DMACTRL_CHREQMCLR_CH29_BIT                     29
#define DMACTRL_CHREQMCLR_CH30_BIT                     30
#define DMACTRL_CHREQMCLR_CH31_BIT                     31
#define DMACTRL_CHREQMCLR_CH0_DS                       (1 << DMACTRL_CHREQMCLR_CH0_BIT)
#define DMACTRL_CHREQMCLR_CH1_DS                       (1 << DMACTRL_CHREQMCLR_CH1_BIT)
#define DMACTRL_CHREQMCLR_CH2_DS                       (1 << DMACTRL_CHREQMCLR_CH2_BIT)
#define DMACTRL_CHREQMCLR_CH3_DS                       (1 << DMACTRL_CHREQMCLR_CH3_BIT)
#define DMACTRL_CHREQMCLR_CH4_DS                       (1 << DMACTRL_CHREQMCLR_CH4_BIT)
#define DMACTRL_CHREQMCLR_CH5_DS                       (1 << DMACTRL_CHREQMCLR_CH5_BIT)
#define DMACTRL_CHREQMCLR_CH6_DS                       (1 << DMACTRL_CHREQMCLR_CH6_BIT)
#define DMACTRL_CHREQMCLR_CH7_DS                       (1 << DMACTRL_CHREQMCLR_CH7_BIT)
#define DMACTRL_CHREQMCLR_CH8_DS                       (1 << DMACTRL_CHREQMCLR_CH8_BIT)
#define DMACTRL_CHREQMCLR_CH9_DS                       (1 << DMACTRL_CHREQMCLR_CH9_BIT)
#define DMACTRL_CHREQMCLR_CH10_DS                      (1 << DMACTRL_CHREQMCLR_CH10_BIT)
#define DMACTRL_CHREQMCLR_CH11_DS                      (1 << DMACTRL_CHREQMCLR_CH11_BIT)
#define DMACTRL_CHREQMCLR_CH12_DS                      (1 << DMACTRL_CHREQMCLR_CH12_BIT)
#define DMACTRL_CHREQMCLR_CH13_DS                      (1 << DMACTRL_CHREQMCLR_CH13_BIT)
#define DMACTRL_CHREQMCLR_CH14_DS                      (1 << DMACTRL_CHREQMCLR_CH14_BIT)
#define DMACTRL_CHREQMCLR_CH15_DS                      (1 << DMACTRL_CHREQMCLR_CH15_BIT)
#define DMACTRL_CHREQMCLR_CH16_DS                      (1 << DMACTRL_CHREQMCLR_CH16_BIT)
#define DMACTRL_CHREQMCLR_CH17_DS                      (1 << DMACTRL_CHREQMCLR_CH17_BIT)
#define DMACTRL_CHREQMCLR_CH18_DS                      (1 << DMACTRL_CHREQMCLR_CH18_BIT)
#define DMACTRL_CHREQMCLR_CH19_DS                      (1 << DMACTRL_CHREQMCLR_CH19_BIT)
#define DMACTRL_CHREQMCLR_CH20_DS                      (1 << DMACTRL_CHREQMCLR_CH20_BIT)
#define DMACTRL_CHREQMCLR_CH21_DS                      (1 << DMACTRL_CHREQMCLR_CH21_BIT)
#define DMACTRL_CHREQMCLR_CH22_DS                      (1 << DMACTRL_CHREQMCLR_CH22_BIT)
#define DMACTRL_CHREQMCLR_CH23_DS                      (1 << DMACTRL_CHREQMCLR_CH23_BIT)
#define DMACTRL_CHREQMCLR_CH24_DS                      (1 << DMACTRL_CHREQMCLR_CH24_BIT)
#define DMACTRL_CHREQMCLR_CH25_DS                      (1 << DMACTRL_CHREQMCLR_CH25_BIT)
#define DMACTRL_CHREQMCLR_CH26_DS                      (1 << DMACTRL_CHREQMCLR_CH26_BIT)
#define DMACTRL_CHREQMCLR_CH27_DS                      (1 << DMACTRL_CHREQMCLR_CH27_BIT)
#define DMACTRL_CHREQMCLR_CH28_DS                      (1 << DMACTRL_CHREQMCLR_CH28_BIT)
#define DMACTRL_CHREQMCLR_CH29_DS                      (1 << DMACTRL_CHREQMCLR_CH29_BIT)
#define DMACTRL_CHREQMCLR_CH30_DS                      (1 << DMACTRL_CHREQMCLR_CH30_BIT)
#define DMACTRL_CHREQMCLR_CH31_DS                      (1U << DMACTRL_CHREQMCLR_CH31_BIT)






#define DMACTRL_CHENSET_CH0_MASK                       0x00000001
#define DMACTRL_CHENSET_CH1_MASK                       0x00000002
#define DMACTRL_CHENSET_CH2_MASK                       0x00000004
#define DMACTRL_CHENSET_CH3_MASK                       0x00000008
#define DMACTRL_CHENSET_CH4_MASK                       0x00000010
#define DMACTRL_CHENSET_CH5_MASK                       0x00000020
#define DMACTRL_CHENSET_CH6_MASK                       0x00000040
#define DMACTRL_CHENSET_CH7_MASK                       0x00000080
#define DMACTRL_CHENSET_CH8_MASK                       0x00000100
#define DMACTRL_CHENSET_CH9_MASK                       0x00000200
#define DMACTRL_CHENSET_CH10_MASK                      0x00000400
#define DMACTRL_CHENSET_CH11_MASK                      0x00000800
#define DMACTRL_CHENSET_CH12_MASK                      0x00001000
#define DMACTRL_CHENSET_CH13_MASK                      0x00002000
#define DMACTRL_CHENSET_CH14_MASK                      0x00004000
#define DMACTRL_CHENSET_CH15_MASK                      0x00008000
#define DMACTRL_CHENSET_CH16_MASK                      0x00010000
#define DMACTRL_CHENSET_CH17_MASK                      0x00020000
#define DMACTRL_CHENSET_CH18_MASK                      0x00040000
#define DMACTRL_CHENSET_CH19_MASK                      0x00080000
#define DMACTRL_CHENSET_CH20_MASK                      0x00100000
#define DMACTRL_CHENSET_CH21_MASK                      0x00200000
#define DMACTRL_CHENSET_CH22_MASK                      0x00400000
#define DMACTRL_CHENSET_CH23_MASK                      0x00800000
#define DMACTRL_CHENSET_CH24_MASK                      0x01000000
#define DMACTRL_CHENSET_CH25_MASK                      0x02000000
#define DMACTRL_CHENSET_CH26_MASK                      0x04000000
#define DMACTRL_CHENSET_CH27_MASK                      0x08000000
#define DMACTRL_CHENSET_CH28_MASK                      0x10000000
#define DMACTRL_CHENSET_CH29_MASK                      0x20000000
#define DMACTRL_CHENSET_CH30_MASK                      0x40000000
#define DMACTRL_CHENSET_CH31_MASK                      0x80000000
#define DMACTRL_CHENSET_CH0_BIT                        0  /* CH0<0>: Channel 0 Enable.                      */
#define DMACTRL_CHENSET_CH1_BIT                        1  /* CH1<1>: Channel 1 Enable.                      */
#define DMACTRL_CHENSET_CH2_BIT                        2  /* CH2<2>: Channel 2 Enable.                      */
#define DMACTRL_CHENSET_CH3_BIT                        3  /* CH3<3>: Channel 3 Enable.                      */
#define DMACTRL_CHENSET_CH4_BIT                        4  /* CH4<4>: Channel 4 Enable.                      */
#define DMACTRL_CHENSET_CH5_BIT                        5  /* CH5<5>: Channel 5 Enable.                      */
#define DMACTRL_CHENSET_CH6_BIT                        6  /* CH6<6>: Channel 6 Enable.                      */
#define DMACTRL_CHENSET_CH7_BIT                        7  /* CH7<7>: Channel 7 Enable.                      */
#define DMACTRL_CHENSET_CH8_BIT                        8  /* CH8<8>: Channel 8 Enable.                      */
#define DMACTRL_CHENSET_CH9_BIT                        9  /* CH9<9>: Channel 9 Enable.                      */
#define DMACTRL_CHENSET_CH10_BIT                       10 /* CH10<10>: Channel 10 Enable.                   */
#define DMACTRL_CHENSET_CH11_BIT                       11 /* CH11<11>: Channel 11 Enable.                   */
#define DMACTRL_CHENSET_CH12_BIT                       12 /* CH12<12>: Channel 12 Enable.                   */
#define DMACTRL_CHENSET_CH13_BIT                       13 /* CH13<13>: Channel 13 Enable.                   */
#define DMACTRL_CHENSET_CH14_BIT                       14 /* CH14<14>: Channel 14 Enable.                   */
#define DMACTRL_CHENSET_CH15_BIT                       15 /* CH15<15>: Channel 15 Enable.                   */
#define DMACTRL_CHENSET_CH16_BIT                       16
#define DMACTRL_CHENSET_CH17_BIT                       17
#define DMACTRL_CHENSET_CH18_BIT                       18
#define DMACTRL_CHENSET_CH19_BIT                       19
#define DMACTRL_CHENSET_CH20_BIT                       20
#define DMACTRL_CHENSET_CH21_BIT                       21
#define DMACTRL_CHENSET_CH22_BIT                       22
#define DMACTRL_CHENSET_CH23_BIT                       23
#define DMACTRL_CHENSET_CH24_BIT                       24
#define DMACTRL_CHENSET_CH25_BIT                       25
#define DMACTRL_CHENSET_CH26_BIT                       26
#define DMACTRL_CHENSET_CH27_BIT                       27
#define DMACTRL_CHENSET_CH28_BIT                       28
#define DMACTRL_CHENSET_CH29_BIT                       29
#define DMACTRL_CHENSET_CH30_BIT                       30
#define DMACTRL_CHENSET_CH31_BIT                       31
#define DMACTRL_CHENSET_CH0_EN                         (1 << DMACTRL_CHENSET_CH0_BIT)
#define DMACTRL_CHENSET_CH1_EN                         (1 << DMACTRL_CHENSET_CH1_BIT)
#define DMACTRL_CHENSET_CH2_EN                         (1 << DMACTRL_CHENSET_CH2_BIT)
#define DMACTRL_CHENSET_CH3_EN                         (1 << DMACTRL_CHENSET_CH3_BIT)
#define DMACTRL_CHENSET_CH4_EN                         (1 << DMACTRL_CHENSET_CH4_BIT)
#define DMACTRL_CHENSET_CH5_EN                         (1 << DMACTRL_CHENSET_CH5_BIT)
#define DMACTRL_CHENSET_CH6_EN                         (1 << DMACTRL_CHENSET_CH6_BIT)
#define DMACTRL_CHENSET_CH7_EN                         (1 << DMACTRL_CHENSET_CH7_BIT)
#define DMACTRL_CHENSET_CH8_EN                         (1 << DMACTRL_CHENSET_CH8_BIT)
#define DMACTRL_CHENSET_CH9_EN                         (1 << DMACTRL_CHENSET_CH9_BIT)
#define DMACTRL_CHENSET_CH10_EN                        (1 << DMACTRL_CHENSET_CH10_BIT)
#define DMACTRL_CHENSET_CH11_EN                        (1 << DMACTRL_CHENSET_CH11_BIT)
#define DMACTRL_CHENSET_CH12_EN                        (1 << DMACTRL_CHENSET_CH12_BIT)
#define DMACTRL_CHENSET_CH13_EN                        (1 << DMACTRL_CHENSET_CH13_BIT)
#define DMACTRL_CHENSET_CH14_EN                        (1 << DMACTRL_CHENSET_CH14_BIT)
#define DMACTRL_CHENSET_CH15_EN                        (1 << DMACTRL_CHENSET_CH15_BIT)
#define DMACTRL_CHENSET_CH16_EN                        (1 << DMACTRL_CHENSET_CH16_BIT)
#define DMACTRL_CHENSET_CH17_EN                        (1 << DMACTRL_CHENSET_CH17_BIT)
#define DMACTRL_CHENSET_CH18_EN                        (1 << DMACTRL_CHENSET_CH18_BIT)
#define DMACTRL_CHENSET_CH19_EN                        (1 << DMACTRL_CHENSET_CH19_BIT)
#define DMACTRL_CHENSET_CH20_EN                        (1 << DMACTRL_CHENSET_CH20_BIT)
#define DMACTRL_CHENSET_CH21_EN                        (1 << DMACTRL_CHENSET_CH21_BIT)
#define DMACTRL_CHENSET_CH22_EN                        (1 << DMACTRL_CHENSET_CH22_BIT)
#define DMACTRL_CHENSET_CH23_EN                        (1 << DMACTRL_CHENSET_CH23_BIT)
#define DMACTRL_CHENSET_CH24_EN                        (1 << DMACTRL_CHENSET_CH24_BIT)
#define DMACTRL_CHENSET_CH25_EN                        (1 << DMACTRL_CHENSET_CH25_BIT)
#define DMACTRL_CHENSET_CH26_EN                        (1 << DMACTRL_CHENSET_CH26_BIT)
#define DMACTRL_CHENSET_CH27_EN                        (1 << DMACTRL_CHENSET_CH27_BIT)
#define DMACTRL_CHENSET_CH28_EN                        (1 << DMACTRL_CHENSET_CH28_BIT)
#define DMACTRL_CHENSET_CH29_EN                        (1 << DMACTRL_CHENSET_CH29_BIT)
#define DMACTRL_CHENSET_CH30_EN                        (1 << DMACTRL_CHENSET_CH30_BIT)
#define DMACTRL_CHENSET_CH31_EN                        (1U << DMACTRL_CHENSET_CH31_BIT)


#define DMACTRL_CHENCLR_CH0_MASK                       0x00000001
#define DMACTRL_CHENCLR_CH1_MASK                       0x00000002
#define DMACTRL_CHENCLR_CH2_MASK                       0x00000004
#define DMACTRL_CHENCLR_CH3_MASK                       0x00000008
#define DMACTRL_CHENCLR_CH4_MASK                       0x00000010
#define DMACTRL_CHENCLR_CH5_MASK                       0x00000020
#define DMACTRL_CHENCLR_CH6_MASK                       0x00000040
#define DMACTRL_CHENCLR_CH7_MASK                       0x00000080
#define DMACTRL_CHENCLR_CH8_MASK                       0x00000100
#define DMACTRL_CHENCLR_CH9_MASK                       0x00000200
#define DMACTRL_CHENCLR_CH10_MASK                      0x00000400
#define DMACTRL_CHENCLR_CH11_MASK                      0x00000800
#define DMACTRL_CHENCLR_CH12_MASK                      0x00001000
#define DMACTRL_CHENCLR_CH13_MASK                      0x00002000
#define DMACTRL_CHENCLR_CH14_MASK                      0x00004000
#define DMACTRL_CHENCLR_CH15_MASK                      0x00008000
#define DMACTRL_CHENCLR_CH16_MASK                      0x00010000
#define DMACTRL_CHENCLR_CH17_MASK                      0x00020000
#define DMACTRL_CHENCLR_CH18_MASK                      0x00040000
#define DMACTRL_CHENCLR_CH19_MASK                      0x00080000
#define DMACTRL_CHENCLR_CH20_MASK                      0x00100000
#define DMACTRL_CHENCLR_CH21_MASK                      0x00200000
#define DMACTRL_CHENCLR_CH22_MASK                      0x00400000
#define DMACTRL_CHENCLR_CH23_MASK                      0x00800000
#define DMACTRL_CHENCLR_CH24_MASK                      0x01000000
#define DMACTRL_CHENCLR_CH25_MASK                      0x02000000
#define DMACTRL_CHENCLR_CH26_MASK                      0x04000000
#define DMACTRL_CHENCLR_CH27_MASK                      0x08000000
#define DMACTRL_CHENCLR_CH28_MASK                      0x10000000
#define DMACTRL_CHENCLR_CH29_MASK                      0x20000000
#define DMACTRL_CHENCLR_CH30_MASK                      0x40000000
#define DMACTRL_CHENCLR_CH31_MASK                      0x80000000
#define DMACTRL_CHENCLR_CH0_BIT                        0  /* CH0<0>: Channel 0 Disable.                     */
#define DMACTRL_CHENCLR_CH1_BIT                        1  /* CH1<1>: Channel 1 Disable.                     */
#define DMACTRL_CHENCLR_CH2_BIT                        2  /* CH2<2>: Channel 2 Disable.                     */
#define DMACTRL_CHENCLR_CH3_BIT                        3  /* CH3<3>: Channel 3 Disable.                     */
#define DMACTRL_CHENCLR_CH4_BIT                        4  /* CH4<4>: Channel 4 Disable.                     */
#define DMACTRL_CHENCLR_CH5_BIT                        5  /* CH5<5>: Channel 5 Disable.                     */
#define DMACTRL_CHENCLR_CH6_BIT                        6  /* CH6<6>: Channel 6 Disable.                     */
#define DMACTRL_CHENCLR_CH7_BIT                        7  /* CH7<7>: Channel 7 Disable.                     */
#define DMACTRL_CHENCLR_CH8_BIT                        8  /* CH8<8>: Channel 8 Disable.                     */
#define DMACTRL_CHENCLR_CH9_BIT                        9  /* CH9<9>: Channel 9 Disable.                     */
#define DMACTRL_CHENCLR_CH10_BIT                       10 /* CH10<10>: Channel 10 Disable.                  */
#define DMACTRL_CHENCLR_CH11_BIT                       11 /* CH11<11>: Channel 11 Disable.                  */
#define DMACTRL_CHENCLR_CH12_BIT                       12 /* CH12<12>: Channel 12 Disable.                  */
#define DMACTRL_CHENCLR_CH13_BIT                       13 /* CH13<13>: Channel 13 Disable.                  */
#define DMACTRL_CHENCLR_CH14_BIT                       14 /* CH14<14>: Channel 14 Disable.                  */
#define DMACTRL_CHENCLR_CH15_BIT                       15 /* CH15<15>: Channel 15 Disable.                  */
#define DMACTRL_CHENCLR_CH16_BIT                       16
#define DMACTRL_CHENCLR_CH17_BIT                       17
#define DMACTRL_CHENCLR_CH18_BIT                       18
#define DMACTRL_CHENCLR_CH19_BIT                       19
#define DMACTRL_CHENCLR_CH20_BIT                       20
#define DMACTRL_CHENCLR_CH21_BIT                       21
#define DMACTRL_CHENCLR_CH22_BIT                       22
#define DMACTRL_CHENCLR_CH23_BIT                       23
#define DMACTRL_CHENCLR_CH24_BIT                       24
#define DMACTRL_CHENCLR_CH25_BIT                       25
#define DMACTRL_CHENCLR_CH26_BIT                       26
#define DMACTRL_CHENCLR_CH27_BIT                       27
#define DMACTRL_CHENCLR_CH28_BIT                       28
#define DMACTRL_CHENCLR_CH29_BIT                       29
#define DMACTRL_CHENCLR_CH30_BIT                       30
#define DMACTRL_CHENCLR_CH31_BIT                       31
#define DMACTRL_CHENCLR_CH0_DS                         (1 << DMACTRL_CHENCLR_CH0_BIT)
#define DMACTRL_CHENCLR_CH1_DS                         (1 << DMACTRL_CHENCLR_CH1_BIT)
#define DMACTRL_CHENCLR_CH2_DS                         (1 << DMACTRL_CHENCLR_CH2_BIT)
#define DMACTRL_CHENCLR_CH3_DS                         (1 << DMACTRL_CHENCLR_CH3_BIT)
#define DMACTRL_CHENCLR_CH4_DS                         (1 << DMACTRL_CHENCLR_CH4_BIT)
#define DMACTRL_CHENCLR_CH5_DS                         (1 << DMACTRL_CHENCLR_CH5_BIT)
#define DMACTRL_CHENCLR_CH6_DS                         (1 << DMACTRL_CHENCLR_CH6_BIT)
#define DMACTRL_CHENCLR_CH7_DS                         (1 << DMACTRL_CHENCLR_CH7_BIT)
#define DMACTRL_CHENCLR_CH8_DS                         (1 << DMACTRL_CHENCLR_CH8_BIT)
#define DMACTRL_CHENCLR_CH9_DS                         (1 << DMACTRL_CHENCLR_CH9_BIT)
#define DMACTRL_CHENCLR_CH10_DS                        (1 << DMACTRL_CHENCLR_CH10_BIT)
#define DMACTRL_CHENCLR_CH11_DS                        (1 << DMACTRL_CHENCLR_CH11_BIT)
#define DMACTRL_CHENCLR_CH12_DS                        (1 << DMACTRL_CHENCLR_CH12_BIT)
#define DMACTRL_CHENCLR_CH13_DS                        (1 << DMACTRL_CHENCLR_CH13_BIT)
#define DMACTRL_CHENCLR_CH14_DS                        (1 << DMACTRL_CHENCLR_CH14_BIT)
#define DMACTRL_CHENCLR_CH15_DS                        (1 << DMACTRL_CHENCLR_CH15_BIT)
#define DMACTRL_CHENCLR_CH16_DS                        (1 << DMACTRL_CHENCLR_CH16_BIT)
#define DMACTRL_CHENCLR_CH17_DS                        (1 << DMACTRL_CHENCLR_CH17_BIT)
#define DMACTRL_CHENCLR_CH18_DS                        (1 << DMACTRL_CHENCLR_CH18_BIT)
#define DMACTRL_CHENCLR_CH19_DS                        (1 << DMACTRL_CHENCLR_CH19_BIT)
#define DMACTRL_CHENCLR_CH20_DS                        (1 << DMACTRL_CHENCLR_CH20_BIT)
#define DMACTRL_CHENCLR_CH21_DS                        (1 << DMACTRL_CHENCLR_CH21_BIT)
#define DMACTRL_CHENCLR_CH22_DS                        (1 << DMACTRL_CHENCLR_CH22_BIT)
#define DMACTRL_CHENCLR_CH23_DS                        (1 << DMACTRL_CHENCLR_CH23_BIT)
#define DMACTRL_CHENCLR_CH24_DS                        (1 << DMACTRL_CHENCLR_CH24_BIT)
#define DMACTRL_CHENCLR_CH25_DS                        (1 << DMACTRL_CHENCLR_CH25_BIT)
#define DMACTRL_CHENCLR_CH26_DS                        (1 << DMACTRL_CHENCLR_CH26_BIT)
#define DMACTRL_CHENCLR_CH27_DS                        (1 << DMACTRL_CHENCLR_CH27_BIT)
#define DMACTRL_CHENCLR_CH28_DS                        (1 << DMACTRL_CHENCLR_CH28_BIT)
#define DMACTRL_CHENCLR_CH29_DS                        (1 << DMACTRL_CHENCLR_CH29_BIT)
#define DMACTRL_CHENCLR_CH30_DS                        (1 << DMACTRL_CHENCLR_CH30_BIT)
#define DMACTRL_CHENCLR_CH31_DS                        (1U << DMACTRL_CHENCLR_CH31_BIT)



#define DMACTRL_CHALTSET_CH0_MASK                      0x00000001
#define DMACTRL_CHALTSET_CH1_MASK                      0x00000002
#define DMACTRL_CHALTSET_CH2_MASK                      0x00000004
#define DMACTRL_CHALTSET_CH3_MASK                      0x00000008
#define DMACTRL_CHALTSET_CH4_MASK                      0x00000010
#define DMACTRL_CHALTSET_CH5_MASK                      0x00000020
#define DMACTRL_CHALTSET_CH6_MASK                      0x00000040
#define DMACTRL_CHALTSET_CH7_MASK                      0x00000080
#define DMACTRL_CHALTSET_CH8_MASK                      0x00000100
#define DMACTRL_CHALTSET_CH9_MASK                      0x00000200
#define DMACTRL_CHALTSET_CH10_MASK                     0x00000400
#define DMACTRL_CHALTSET_CH11_MASK                     0x00000800
#define DMACTRL_CHALTSET_CH12_MASK                     0x00001000
#define DMACTRL_CHALTSET_CH13_MASK                     0x00002000
#define DMACTRL_CHALTSET_CH14_MASK                     0x00004000
#define DMACTRL_CHALTSET_CH15_MASK                     0x00008000
#define DMACTRL_CHALTSET_CH16_MASK                     0x00010000
#define DMACTRL_CHALTSET_CH17_MASK                     0x00020000
#define DMACTRL_CHALTSET_CH18_MASK                     0x00040000
#define DMACTRL_CHALTSET_CH19_MASK                     0x00080000
#define DMACTRL_CHALTSET_CH20_MASK                     0x00100000
#define DMACTRL_CHALTSET_CH21_MASK                     0x00200000
#define DMACTRL_CHALTSET_CH22_MASK                     0x00400000
#define DMACTRL_CHALTSET_CH23_MASK                     0x00800000
#define DMACTRL_CHALTSET_CH24_MASK                     0x01000000
#define DMACTRL_CHALTSET_CH25_MASK                     0x02000000
#define DMACTRL_CHALTSET_CH26_MASK                     0x04000000
#define DMACTRL_CHALTSET_CH27_MASK                     0x08000000
#define DMACTRL_CHALTSET_CH28_MASK                     0x10000000
#define DMACTRL_CHALTSET_CH29_MASK                     0x20000000
#define DMACTRL_CHALTSET_CH30_MASK                     0x40000000
#define DMACTRL_CHALTSET_CH31_MASK                     0x80000000
#define DMACTRL_CHALTSET_CH0_BIT                       0  /* CH0<0>: Channel 0 Alternate Enable.            */
#define DMACTRL_CHALTSET_CH1_BIT                       1  /* CH1<1>: Channel 1 Alternate Enable.            */
#define DMACTRL_CHALTSET_CH2_BIT                       2  /* CH2<2>: Channel 2 Alternate Enable.            */
#define DMACTRL_CHALTSET_CH3_BIT                       3  /* CH3<3>: Channel 3 Alternate Enable.            */
#define DMACTRL_CHALTSET_CH4_BIT                       4  /* CH4<4>: Channel 4 Alternate Enable.            */
#define DMACTRL_CHALTSET_CH5_BIT                       5  /* CH5<5>: Channel 5 Alternate Enable.            */
#define DMACTRL_CHALTSET_CH6_BIT                       6  /* CH6<6>: Channel 6 Alternate Enable.            */
#define DMACTRL_CHALTSET_CH7_BIT                       7  /* CH7<7>: Channel 7 Alternate Enable.            */
#define DMACTRL_CHALTSET_CH8_BIT                       8  /* CH8<8>: Channel 8 Alternate Enable.            */
#define DMACTRL_CHALTSET_CH9_BIT                       9  /* CH9<9>: Channel 9 Alternate Enable.            */
#define DMACTRL_CHALTSET_CH10_BIT                      10 /* CH10<10>: Channel 10 Alternate Enable.         */
#define DMACTRL_CHALTSET_CH11_BIT                      11 /* CH11<11>: Channel 11 Alternate Enable.         */
#define DMACTRL_CHALTSET_CH12_BIT                      12 /* CH12<12>: Channel 12 Alternate Enable.         */
#define DMACTRL_CHALTSET_CH13_BIT                      13 /* CH13<13>: Channel 13 Alternate Enable.         */
#define DMACTRL_CHALTSET_CH14_BIT                      14 /* CH14<14>: Channel 14 Alternate Enable.         */
#define DMACTRL_CHALTSET_CH15_BIT                      15 /* CH15<15>: Channel 15 Alternate Enable.         */
#define DMACTRL_CHALTSET_CH16_BIT                      16
#define DMACTRL_CHALTSET_CH17_BIT                      17
#define DMACTRL_CHALTSET_CH18_BIT                      18
#define DMACTRL_CHALTSET_CH19_BIT                      19
#define DMACTRL_CHALTSET_CH20_BIT                      20
#define DMACTRL_CHALTSET_CH21_BIT                      21
#define DMACTRL_CHALTSET_CH22_BIT                      22
#define DMACTRL_CHALTSET_CH23_BIT                      23
#define DMACTRL_CHALTSET_CH24_BIT                      24
#define DMACTRL_CHALTSET_CH25_BIT                      25
#define DMACTRL_CHALTSET_CH26_BIT                      26
#define DMACTRL_CHALTSET_CH27_BIT                      27
#define DMACTRL_CHALTSET_CH28_BIT                      28
#define DMACTRL_CHALTSET_CH29_BIT                      29
#define DMACTRL_CHALTSET_CH30_BIT                      30
#define DMACTRL_CHALTSET_CH31_BIT                      31
#define DMACTRL_CHALTSET_CH0_EN                        (1 << DMACTRL_CHALTSET_CH0_BIT)
#define DMACTRL_CHALTSET_CH1_EN                        (1 << DMACTRL_CHALTSET_CH1_BIT)
#define DMACTRL_CHALTSET_CH2_EN                        (1 << DMACTRL_CHALTSET_CH2_BIT)
#define DMACTRL_CHALTSET_CH3_EN                        (1 << DMACTRL_CHALTSET_CH3_BIT)
#define DMACTRL_CHALTSET_CH4_EN                        (1 << DMACTRL_CHALTSET_CH4_BIT)
#define DMACTRL_CHALTSET_CH5_EN                        (1 << DMACTRL_CHALTSET_CH5_BIT)
#define DMACTRL_CHALTSET_CH6_EN                        (1 << DMACTRL_CHALTSET_CH6_BIT)
#define DMACTRL_CHALTSET_CH7_EN                        (1 << DMACTRL_CHALTSET_CH7_BIT)
#define DMACTRL_CHALTSET_CH8_EN                        (1 << DMACTRL_CHALTSET_CH8_BIT)
#define DMACTRL_CHALTSET_CH9_EN                        (1 << DMACTRL_CHALTSET_CH9_BIT)
#define DMACTRL_CHALTSET_CH10_EN                       (1 << DMACTRL_CHALTSET_CH10_BIT)
#define DMACTRL_CHALTSET_CH11_EN                       (1 << DMACTRL_CHALTSET_CH11_BIT)
#define DMACTRL_CHALTSET_CH12_EN                       (1 << DMACTRL_CHALTSET_CH12_BIT)
#define DMACTRL_CHALTSET_CH13_EN                       (1 << DMACTRL_CHALTSET_CH13_BIT)
#define DMACTRL_CHALTSET_CH14_EN                       (1 << DMACTRL_CHALTSET_CH14_BIT)
#define DMACTRL_CHALTSET_CH15_EN                       (1 << DMACTRL_CHALTSET_CH15_BIT)
#define DMACTRL_CHALTSET_CH16_EN                       (1 << DMACTRL_CHALTSET_CH16_BIT)
#define DMACTRL_CHALTSET_CH17_EN                       (1 << DMACTRL_CHALTSET_CH17_BIT)
#define DMACTRL_CHALTSET_CH18_EN                       (1 << DMACTRL_CHALTSET_CH18_BIT)
#define DMACTRL_CHALTSET_CH19_EN                       (1 << DMACTRL_CHALTSET_CH19_BIT)
#define DMACTRL_CHALTSET_CH20_EN                       (1 << DMACTRL_CHALTSET_CH20_BIT)
#define DMACTRL_CHALTSET_CH21_EN                       (1 << DMACTRL_CHALTSET_CH21_BIT)
#define DMACTRL_CHALTSET_CH22_EN                       (1 << DMACTRL_CHALTSET_CH22_BIT)
#define DMACTRL_CHALTSET_CH23_EN                       (1 << DMACTRL_CHALTSET_CH23_BIT)
#define DMACTRL_CHALTSET_CH24_EN                       (1 << DMACTRL_CHALTSET_CH24_BIT)
#define DMACTRL_CHALTSET_CH25_EN                       (1 << DMACTRL_CHALTSET_CH25_BIT)
#define DMACTRL_CHALTSET_CH26_EN                       (1 << DMACTRL_CHALTSET_CH26_BIT)
#define DMACTRL_CHALTSET_CH27_EN                       (1 << DMACTRL_CHALTSET_CH27_BIT)
#define DMACTRL_CHALTSET_CH28_EN                       (1 << DMACTRL_CHALTSET_CH28_BIT)
#define DMACTRL_CHALTSET_CH29_EN                       (1 << DMACTRL_CHALTSET_CH29_BIT)
#define DMACTRL_CHALTSET_CH30_EN                       (1 << DMACTRL_CHALTSET_CH30_BIT)
#define DMACTRL_CHALTSET_CH31_EN                       (1U << DMACTRL_CHALTSET_CH31_BIT)





#define DMACTRL_CHALTCLR_CH0_MASK                      0x00000001
#define DMACTRL_CHALTCLR_CH1_MASK                      0x00000002
#define DMACTRL_CHALTCLR_CH2_MASK                      0x00000004
#define DMACTRL_CHALTCLR_CH3_MASK                      0x00000008
#define DMACTRL_CHALTCLR_CH4_MASK                      0x00000010
#define DMACTRL_CHALTCLR_CH5_MASK                      0x00000020
#define DMACTRL_CHALTCLR_CH6_MASK                      0x00000040
#define DMACTRL_CHALTCLR_CH7_MASK                      0x00000080
#define DMACTRL_CHALTCLR_CH8_MASK                      0x00000100
#define DMACTRL_CHALTCLR_CH9_MASK                      0x00000200
#define DMACTRL_CHALTCLR_CH10_MASK                     0x00000400
#define DMACTRL_CHALTCLR_CH11_MASK                     0x00000800
#define DMACTRL_CHALTCLR_CH12_MASK                     0x00001000
#define DMACTRL_CHALTCLR_CH13_MASK                     0x00002000
#define DMACTRL_CHALTCLR_CH14_MASK                     0x00004000
#define DMACTRL_CHALTCLR_CH15_MASK                     0x00008000
#define DMACTRL_CHALTCLR_CH16_MASK                     0x00010000
#define DMACTRL_CHALTCLR_CH17_MASK                     0x00020000
#define DMACTRL_CHALTCLR_CH18_MASK                     0x00040000
#define DMACTRL_CHALTCLR_CH19_MASK                     0x00080000
#define DMACTRL_CHALTCLR_CH20_MASK                     0x00100000
#define DMACTRL_CHALTCLR_CH21_MASK                     0x00200000
#define DMACTRL_CHALTCLR_CH22_MASK                     0x00400000
#define DMACTRL_CHALTCLR_CH23_MASK                     0x00800000
#define DMACTRL_CHALTCLR_CH24_MASK                     0x01000000
#define DMACTRL_CHALTCLR_CH25_MASK                     0x02000000
#define DMACTRL_CHALTCLR_CH26_MASK                     0x04000000
#define DMACTRL_CHALTCLR_CH27_MASK                     0x08000000
#define DMACTRL_CHALTCLR_CH28_MASK                     0x10000000
#define DMACTRL_CHALTCLR_CH29_MASK                     0x20000000
#define DMACTRL_CHALTCLR_CH30_MASK                     0x40000000
#define DMACTRL_CHALTCLR_CH31_MASK                     0x80000000
#define DMACTRL_CHALTCLR_CH0_BIT                       0  /* CH0<0>: Channel 0 Alternate Disable.           */
#define DMACTRL_CHALTCLR_CH1_BIT                       1  /* CH1<1>: Channel 1 Alternate Disable.           */
#define DMACTRL_CHALTCLR_CH2_BIT                       2  /* CH2<2>: Channel 2 Alternate Disable.           */
#define DMACTRL_CHALTCLR_CH3_BIT                       3  /* CH3<3>: Channel 3 Alternate Disable.           */
#define DMACTRL_CHALTCLR_CH4_BIT                       4  /* CH4<4>: Channel 4 Alternate Disable.           */
#define DMACTRL_CHALTCLR_CH5_BIT                       5  /* CH5<5>: Channel 5 Alternate Disable.           */
#define DMACTRL_CHALTCLR_CH6_BIT                       6  /* CH6<6>: Channel 6 Alternate Disable.           */
#define DMACTRL_CHALTCLR_CH7_BIT                       7  /* CH7<7>: Channel 7 Alternate Disable.           */
#define DMACTRL_CHALTCLR_CH8_BIT                       8  /* CH8<8>: Channel 8 Alternate Disable.           */
#define DMACTRL_CHALTCLR_CH9_BIT                       9  /* CH9<9>: Channel 9 Alternate Disable.           */
#define DMACTRL_CHALTCLR_CH10_BIT                      10 /* CH10<10>: Channel 10 Alternate Disable.        */
#define DMACTRL_CHALTCLR_CH11_BIT                      11 /* CH11<11>: Channel 11 Alternate Disable.        */
#define DMACTRL_CHALTCLR_CH12_BIT                      12 /* CH12<12>: Channel 12 Alternate Disable.        */
#define DMACTRL_CHALTCLR_CH13_BIT                      13 /* CH13<13>: Channel 13 Alternate Disable.        */
#define DMACTRL_CHALTCLR_CH14_BIT                      14 /* CH14<14>: Channel 14 Alternate Disable.        */
#define DMACTRL_CHALTCLR_CH15_BIT                      15 /* CH15<15>: Channel 15 Alternate Disable.        */
#define DMACTRL_CHALTCLR_CH16_BIT                      16
#define DMACTRL_CHALTCLR_CH17_BIT                      17
#define DMACTRL_CHALTCLR_CH18_BIT                      18
#define DMACTRL_CHALTCLR_CH19_BIT                      19
#define DMACTRL_CHALTCLR_CH20_BIT                      20
#define DMACTRL_CHALTCLR_CH21_BIT                      21
#define DMACTRL_CHALTCLR_CH22_BIT                      22
#define DMACTRL_CHALTCLR_CH23_BIT                      23
#define DMACTRL_CHALTCLR_CH24_BIT                      24
#define DMACTRL_CHALTCLR_CH25_BIT                      25
#define DMACTRL_CHALTCLR_CH26_BIT                      26
#define DMACTRL_CHALTCLR_CH27_BIT                      27
#define DMACTRL_CHALTCLR_CH28_BIT                      28
#define DMACTRL_CHALTCLR_CH29_BIT                      29
#define DMACTRL_CHALTCLR_CH30_BIT                      30
#define DMACTRL_CHALTCLR_CH31_BIT                      31
#define DMACTRL_CHALTCLR_CH0_DS                        (1 << DMACTRL_CHALTCLR_CH0_BIT)
#define DMACTRL_CHALTCLR_CH1_DS                        (1 << DMACTRL_CHALTCLR_CH1_BIT)
#define DMACTRL_CHALTCLR_CH2_DS                        (1 << DMACTRL_CHALTCLR_CH2_BIT)
#define DMACTRL_CHALTCLR_CH3_DS                        (1 << DMACTRL_CHALTCLR_CH3_BIT)
#define DMACTRL_CHALTCLR_CH4_DS                        (1 << DMACTRL_CHALTCLR_CH4_BIT)
#define DMACTRL_CHALTCLR_CH5_DS                        (1 << DMACTRL_CHALTCLR_CH5_BIT)
#define DMACTRL_CHALTCLR_CH6_DS                        (1 << DMACTRL_CHALTCLR_CH6_BIT)
#define DMACTRL_CHALTCLR_CH7_DS                        (1 << DMACTRL_CHALTCLR_CH7_BIT)
#define DMACTRL_CHALTCLR_CH8_DS                        (1 << DMACTRL_CHALTCLR_CH8_BIT)
#define DMACTRL_CHALTCLR_CH9_DS                        (1 << DMACTRL_CHALTCLR_CH9_BIT)
#define DMACTRL_CHALTCLR_CH10_DS                       (1 << DMACTRL_CHALTCLR_CH10_BIT)
#define DMACTRL_CHALTCLR_CH11_DS                       (1 << DMACTRL_CHALTCLR_CH11_BIT)
#define DMACTRL_CHALTCLR_CH12_DS                       (1 << DMACTRL_CHALTCLR_CH12_BIT)
#define DMACTRL_CHALTCLR_CH13_DS                       (1 << DMACTRL_CHALTCLR_CH13_BIT)
#define DMACTRL_CHALTCLR_CH14_DS                       (1 << DMACTRL_CHALTCLR_CH14_BIT)
#define DMACTRL_CHALTCLR_CH15_DS                       (1 << DMACTRL_CHALTCLR_CH15_BIT)
#define DMACTRL_CHALTCLR_CH16_DS                       (1 << DMACTRL_CHALTCLR_CH16_BIT)
#define DMACTRL_CHALTCLR_CH17_DS                       (1 << DMACTRL_CHALTCLR_CH17_BIT)
#define DMACTRL_CHALTCLR_CH18_DS                       (1 << DMACTRL_CHALTCLR_CH18_BIT)
#define DMACTRL_CHALTCLR_CH19_DS                       (1 << DMACTRL_CHALTCLR_CH19_BIT)
#define DMACTRL_CHALTCLR_CH20_DS                       (1 << DMACTRL_CHALTCLR_CH20_BIT)
#define DMACTRL_CHALTCLR_CH21_DS                       (1 << DMACTRL_CHALTCLR_CH21_BIT)
#define DMACTRL_CHALTCLR_CH22_DS                       (1 << DMACTRL_CHALTCLR_CH22_BIT)
#define DMACTRL_CHALTCLR_CH23_DS                       (1 << DMACTRL_CHALTCLR_CH23_BIT)
#define DMACTRL_CHALTCLR_CH24_DS                       (1 << DMACTRL_CHALTCLR_CH24_BIT)
#define DMACTRL_CHALTCLR_CH25_DS                       (1 << DMACTRL_CHALTCLR_CH25_BIT)
#define DMACTRL_CHALTCLR_CH26_DS                       (1 << DMACTRL_CHALTCLR_CH26_BIT)
#define DMACTRL_CHALTCLR_CH27_DS                       (1 << DMACTRL_CHALTCLR_CH27_BIT)
#define DMACTRL_CHALTCLR_CH28_DS                       (1 << DMACTRL_CHALTCLR_CH28_BIT)
#define DMACTRL_CHALTCLR_CH29_DS                       (1 << DMACTRL_CHALTCLR_CH29_BIT)
#define DMACTRL_CHALTCLR_CH30_DS                       (1 << DMACTRL_CHALTCLR_CH30_BIT)
#define DMACTRL_CHALTCLR_CH31_DS                       (1U << DMACTRL_CHALTCLR_CH31_BIT)



#define DMACTRL_CHHPSET_CH0_MASK                       0x00000001
#define DMACTRL_CHHPSET_CH1_MASK                       0x00000002
#define DMACTRL_CHHPSET_CH2_MASK                       0x00000004
#define DMACTRL_CHHPSET_CH3_MASK                       0x00000008
#define DMACTRL_CHHPSET_CH4_MASK                       0x00000010
#define DMACTRL_CHHPSET_CH5_MASK                       0x00000020
#define DMACTRL_CHHPSET_CH6_MASK                       0x00000040
#define DMACTRL_CHHPSET_CH7_MASK                       0x00000080
#define DMACTRL_CHHPSET_CH8_MASK                       0x00000100
#define DMACTRL_CHHPSET_CH9_MASK                       0x00000200
#define DMACTRL_CHHPSET_CH10_MASK                      0x00000400
#define DMACTRL_CHHPSET_CH11_MASK                      0x00000800
#define DMACTRL_CHHPSET_CH12_MASK                      0x00001000
#define DMACTRL_CHHPSET_CH13_MASK                      0x00002000
#define DMACTRL_CHHPSET_CH14_MASK                      0x00004000
#define DMACTRL_CHHPSET_CH15_MASK                      0x00008000
#define DMACTRL_CHHPSET_CH16_MASK                      0x00010000
#define DMACTRL_CHHPSET_CH17_MASK                      0x00020000
#define DMACTRL_CHHPSET_CH18_MASK                      0x00040000
#define DMACTRL_CHHPSET_CH19_MASK                      0x00080000
#define DMACTRL_CHHPSET_CH20_MASK                      0x00100000
#define DMACTRL_CHHPSET_CH21_MASK                      0x00200000
#define DMACTRL_CHHPSET_CH22_MASK                      0x00400000
#define DMACTRL_CHHPSET_CH23_MASK                      0x00800000
#define DMACTRL_CHHPSET_CH24_MASK                      0x01000000
#define DMACTRL_CHHPSET_CH25_MASK                      0x02000000
#define DMACTRL_CHHPSET_CH26_MASK                      0x04000000
#define DMACTRL_CHHPSET_CH27_MASK                      0x08000000
#define DMACTRL_CHHPSET_CH28_MASK                      0x10000000
#define DMACTRL_CHHPSET_CH29_MASK                      0x20000000
#define DMACTRL_CHHPSET_CH30_MASK                      0x40000000
#define DMACTRL_CHHPSET_CH31_MASK                      0x80000000
#define DMACTRL_CHHPSET_CH0_BIT                        0  /* CH0<0>: Channel 0 High Priority Enable.        */
#define DMACTRL_CHHPSET_CH1_BIT                        1  /* CH1<1>: Channel 1 High Priority Enable.        */
#define DMACTRL_CHHPSET_CH2_BIT                        2  /* CH2<2>: Channel 2 High Priority Enable.        */
#define DMACTRL_CHHPSET_CH3_BIT                        3  /* CH3<3>: Channel 3 High Priority Enable.        */
#define DMACTRL_CHHPSET_CH4_BIT                        4  /* CH4<4>: Channel 4 High Priority Enable.        */
#define DMACTRL_CHHPSET_CH5_BIT                        5  /* CH5<5>: Channel 5 High Priority Enable.        */
#define DMACTRL_CHHPSET_CH6_BIT                        6  /* CH6<6>: Channel 6 High Priority Enable.        */
#define DMACTRL_CHHPSET_CH7_BIT                        7  /* CH7<7>: Channel 7 High Priority Enable.        */
#define DMACTRL_CHHPSET_CH8_BIT                        8  /* CH8<8>: Channel 8 High Priority Enable.        */
#define DMACTRL_CHHPSET_CH9_BIT                        9  /* CH9<9>: Channel 9 High Priority Enable.        */
#define DMACTRL_CHHPSET_CH10_BIT                       10 /* CH10<10>: Channel 10 High Priority Enable.     */
#define DMACTRL_CHHPSET_CH11_BIT                       11 /* CH11<11>: Channel 11 High Priority Enable.     */
#define DMACTRL_CHHPSET_CH12_BIT                       12 /* CH12<12>: Channel 12 High Priority Enable.     */
#define DMACTRL_CHHPSET_CH13_BIT                       13 /* CH13<13>: Channel 13 High Priority Enable.     */
#define DMACTRL_CHHPSET_CH14_BIT                       14 /* CH14<14>: Channel 14 High Priority Enable.     */
#define DMACTRL_CHHPSET_CH15_BIT                       15 /* CH15<15>: Channel 15 High Priority Enable.     */
#define DMACTRL_CHHPSET_CH16_BIT                       16
#define DMACTRL_CHHPSET_CH17_BIT                       17
#define DMACTRL_CHHPSET_CH18_BIT                       18
#define DMACTRL_CHHPSET_CH19_BIT                       19
#define DMACTRL_CHHPSET_CH20_BIT                       20
#define DMACTRL_CHHPSET_CH21_BIT                       21
#define DMACTRL_CHHPSET_CH22_BIT                       22
#define DMACTRL_CHHPSET_CH23_BIT                       23
#define DMACTRL_CHHPSET_CH24_BIT                       24
#define DMACTRL_CHHPSET_CH25_BIT                       25
#define DMACTRL_CHHPSET_CH26_BIT                       26
#define DMACTRL_CHHPSET_CH27_BIT                       27
#define DMACTRL_CHHPSET_CH28_BIT                       28
#define DMACTRL_CHHPSET_CH29_BIT                       29
#define DMACTRL_CHHPSET_CH30_BIT                       30
#define DMACTRL_CHHPSET_CH31_BIT                       31
#define DMACTRL_CHHPSET_CH0_EN                         (1 << DMACTRL_CHHPSET_CH0_BIT)
#define DMACTRL_CHHPSET_CH1_EN                         (1 << DMACTRL_CHHPSET_CH1_BIT)
#define DMACTRL_CHHPSET_CH2_EN                         (1 << DMACTRL_CHHPSET_CH2_BIT)
#define DMACTRL_CHHPSET_CH3_EN                         (1 << DMACTRL_CHHPSET_CH3_BIT)
#define DMACTRL_CHHPSET_CH4_EN                         (1 << DMACTRL_CHHPSET_CH4_BIT)
#define DMACTRL_CHHPSET_CH5_EN                         (1 << DMACTRL_CHHPSET_CH5_BIT)
#define DMACTRL_CHHPSET_CH6_EN                         (1 << DMACTRL_CHHPSET_CH6_BIT)
#define DMACTRL_CHHPSET_CH7_EN                         (1 << DMACTRL_CHHPSET_CH7_BIT)
#define DMACTRL_CHHPSET_CH8_EN                         (1 << DMACTRL_CHHPSET_CH8_BIT)
#define DMACTRL_CHHPSET_CH9_EN                         (1 << DMACTRL_CHHPSET_CH9_BIT)
#define DMACTRL_CHHPSET_CH10_EN                        (1 << DMACTRL_CHHPSET_CH10_BIT)
#define DMACTRL_CHHPSET_CH11_EN                        (1 << DMACTRL_CHHPSET_CH11_BIT)
#define DMACTRL_CHHPSET_CH12_EN                        (1 << DMACTRL_CHHPSET_CH12_BIT)
#define DMACTRL_CHHPSET_CH13_EN                        (1 << DMACTRL_CHHPSET_CH13_BIT)
#define DMACTRL_CHHPSET_CH14_EN                        (1 << DMACTRL_CHHPSET_CH14_BIT)
#define DMACTRL_CHHPSET_CH15_EN                        (1 << DMACTRL_CHHPSET_CH15_BIT)
#define DMACTRL_CHHPSET_CH16_EN                        (1 << DMACTRL_CHHPSET_CH16_BIT)
#define DMACTRL_CHHPSET_CH17_EN                        (1 << DMACTRL_CHHPSET_CH17_BIT)
#define DMACTRL_CHHPSET_CH18_EN                        (1 << DMACTRL_CHHPSET_CH18_BIT)
#define DMACTRL_CHHPSET_CH19_EN                        (1 << DMACTRL_CHHPSET_CH19_BIT)
#define DMACTRL_CHHPSET_CH20_EN                        (1 << DMACTRL_CHHPSET_CH20_BIT)
#define DMACTRL_CHHPSET_CH21_EN                        (1 << DMACTRL_CHHPSET_CH21_BIT)
#define DMACTRL_CHHPSET_CH22_EN                        (1 << DMACTRL_CHHPSET_CH22_BIT)
#define DMACTRL_CHHPSET_CH23_EN                        (1 << DMACTRL_CHHPSET_CH23_BIT)
#define DMACTRL_CHHPSET_CH24_EN                        (1 << DMACTRL_CHHPSET_CH24_BIT)
#define DMACTRL_CHHPSET_CH25_EN                        (1 << DMACTRL_CHHPSET_CH25_BIT)
#define DMACTRL_CHHPSET_CH26_EN                        (1 << DMACTRL_CHHPSET_CH26_BIT)
#define DMACTRL_CHHPSET_CH27_EN                        (1 << DMACTRL_CHHPSET_CH27_BIT)
#define DMACTRL_CHHPSET_CH28_EN                        (1 << DMACTRL_CHHPSET_CH28_BIT)
#define DMACTRL_CHHPSET_CH29_EN                        (1 << DMACTRL_CHHPSET_CH29_BIT)
#define DMACTRL_CHHPSET_CH30_EN                        (1 << DMACTRL_CHHPSET_CH30_BIT)
#define DMACTRL_CHHPSET_CH31_EN                        (1U << DMACTRL_CHHPSET_CH31_BIT)


#define DMACTRL_CHHPCLR_CH0_MASK                       0x00000001
#define DMACTRL_CHHPCLR_CH1_MASK                       0x00000002
#define DMACTRL_CHHPCLR_CH2_MASK                       0x00000004
#define DMACTRL_CHHPCLR_CH3_MASK                       0x00000008
#define DMACTRL_CHHPCLR_CH4_MASK                       0x00000010
#define DMACTRL_CHHPCLR_CH5_MASK                       0x00000020
#define DMACTRL_CHHPCLR_CH6_MASK                       0x00000040
#define DMACTRL_CHHPCLR_CH7_MASK                       0x00000080
#define DMACTRL_CHHPCLR_CH8_MASK                       0x00000100
#define DMACTRL_CHHPCLR_CH9_MASK                       0x00000200
#define DMACTRL_CHHPCLR_CH10_MASK                      0x00000400
#define DMACTRL_CHHPCLR_CH11_MASK                      0x00000800
#define DMACTRL_CHHPCLR_CH12_MASK                      0x00001000
#define DMACTRL_CHHPCLR_CH13_MASK                      0x00002000
#define DMACTRL_CHHPCLR_CH14_MASK                      0x00004000
#define DMACTRL_CHHPCLR_CH15_MASK                      0x00008000
#define DMACTRL_CHHPCLR_CH16_MASK                      0x00010000
#define DMACTRL_CHHPCLR_CH17_MASK                      0x00020000
#define DMACTRL_CHHPCLR_CH18_MASK                      0x00040000
#define DMACTRL_CHHPCLR_CH19_MASK                      0x00080000
#define DMACTRL_CHHPCLR_CH20_MASK                      0x00100000
#define DMACTRL_CHHPCLR_CH21_MASK                      0x00200000
#define DMACTRL_CHHPCLR_CH22_MASK                      0x00400000
#define DMACTRL_CHHPCLR_CH23_MASK                      0x00800000
#define DMACTRL_CHHPCLR_CH24_MASK                      0x01000000
#define DMACTRL_CHHPCLR_CH25_MASK                      0x02000000
#define DMACTRL_CHHPCLR_CH26_MASK                      0x04000000
#define DMACTRL_CHHPCLR_CH27_MASK                      0x08000000
#define DMACTRL_CHHPCLR_CH28_MASK                      0x10000000
#define DMACTRL_CHHPCLR_CH29_MASK                      0x20000000
#define DMACTRL_CHHPCLR_CH30_MASK                      0x40000000
#define DMACTRL_CHHPCLR_CH31_MASK                      0x80000000
#define DMACTRL_CHHPCLR_CH0_BIT                        0  /* CH0<0>: Channel 0 High Priority Disable.       */
#define DMACTRL_CHHPCLR_CH1_BIT                        1  /* CH1<1>: Channel 1 High Priority Disable.       */
#define DMACTRL_CHHPCLR_CH2_BIT                        2  /* CH2<2>: Channel 2 High Priority Disable.       */
#define DMACTRL_CHHPCLR_CH3_BIT                        3  /* CH3<3>: Channel 3 High Priority Disable.       */
#define DMACTRL_CHHPCLR_CH4_BIT                        4  /* CH4<4>: Channel 4 High Priority Disable.       */
#define DMACTRL_CHHPCLR_CH5_BIT                        5  /* CH5<5>: Channel 5 High Priority Disable.       */
#define DMACTRL_CHHPCLR_CH6_BIT                        6  /* CH6<6>: Channel 6 High Priority Disable.       */
#define DMACTRL_CHHPCLR_CH7_BIT                        7  /* CH7<7>: Channel 7 High Priority Disable.       */
#define DMACTRL_CHHPCLR_CH8_BIT                        8  /* CH8<8>: Channel 8 High Priority Disable.       */
#define DMACTRL_CHHPCLR_CH9_BIT                        9  /* CH9<9>: Channel 9 High Priority Disable.       */
#define DMACTRL_CHHPCLR_CH10_BIT                       10 /* CH10<10>: Channel 10 High Priority Disable.    */
#define DMACTRL_CHHPCLR_CH11_BIT                       11 /* CH11<11>: Channel 11 High Priority Disable.    */
#define DMACTRL_CHHPCLR_CH12_BIT                       12 /* CH12<12>: Channel 12 High Priority Disable.    */
#define DMACTRL_CHHPCLR_CH13_BIT                       13 /* CH13<13>: Channel 13 High Priority Disable.    */
#define DMACTRL_CHHPCLR_CH14_BIT                       14 /* CH14<14>: Channel 14 High Priority Disable.    */
#define DMACTRL_CHHPCLR_CH15_BIT                       15 /* CH15<15>: Channel 15 High Priority Disable.    */
#define DMACTRL_CHHPCLR_CH16_BIT                       16
#define DMACTRL_CHHPCLR_CH17_BIT                       17
#define DMACTRL_CHHPCLR_CH18_BIT                       18
#define DMACTRL_CHHPCLR_CH19_BIT                       19
#define DMACTRL_CHHPCLR_CH20_BIT                       20
#define DMACTRL_CHHPCLR_CH21_BIT                       21
#define DMACTRL_CHHPCLR_CH22_BIT                       22
#define DMACTRL_CHHPCLR_CH23_BIT                       23
#define DMACTRL_CHHPCLR_CH24_BIT                       24
#define DMACTRL_CHHPCLR_CH25_BIT                       25
#define DMACTRL_CHHPCLR_CH26_BIT                       26
#define DMACTRL_CHHPCLR_CH27_BIT                       27
#define DMACTRL_CHHPCLR_CH28_BIT                       28
#define DMACTRL_CHHPCLR_CH29_BIT                       29
#define DMACTRL_CHHPCLR_CH30_BIT                       30
#define DMACTRL_CHHPCLR_CH31_BIT                       31
#define DMACTRL_CHHPCLR_CH0_DS                         (1 << DMACTRL_CHHPCLR_CH0_BIT)
#define DMACTRL_CHHPCLR_CH1_DS                         (1 << DMACTRL_CHHPCLR_CH1_BIT)
#define DMACTRL_CHHPCLR_CH2_DS                         (1 << DMACTRL_CHHPCLR_CH2_BIT)
#define DMACTRL_CHHPCLR_CH3_DS                         (1 << DMACTRL_CHHPCLR_CH3_BIT)
#define DMACTRL_CHHPCLR_CH4_DS                         (1 << DMACTRL_CHHPCLR_CH4_BIT)
#define DMACTRL_CHHPCLR_CH5_DS                         (1 << DMACTRL_CHHPCLR_CH5_BIT)
#define DMACTRL_CHHPCLR_CH6_DS                         (1 << DMACTRL_CHHPCLR_CH6_BIT)
#define DMACTRL_CHHPCLR_CH7_DS                         (1 << DMACTRL_CHHPCLR_CH7_BIT)
#define DMACTRL_CHHPCLR_CH8_DS                         (1 << DMACTRL_CHHPCLR_CH8_BIT)
#define DMACTRL_CHHPCLR_CH9_DS                         (1 << DMACTRL_CHHPCLR_CH9_BIT)
#define DMACTRL_CHHPCLR_CH10_DS                        (1 << DMACTRL_CHHPCLR_CH10_BIT)
#define DMACTRL_CHHPCLR_CH11_DS                        (1 << DMACTRL_CHHPCLR_CH11_BIT)
#define DMACTRL_CHHPCLR_CH12_DS                        (1 << DMACTRL_CHHPCLR_CH12_BIT)
#define DMACTRL_CHHPCLR_CH13_DS                        (1 << DMACTRL_CHHPCLR_CH13_BIT)
#define DMACTRL_CHHPCLR_CH14_DS                        (1 << DMACTRL_CHHPCLR_CH14_BIT)
#define DMACTRL_CHHPCLR_CH15_DS                        (1 << DMACTRL_CHHPCLR_CH15_BIT)
#define DMACTRL_CHHPCLR_CH16_DS                        (1 << DMACTRL_CHHPCLR_CH16_BIT)
#define DMACTRL_CHHPCLR_CH17_DS                        (1 << DMACTRL_CHHPCLR_CH17_BIT)
#define DMACTRL_CHHPCLR_CH18_DS                        (1 << DMACTRL_CHHPCLR_CH18_BIT)
#define DMACTRL_CHHPCLR_CH19_DS                        (1 << DMACTRL_CHHPCLR_CH19_BIT)
#define DMACTRL_CHHPCLR_CH20_DS                        (1 << DMACTRL_CHHPCLR_CH20_BIT)
#define DMACTRL_CHHPCLR_CH21_DS                        (1 << DMACTRL_CHHPCLR_CH21_BIT)
#define DMACTRL_CHHPCLR_CH22_DS                        (1 << DMACTRL_CHHPCLR_CH22_BIT)
#define DMACTRL_CHHPCLR_CH23_DS                        (1 << DMACTRL_CHHPCLR_CH23_BIT)
#define DMACTRL_CHHPCLR_CH24_DS                        (1 << DMACTRL_CHHPCLR_CH24_BIT)
#define DMACTRL_CHHPCLR_CH25_DS                        (1 << DMACTRL_CHHPCLR_CH25_BIT)
#define DMACTRL_CHHPCLR_CH26_DS                        (1 << DMACTRL_CHHPCLR_CH26_BIT)
#define DMACTRL_CHHPCLR_CH27_DS                        (1 << DMACTRL_CHHPCLR_CH27_BIT)
#define DMACTRL_CHHPCLR_CH28_DS                        (1 << DMACTRL_CHHPCLR_CH28_BIT)
#define DMACTRL_CHHPCLR_CH29_DS                        (1 << DMACTRL_CHHPCLR_CH29_BIT)
#define DMACTRL_CHHPCLR_CH30_DS                        (1 << DMACTRL_CHHPCLR_CH30_BIT)
#define DMACTRL_CHHPCLR_CH31_DS                        (1U << DMACTRL_CHHPCLR_CH31_BIT)

#define DMACTRL_BERRCLR_ERROR_MASK                     0x00000001
#define DMACTRL_BERRCLR_ERROR_BIT                      0  /* ERROR<0>: DMA Bus Error Clear.                 */
#define DMACTRL_BERRCLR_ERROR_CLEAR                    (1 << DMACTRL_BERRCLR_ERROR_BIT)


typedef struct dma_tube_reg_map
{
   volatile uint32_t SRCEND         ; // Base Address + 0x0
   volatile uint32_t DSTEND         ; // Base Address + 0x4
   volatile uint32_t CONFIG         ; // Base Address + 0x8
   uint32_t          reserved0;
} dma_tube_reg_map;

#define DMADESC_SRCEND_MASK                            0xFFFFFFFF
#define DMADESC_SRCEND_BIT                             0

#define DMADESC_DSTEND_MASK                            0xFFFFFFFF
#define DMADESC_DSTEND_BIT                             0

#define DMADESC_CFGR_TMD_MASK                          0x00000007
#define DMADESC_CFGR_NCOUNT_MASK                       0x00003FF0
#define DMADESC_CFGR_RPOWER_MASK                       0x0003C000
#define DMADESC_CFGR_SRCSIZE_MASK                      0x03000000
#define DMADESC_CFGR_SRCAIMD_MASK                      0x0C000000
#define DMADESC_CFGR_DSTSIZE_MASK                      0x30000000
#define DMADESC_CFGR_DSTAIMD_MASK                      0xC0000000
#define DMADESC_CFGR_TMD_BIT                           0
#define DMADESC_CFGR_NCOUNT_BIT                        4
#define DMADESC_CFGR_RPOWER_BIT                        14
#define DMADESC_CFGR_SRCSIZE_BIT                       24
#define DMADESC_CFGR_SRCAIMD_BIT                       26
#define DMADESC_CFGR_DSTSIZE_BIT                       28
#define DMADESC_CFGR_DSTAIMD_BIT                       30
#define DMACTRL_CFGR_DMAEN_DS                          (0 << DMACTRL_CFGR_DMAEN_BIT)
#define DMACTRL_CFGR_DMAEN_EN                          (1 << DMACTRL_CFGR_DMAEN_BIT)
#define DMADESC_CFGR_TMD_STOP                          (0 << DMADESC_CFGR_TMD_BIT)
#define DMADESC_CFGR_TMD_BASIC                         (1 << DMADESC_CFGR_TMD_BIT)
#define DMADESC_CFGR_TMD_AUTO_REQUEST                  (2 << DMADESC_CFGR_TMD_BIT)
#define DMADESC_CFGR_TMD_PING_PONG                     (3 << DMADESC_CFGR_TMD_BIT)
#define DMADESC_CFGR_TMD_MEMORY_SCATTER_GATHER_P       (4 << DMADESC_CFGR_TMD_BIT)
#define DMADESC_CFGR_TMD_MEMORY_SCATTER_GATHER         (5 << DMADESC_CFGR_TMD_BIT)
#define DMADESC_CFGR_TMD_PERIPHERAL_SCATTER_GATHER_P   (6 << DMADESC_CFGR_TMD_BIT)
#define DMADESC_CFGR_TMD_PERIPHERAL_SCATTER_GATHER     (7 << DMADESC_CFGR_TMD_BIT)
#define DMADESC_CFGR_SRCSIZE_BYTE                      (0 << DMADESC_CFGR_SRCSIZE_BIT)
#define DMADESC_CFGR_SRCSIZE_HALF_WORD                 (1 << DMADESC_CFGR_SRCSIZE_BIT)
#define DMADESC_CFGR_SRCSIZE_WORD                      (2 << DMADESC_CFGR_SRCSIZE_BIT)
#define DMADESC_CFGR_SRCAIMD_BYTE                      (0 << DMADESC_CFGR_SRCAIMD_BIT)
#define DMADESC_CFGR_SRCAIMD_HALF_WORD                 (1 << DMADESC_CFGR_SRCAIMD_BIT)
#define DMADESC_CFGR_SRCAIMD_WORD                      (2 << DMADESC_CFGR_SRCAIMD_BIT)
#define DMADESC_CFGR_SRCAIMD_NO_INCREMENT              (3 << DMADESC_CFGR_SRCAIMD_BIT)
#define DMADESC_CFGR_DSTSIZE_BYTE                      (0 << DMADESC_CFGR_DSTSIZE_BIT)
#define DMADESC_CFGR_DSTSIZE_HALF_WORD                 (1 << DMADESC_CFGR_DSTSIZE_BIT)
#define DMADESC_CFGR_DSTSIZE_WORD                      (2 << DMADESC_CFGR_DSTSIZE_BIT)
#define DMADESC_CFGR_DSTAIMD_BYTE                      (0U << DMADESC_CFGR_DSTAIMD_BIT)
#define DMADESC_CFGR_DSTAIMD_HALF_WORD                 (1U << DMADESC_CFGR_DSTAIMD_BIT)
#define DMADESC_CFGR_DSTAIMD_WORD                      (2U << DMADESC_CFGR_DSTAIMD_BIT)
#define DMADESC_CFGR_DSTAIMD_NO_INCREMENT              (3U << DMADESC_CFGR_DSTAIMD_BIT)


typedef struct dma_xbar_reg_map
{
   volatile uint32_t DMAXBAR0       ; // Base Address + 0x0
   volatile uint32_t DMAXBAR0_SET;
   volatile uint32_t DMAXBAR0_CLR;
   uint32_t          reserved0;
   volatile uint32_t DMAXBAR1       ; // Base Address + 0x10
   volatile uint32_t DMAXBAR1_SET;
   volatile uint32_t DMAXBAR1_CLR;
   uint32_t          reserved1;
} dma_xbar_reg_map;

#define DMA1_XBAR_BASE = ((dma_xbar_reg_map*)0x40037000);

#define DMAXBAR_DMAXBAR0_CH0SEL_MASK           0x0000000F
#define DMAXBAR_DMAXBAR0_CH1SEL_MASK           0x000000F0
#define DMAXBAR_DMAXBAR0_CH2SEL_MASK           0x00000F00
#define DMAXBAR_DMAXBAR0_CH3SEL_MASK           0x0000F000
#define DMAXBAR_DMAXBAR0_CH4SEL_MASK           0x000F0000
#define DMAXBAR_DMAXBAR0_CH5SEL_MASK           0x00F00000
#define DMAXBAR_DMAXBAR0_CH6SEL_MASK           0x0F000000
#define DMAXBAR_DMAXBAR0_CH7SEL_MASK           0xF0000000
#define DMAXBAR_DMAXBAR1_CH8SEL_MASK           0x0000000F
#define DMAXBAR_DMAXBAR1_CH9SEL_MASK           0x000000F0
#define DMAXBAR_DMAXBAR1_CH10SEL_MASK          0x00000F00
#define DMAXBAR_DMAXBAR1_CH11SEL_MASK          0x0000F000
#define DMAXBAR_DMAXBAR1_CH12SEL_MASK          0x000F0000
#define DMAXBAR_DMAXBAR1_CH13SEL_MASK          0x00F00000
#define DMAXBAR_DMAXBAR1_CH14SEL_MASK          0x0F000000
#define DMAXBAR_DMAXBAR1_CH15SEL_MASK          0xF0000000
#define DMAXBAR_DMAXBAR0_CH0SEL_BIT            0  /* CH0SEL<3:0>: DMA Channel 0 Peripheral Select.  */
#define DMAXBAR_DMAXBAR0_CH1SEL_BIT            4  /* CH1SEL<7:4>: DMA Channel 1 Peripheral Select.  */
#define DMAXBAR_DMAXBAR0_CH2SEL_BIT            8  /* CH2SEL<11:8>: DMA Channel 2 Peripheral Select. */
#define DMAXBAR_DMAXBAR0_CH3SEL_BIT            12 /* CH3SEL<15:12>: DMA Channel 3 Peripheral Select. */
#define DMAXBAR_DMAXBAR0_CH4SEL_BIT            16 /* CH4SEL<19:16>: DMA Channel 4 Peripheral Select. */
#define DMAXBAR_DMAXBAR0_CH5SEL_BIT            20 /* CH5SEL<23:20>: DMA Channel 5 Peripheral Select. */
#define DMAXBAR_DMAXBAR0_CH6SEL_BIT            24 /* CH6SEL<27:24>: DMA Channel 6 Peripheral Select. */
#define DMAXBAR_DMAXBAR0_CH7SEL_BIT            28 /* CH7SEL<31:28>: DMA Channel 7 Peripheral Select. */
#define DMAXBAR_DMAXBAR1_CH8SEL_BIT            0  /* CH8SEL<3:0>: DMA Channel 8 Peripheral Select.  */
#define DMAXBAR_DMAXBAR1_CH9SEL_BIT            4  /* CH9SEL<7:4>: DMA Channel 9 Peripheral Select.  */
#define DMAXBAR_DMAXBAR1_CH10SEL_BIT           8  /* CH10SEL<11:8>: DMA Channel 10 Peripheral Select. */
#define DMAXBAR_DMAXBAR1_CH11SEL_BIT           12 /* CH11SEL<15:12>: DMA Channel 11 Peripheral Select. */
#define DMAXBAR_DMAXBAR1_CH12SEL_BIT           16 /* CH12SEL<19:16>: DMA Channel 12 Peripheral Select. */
#define DMAXBAR_DMAXBAR1_CH13SEL_BIT           20 /* CH13SEL<23:20>: DMA Channel 13 Peripheral Select. */
#define DMAXBAR_DMAXBAR1_CH14SEL_BIT           24 /* CH14SEL<27:24>: DMA Channel 14 Peripheral Select. */
#define DMAXBAR_DMAXBAR1_CH15SEL_BIT           28 /* CH15SEL<31:28>: DMA Channel 15 Peripheral Select. */
#define DMAXBAR_DMAXBAR0_CH0SEL_USB0_EP4_OUT   (0 << DMAXBAR_DMAXBAR0_CH0SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH0SEL_SPI1_RX        (1 << DMAXBAR_DMAXBAR0_CH0SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH0SEL_USART0_RX      (2 << DMAXBAR_DMAXBAR0_CH0SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH0SEL_I2C0_TX        (3 << DMAXBAR_DMAXBAR0_CH0SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH0SEL_DMA0T0_RISE    (4 << DMAXBAR_DMAXBAR0_CH0SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH0SEL_DMA0T0_FALL    (5 << DMAXBAR_DMAXBAR0_CH0SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH0SEL_DMA0T1_RISE    (6 << DMAXBAR_DMAXBAR0_CH0SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH0SEL_DMA0T1_FALL    (7 << DMAXBAR_DMAXBAR0_CH0SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH0SEL_TIMER0L        (8 << DMAXBAR_DMAXBAR0_CH0SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH0SEL_TIMER0H        (9 << DMAXBAR_DMAXBAR0_CH0SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH0SEL_TIMER1L        (10 << DMAXBAR_DMAXBAR0_CH0SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH0SEL_TIMER1H        (11 << DMAXBAR_DMAXBAR0_CH0SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH1SEL_USB0_EP3_OUT   (0 << DMAXBAR_DMAXBAR0_CH1SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH1SEL_SPI0_RX        (1 << DMAXBAR_DMAXBAR0_CH1SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH1SEL_USART1_RX      (2 << DMAXBAR_DMAXBAR0_CH1SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH1SEL_I2C0_RX        (3 << DMAXBAR_DMAXBAR0_CH1SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH1SEL_IDAC1          (4 << DMAXBAR_DMAXBAR0_CH1SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH1SEL_EPCA0_CONTROL  (5 << DMAXBAR_DMAXBAR0_CH1SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH1SEL_DMA0T0_RISE    (6 << DMAXBAR_DMAXBAR0_CH1SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH1SEL_DMA0T0_FALL    (7 << DMAXBAR_DMAXBAR0_CH1SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH1SEL_DMA0T1_RISE    (8 << DMAXBAR_DMAXBAR0_CH1SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH1SEL_DMA0T1_FALL    (9 << DMAXBAR_DMAXBAR0_CH1SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH1SEL_TIMER0L        (10 << DMAXBAR_DMAXBAR0_CH1SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH1SEL_TIMER1L        (11 << DMAXBAR_DMAXBAR0_CH1SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH1SEL_TIMER1H        (12 << DMAXBAR_DMAXBAR0_CH1SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH2SEL_USB0_EP2_OUT   (0 << DMAXBAR_DMAXBAR0_CH2SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH2SEL_SPI0_TX        (1 << DMAXBAR_DMAXBAR0_CH2SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH2SEL_USART0_TX      (2 << DMAXBAR_DMAXBAR0_CH2SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH2SEL_SARADC0        (3 << DMAXBAR_DMAXBAR0_CH2SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH2SEL_IDAC1          (4 << DMAXBAR_DMAXBAR0_CH2SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH2SEL_I2S0_TX        (5 << DMAXBAR_DMAXBAR0_CH2SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH2SEL_EPCA0_CONTROL  (6 << DMAXBAR_DMAXBAR0_CH2SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH2SEL_DMA0T0_RISE    (7 << DMAXBAR_DMAXBAR0_CH2SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH2SEL_DMA0T0_FALL    (8 << DMAXBAR_DMAXBAR0_CH2SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH2SEL_DMA0T1_RISE    (9 << DMAXBAR_DMAXBAR0_CH2SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH2SEL_DMA0T1_FALL    (10 << DMAXBAR_DMAXBAR0_CH2SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH3SEL_USB0_EP1_OUT   (0 << DMAXBAR_DMAXBAR0_CH3SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH3SEL_SARADC1        (1 << DMAXBAR_DMAXBAR0_CH3SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH3SEL_IDAC0          (2 << DMAXBAR_DMAXBAR0_CH3SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH3SEL_I2S0_TX        (3 << DMAXBAR_DMAXBAR0_CH3SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH3SEL_EPCA0_CAPTURE  (4 << DMAXBAR_DMAXBAR0_CH3SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH3SEL_DMA0T0_RISE    (5 << DMAXBAR_DMAXBAR0_CH3SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH3SEL_DMA0T0_FALL    (6 << DMAXBAR_DMAXBAR0_CH3SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH3SEL_DMA0T1_RISE    (7 << DMAXBAR_DMAXBAR0_CH3SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH3SEL_DMA0T1_FALL    (8 << DMAXBAR_DMAXBAR0_CH3SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH3SEL_TIMER1H        (9 << DMAXBAR_DMAXBAR0_CH3SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH4SEL_USB0_EP4_IN    (0 << DMAXBAR_DMAXBAR0_CH4SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH4SEL_SPI1_TX        (1 << DMAXBAR_DMAXBAR0_CH4SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH4SEL_USART0_TX      (2 << DMAXBAR_DMAXBAR0_CH4SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH4SEL_SARADC0        (3 << DMAXBAR_DMAXBAR0_CH4SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH4SEL_I2S0_RX        (4 << DMAXBAR_DMAXBAR0_CH4SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH4SEL_EPCA0_CAPTURE  (5 << DMAXBAR_DMAXBAR0_CH4SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH4SEL_DMA0T0_RISE    (6 << DMAXBAR_DMAXBAR0_CH4SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH4SEL_DMA0T0_FALL    (7 << DMAXBAR_DMAXBAR0_CH4SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH4SEL_DMA0T1_RISE    (8 << DMAXBAR_DMAXBAR0_CH4SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH4SEL_DMA0T1_FALL    (9 << DMAXBAR_DMAXBAR0_CH4SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH4SEL_TIMER0H        (10 << DMAXBAR_DMAXBAR0_CH4SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH5SEL_USB0_EP3_IN    (0 << DMAXBAR_DMAXBAR0_CH5SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH5SEL_AES0_TX        (1 << DMAXBAR_DMAXBAR0_CH5SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH5SEL_USART1_TX      (2 << DMAXBAR_DMAXBAR0_CH5SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH5SEL_SARADC0        (3 << DMAXBAR_DMAXBAR0_CH5SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH5SEL_I2S0_RX        (4 << DMAXBAR_DMAXBAR0_CH5SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH5SEL_DMA0T0_RISE    (5 << DMAXBAR_DMAXBAR0_CH5SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH5SEL_DMA0T0_FALL    (6 << DMAXBAR_DMAXBAR0_CH5SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH5SEL_DMA0T1_RISE    (7 << DMAXBAR_DMAXBAR0_CH5SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH5SEL_DMA0T1_FALL    (8 << DMAXBAR_DMAXBAR0_CH5SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH6SEL_USB0_EP2_IN    (0 << DMAXBAR_DMAXBAR0_CH6SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH6SEL_AES0_RX        (1 << DMAXBAR_DMAXBAR0_CH6SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH6SEL_USART0_RX      (2 << DMAXBAR_DMAXBAR0_CH6SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH6SEL_I2C0_RX        (3 << DMAXBAR_DMAXBAR0_CH6SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH6SEL_IDAC0          (4 << DMAXBAR_DMAXBAR0_CH6SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH6SEL_DMA0T0_RISE    (5 << DMAXBAR_DMAXBAR0_CH6SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH6SEL_DMA0T0_FALL    (6 << DMAXBAR_DMAXBAR0_CH6SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH6SEL_DMA0T1_RISE    (7 << DMAXBAR_DMAXBAR0_CH6SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH6SEL_DMA0T1_FALL    (8 << DMAXBAR_DMAXBAR0_CH6SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH6SEL_TIMER0H        (9 << DMAXBAR_DMAXBAR0_CH6SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH7SEL_USB0_EP1_IN    (0U << DMAXBAR_DMAXBAR0_CH7SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH7SEL_AES0_XOR       (1U << DMAXBAR_DMAXBAR0_CH7SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH7SEL_SPI1_TX        (2U << DMAXBAR_DMAXBAR0_CH7SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH7SEL_USART0_TX      (3U << DMAXBAR_DMAXBAR0_CH7SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH7SEL_DMA0T0_RISE    (4U << DMAXBAR_DMAXBAR0_CH7SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH7SEL_DMA0T0_FALL    (5U << DMAXBAR_DMAXBAR0_CH7SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH7SEL_DMA0T1_RISE    (6U << DMAXBAR_DMAXBAR0_CH7SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH7SEL_DMA0T1_FALL    (7U << DMAXBAR_DMAXBAR0_CH7SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH7SEL_TIMER0L        (8U << DMAXBAR_DMAXBAR0_CH7SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH7SEL_TIMER1L        (9U << DMAXBAR_DMAXBAR0_CH7SEL_BIT)
#define DMAXBAR_DMAXBAR0_CH7SEL_TIMER1H        (10U << DMAXBAR_DMAXBAR0_CH7SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH8SEL_USB0_EP4_OUT   (0 << DMAXBAR_DMAXBAR1_CH8SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH8SEL_USART1_RX      (1 << DMAXBAR_DMAXBAR1_CH8SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH8SEL_SPI1_RX        (2 << DMAXBAR_DMAXBAR1_CH8SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH8SEL_USART0_RX      (3 << DMAXBAR_DMAXBAR1_CH8SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH8SEL_EPCA0_CAPTURE  (4 << DMAXBAR_DMAXBAR1_CH8SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH8SEL_DMA0T0_RISE    (5 << DMAXBAR_DMAXBAR1_CH8SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH8SEL_DMA0T0_FALL    (6 << DMAXBAR_DMAXBAR1_CH8SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH8SEL_DMA0T1_RISE    (7 << DMAXBAR_DMAXBAR1_CH8SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH8SEL_DMA0T1_FALL    (8 << DMAXBAR_DMAXBAR1_CH8SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH9SEL_USB0_EP3_OUT   (0 << DMAXBAR_DMAXBAR1_CH9SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH9SEL_USART1_TX      (1 << DMAXBAR_DMAXBAR1_CH9SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH9SEL_I2C0_TX        (2 << DMAXBAR_DMAXBAR1_CH9SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH9SEL_EPCA0_CAPTURE  (3 << DMAXBAR_DMAXBAR1_CH9SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH9SEL_DMA0T0_RISE    (4 << DMAXBAR_DMAXBAR1_CH9SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH9SEL_DMA0T0_FALL    (5 << DMAXBAR_DMAXBAR1_CH9SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH9SEL_DMA0T1_RISE    (6 << DMAXBAR_DMAXBAR1_CH9SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH9SEL_DMA0T1_FALL    (7 << DMAXBAR_DMAXBAR1_CH9SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH9SEL_TIMER0H        (8 << DMAXBAR_DMAXBAR1_CH9SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH10SEL_USB0_EP2_OUT  (0 << DMAXBAR_DMAXBAR1_CH10SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH10SEL_AES0_TX       (1 << DMAXBAR_DMAXBAR1_CH10SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH10SEL_SARADC1       (2 << DMAXBAR_DMAXBAR1_CH10SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH10SEL_I2S0_RX       (3 << DMAXBAR_DMAXBAR1_CH10SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH10SEL_DMA0T0_RISE   (4 << DMAXBAR_DMAXBAR1_CH10SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH10SEL_DMA0T0_FALL   (5 << DMAXBAR_DMAXBAR1_CH10SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH10SEL_DMA0T1_RISE   (6 << DMAXBAR_DMAXBAR1_CH10SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH10SEL_DMA0T1_FALL   (7 << DMAXBAR_DMAXBAR1_CH10SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH10SEL_TIMER1H       (8 << DMAXBAR_DMAXBAR1_CH10SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH11SEL_USB0_EP1_OUT  (0 << DMAXBAR_DMAXBAR1_CH11SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH11SEL_AES0_RX       (1 << DMAXBAR_DMAXBAR1_CH11SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH11SEL_USART1_RX     (2 << DMAXBAR_DMAXBAR1_CH11SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH11SEL_USART0_RX     (3 << DMAXBAR_DMAXBAR1_CH11SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH11SEL_I2C0_RX       (4 << DMAXBAR_DMAXBAR1_CH11SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH11SEL_I2S0_RX       (5 << DMAXBAR_DMAXBAR1_CH11SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH11SEL_DMA0T0_RISE   (6 << DMAXBAR_DMAXBAR1_CH11SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH11SEL_DMA0T0_FALL   (7 << DMAXBAR_DMAXBAR1_CH11SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH11SEL_DMA0T1_RISE   (8 << DMAXBAR_DMAXBAR1_CH11SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH11SEL_DMA0T1_FALL   (9 << DMAXBAR_DMAXBAR1_CH11SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH11SEL_TIMER0H       (10 << DMAXBAR_DMAXBAR1_CH11SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH12SEL_USB0_EP4_IN   (0 << DMAXBAR_DMAXBAR1_CH12SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH12SEL_AES0_XOR      (1 << DMAXBAR_DMAXBAR1_CH12SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH12SEL_USART1_TX     (2 << DMAXBAR_DMAXBAR1_CH12SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH12SEL_SPI1_TX       (3 << DMAXBAR_DMAXBAR1_CH12SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH12SEL_IDAC1         (4 << DMAXBAR_DMAXBAR1_CH12SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH12SEL_I2S0_TX       (5 << DMAXBAR_DMAXBAR1_CH12SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH12SEL_DMA0T0_RISE   (6 << DMAXBAR_DMAXBAR1_CH12SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH12SEL_DMA0T0_FALL   (7 << DMAXBAR_DMAXBAR1_CH12SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH12SEL_DMA0T1_RISE   (8 << DMAXBAR_DMAXBAR1_CH12SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH12SEL_DMA0T1_FALL   (9 << DMAXBAR_DMAXBAR1_CH12SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH12SEL_TIMER0L       (10 << DMAXBAR_DMAXBAR1_CH12SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH12SEL_TIMER1L       (11 << DMAXBAR_DMAXBAR1_CH12SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH12SEL_TIMER1H       (12 << DMAXBAR_DMAXBAR1_CH12SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH13SEL_USB0_EP3_IN   (0 << DMAXBAR_DMAXBAR1_CH13SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH13SEL_SPI0_RX       (1 << DMAXBAR_DMAXBAR1_CH13SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH13SEL_USART0_RX     (2 << DMAXBAR_DMAXBAR1_CH13SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH13SEL_IDAC1         (3 << DMAXBAR_DMAXBAR1_CH13SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH13SEL_I2S0_TX       (4 << DMAXBAR_DMAXBAR1_CH13SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH13SEL_DMA0T0_RISE   (5 << DMAXBAR_DMAXBAR1_CH13SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH13SEL_DMA0T0_FALL   (6 << DMAXBAR_DMAXBAR1_CH13SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH13SEL_DMA0T1_RISE   (7 << DMAXBAR_DMAXBAR1_CH13SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH13SEL_DMA0T1_FALL   (8 << DMAXBAR_DMAXBAR1_CH13SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH13SEL_TIMER0H       (9 << DMAXBAR_DMAXBAR1_CH13SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH14SEL_USB0_EP2_IN   (0 << DMAXBAR_DMAXBAR1_CH14SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH14SEL_SPI0_TX       (1 << DMAXBAR_DMAXBAR1_CH14SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH14SEL_USART0_TX     (2 << DMAXBAR_DMAXBAR1_CH14SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH14SEL_IDAC0         (3 << DMAXBAR_DMAXBAR1_CH14SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH14SEL_EPCA0_CONTROL (4 << DMAXBAR_DMAXBAR1_CH14SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH14SEL_DMA0T0_RISE   (5 << DMAXBAR_DMAXBAR1_CH14SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH14SEL_DMA0T0_FALL   (6 << DMAXBAR_DMAXBAR1_CH14SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH14SEL_DMA0T1_RISE   (7 << DMAXBAR_DMAXBAR1_CH14SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH14SEL_DMA0T1_FALL   (8 << DMAXBAR_DMAXBAR1_CH14SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH14SEL_TIMER0L       (9 << DMAXBAR_DMAXBAR1_CH14SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH14SEL_TIMER1L       (10 << DMAXBAR_DMAXBAR1_CH14SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH15SEL_USB0_EP1_IN   (0U << DMAXBAR_DMAXBAR1_CH15SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH15SEL_SARADC1       (1U << DMAXBAR_DMAXBAR1_CH15SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH15SEL_IDAC0         (2U << DMAXBAR_DMAXBAR1_CH15SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH15SEL_EPCA0_CONTROL (3U << DMAXBAR_DMAXBAR1_CH15SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH15SEL_DMA0T0_RISE   (4U << DMAXBAR_DMAXBAR1_CH15SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH15SEL_DMA0T0_FALL   (5U << DMAXBAR_DMAXBAR1_CH15SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH15SEL_DMA0T1_RISE   (6U << DMAXBAR_DMAXBAR1_CH15SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH15SEL_DMA0T1_FALL   (7U << DMAXBAR_DMAXBAR1_CH15SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH15SEL_TIMER0H       (8U << DMAXBAR_DMAXBAR1_CH15SEL_BIT)
#define DMAXBAR_DMAXBAR1_CH15SEL_TIMER1H       (9U << DMAXBAR_DMAXBAR1_CH15SEL_BIT)


/*
 * Devices
 */

extern dma_dev *DMA1;

/*
 * Other types needed by, or useful for, <libmaple/dma.h>
 */

/**
 * @brief DMA streams
 * This is also the dma_tube type for STM32F2.
 * @see dma_tube
 */
typedef enum dma_stream {
    DMA_S0  =  0,
    DMA_S1  =  1,
    DMA_S2  =  2,
    DMA_S3  =  3,
    DMA_S4  =  4,
    DMA_S5  =  5,
    DMA_S6  =  6,
    DMA_S7  =  7,
    DMA_S8  =  8,
    DMA_S9  =  9,
    DMA_S10 = 10,
    DMA_S11 = 11,
    DMA_S12 = 12,
    DMA_S13 = 13,
    DMA_S14 = 14,
    DMA_S15 = 15,
} dma_stream;

/** STM32F2 dma_tube (=dma_stream) */
#define dma_tube dma_stream





#if 0
/**
 * @brief STM32F2 configuration flags for dma_tube_config.
 * @see struct dma_tube_config
 */
typedef enum dma_cfg_flags {
    /* NB: flags that aren't SCR bits are treated specially. */

    /**
     * Source address increment mode
     *
     * If this flag is set, the source address is incremented (by the
     * source size) after each DMA transfer.
     */
    DMA_CFG_SRC_INC = 1U << 31,

    /**
     * Destination address increment mode
     *
     * If this flag is set, the destination address is incremented (by
     * the destination size) after each DMA transfer.
     */
    DMA_CFG_DST_INC = 1U << 30,

    /**
     * Circular mode
     *
     * This mode is not available for memory-to-memory transfers.
     */
    DMA_CFG_CIRC = DMA_SCR_CIRC,

    /** Transfer complete interrupt enable */
    DMA_CFG_CMPLT_IE      = DMA_SCR_TCIE,
    /** Transfer half-complete interrupt enable  */
    DMA_CFG_HALF_CMPLT_IE = DMA_SCR_HTIE,
    /** Transfer error interrupt enable */
    DMA_CFG_ERR_IE        = DMA_SCR_TEIE,
    /** Direct mode error interrupt enable */
    DMA_CFG_DM_ERR_IE     = DMA_SCR_DMEIE,
    /** FIFO error interrupt enable  */
    DMA_CFG_FIFO_ERR_IE   = (1U << 29),
} dma_cfg_flags;





/*
 * Tube conveniences
 */

static inline dma_tube_reg_map* dma_tube_regs(dma_dev *dev,
                                              dma_tube tube) {
    ASSERT(DMA_S0 <= tube && tube <= DMA_S7);
    switch (dev->clk_id) {
    case RCC_DMA1:
        return DMA1S0_BASE + (int)tube;
    case RCC_DMA2:
        return DMA2S0_BASE + (int)tube;
    default:
        /* Can't happen */
        ASSERT(0);
        return 0;
    }
}

static inline uint8 dma_is_enabled(dma_dev *dev, dma_tube tube) {
    return 0;
}

/* F2-only; available because of double-buffering. */
void dma_set_mem_n_addr(dma_dev *dev, dma_tube tube, int n,
                        __io void *address);

/**
 * @brief Set memory 0 address.
 * Availability: STM32F2.
 *
 * @param dev DMA device
 * @param tube Tube whose memory 0 address to set
 * @param addr Address to use as memory 0
 */
static __always_inline void
dma_set_mem0_addr(dma_dev *dev, dma_tube tube, __io void *addr) {

}

/**
 * @brief Set memory 1 address.
 * Availability: STM32F2.
 *
 * @param dev DMA device
 * @param tube Tube whose memory 1 address to set
 * @param addr Address to use as memory 1
 */
static __always_inline void
dma_set_mem1_addr(dma_dev *dev, dma_tube tube, __io void *addr) {

}

/* Assume the user means SM0AR in a non-double-buffered configuration. */
static __always_inline void
dma_set_mem_addr(dma_dev *dev, dma_tube tube, __io void *addr) {

}

/* SM0AR and SM1AR are treated as though they have the same size */
static inline dma_xfer_size dma_get_mem_size(dma_dev *dev, dma_tube tube) {
    return (dma_xfer_size)(dma_tube_regs(dev, tube)->SCR >> 13);
}

static inline dma_xfer_size dma_get_per_size(dma_dev *dev, dma_tube tube) {
    return (dma_xfer_size)(0);
}

void dma_enable_fifo(dma_dev *dev, dma_tube tube);
void dma_disable_fifo(dma_dev *dev, dma_tube tube);

static __always_inline int dma_is_fifo_enabled(dma_dev *dev, dma_tube tube) {
    return 0;
}

/*
 * TODO:
 * - Double-buffer configuration function
 * - FIFO configuration function
 * - MBURST/PBURST configuration function
 */

/*
 * ISR/IFCR conveniences.
 */

/* (undocumented) helper for reading LISR/HISR and writing
 * LIFCR/HIFCR. For these registers,
 *
 * S0, S4:  bits start at bit 0
 * S1, S5:                    6
 * S2, S6:                   16
 * S3, S7:                   22
 *
 * I can't imagine why ST didn't just use a byte for each group. The
 * bits fit, and it would have made functions like these simpler and
 * faster.  Oh well. */
static __always_inline uint32 _dma_sr_fcr_shift(dma_tube tube) {

    return 0;
}

static inline uint8 dma_get_isr_bits(dma_dev *dev, dma_tube tube) {

    return 0;
}

static inline void dma_clear_isr_bits(dma_dev *dev, dma_tube tube) {

}

#undef _DMA_IRQ_BIT_SHIFT
#endif
#ifdef __cplusplus
} // extern "C"
#endif

#endif
