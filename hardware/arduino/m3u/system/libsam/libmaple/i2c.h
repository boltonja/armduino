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

/**
 * @file libmaple/include/libmaple/i2c.h
 * @brief Inter-Integrated Circuit (I2C) peripheral support
 *
 * Currently master-only. Usage notes:
 *
 * - Enable an I2C device with i2c_master_enable().
 * - Initialize an array of struct i2c_msg to suit the bus
 *   transactions (reads/writes) you wish to perform.
 * - Call i2c_master_xfer() to do the work.
 */

#ifndef _LIBMAPLE_I2C_H_
#define _LIBMAPLE_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Series header must provide:
 *
 * - uint32 _i2c_bus_clk(i2c_dev*): Clock frequency of dev's bus, in
 *   MHz. (This is for internal use only).
 *
 * - (optional) _I2C_HAVE_IRQ_FIXUP: Leave undefined, or define to 1.
 *   This is for internal use only. It's a hack to work around a
 *   silicon bug related to I2C IRQ pre-emption on some targets. If 1,
 *   the series header must also declare and implement a routine with
 *   this signature (it may also be provided as a macro):
 *
 *       void _i2c_irq_priority_fixup(i2c_dev*)
 *
 *   This will be called by i2c_enable_irq() before actually enabling
 *   I2C interrupts.
 *
 * - Reg. map base pointers, device pointer declarations.
 */

#include <series/i2c.h>


#include <libmaple/libmaple_types.h>
#include <libmaple/rcc.h>
#include <libmaple/nvic.h>
#include <libmaple/gpio.h>
struct gpio_dev;
struct i2c_reg_map;
struct i2c_msg;

/** I2C device states */
typedef enum i2c_state {
    I2C_STATE_DISABLED          = 0, /**< Disabled */
    I2C_STATE_IDLE              = 1, /**< Idle */
    I2C_STATE_XFER_DONE         = 2, /**< Done with transfer */
    I2C_STATE_BUSY              = 3, /**< Busy */
    I2C_STATE_ERROR             = -1 /**< Error occurred */
} i2c_state;

/**
 * @brief I2C device type.
 */
typedef struct i2c_dev {
    struct i2c_reg_map *regs;   /**< Register map */
    struct i2c_msg *msg;        /**< Messages */
    uint32 error_flags;         /**< Error flags, set on I2C error condition */
    volatile uint32 timestamp;  /**< For internal use */

    /**
     * @brief Deprecated. Use .scl_port or .sda_port instead.
     * If non-null, this will be used as SDA, SCL pins' GPIO port. If
     * null, then .sda_port will be used for SDA, and .sda_port for
     * SDA. */
    struct gpio_dev *gpio_port;

    /**
     * @brief SDA GPIO device (but see .gpio_port).
     */
    struct gpio_dev *sda_port;

    /**
     * @brief SCL GPIO device (but see .gpio_port).
     */
    struct gpio_dev *scl_port;

    uint16 msgs_left;           /**< Messages left */
    uint8 sda_pin;              /**< SDA bit on gpio_port */
    uint8 scl_pin;              /**< SCL bit on gpio_port */
    clk_dev_id clk_id;          /**< RCC clock information */
    nvic_irq_num ev_nvic_line;  /**< Event IRQ number */
    nvic_irq_num er_nvic_line;  /**< Error IRQ number */
    volatile i2c_state state;   /**< Device state */
} i2c_dev;

#define I2C_MSG_READ            0x1
#define I2C_MSG_10BIT_ADDR      0x2
/**
 * @brief I2C message type
 */
typedef struct i2c_msg {
    uint16 addr;                /**< Address */

    /**
     * Bitwise OR of:
     * - I2C_MSG_READ (write is default)
     * - I2C_MSG_10BIT_ADDR (7-bit is default) */
    uint16 flags;

    uint16 length;              /**< Message length */
    uint16 xferred;             /**< Messages transferred */
    uint8 *data;                /**< Data */
} i2c_msg;

extern i2c_dev* const I2C1;
extern i2c_dev* const I2C2;

/*
 * Convenience routines
 */

/* Main I2C API */

/* I2C enable options */
#define I2C_FAST_MODE           0x1           // 400 khz
#define I2C_DUTY_16_9           0x2           // 16/9 duty ratio
/* Flag 0x4 is reserved; DO NOT USE. */
#define I2C_BUS_RESET           0x8           // Perform a bus reset
void i2c_master_enable(i2c_dev *dev, uint32 flags);

#define I2C_ERROR_PROTOCOL      (-1)
#define I2C_ERROR_TIMEOUT       (-2)
static inline uint32 _i2c_bus_clk(i2c_dev *dev) {
    /* Both I2C peripherals are on APB1 */
    return 0;
}

#define _I2C_HAVE_IRQ_FIXUP 1
void _i2c_irq_priority_fixup(i2c_dev *dev);

/*
 * Deprecated functionality
 */

/* Flag to use alternate pin mapping in i2c_master_enable(). */
#define _I2C_HAVE_DEPRECATED_I2C_REMAP 1
#define I2C_REMAP 0x4
static inline void _i2c_handle_remap(i2c_dev *dev, uint32 flags) {

}

int32 i2c_master_xfer(i2c_dev *dev, i2c_msg *msgs, uint16 num, uint32 timeout);

void i2c_bus_reset(const i2c_dev *dev);

/**
 * @brief Disable an I2C device
 *
 * This function disables the corresponding peripheral and marks dev's
 * state as I2C_STATE_DISABLED.
 *
 * @param dev Device to disable.
 */
static inline void i2c_disable(i2c_dev *dev) {

}

/* Start/stop conditions */

/**
 * @brief Generate a start condition on the bus.
 * @param dev I2C device
 */
static inline void i2c_start_condition(i2c_dev *dev) {

}

/**
 * @brief Generate a stop condition on the bus
 * @param dev I2C device
 */
static inline void i2c_stop_condition(i2c_dev *dev) {

}

/* IRQ enable/disable */

#ifndef _I2C_HAVE_IRQ_FIXUP
/* The series header provides this if _I2C_HAVE_IRQ_FIXUP is defined,
 * but we need it either way. */
#define _i2c_irq_priority_fixup(dev) ((void)0)
#endif

#define I2C_IRQ_ERROR              I2C_CR2_ITERREN
#define I2C_IRQ_EVENT              I2C_CR2_ITEVTEN
#define I2C_IRQ_BUFFER             I2C_CR2_ITBUFEN
/**
 * @brief Enable one or more I2C interrupts
 * @param dev I2C device
 * @param irqs Bitwise or of:
 *             I2C_IRQ_ERROR (error interrupt),
 *             I2C_IRQ_EVENT (event interrupt), and
 *             I2C_IRQ_BUFFER (buffer interrupt).
 */
static inline void i2c_enable_irq(i2c_dev *dev, uint32 irqs) {

}

/**
 * @brief Disable one or more I2C interrupts
 * @param dev I2C device
 * @param irqs Bitwise or of:
 *             I2C_IRQ_ERROR (error interrupt),
 *             I2C_IRQ_EVENT (event interrupt), and
 *             I2C_IRQ_BUFFER (buffer interrupt).
 */
static inline void i2c_disable_irq(i2c_dev *dev, uint32 irqs) {

}

/* ACK/NACK */

/**
 * @brief Enable I2C acknowledgment
 * @param dev I2C device
 */
static inline void i2c_enable_ack(i2c_dev *dev) {

}

/**
 * @brief Disable I2C acknowledgment
 * @param dev I2C device
 */
static inline void i2c_disable_ack(i2c_dev *dev) {

}

/* GPIO control */

/**
 * @brief Configure device GPIOs.
 *
 * Configure GPIO bits dev->sda_pin and dev->scl_pin on GPIO device
 * dev->gpio_port for use with I2C device dev.
 *
 * @param dev I2C Device
 * @see i2c_release_gpios()
 */
extern void i2c_config_gpios(const i2c_dev *dev);

/**
 * @brief Release GPIOs controlling an I2C bus
 *
 * Releases the I2C bus controlled by dev as master, and disconnects
 * GPIO bits dev->sda_pin and dev->scl_pin on GPIO device
 * dev->gpio_port from I2C device dev.
 *
 * @param dev I2C device
 * @see i2c_config_gpios()
 */
extern void i2c_master_release_bus(const i2c_dev *dev);

/* Miscellaneous low-level routines */

void i2c_init(i2c_dev *dev);

/**
 * @brief Turn on an I2C peripheral
 * @param dev Device to enable
 */
static inline void i2c_peripheral_enable(i2c_dev *dev) {

}

/**
 * @brief Turn off an I2C peripheral
 * @param dev Device to turn off
 */
static inline void i2c_peripheral_disable(i2c_dev *dev) {

}

/**
 * @brief Fill transmit register
 * @param dev I2C device
 * @param byte Byte to write
 */
static inline void i2c_write(i2c_dev *dev, uint8 byte) {
    dev->regs->DR = byte;
}

/**
 * @brief Set input clock frequency, in MHz
 * @param dev I2C device
 * @param freq Frequency, in MHz. This must be at least 2, and at most
 *             the APB frequency of dev's bus. (For example, if
 *             rcc_dev_clk(dev) == RCC_APB1, freq must be at most
 *             PCLK1, in MHz). There is an additional limit of 46 MHz.
 */
static inline void i2c_set_input_clk(i2c_dev *dev, uint32 freq) {

}

/**
 * @brief Set I2C clock control register.
 *
 * See the chip reference manual for the details.
 *
 * @param dev I2C device
 * @param val Value to use for clock control register (in
 *            Fast/Standard mode)
 */
static inline void i2c_set_clk_control(i2c_dev *dev, uint32 val) {

}

/**
 * @brief Set SCL rise time
 * @param dev I2C device
 * @param trise Maximum rise time in fast/standard mode (see chip
 *              reference manual for the relevant formulas).
 */
static inline void i2c_set_trise(i2c_dev *dev, uint32 trise) {

}
/* For old-style definitions (SDA/SCL on same GPIO device) */
#define I2C_DEV_OLD(num, port, sda, scl)          \
    {                                             \
        .regs         = I2C##num##_BASE,          \
        .gpio_port    = port,                     \
        .scl_port     = NULL,                     \
        .sda_port     = NULL,                     \
        .sda_pin      = sda,                      \
        .scl_pin      = scl,                      \
        .clk_id       = RCC_I2C##num,             \
        .ev_nvic_line = NVIC_I2C##num##_EV,       \
        .er_nvic_line = NVIC_I2C##num##_ER,       \
        .state        = I2C_STATE_DISABLED,       \
    }

/* For new-style definitions (SDA/SCL may be on different GPIO devices) */
#define I2C_DEV_NEW(num, sdaport, sdabit, sclport, sclbit)          \
    {                                                               \
        .regs         = I2C##num##_BASE,                            \
        .gpio_port    = NULL,                                       \
        .scl_port     = sclport,                                    \
        .scl_pin      = sclbit,                                     \
        .sda_port     = sdaport,                                    \
        .sda_pin      = sdabit,                                     \
        .clk_id       = RCC_I2C##num,                               \
        .ev_nvic_line = NVIC_I2C##num##_EV,                         \
        .er_nvic_line = NVIC_I2C##num##_ER,                         \
        .state        = I2C_STATE_DISABLED,                         \
    }

void _i2c_irq_handler(i2c_dev *dev);
void _i2c_irq_error_handler(i2c_dev *dev);

struct gpio_dev;

static inline struct gpio_dev* scl_port(const i2c_dev *dev) {
    return NULL;
}

static inline struct gpio_dev* sda_port(const i2c_dev *dev) {
    return NULL;
}

/* Auxiliary procedure for enabling an I2C peripheral; `flags' as for
 * i2c_master_enable(). */
void _i2c_set_ccr_trise(i2c_dev *dev, uint32 flags);

#ifdef __cplusplus
}
#endif

#endif
