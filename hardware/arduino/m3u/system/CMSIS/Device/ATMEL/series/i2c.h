/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung (from <libmaple/i2c.h>).
 * Copyright (c) 2012 LeafLabs, LLC.
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
 * @file libmaple/stm32f1/include/series/i2c.h
 * @brief STM32F1 I2C
 */

#ifndef _I2C_REGISTERS_H_
#define _I2C_REGISTERS_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** I2C register map type */
typedef struct SI32_I2C_A_Struct
{
   volatile uint32_t    CONTROL        ; // Base Address + 0x0
   volatile uint32_t    CONTROL_SET;
   volatile uint32_t    CONTROL_CLR;
   uint32_t             reserved0;
   volatile uint32_t    CONFIG         ; // Base Address + 0x10
   volatile uint32_t    CONFIG_SET;
   volatile uint32_t    CONFIG_CLR;
   uint32_t             reserved1;
   volatile uint32_t    SADDRESS       ; // Base Address + 0x20
   uint32_t             reserved2;
   uint32_t             reserved3;
   uint32_t             reserved4;
   volatile uint32_t    SMASK          ; // Base Address + 0x30
   uint32_t             reserved5;
   uint32_t             reserved6;
   uint32_t             reserved7;
   volatile uint32_t    DATA           ; // Base Address + 0x40
   uint32_t             reserved8;
   uint32_t             reserved9;
   uint32_t             reserved10;
   volatile uint32_t    TIMER          ; // Base Address + 0x50
   uint32_t             reserved11;
   uint32_t             reserved12;
   uint32_t             reserved13;
   volatile uint32_t    TIMERRL        ; // Base Address + 0x60
   uint32_t             reserved14;
   uint32_t             reserved15;
   uint32_t             reserved16;
   volatile uint32_t    SCONFIG        ; // Base Address + 0x70
   uint32_t             reserved17;
   uint32_t             reserved18;
   uint32_t             reserved19;
   volatile uint32_t    I2CDMA         ; // Base Address + 0x80
   uint32_t             reserved20;
   uint32_t             reserved21;
   uint32_t             reserved22;
   uint32_t             reserved23[4];
} SI32_I2C_A_Type;

/*
 * Register maps
 */


//I2C register bases

#define I2C0_BASE ((struct i2c_reg_map*) 0x40009000)
#define I2C1_BASE ((struct i2c_reg_map*) 0x4000A000)


// Control Register

#define I2C_CR_BUSYF_MASK          0x00000001
#define I2C_CR_ACK_MASK            0x00000002
#define I2C_CR_ARBLF_MASK          0x00000004
#define I2C_CR_ACKRQF_MASK         0x00000008
#define I2C_CR_STO_MASK            0x00000010
#define I2C_CR_STA_MASK            0x00000020
#define I2C_CR_TXMDF_MASK          0x00000040
#define I2C_CR_MSMDF_MASK          0x00000080
#define I2C_CR_STOI_MASK           0x00000100
#define I2C_CR_ACKI_MASK           0x00000200
#define I2C_CR_RXI_MASK            0x00000400
#define I2C_CR_TXI_MASK            0x00000800
#define I2C_CR_STAI_MASK           0x00001000
#define I2C_CR_ARBLI_MASK          0x00002000
#define I2C_CR_T0I_MASK            0x00004000
#define I2C_CR_T1I_MASK            0x00008000
#define I2C_CR_T2I_MASK            0x00010000
#define I2C_CR_T3I_MASK            0x00020000
#define I2C_CR_RXARM_MASK          0x00040000
#define I2C_CR_TXARM_MASK          0x00080000
#define I2C_CR_SLVAF_MASK          0x00100000
#define I2C_CR_ATXRXEN_MASK        0x00200000
#define I2C_CR_FMD_MASK            0x00400000
#define I2C_CR_DBGMD_MASK          0x00800000
#define I2C_CR_SMINH_MASK          0x01000000
#define I2C_CR_HACKEN_MASK         0x02000000
#define I2C_CR_LBACKEN_MASK        0x08000000
#define I2C_CR_GCEN_MASK           0x20000000
#define I2C_CR_RESET_MASK          0x40000000
#define I2C_CR_I2CEN_MASK          0x80000000


#define I2C_CR_BUSYF_BIT           0  /* BUSYF<0>: Busy Flag.                           */
#define I2C_CR_ACK_BIT             1  /* ACK<1>: Acknowledge.                           */
#define I2C_CR_ARBLF_BIT           2  /* ARBLF<2>: Arbitration Lost Flag.               */
#define I2C_CR_ACKRQF_BIT          3  /* ACKRQF<3>: Acknowledge Request Flag.           */
#define I2C_CR_STO_BIT             4  /* STO<4>: Stop.                                  */
#define I2C_CR_STA_BIT             5  /* STA<5>: Start.                                 */
#define I2C_CR_TXMDF_BIT           6  /* TXMDF<6>: Transmit Mode Flag.                  */
#define I2C_CR_MSMDF_BIT           7  /* MSMDF<7>: Master/Slave Mode Flag.              */
#define I2C_CR_STOI_BIT            8  /* STOI<8>: Stop Interrupt Flag.                  */
#define I2C_CR_ACKI_BIT            9  /* ACKI<9>: Acknowledge Interrupt Flag.           */
#define I2C_CR_RXI_BIT             10 /* RXI<10>: Receive Done Interrupt Flag.          */
#define I2C_CR_TXI_BIT             11 /* TXI<11>: Transmit Done Interrupt Flag.         */
#define I2C_CR_STAI_BIT            12 /* STAI<12>: Start Interrupt Flag.                */
#define I2C_CR_ARBLI_BIT           13 /* ARBLI<13>: Arbitration Lost Interrupt Flag.    */
#define I2C_CR_T0I_BIT             14 /* T0I<14>: I2C Timer Byte 0 Interrupt Flag.      */
#define I2C_CR_T1I_BIT             15 /* T1I<15>: I2C Timer Byte 1 Interrupt Flag.      */
#define I2C_CR_T2I_BIT             16 /* T2I<16>: I2C Timer Byte 2 Interrupt Flag.      */
#define I2C_CR_T3I_BIT             17 /* T3I<17>: I2C Timer Byte 3 Interrupt Flag.      */
#define I2C_CR_RXARM_BIT           18 /* RXARM<18>: Receive Arm.                        */
#define I2C_CR_TXARM_BIT           19 /* TXARM<19>: Transmit Arm.                       */
#define I2C_CR_SLVAF_BIT           20 /* SLVAF<20>: Slave Address Type Flag.            */
#define I2C_CR_ATXRXEN_BIT         21 /* ATXRXEN<21>: Auto Transmit or Receive Enable.  */
#define I2C_CR_FMD_BIT             22 /* FMD<22>: Filter Mode.                          */
#define I2C_CR_DBGMD_BIT           23 /* DBGMD<23>: I2C Debug Mode.                     */
#define I2C_CR_SMINH_BIT           24 /* SMINH<24>: Slave Mode Inhibit.                 */
#define I2C_CR_HACKEN_BIT          25 /* HACKEN<25>: Auto Acknowledge Enable .          */
#define I2C_CR_LBACKEN_BIT         27 /* LBACKEN<27>: Last Byte Acknowledge Enable.     */
#define I2C_CR_GCEN_BIT            29 /* GCEN<29>: General Call Address Enable.         */
#define I2C_CR_RESET_BIT           30 /* RESET<30>: Module Soft Reset.                  */
#define I2C_CR_I2CEN_BIT           31 /* I2CEN<31>: I2C Enable.                         */


#define I2C_CR_BUSYF_NOT_SET       (0 << I2C_CR_BUSYF_BIT)
#define I2C_CR_BUSYF_SET           (1 << I2C_CR_BUSYF_BIT)
#define I2C_CR_ACK_NOT_SET         (0 << I2C_CR_ACK_BIT)
#define I2C_CR_ACK_SET             (1 << I2C_CR_ACK_BIT)
#define I2C_CR_ARBLF_NOT_SET       (0 << I2C_CR_ARBLF_BIT)
#define I2C_CR_ARBLF_SET           (1 << I2C_CR_ARBLF_BIT)
#define I2C_CR_ACKRQF_NOT_SET      (0 << I2C_CR_ACKRQF_BIT)
#define I2C_CR_ACKRQF_SET          (1 << I2C_CR_ACKRQF_BIT)
#define I2C_CR_STO_NOT_SET         (0 << I2C_CR_STO_BIT)
#define I2C_CR_STO_SET             (1 << I2C_CR_STO_BIT)
#define I2C_CR_STA_NOT_SET         (0 << I2C_CR_STA_BIT)
#define I2C_CR_STA_SET             (1 << I2C_CR_STA_BIT)
#define I2C_CR_TXMDF_RECEIVE       (0 << I2C_CR_TXMDF_BIT)
#define I2C_CR_TXMDF_TRANSMIT      (1 << I2C_CR_TXMDF_BIT)
#define I2C_CR_MSMDF_SLAVE         (0 << I2C_CR_MSMDF_BIT)
#define I2C_CR_MSMDF_MASTER        (1 << I2C_CR_MSMDF_BIT)
#define I2C_CR_STOI_NOT_SET        (0 << I2C_CR_STOI_BIT)
#define I2C_CR_STOI_SET            (1 << I2C_CR_STOI_BIT)
#define I2C_CR_ACKI_NOT_SET        (0 << I2C_CR_ACKI_BIT)
#define I2C_CR_ACKI_SET            (1 << I2C_CR_ACKI_BIT)
#define I2C_CR_RXI_NOT_SET         (0 << I2C_CR_RXI_BIT)
#define I2C_CR_RXI_SET             (1 << I2C_CR_RXI_BIT)
#define I2C_CR_TXI_NOT_SET         (0 << I2C_CR_TXI_BIT)
#define I2C_CR_TXI_SET             (1 << I2C_CR_TXI_BIT)
#define I2C_CR_STAI_NOT_SET        (0 << I2C_CR_STAI_BIT)
#define I2C_CR_STAI_SET            (1 << I2C_CR_STAI_BIT)
#define I2C_CR_ARBLI_NOT_SET       (0 << I2C_CR_ARBLI_BIT)
#define I2C_CR_ARBLI_SET           (1 << I2C_CR_ARBLI_BIT)
#define I2C_CR_T0I_NOT_SET         (0 << I2C_CR_T0I_BIT)
#define I2C_CR_T0I_SET             (1 << I2C_CR_T0I_BIT)
#define I2C_CR_T1I_NOT_SET         (0 << I2C_CR_T1I_BIT)
#define I2C_CR_T1I_SET             (1 << I2C_CR_T1I_BIT)
#define I2C_CR_T2I_NOT_SET         (0 << I2C_CR_T2I_BIT)
#define I2C_CR_T2I_SET             (1 << I2C_CR_T2I_BIT)
#define I2C_CR_T3I_NOT_SET         (0 << I2C_CR_T3I_BIT)
#define I2C_CR_T3I_SET             (1 << I2C_CR_T3I_BIT)
#define I2C_CR_RXARM_DS            (0 << I2C_CR_RXARM_BIT)
#define I2C_CR_RXARM_EN            (1 << I2C_CR_RXARM_BIT)
#define I2C_CR_TXARM_DS            (0 << I2C_CR_TXARM_BIT)
#define I2C_CR_TXARM_EN            (1 << I2C_CR_TXARM_BIT)
#define I2C_CR_SLVAF_SLAVE_ADDRESS (0 << I2C_CR_SLVAF_BIT)
#define I2C_CR_SLVAF_GENERAL_CALL  (1 << I2C_CR_SLVAF_BIT)
#define I2C_CR_ATXRXEN_DS          (0 << I2C_CR_ATXRXEN_BIT)
#define I2C_CR_ATXRXEN_EN          (1 << I2C_CR_ATXRXEN_BIT)
#define I2C_CR_FMD_DS              (0 << I2C_CR_FMD_BIT)
#define I2C_CR_FMD_EN              (1 << I2C_CR_FMD_BIT)
#define I2C_CR_DBGMD_RUN           (0 << I2C_CR_DBGMD_BIT)
#define I2C_CR_DBGMD_HALT          (1 << I2C_CR_DBGMD_BIT)
#define I2C_CR_SMINH_INACTV        (0 << I2C_CR_SMINH_BIT)
#define I2C_CR_SMINH_ACTV          (1 << I2C_CR_SMINH_BIT)
#define I2C_CR_HACKEN_DS           (0 << I2C_CR_HACKEN_BIT)
#define I2C_CR_HACKEN_EN           (1 << I2C_CR_HACKEN_BIT)
#define I2C_CR_LBACKEN_DS          (0 << I2C_CR_LBACKEN_BIT)
#define I2C_CR_LBACKEN_EN          (1 << I2C_CR_LBACKEN_BIT)
#define I2C_CR_GCEN_DS             (0 << I2C_CR_GCEN_BIT)
#define I2C_CR_GCEN_EN             (1 << I2C_CR_GCEN_BIT)
#define I2C_CR_RESET_INACTV        (0 << I2C_CR_RESET_BIT)
#define I2C_CR_RESET_ACTV          (1 << I2C_CR_RESET_BIT)
#define I2C_CR_I2CEN_DS            (0U << I2C_CR_I2CEN_BIT)
#define I2C_CR_I2CEN_EN            (1U << I2C_CR_I2CEN_BIT)





// Configure register

#define I2C_CFGR_SCALER_MASK       0x0000003F
#define I2C_CFGR_STOIEN_MASK       0x00000100
#define I2C_CFGR_ACKIEN_MASK       0x00000200
#define I2C_CFGR_RXIEN_MASK        0x00000400
#define I2C_CFGR_TXIEN_MASK        0x00000800
#define I2C_CFGR_STAIEN_MASK       0x00001000
#define I2C_CFGR_ARBLIEN_MASK      0x00002000
#define I2C_CFGR_T0IEN_MASK        0x00004000
#define I2C_CFGR_T1IEN_MASK        0x00008000
#define I2C_CFGR_T2IEN_MASK        0x00010000
#define I2C_CFGR_T3IEN_MASK        0x00020000
#define I2C_CFGR_BC_MASK           0x00300000
#define I2C_CFGR_BP_MASK           0x00C00000
#define I2C_CFGR_T0RUN_MASK        0x01000000
#define I2C_CFGR_T1RUN_MASK        0x02000000
#define I2C_CFGR_T2RUN_MASK        0x04000000
#define I2C_CFGR_T3RUN_MASK        0x08000000
#define I2C_CFGR_TMD_MASK          0x30000000
#define I2C_CFGR_TIMEREN_MASK      0x80000000

#define I2C_CFGR_SCALER_BIT        0  /* SCALER<5:0>: I2C Clock Scaler.                 */
#define I2C_CFGR_STOIEN_BIT        8  /* STOIEN<8>: Stop Interrupt Enable.              */
#define I2C_CFGR_ACKIEN_BIT        9  /* ACKIEN<9>: Acknowledge Interrupt Enable.       */
#define I2C_CFGR_RXIEN_BIT         10 /* RXIEN<10>: Receive Done Interrupt Enable.      */
#define I2C_CFGR_TXIEN_BIT         11 /* TXIEN<11>: Transmit Done Interrupt Enable.     */
#define I2C_CFGR_STAIEN_BIT        12 /* STAIEN<12>: Start Interrupt Enable.            */
#define I2C_CFGR_ARBLIEN_BIT       13 /* ARBLIEN<13>: Arbitration Lost Interrupt Enable. */
#define I2C_CFGR_T0IEN_BIT         14 /* T0IEN<14>: I2C Timer Byte 0 Interrupt Enable.  */
#define I2C_CFGR_T1IEN_BIT         15 /* T1IEN<15>: I2C Timer Byte 1 Interrupt Enable.  */
#define I2C_CFGR_T2IEN_BIT         16 /* T2IEN<16>: I2C Timer Byte 2 Interrupt Enable.  */
#define I2C_CFGR_T3IEN_BIT         17 /* T3IEN<17>: I2C Timer Byte 3 Interrupt Enable.  */
#define I2C_CFGR_BC_BIT            20 /* BC<21:20>: Transfer Byte Count.                */
#define I2C_CFGR_BP_BIT            22 /* BP<23:22>: Transfer Byte Pointer.              */
#define I2C_CFGR_T0RUN_BIT         24 /* T0RUN<24>: I2C Timer Byte 0 Run.               */
#define I2C_CFGR_T1RUN_BIT         25 /* T1RUN<25>: I2C Timer Byte 1 Run.               */
#define I2C_CFGR_T2RUN_BIT         26 /* T2RUN<26>: I2C Timer Byte 2 Run.               */
#define I2C_CFGR_T3RUN_BIT         27 /* T3RUN<27>: I2C Timer Byte 3 Run.               */
#define I2C_CFGR_TMD_BIT           28 /* TMD<29:28>: I2C Timer Mode.                    */
#define I2C_CFGR_TIMEREN_BIT       31 /* TIMEREN<31>: I2C Timer Enable.                 */

#define I2C_CFGR_STOIEN_DS         (0 << I2C_CFGR_STOIEN_BIT)
#define I2C_CFGR_STOIEN_EN         (1 << I2C_CFGR_STOIEN_BIT)
#define I2C_CFGR_ACKIEN_DS         (0 << I2C_CFGR_ACKIEN_BIT)
#define I2C_CFGR_ACKIEN_EN         (1 << I2C_CFGR_ACKIEN_BIT)
#define I2C_CFGR_RXIEN_DS          (0 << I2C_CFGR_RXIEN_BIT)
#define I2C_CFGR_RXIEN_EN          (1 << I2C_CFGR_RXIEN_BIT)
#define I2C_CFGR_TXIEN_DS          (0 << I2C_CFGR_TXIEN_BIT)
#define I2C_CFGR_TXIEN_EN          (1 << I2C_CFGR_TXIEN_BIT)
#define I2C_CFGR_STAIEN_DS         (0 << I2C_CFGR_STAIEN_BIT)
#define I2C_CFGR_STAIEN_EN         (1 << I2C_CFGR_STAIEN_BIT)
#define I2C_CFGR_ARBLIEN_DS        (0 << I2C_CFGR_ARBLIEN_BIT)
#define I2C_CFGR_ARBLIEN_EN        (1 << I2C_CFGR_ARBLIEN_BIT)
#define I2C_CFGR_T0IEN_DS          (0 << I2C_CFGR_T0IEN_BIT)
#define I2C_CFGR_T0IEN_EN          (1 << I2C_CFGR_T0IEN_BIT)
#define I2C_CFGR_T1IEN_DS          (0 << I2C_CFGR_T1IEN_BIT)
#define I2C_CFGR_T1IEN_EN          (1 << I2C_CFGR_T1IEN_BIT)
#define I2C_CFGR_T2IEN_DS          (0 << I2C_CFGR_T2IEN_BIT)
#define I2C_CFGR_T2IEN_EN          (1 << I2C_CFGR_T2IEN_BIT)
#define I2C_CFGR_T3IEN_DS          (0 << I2C_CFGR_T3IEN_BIT)
#define I2C_CFGR_T3IEN_EN          (1 << I2C_CFGR_T3IEN_BIT)
#define I2C_CFGR_T0RUN_STOP        (0 << I2C_CFGR_T0RUN_BIT)
#define I2C_CFGR_T0RUN_START       (1 << I2C_CFGR_T0RUN_BIT)
#define I2C_CFGR_T1RUN_STOP        (0 << I2C_CFGR_T1RUN_BIT)
#define I2C_CFGR_T1RUN_START       (1 << I2C_CFGR_T1RUN_BIT)
#define I2C_CFGR_T2RUN_STOP        (0 << I2C_CFGR_T2RUN_BIT)
#define I2C_CFGR_T2RUN_START       (1 << I2C_CFGR_T2RUN_BIT)
#define I2C_CFGR_T3RUN_STOP        (0 << I2C_CFGR_T3RUN_BIT)
#define I2C_CFGR_T3RUN_START       (1 << I2C_CFGR_T3RUN_BIT)
#define I2C_CFGR_TMD_MODE0         (0 << I2C_CFGR_TMD_BIT)
#define I2C_CFGR_TMD_MODE1         (1 << I2C_CFGR_TMD_BIT)
#define I2C_CFGR_TMD_MODE2         (2 << I2C_CFGR_TMD_BIT)
#define I2C_CFGR_TMD_MODE3         (3 << I2C_CFGR_TMD_BIT)
#define I2C_CFGR_TIMEREN_DS        (0U << I2C_CFGR_TIMEREN_BIT)
#define I2C_CFGR_TIMEREN_EN        (1U << I2C_CFGR_TIMEREN_BIT)





#define I2C_SADDRESS_ADDRESS_MASK  0x000000FE
#define I2C_SMASK_MASK_MASK        0x000000FE
#define I2C_DATA_MASK              0xFFFFFFFF
#define I2C_TIMER_T0_MASK          0x000000FF
#define I2C_TIMER_T1_MASK          0x0000FF00
#define I2C_TIMER_T2_MASK          0x00FF0000
#define I2C_TIMER_T3_MASK          0xFF000000
#define I2C_TIMERRL_T0RL_MASK      0x000000FF
#define I2C_TIMERRL_T1RL_MASK      0x0000FF00
#define I2C_TIMERRL_T2RL_MASK      0x00FF0000
#define I2C_TIMERRL_T3RL_MASK      0xFF000000
#define I2C_SCONFIG_SETUP_MASK     0x0000000F
#define I2C_SCONFIG_HOLD_MASK      0x000000F0
#define I2C_SCONFIG_SCLL_MASK      0x0000FF00
#define I2C_SCONFIG_SCLLTIMER_MASK 0x000F0000
#define I2C_I2CDMA_DMALEN_MASK     0x000000FF
#define I2C_I2CDMA_DMAEN_MASK      0x80000000



#define I2C_SADDRESS_ADDRESS_BIT   1  /* ADDRESS<10:1>: Slave Address.                  */
#define I2C_SMASK_MASK_BIT         1  /* MASK<10:1>: Slave Address Mask.                */
#define I2C_DATA_BIT               0  /* DATA<31:0>: Data.                              */
#define I2C_TIMER_T0_BIT           0  /* T0<7:0>: Timer Byte 0.                         */
#define I2C_TIMER_T1_BIT           8  /* T1<15:8>: Timer Byte 1.                        */
#define I2C_TIMER_T2_BIT           16 /* T2<23:16>: Timer Byte 2.                       */
#define I2C_TIMER_T3_BIT           24 /* T3<31:24>: Timer Byte 3.                       */
#define I2C_TIMERRL_T0RL_BIT       0  /* T0RL<7:0>: Timer Byte 0 Reload Value.          */
#define I2C_TIMERRL_T1RL_BIT       8  /* T1RL<256>: ֠                                  */
#define I2C_TIMERRL_T2RL_BIT       16 /* T2RL<23:16>: Timer Byte 2 Reload Value.        */
#define I2C_TIMERRL_T3RL_BIT       24 /* T3RL<31:24>: Timer Byte 3 Reload Value.        */
#define I2C_SCONFIG_SETUP_BIT      0  /* SETUP<17>: ֠                                  */
#define I2C_SCONFIG_HOLD_BIT       4  /* HOLD<16>: ֠                                   */
#define I2C_SCONFIG_SCLL_BIT       8  /* SCLL<256>: ֠                                  */
#define I2C_SCONFIG_SCLLTIMER_BIT  16 /* SCLLTIMER<19:16>: SCL Low Timer Bits [3:0].    */
#define I2C_I2CDMA_DMALEN_BIT      0  /* DMALEN<7:0>: DMA Transfer Length.              */
#define I2C_I2CDMA_DMAEN_BIT       31 /* DMAEN<31>: DMA Mode Enable.                    */



#define I2C_I2CDMA_DMAEN_DS        (0U << I2C_I2CDMA_DMAEN_BIT)
#define I2C_I2CDMA_DMAEN_EN        (1U << I2C_I2CDMA_DMAEN_BIT)

#ifdef __cplusplus
}
#endif

#endif  //_I2C_REGISTERS_H_
