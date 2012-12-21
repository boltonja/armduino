/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Michael Hope.
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
 * @file libmaple/dma.c
 * @author Marti Bolivar <mbolivar@leaflabs.com>;
 *         Original implementation by Michael Hope
 * @brief Portable DMA routines.
 */

#include <libmaple/dma.h>
#include "dma_private.h"
#include <wirish/../arch/arch.h> //todo fix header here

/*
 * Devices
 */

static dma_dev dma1 = {
    .regs = DMA1_BASE,
    .xbar_regs = DMA1_XBAR_BASE,
    .handlers = {
        {.handler = NULL, .irq_line = NVIC_DMACH0  },
        {.handler = NULL, .irq_line = NVIC_DMACH1  },
        {.handler = NULL, .irq_line = NVIC_DMACH2  },
        {.handler = NULL, .irq_line = NVIC_DMACH3  },
        {.handler = NULL, .irq_line = NVIC_DMACH4  },
        {.handler = NULL, .irq_line = NVIC_DMACH5  },
        {.handler = NULL, .irq_line = NVIC_DMACH6  },
        {.handler = NULL, .irq_line = NVIC_DMACH7  },
        {.handler = NULL, .irq_line = NVIC_DMACH8  },
        {.handler = NULL, .irq_line = NVIC_DMACH9  },
        {.handler = NULL, .irq_line = NVIC_DMACH10 },
        {.handler = NULL, .irq_line = NVIC_DMACH11 },
        {.handler = NULL, .irq_line = NVIC_DMACH12 },
        {.handler = NULL, .irq_line = NVIC_DMACH13 },
        {.handler = NULL, .irq_line = NVIC_DMACH14 },
        {.handler = NULL, .irq_line = NVIC_DMACH15 }
    },
};
dma_dev *DMA1 = &dma1;

/*
 * Convenience routines
 */


void dma_init(dma_dev *dev, dma_tube_reg_map tube_regs) {
    // Enable DMA
    if (tube_regs == NULL) {
        return;
    }
    dev->regs->CONFIG = 1;
    dev->regs->BASEPTR = tube_regs;
}

const tube_info dma_saradc0_tubes = {
        {DMA_S2, DMAXBAR_DMAXBAR0_CH2SEL_SARADC0},
        {DMA_S4, DMAXBAR_DMAXBAR0_CH4SEL_SARADC0},
        {DMA_S5, DMAXBAR_DMAXBAR0_CH5SEL_SARADC0}};
dma_dev_tubes dma_saradc0 = {.num_tubes = sizeof(dma_saradc0_tubes) / sizeof(tube_info), &dma_saradc0_tubes};

const tube_info dma_saradc1_tubes = {
        {DMA_S3,  DMAXBAR_DMAXBAR0_CH3SEL_SARADC1},
        {DMA_S10, DMAXBAR_DMAXBAR1_CH10SEL_SARADC1},
        {DMA_S15, DMAXBAR_DMAXBAR1_CH15SEL_SARADC1}};
dma_dev_tubes dma_saradc1 = {.num_tubes = sizeof(dma_saradc1_tubes) / sizeof(tube_info), &dma_saradc1_tubes};




/* Hack to ensure inlining in dma_irq_handler() */
#define DMA_GET_HANDLER(dev, tube) (dev->handlers[tube].handler)

uint8_t dma_tube_enabled(dma_dev *dev, uint8_t tube_num) {
    return (dev->regs->CHENSET & (1 << tube_num) ? 1 : 0);
}

uint8_t dma_lock_tube(dma_dev *dev, uint8_t tube_num)
{
    if (dev->tube_mutex_bits & (1 << tube_num)) {
        // Tube is used
        return 0;
    }
    // Lock tube mutex
    dev->tube_mutex_bits |= 1 << tube_num;
    return 1;
}

void dma_unlock_tube(dma_dev *dev, uint8_t tube_num)
{
    dev->tube_mutex_bits &= ~(uint16_t)(1 << tube_num);
}

static inline void dma_set_tube_trig(dma_dev *dev, uint8_t tube_num, uint8_t tube_bits) {
    volatile uint32_t *reg = dma_get_xbar_reg(dev, tube_num);
    uint32_t set, clr;
    uint32_t shift = 4 * (tube_num % 8);
    clr = 0xf << shift;
    set = tube_bits << shift;
    // Clear bits in the peripheral select register (DMAXBAR0)
    REG_SET_CLR(*reg, 0, clr);
    // Set the peripheral
    REG_SET_CLR(*reg, 1, set);
}


/*
 * IRQ handlers
 */

void __irq_dma1_stream0(void) {

}

void __irq_dma1_stream1(void) {

}

void __irq_dma1_stream2(void) {
}

void __irq_dma1_stream3(void) {

}

void __irq_dma1_stream4(void) {

}

void __irq_dma1_stream5(void) {

}

void __irq_dma1_stream6(void) {

}

void __irq_dma1_stream7(void) {

}

void __irq_dma1_stream8(void) {

}

void __irq_dma1_stream9(void) {

}

void __irq_dma1_stream10(void) {

}

void __irq_dma1_stream11(void) {

}

void __irq_dma1_stream12(void) {

}

void __irq_dma1_stream13(void) {

}

void __irq_dma1_stream14(void) {

}

void __irq_dma1_stream15(void) {

}

