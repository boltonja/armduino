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

#ifndef _VARIANT_SILABS_ACB_X_
#define _VARIANT_SILABS_ACB_X_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "Arduino.h"
#ifdef __cplusplus
#include "UARTClass.h"
#include "USARTClass.h"
#endif

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus
typedef struct stm32_pin_info {
    gpio_dev *gpio_device;      /**< Maple pin's GPIO device */
    void *timer_device;    /**< Pin's timer device, if any. */
    const void *adc_device;  /**< ADC device, if any. */
    uint8_t gpio_bit;             /**< Pin's GPIO port bit. */
    uint8_t timer_channel;        /**< Timer channel, or 0 if none. */
    uint8_t adc_channel;          /**< Pin ADC channel, or ADCx if none. */
    uint8_t exti_triger;          /**< External interrupt trigger, or 0 if none. */
} stm32_pin_info;
extern const stm32_pin_info PIN_MAP[];
extern const stm32_pin_info PIN_MAP_SHORTS[];
/**
 * @brief Pins capable of PWM output.
 *
 * Its length is BOARD_NR_PWM_PINS.
 */
extern const uint8_t boardPWMPins[];

/**
 * @brief Array of pins capable of analog input.
 *
 * Its length is BOARD_NR_ADC_PINS.
 */
extern const uint8_t boardADCPins[];

/**
 * @brief Pins which are connected to external hardware.
 *
 * For example, on Maple boards, it always at least includes
 * BOARD_LED_PIN.  Its length is BOARD_NR_USED_PINS.
 */
extern const uint8_t boardUsedPins[];
/* Pins table to be instanciated into variant.cpp */
//extern const PinDescription g_APinDescription[] ;
#define PMAP_ROW(gpio_dev, gpio_bit, timer_dev, timer_ch, adc_dev, adc_ch, exti_trg) \
    { gpio_dev, timer_dev, adc_dev, gpio_bit, timer_ch, adc_ch, exti_trg}
/**
 * Libc porting layers
 */
#if defined (  __GNUC__  ) /* GCC CS3 */
#    include <syscalls.h> /** RedHat Newlib minimal stub */
#endif

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/
/* Changing a shorted pin to unshorted
 *   1) Comment out "#define PIN_Dx_SHORTED and change the sequence order
 *   2) Change BOARD_NR_SHORTED_PINS
 *   3) Add pin to both enums
 */
#define PIN_D30_SHORTED 0
#define PIN_D31_SHORTED 1
#define PIN_D32_SHORTED 2
#define PIN_D33_SHORTED 3
#define PIN_D34_SHORTED 4
#define PIN_D35_SHORTED 5
#define BOARD_NR_SHORTED_PINS  6

/* Pin aliases: these give the GPIO port/bit for each pin as an
 * enum. These are optional, but recommended. They make it easier to
 * write code using low-level GPIO functionality. */
enum {
    PD5, PD4, PD7, PD6, PC9, PD8, PD9, PC10, PD10,
    PD11,PD3, PD2, PD1, PD0, PA0, PA1, PA2, PA3,
    PA4, PA5, PA6, PA7, PA13, PA14, PA15, PB0, PB2,
    /* Shorted Pins */ //PE5, PE4, PE3, PE2, PE1, PE0,
    PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7, PC8,
    PC11, PC12, PC13, PC14,PA8, PA11, PB1, PB3,
    PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12,
    PB13, PB14, PB15, PA12
};

/* Board pins */
enum {
    D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10,
    D11, D12, D13, D14, D15, D16, D17, D18, D19,
    D20, D21, D22, D23, D24, D25, D26,
    /* Shorted pins */ //D30, D31, D32, D33, D34, D35,
    D36, D37, D38, D39, D40, D41, D42, D45, D46,
    D49, D50, D51, D52, A0, A1, A2, A3, A4, A5,
    A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, AREF
};
/*----------------------------------------------------------------------------*/

#define SilabsACBX_DevEd

/** Name of the board */
#define VARIANT_NAME		"Silabs_ACB_Dev_Ed"

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC     32768

/** Master clock frequency */
#define VARIANT_MCK         80000000

/* System clock options:
 * 1) 2.5 MHz - This speed is not well supported by the peripherals. ex: baud rate must be lowered to ~56k
 * 2) 20 MHz
 * 3) 23-80MHz
 *
 * Note: AHB and APB bus frequencies are configurable in boards_setup.cpp.
 *       They are configured to work as fast as possible,
 *       so modification isn't necessary.
 */
#define CYCLES_PER_MICROSECOND  (VARIANT_MCK / 1000000)

#define RTC_XTAL_HZ             VARIANT_MAINOSC

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

/* Pin number for the built-in button. */
#define BOARD_BUTTON_PIN        0

/* Pin number for the built-in LED. */
#define BOARD_LED_PIN           D13

/* Number of USARTs/UARTs whose pins are broken out to headers. */
#define BOARD_NR_USARTS         4

/* USART pin numbers. */
#define BOARD_USART1_TX_PIN     A12
#define BOARD_USART1_RX_PIN     A13
#define BOARD_USART2_TX_PIN     D0
#define BOARD_USART2_RX_PIN     D1
#define BOARD_USART3_TX_PIN     D14
#define BOARD_USART3_RX_PIN     D15
#define BOARD_USART4_TX_PIN     D20
#define BOARD_USART4_RX_PIN     D21

/* Number of SPI ports broken out to headers. */
#define BOARD_NR_SPI            3

/* SPI pin numbers. */
#define BOARD_SPI1_NSS_PIN      D19
#define BOARD_SPI1_MOSI_PIN     D18
#define BOARD_SPI1_MISO_PIN     D17
#define BOARD_SPI1_SCK_PIN      D16
#define BOARD_SPI2_NSS_PIN      D4
#define BOARD_SPI2_MOSI_PIN     D46
#define BOARD_SPI2_MISO_PIN     D45
#define BOARD_SPI2_SCK_PIN      D42
#define BOARD_SPI3_NSS_PIN      D10
#define BOARD_SPI3_MOSI_PIN     D11
#define BOARD_SPI3_MISO_PIN     D12
#define BOARD_SPI3_SCK_PIN      D13



/* Timer pin numbers. */
#define BOARD_TIMER1C1_PIN      0xFE
#define BOARD_TIMER1C2_PIN      0xFE
#define BOARD_TIMER1C3_PIN      0xFE
#define BOARD_TIMER1C4_PIN      0xFE
#define BOARD_TIMER1C5_PIN      0xFE
#define BOARD_TIMER1C6_PIN      0xFE
#define BOARD_TIMER2C1_PIN      A1
#define BOARD_TIMER2C2_PIN      D22
#define BOARD_TIMER3C1_PIN      D23
#define BOARD_TIMER3C2_PIN      D24
#define BOARD_TIMER4CX_PIN      A8
#define BOARD_TIMER4EX_PIN      A9
#define BOARD_TIMER5CX_PIN      A10
#define BOARD_TIMER5EX_PIN      A11

/* I2C pin numbers */
#define BOARD_I2C1_SDA_PIN      0xFF
#define BOARD_I2C1_SCL_PIN      0xFF
#define BOARD_I2C2_SDA_PIN      0xFF
#define BOARD_I2C2_SCL_PIN      0xFF

/* I2S pin numbers */
#define BOARD_I2S1TX_WS_PIN      0xFF
#define BOARD_I2S1TX_SCK_PIN     0xFF
#define BOARD_I2S1TX_SD_PIN      0xFF
#define BOARD_I2S1RX_WS_PIN      0xFF
#define BOARD_I2S1RX_SCK_PIN     0xFF
#define BOARD_I2S1RX_SD_PIN      0xFF

/* AHB (divided by 16) out pin number */
#define BOARD_AHB_OUT_PIN      0xFF


/* Total number of GPIO pins that are broken out to headers and
 * intended for use. This includes pins like the LED, button, and
 * debug port (JTAG/SWD) pins. */
#define BOARD_NR_GPIO_PINS      (63 - BOARD_NR_SHORTED_PINS)

/* Number of pins capable of PWM output. */
#define BOARD_NR_PWM_PINS       12

/* Number of pins capable of ADC conversion. */
#define BOARD_NR_ADC_PINS       11

/* Number of pins already connected to external hardware.  For Maple,
 * these are just BOARD_LED_PIN, BOARD_BUTTON_PIN, and the debug port
 * pins (see below). */
#define BOARD_NR_USED_PINS       0
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Number of pins defined in PinDescription array
#define PINS_COUNT           (79u)

// LEDs
#define PIN_LED_13           (13u)
#define PIN_LED_RXL          (72u)
#define PIN_LED_TXL          (73u)
#define PIN_LED              PIN_LED_13
#define PIN_LED2             PIN_LED_RXL
#define PIN_LED3             PIN_LED_TXL

/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 1

#define SPI_INTERFACE        SPI0
#define SPI_INTERFACE_ID     ID_SPI0
#define SPI_CHANNELS_NUM 4
#define PIN_SPI_SS0          (77u)
#define PIN_SPI_SS1          (87u)
#define PIN_SPI_SS2          (86u)
#define PIN_SPI_SS3          (78u)
#define PIN_SPI_MOSI         (75u)
#define PIN_SPI_MISO         (74u)
#define PIN_SPI_SCK          (76u)
#define BOARD_SPI_SS0        (10u)
#define BOARD_SPI_SS1        (4u)
#define BOARD_SPI_SS2        (52u)
#define BOARD_SPI_SS3        PIN_SPI_SS3
#define BOARD_SPI_DEFAULT_SS BOARD_SPI_SS2

#define BOARD_PIN_TO_SPI_PIN(x) \
    (x==BOARD_SPI_SS0 ? PIN_SPI_SS0 : \
    (x==BOARD_SPI_SS1 ? PIN_SPI_SS1 : \
    (x==BOARD_SPI_SS2 ? PIN_SPI_SS2 : PIN_SPI_SS3 )))
#define BOARD_PIN_TO_SPI_CHANNEL(x) \
    (x==BOARD_SPI_SS0 ? 0 : \
    (x==BOARD_SPI_SS1 ? 1 : \
    (x==BOARD_SPI_SS2 ? 2 : 3)))

static const uint8_t SS   = BOARD_SPI_SS0;
static const uint8_t SS1  = BOARD_SPI_SS1;
static const uint8_t SS2  = BOARD_SPI_SS2;
static const uint8_t SS3  = BOARD_SPI_SS3;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 2

#define PIN_WIRE_SDA         (20u)
#define PIN_WIRE_SCL         (21u)
#define WIRE_INTERFACE       TWI1
#define WIRE_INTERFACE_ID    ID_TWI1
#define WIRE_ISR_HANDLER     TWI1_Handler

#define PIN_WIRE1_SDA        (70u)
#define PIN_WIRE1_SCL        (71u)
#define WIRE1_INTERFACE      TWI0
#define WIRE1_INTERFACE_ID   ID_TWI0
#define WIRE1_ISR_HANDLER    TWI0_Handler

/*
 * UART/USART Interfaces
 */
// Serial
#define PINS_UART            (81u)
// Serial1
#define PINS_USART0          (82u)
// Serial2
#define PINS_USART1          (83u)
// Serial3
#define PINS_USART3          (84u)

/*
 * USB Interfaces
 */
#define PINS_USB             (85u)

/*
 * Analog pins
 */

static const uint8_t DAC0 = 66;
static const uint8_t DAC1 = 67;
static const uint8_t CANRX = 68;
static const uint8_t CANTX = 69;
#define ADC_RESOLUTION      12

/*
 * DACC
 */
#define DACC_INTERFACE      DACC
#define DACC_INTERFACE_ID   ID_DACC
#define DACC_RESOLUTION     12
#define DACC_ISR_HANDLER    DACC_Handler
#define DACC_ISR_ID         DACC_IRQn

/*
 * PWM
 */
#define PWM_INTERFACE       PWM
#define PWM_INTERFACE_ID    ID_PWM
#define PWM_FREQUENCY       1000
#define PWM_MAX_DUTY_CYCLE  255
#define PWM_MIN_DUTY_CYCLE  0
#define PWM_RESOLUTION      8

/*
 * TC
 */
#define TC_INTERFACE        TC0
#define TC_INTERFACE_ID     ID_TC0
#define TC_FREQUENCY        1000
#define TC_MAX_DUTY_CYCLE   255
#define TC_MIN_DUTY_CYCLE   0
#define TC_RESOLUTION       8


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/


#ifdef __cplusplus


extern UARTClass Serial1;
extern UARTClass Serial2;
extern UARTClass Serial3;
extern UARTClass Serial4;
extern UARTClass &Serial;
// todo [silabs]: Declare Spi as a reference here
//HardwareSPI &Spi;
#endif

#endif /* _VARIANT_SILABS_ACB_X_ */

