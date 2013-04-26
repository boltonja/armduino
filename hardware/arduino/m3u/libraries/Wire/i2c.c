/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////mine
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @file libmaple/i2c.c
 * @author Perry Hung <perry@leaflabs.com>
 * @brief Inter-Integrated Circuit (I2C) support.
 *
 * Currently, only master mode is supported.
 */



#include <libmaple/libmaple.h>
#include <libmaple/rcc.h>
#include <libmaple/gpio.h>
#include <libmaple/nvic.h>
#include <libmaple/i2c.h>
#include <libmaple/systick.h>

#include <variant.h>
#include <string.h>
#include "delay.h"


static inline int32 wait_for_state_change(i2c_dev *dev,
                                          i2c_state state,
                                          uint32 timeout);
static void set_freq_scl(i2c_dev *dev, uint32 flags);

/**
 * @brief Fill data register with slave address
 * @param dev I2C device
 * @param addr Slave address
 * @param rw Read/write bit
 */
static inline void i2c_send_slave_addr(i2c_dev *dev, uint32 addr, uint32 rw) {
    //dev->regs->DATA = (addr << 1) | rw;
	
	dev -> regs->DATA = addr | rw;
}

/*
 * Simple debugging trail. Define I2C_DEBUG to turn on.
 */
#ifdef I2C_DEBUG

#define NR_CRUMBS       128
static struct crumb crumbs[NR_CRUMBS];
static uint32 cur_crumb = 0;

static inline void i2c_drop_crumb(uint32 event, uint32 arg0, uint32 arg1) {
    if (cur_crumb < NR_CRUMBS) {
        struct crumb *crumb = &crumbs[cur_crumb++];
        crumb->event = event;
        crumb->arg0 = arg0;
        crumb->arg1 = arg1;
    }
}
#define I2C_CRUMB(event, arg0, arg1) i2c_drop_crumb(event, arg0, arg1)

#else
#define I2C_CRUMB(event, arg0, arg1)
#endif

extern fooprint(char *s);
extern void dumpxbar();
extern sqwave();

struct crumb {
    uint32 event;
    uint32 arg0;
    uint32 arg1;
};

enum {
    IRQ_ENTRY           = 1,
    TXE_ONLY            = 2,
    TXE_BTF             = 3,
    STOP_SENT           = 4,
    TEST                = 5,
    RX_ADDR_START       = 6,
    RX_ADDR_STOP        = 7,
    RXNE_ONLY           = 8,
    RXNE_SENDING        = 9,
    RXNE_START_SENT     = 10,
    RXNE_STOP_SENT      = 11,
    RXNE_DONE           = 12,
    ERROR_ENTRY         = 13,
};

/**
 * @brief Reset an I2C bus.
 *
 * Reset is accomplished by clocking out pulses until any hung slaves
 * release SDA and SCL, then generating a START condition, then a STOP
 * condition.
 *
 * @param dev I2C device
 */
void i2c_bus_reset(const i2c_dev *dev) {
    /* Release both lines */
    fooprint("i2c_bus_reset: entry");
    i2c_master_release_bus(dev);

    fooprint("i2c_bus_reset: dumping xbar cfg");
	
    //dumpxbar();
	fooprint("before reset");
	dev -> regs->CONTROL |=I2C_CR_RESET_MASK;
	
	while(dev -> regs->CONTROL&I2C_CR_RESET_MASK){
	;
	}
	fooprint("after reset");

}

/**
 * @brief Initialize an I2C device and reset its registers to their
 *        default values.
 * @param dev Device to initialize.
 */
void i2c_init(i2c_dev *dev){
    clk_enable_dev(dev->clk_id);

}

/* Hack for deprecated bit of STM32F1 functionality */
#ifndef _I2C_HAVE_DEPRECATED_I2C_REMAP
#define _i2c_handle_remap(dev, flags) ((void)0)
#endif

/**
 * @brief Initialize an I2C device as bus master
 * @param dev Device to enable
 * @param flags Bitwise or of the following I2C options:
 *              I2C_FAST_MODE: 400 khz operation,
 *              I2C_DUTY_16_9: 16/9 Tlow/Thigh duty cycle (only applicable for
 *                             fast mode),
 *              I2C_BUS_RESET: Reset the bus and clock out any hung slaves on
 *                             initialization,
 *              I2C_10BIT_ADDRESSING: Enable 10-bit addressing,
 *              I2C_REMAP: (deprecated, STM32F1 only) Remap I2C1 to SCL/PB8
 *                         SDA/PB9.
 */
void i2c_master_enable(i2c_dev *dev, uint32 flags) {
    /* Reset the bus. Clock out any hung slaves. */
    if (flags & I2C_BUS_RESET) {
        fooprint("i2c_master_enable: calling i2c_bus_reset");
        i2c_bus_reset(dev);
    }
    fooprint("i2c_master_enable: entry");
    /* PE must be disabled to configure the device */
   // ASSERT(!(dev->regs->CR1 & I2C_CR1_PE));

    /* Ugh */
   //_i2c_handle_remap(dev, flags);

    fooprint("i2c_master_enable: calling i2c_init");
    /* Turn on clock and set GPIO modes */
    i2c_init(dev);
	
    fooprint("i2c_master_enable: calling i2c_config_gpios");
    i2c_config_gpios(dev);

    fooprint("i2c_master_enable: calling set_freq_scl");
    /* Configure clock and rise time */
    set_freq_scl(dev, flags);

    fooprint("i2c_master_enable: calling nvic_irq_enable(ev)");
    /* Enable event and buffer interrupts */
    nvic_irq_enable(dev->ev_nvic_line);
    fooprint("i2c_master_enable: calling nvic_irq_enable(er)");
    nvic_irq_enable(dev->er_nvic_line);
	
	//gutted
	
    fooprint("i2c_master_enable: calling i2c_enable_irq");
    i2c_enable_irq(dev, I2C_CFGR_STOIEN_MASK | I2C_CFGR_ACKIEN_MASK | I2C_CFGR_RXIEN_MASK | I2C_CFGR_TXIEN_MASK | I2C_CFGR_STAIEN_MASK | I2C_CFGR_ARBLIEN_MASK);

    /* Make it go! */
	
    fooprint("i2c_master_enable: calling i2c_peripheral_enable");
	//gutted

    i2c_peripheral_enable(dev);




    dev->state = I2C_STATE_IDLE;
    fooprint("i2c_master_enable: exit, dev-state = I2C_STATE_IDLE");
}

/**
 * @brief Process an i2c transaction.
 *
 * Transactions are composed of one or more i2c_msg's, and may be read
 * or write tranfers.  Multiple i2c_msg's will generate a repeated
 * start in between messages.
 *
 * @param dev I2C device
 * @param msgs Messages to send/receive
 * @param num Number of messages to send/receive
 * @param timeout Bus idle timeout in milliseconds before aborting the
 *                transfer.  0 denotes no timeout.
 * @return 0 on success,
 *         I2C_ERROR_PROTOCOL if there was a protocol error,
 *         I2C_ERROR_TIMEOUT if the transfer timed out.
 */
int32 i2c_master_xfer(i2c_dev *dev,
                      i2c_msg *msgs,
                      uint16 num,
                      uint32 timeout) {
    int32 rc;
	fooprint("master xfer1");
	//fooprint("me1");
    ASSERT(dev->state == I2C_STATE_IDLE);

    dev->msg = msgs;
    dev->msgs_left = num;

	// what is this?????????????????????????????????????????
    dev->timestamp = systick_uptime();
    dev->state = I2C_STATE_BUSY;

	// already enabled in master enable
    //i2c_enable_irq(dev, I2C_IRQ_EVENT);
	fooprint("master exfer2");
    i2c_start_condition(dev);
fooprint("master exfer3");
    rc = wait_for_state_change(dev, I2C_STATE_XFER_DONE, timeout);
	fooprint("master exfer after wait for state");
    if (rc < 0) {
        goto out;
    }

    dev->state = I2C_STATE_IDLE;
out:
    return rc;
}

/**
 * @brief Wait for an I2C event, or time out in case of error.
 * @param dev I2C device
 * @param state I2C_state state to wait for
 * @param timeout Timeout, in milliseconds
 * @return 0 if target state is reached, a negative value on error.
 */
static inline int32 wait_for_state_change(i2c_dev *dev,
                                          i2c_state state,
                                          uint32 timeout) {
    i2c_state tmp;
fooprint("wait for state");
    while (1) {
        tmp = dev->state;

        if (tmp == I2C_STATE_ERROR) {
            return I2C_STATE_ERROR;
			fooprint("me2errer");
        }

        if (tmp == state) {
            return 0;
        }

        // if (timeout) {
          //  if (systick_uptime() > (dev->timestamp + timeout)) {
         //       /* TODO: overflow? */
        //       /* TODO: racy? */
		//		fooprint("timeout");
          //      return I2C_ERROR_TIMEOUT;
         //   }
        //}
    }
}

/*
 * Private API
 */

/*
 * IRQ handler for I2C master. Handles transmission/reception.
 */
void _i2c_irq_handler(i2c_dev *dev) {
    /* WTFs:
     * - Where is I2C_MSG_10BIT_ADDR handled?
     */
	fooprint("inside interrupt");
    i2c_msg *msg = dev->msg;

	// true if this is a receive intruction
    uint8 read = msg->flags & I2C_MSG_READ;

    //uint32 sr1 = dev->regs->SR1;
    //uint32 sr2 = dev->regs->SR2;
    //I2C_CRUMB(IRQ_ENTRY, sr1, sr2);
	uint32_t controlReg = dev ->regs->CONTROL;

    /*
     * Reset timeout counter
     */
    dev->timestamp = systick_uptime();

	/*
     * Master needs to acknowledge after recieving every byte and clear the acknowledge interrupt bit
     */
	if (controlReg &I2C_CR_ACKI_MASK){
	fooprint("ack condition");
		dev -> regs->CONTROL |=I2C_CR_ACK_MASK;
		dev -> regs->CONTROL &= ~I2C_CR_ACKI_MASK;
		return;
	}
	
	
	/*
     * Stop Condition Sent
     */
	if (controlReg & I2C_CR_STO_MASK){
	fooprint("stop condition");
		dev -> regs->CONTROL &= ~I2C_CR_STO_MASK;
		dev -> regs->CONTROL &= ~I2C_CR_STOI_MASK;
		return;
	}
	
    /*
     * EV5: Start condition sent
     */
    if (controlReg & I2C_CR_STAI_MASK) {
		fooprint("start condition");
        msg->xferred = 0;
        //i2c_enable_irq(dev, I2C_IRQ_BUFFER);
		
		// clear Start bit (sta) and
		dev -> regs->CONTROL &= (~I2C_CR_STA_MASK);
		


        /*
         * Master receiver
         */
		 //???????????????????????????????????????????????????????????????
		 // enable an acknowledge interrupt
        if (read) {
            i2c_enable_ack(dev);
        }
		
		
		int32_t bytesLeft = msg -> length - msg -> xferred;
		bytesLeft = bytesLeft - 1;
		if (bytesLeft >=3){
			bytesLeft = 3;
		//clear BC bits
			dev -> regs->CONFIG &= ~I2C_CFGR_BC_MASK;
			dev -> regs->CONFIG |= bytesLeft << I2C_CFGR_BC_BIT;
		}
		else{
			dev -> regs->CONFIG &= ~I2C_CFGR_BC_MASK;
			// N left is set a N-1 in BC
			dev -> regs->CONFIG |= bytesLeft << I2C_CFGR_BC_BIT;
		}	

		
		// sets the slave address and read/write direction
        i2c_send_slave_addr(dev, msg->addr, read);

		controlReg = 0;
		// set the arm transmit bit to enable transmission of message
		dev -> regs->CONTROL |= I2C_CR_TXARM_MASK;
		
		// clear start interrupt flag(STAI) bit
		dev -> regs->CONTROL &= (~I2C_CR_STAI_MASK);		
    }

    /*
     * EV6: Slave address sent
     */
	 //sr1 & I2C_SR1_ADDR
	 // is true when a transmit is done
    if (controlReg & I2C_CR_TXI_MASK) {
       fooprint("transfer");
		 
		 //if slave doesn't acknowledge generate a stop
		if (!(controlReg & I2C_CR_ACK_MASK)){
			fooprint("nack");
			i2c_stop_condition(dev);
			return;
		}
        
		fooprint(" no nack");
		if (read) {        
			int32_t bytesLeft = msg -> length - msg -> xferred;	
			bytesLeft = bytesLeft -1;
			if (bytesLeft >= 3){
			//clear BC bits
				bytesLeft = 3;
			}
			dev -> regs->CONFIG &= ~I2C_CFGR_BC_MASK;
			dev -> regs->CONFIG |= bytesLeft << I2C_CFGR_BC_BIT;
			// load the data Buffer
			i2c_write(dev, bytesLeft);

			// clear the transmit interrupt flag
			dev -> regs->CONFIG &= ~I2C_CFGR_TXIEN_MASK;
			// set the receive arm interrupt bit
			dev -> regs->CONTROL |= I2C_CR_RXARM_MASK; 

        } 
		else {
		fooprint("transfer writing");
			int32_t bytesLeft = msg -> length - msg -> xferred;	
			// if the last byte is transferred and there are no more messages generate a stop condition
			if (bytesLeft == 0 && dev->msgs_left == 0){
				i2c_stop_condition(dev);
				// clear the transmit interrupt flag
				dev -> regs->CONFIG &= ~I2C_CFGR_TXIEN_MASK;
				return;
			}
			// are no more bytes to transfere and there are messages do a repeated start
			else if(bytesLeft == 0){
				i2c_start_condition(dev);
				// clear the transmit interrupt flag
				dev -> regs->CONFIG &= ~I2C_CFGR_TXIEN_MASK;
				return;
			}
            // determine BC
			
			// N left is set a N-1 in BC
			bytesLeft = bytesLeft -1;
			if (bytesLeft >= 3){
			//clear BC bits
				bytesLeft = 3;
			}
			dev -> regs->CONFIG &= ~I2C_CFGR_BC_MASK;
			dev -> regs->CONFIG |= bytesLeft << I2C_CFGR_BC_BIT;
			// load the data Buffer
			//fooprint_int(dev->msg->data[0]);
			//fooprint_int(dev->msg->data[1]);
			//fooprint_int(dev->msg->data[2]);
			//fooprint_int(bytesLeft);
			i2c_write(dev, bytesLeft);
			

		// set the arm transmit bit to enable transmission of message
		dev -> regs->CONTROL |= I2C_CR_TXARM_MASK;	
		// clear the transmit interrupt flag
		dev -> regs->CONFIG &= ~I2C_CFGR_TXIEN_MASK;
        }

		fooprint("transfer done");
    }


    /*
     * EV7: Master Receiver
     */
	 //sr1 & I2C_SR1_RXNE
    if (controlReg & I2C_CR_RXI_MASK) {
        //I2C_CRUMB(RXNE_ONLY, 0, 0);
		uint32_t start = dev -> msg -> xferred;
		uint8_t bytes = (dev->regs->CONFIG & I2C_CFGR_BC_MASK) >> I2C_CFGR_BC_BIT;
		memcpy(&dev->msg->data[start], &dev->regs->DATA, bytes);
		start = dev -> msg -> xferred + bytes;
		int32_t bytesLeft = msg -> length - msg -> xferred;	
        if (bytesLeft == 0 && dev->msgs_left == 0){
			// clear the transmit interrupt flag
			dev -> regs->CONFIG &= ~I2C_CFGR_RXIEN_MASK;
			i2c_stop_condition(dev);
			return;
		}
		// are no more bytes to transfere and there are messages do a repeated start
		else if(bytesLeft == 0){
			// clear the transmit interrupt flag
			dev -> regs->CONFIG &= ~I2C_CFGR_RXIEN_MASK;
			i2c_start_condition(dev);
			return;
		}
		
		bytesLeft = bytesLeft -1;
		if (bytesLeft >= 3){
		//clear BC bits
			bytesLeft = 3;
		}
		dev -> regs->CONFIG &= ~I2C_CFGR_BC_MASK;
		dev -> regs->CONFIG |= bytesLeft << I2C_CFGR_BC_BIT;

		// set the receive arm interrupt bit
		dev -> regs->CONTROL |= I2C_CR_RXARM_MASK; 
	
    }
}

/*
 * Interrupt handler for I2C error conditions. Aborts any pending I2C
 * transactions.
 */
 // void _i2c_irq_error_handler(i2c_dev *dev) {
    // I2C_CRUMB(ERROR_ENTRY, dev->regs->SR1, dev->regs->SR2);

    // dev->error_flags = dev->regs->SR2 & (I2C_SR1_BERR |
                                         // I2C_SR1_ARLO |
                                         // I2C_SR1_AF |
                                         // I2C_SR1_OVR);
    // /* Clear flags */
    // dev->regs->SR1 = 0;
    // dev->regs->SR2 = 0;

    // i2c_stop_condition(dev);
    // i2c_disable_irq(dev, I2C_IRQ_BUFFER | I2C_IRQ_EVENT | I2C_IRQ_ERROR);
    // dev->state = I2C_STATE_ERROR;
// } 


/*
 * configure i2c frequency and the scl low and high times for both fast mode and standard
 */
static void set_freq_scl(i2c_dev *dev, uint32 flags) {
		int32_t freq_ic;
		int32_t scl_high;
		int32_t scl_low;
    if (flags & I2C_FAST_MODE) {
		// tlow/thigh = 2
		int32_t freq_ic = 400000;
		int32_t scl_high = freq_ic/3;
		int32_t scl_low = (freq_ic*2)/3;
    } 
	else {
		// tlow/thigh = 1
		int32_t freq_ic = 100000;
		int32_t scl_high = freq_ic/2;
		int32_t scl_low = freq_ic/2;
    }	
	int32_t scalar = 64 - (clk_get_bus_freq(dev->clk_id)/freq_ic);
	int32_t trl = 256 -(scl_high*freq_ic);
	int32_t scll = 256 - (scl_low*freq_ic);
	dev -> regs->CONFIG = (~I2C_CFGR_SCALER_MASK & dev -> regs->CONFIG) | scalar;
	dev -> regs->TIMERRL = (~I2C_TIMERRL_T1RL_MASK & dev -> regs->TIMERRL) | (trl << 8);
	dev -> regs->SCONFIG = (~I2C_SCONFIG_SCLL_MASK & dev -> regs->SCONFIG) | (scll << 8);
}
