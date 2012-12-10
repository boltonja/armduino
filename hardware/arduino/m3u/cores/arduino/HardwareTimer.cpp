/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Bryan Newbold.
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

#include <Arduino.h>
#include "HardwareTimer.h"

// TODO [0.1.0] Remove deprecated pieces

/*
 * Evil hack to infer this->dev from timerNum in the HardwareTimer
 * constructor. See:
 *
 * http://www.parashift.com/c++-faq-lite/pointers-to-members.html#faq-33.2
 * http://yosefk.com/c++fqa/function.html#fqa-33.2
 */

extern "C" {
    static timer_dev **this_devp;
    static clk_dev_id this_id;
    static void set_this_dev(timer_dev *dev) {
        if (dev->clk_id == this_id) {
            *this_devp = dev;
        }
    }
}

/*
 * HardwareTimer routines
 */

HardwareTimer::HardwareTimer(uint8_t timerNum) {
    clk_dev_id timerID = (clk_dev_id)(CLK_EPCA1 + (timerNum - 1));
    // Increment one timerID if not a PCA based timer
    timerID = clk_dev_id((uint32_t)timerID + (timerID >= CLK_SSG ? 1 : 0));
    this->dev = NULL;
    nvic_globalirq_disable(); // Hack to ensure we're the only ones using
                    // set_this_dev() and friends. TODO: use a lock.
    this_id = timerID;
    this_devp = &this->dev;
    timer_foreach(set_this_dev);
    nvic_globalirq_enable();

}

void HardwareTimer::pause(void) {
    timer_pause(this->dev);
}

void HardwareTimer::resume(void) {
    timer_resume(this->dev);
}

uint32_t HardwareTimer::getPrescaleFactor(void) {
    return timer_get_prescaler(this->dev) + 1;
}

void HardwareTimer::setPrescaleFactor(uint32_t factor) {
    timer_set_prescaler(this->dev, (uint16_t)(factor - 1));
}

uint16_t HardwareTimer::getOverflow() {
    return timer_get_reload(this->dev);
}

void HardwareTimer::setOverflow(uint16_t val) {
    timer_set_reload(this->dev, val);
}

uint16_t HardwareTimer::getCount(void) {
    return timer_get_count(this->dev);
}

void HardwareTimer::setCount(uint16_t val) {
    uint16_t ovf = this->getOverflow();
    timer_set_count(this->dev, min(val, ovf));
}

#define MAX_RELOAD ((1 << 16) - 1)
uint16_t HardwareTimer::setPeriod(uint32_t microseconds) {
    // Not the best way to handle this edge case?
    if (!microseconds) {
        this->setPrescaleFactor(1);
        this->setOverflow(1);
        return this->getOverflow();
    }

    uint32_t period_cyc = microseconds * CYCLES_PER_MICROSECOND / 2;
    uint16_t prescaler = (uint16_t)(period_cyc / MAX_RELOAD + 1);
    uint16_t overflow = (uint16_t)((period_cyc + (prescaler / 2)) / prescaler);
    this->setPrescaleFactor(prescaler);
    this->setOverflow(overflow);
    return overflow;
}

void HardwareTimer::setMode(int channel, timer_mode mode) {
    timer_set_mode(this->dev, (uint8_t)channel, (timer_mode)mode);
}

uint16_t HardwareTimer::getCompare(int channel) {
    return timer_get_compare(this->dev, (uint8_t)channel);
}

void HardwareTimer::setCompare(int channel, uint16_t val) {
    uint16_t ovf = this->getOverflow();
    timer_set_compare(this->dev, (uint8_t)channel, min(val, ovf));
}



void HardwareTimer::attachInterrupt(int channel, voidFuncPtr handler) {
    timer_attach_interrupt(this->dev, (uint8_t)channel, handler);
}

void HardwareTimer::detachInterrupt(int channel) {
    timer_detach_interrupt(this->dev, (uint8_t)channel);
}

void HardwareTimer::refresh(void) {
    timer_generate_update(this->dev);
}



HardwareTimer Timer1(1);
HardwareTimer Timer2(2);
HardwareTimer Timer3(3);
HardwareTimer Timer4(4);
HardwareTimer Timer5(5);
