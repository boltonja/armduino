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
 * @file libmaple/include/libmaple/dma.h
 *
 * @author Marti Bolivar <mbolivar@leaflabs.com>;
 *         Original implementation by Michael Hope
 *
 * @brief Direct Memory Access peripheral support
 */

#ifndef _LIBMAPLE_DMA_H_
#define _LIBMAPLE_DMA_H_

#ifdef __cplusplus
extern "C"{
#endif
#include <libmaple/libmaple_types.h>
#include <series/dma.h>



/* Encapsulates state related to user interrupt handlers. You
 * shouldn't touch these directly; use dma_attach_interrupt() and
 * dma_detach_interupt() instead. */
typedef struct dma_handler_config {
    void (*handler)(void);     /* User handler */
    nvic_irq_num irq_line;     /* IRQ line for interrupt */
} dma_handler_config;


typedef struct dma_dev {
    dma_reg_map *regs;
    dma_xbar_reg_map *xbar_regs;
    volatile uint16_t tube_mutex_bits;
    struct dma_handler_config  handlers[]; /**< For internal use */
} dma_dev;

typedef struct tube_info {
    dma_tube id;
    uint8_t dev;
} tube_info;

typedef struct dma_dev_tubes {
    uint8_t num_tubes;
    tube_info *tubes;
} dma_dev_tubes;

extern const dma_dev_tubes dma_saradc0;
#define DMA_SARADC1 (dma_dev_tubes*)&dma_saradc0;
extern const dma_dev_tubes dma_saradc1;
#define DMA_SARADC2 (dma_dev_tubes*)&dma_saradc1;

static inline volatile uint32_t *dma_get_xbar_reg(dma_dev *dev, uint8_t tube_num) {
    return (volatile uint32_t *)(uint32_t(dev->xbar_regs) + (tube_num > 7 ? 4:0));
}

uint8_t dma_lock_tube(dma_dev *dev, uint8_t tube_num);
void dma_unlock_tube(dma_dev *dev, uint8_t tube_num)

uint8_t dma_tube_enabled(dma_dev *dev, uint8_t tube_num);
static inline void dma_enable_tube(dma_dev *dev, uint8_t tube_num) {dev->regs->CHENSET = 1 << tube_num;}
static inline void dma_disable_tube(dma_dev *dev, uint8_t tube_num) {dev->regs->CHENCLR = 1 << tube_num;}
void dma_set_tube_trig(dma_dev *dev, uint8_t tube_num, uint8_t tube_bits);


struct dma_tube_reg_map;


void dma_init(dma_dev *dev);


#ifdef __cplusplus
} // extern "C"
#endif

#endif
