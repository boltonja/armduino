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

#include "variant.h"



#include <libmaple/usart.h>
#include <libmaple/timer.h>
#include <libmaple/adc.h>
#include <libmaple/gpio.h>

#define PIN_NOT_USED PMAP_ROW(NULL,0,NULL,0,NULL,ADCx,0),
extern "C" {
    extern timer_dev timer1;
    extern timer_dev timer2;
    extern timer_dev timer3;
    extern timer_dev timer4;
    extern timer_dev timer5;
    extern adc_dev adc1;
    extern adc_dev adc2;
}
// Pin map: this lets the basic I/O functions (digitalWrite(),
// analogRead(), pwmWrite()) translate from pin numbers to STM32
// peripherals.
//
// PMAP_ROW() lets us specify a row (really a struct stm32_pin_info)
// in the pin map. Its arguments are:
//
// - GPIO:    Port Bank (PB) and PB pin number
// - Timer:   Timer device and timer channel, Null/0 if none
// - ADC:     ADC device and ADC channel, Null/ADCx if none
// - EXTI:    External Interrupt (EXTI) trigger number, 0 if none
//
// Sections:
//      1) Digital
//      2) Analog
// Comments:
//      Function: Arduino compatible function (non compatible ones not listed).
//      Periph:  Default SiM3U1 peripheral used.
//      Shorted:
//      Alternate: Supported alternate SiM3U1 peripheral.
const stm32_pin_info  __attribute__ ((used)) PIN_MAP[BOARD_NR_GPIO_PINS] = {
    /*       GPIO     -    Timer  -   ADC    -    EXTI      Pin        Function      Periph     Shorted Alternate */

    // 0 .. 53 - Digital pins
    // ----------------------
    PMAP_ROW(&gpiod,   5,   NULL,  0,  NULL,  ADCx,  11), /* D0/PD5     UART_RX       UART1_RX           I2C0_SCL   */
    PMAP_ROW(&gpiod,   4,   NULL,  0,  NULL,  ADCx,  10), /* D1/PD4     UART_TX       UART1_TX           I2C0_SDA   */
    PMAP_ROW(&gpiod,   7,   NULL,  0,  NULL,  ADCx,  13), /* D2/PD7     EXT_INT       INT0.12            I2S_RS_SCK */
    PMAP_ROW(&gpiod,   6,   NULL,  0,  NULL,  ADCx,  12), /* D3/PD6     EXT_INT(PWM)  INT0.11    D30     I2S_RX_WS  */
    PMAP_ROW(&gpioc,   9,   NULL,  0,  NULL,  ADCx,   0), /* D4/PC9                   SPI1_NSS                      */
    PMAP_ROW(&gpiod,   8,   NULL,  0,  NULL,  ADCx,  14), /* D5/PD8     (PWM)                    D31                */
    PMAP_ROW(&gpiod,   9,   NULL,  0,  NULL,  ADCx,  15), /* D6/PD9     (PWM)                    D32                */
    PMAP_ROW(&gpioc,  10,   NULL,  0,  NULL,  ADCx,  16), /* D7/PC10                                                */
    PMAP_ROW(&gpiod,  10,   NULL,  0,  NULL,  ADCx,   0), /* D8/PD10                  I2C1_SDA                      */
    PMAP_ROW(&gpiod,  11,   NULL,  0,  NULL,  ADCx,   0), /* D9/PD11    (PWM)         I2C1_SCL           D33        */

    PMAP_ROW(&gpiod,   3,   NULL,  0,  NULL,  ADCx,   0), /* D10/PD3    SPI_SS(PWM)   SPI2_NSS   D34                */
    PMAP_ROW(&gpiod,   2,   NULL,  0,  NULL,  ADCx,   0), /* D11/PD2    SPI_MOSI(PWM) SPI2_MOSI  D35                */
    PMAP_ROW(&gpiod,   1,   NULL,  0,  NULL,  ADCx,   0), /* D12/PD1    SPI_MISO      SPI2_MISO                     */
    PMAP_ROW(&gpiod,   0,   NULL,  0,  NULL,  ADCx,   0), /* D13/PD0    SPI_SCK/LED   SPI2_SCK                      */
    PMAP_ROW(&gpioa,   0,   NULL,  0,  &adc1,     0,   0), /* D14/PA0    UART_TX       USART0_TX          ADC0.0     */
    PMAP_ROW(&gpioa,   1,   NULL,  0,  &adc1,     1,   0), /* D15/PA1    UART_RX       USART0_RX          ADC0.1     */
    PMAP_ROW(&gpioa,   2,   NULL,  0,  &adc1,     2,   0), /* D16/PA2    UART_TX       SPI0_SCK           ADC0.2     */
    PMAP_ROW(&gpioa,   3,   NULL,  0,  &adc1,     3,   0), /* D17/PA3    UART_RX       SPI0_MISO          ADC0.3     */
    PMAP_ROW(&gpioa,   4,   NULL,  0,  &adc1,     4,   0), /* D18/PA4    UART_TX       SPI0_MOSI          ADC0.4     */
    PMAP_ROW(&gpioa,   5,   NULL,  0,  &adc1,     5,   0), /* D19/PA5    UART_RX       SPI0_NSS           ADC0.5     */

    PMAP_ROW(&gpioa,   6,   NULL,  0,  NULL,  ADCx,   0), /* D20/PA6    I2C_SDA       USART1_TX                     */
    PMAP_ROW(&gpioa,   7,   NULL,  0,  &adc1,     6,   0), /* D21/PA7    I2C_SCL       USART1_RX          ADC0.6     */
    PMAP_ROW(&gpioa,  13, &timer2,  2,  NULL,  ADCx,   0), /* D22/PA13                 PCA0_CEX1                     */
    PMAP_ROW(&gpioa,  14, &timer3,  1,  NULL,  ADCx,   0), /* D23/PA14                 PCA1_CEX0                     */
    PMAP_ROW(&gpioa,  15, &timer3,  2,  NULL,  ADCx,  12), /* D24/PA15                 PCA1_CEX1                     */
    PMAP_ROW(&gpiob,   0,   NULL,  0,  NULL,  ADCx,   0), /* D25/PB0                                                */
    PMAP_ROW(&gpiob,   2,   NULL,  0,  NULL,  ADCx,   0), /* D26/PB2                                                */
    PIN_NOT_USED                                          /* D27    ~ Pin Not Used ~                                */
    PIN_NOT_USED                                          /* D28    ~ Pin Not Used ~                                */
    PIN_NOT_USED                                          /* D29    ~ Pin Not Used ~                                */

    PMAP_ROW(&gpioe,   5, &timer1,  6,  NULL,  ADCx,   0), /* D30/PE5    PWM           EPCA_CEX5  D3                 */
    PMAP_ROW(&gpioe,   4, &timer1,  5,  NULL,  ADCx,   0), /* D31/PE4    PWM           EPCA_CEX4  D5                 */
    PMAP_ROW(&gpioe,   3, &timer1,  4,  NULL,  ADCx,   0), /* D32/PE3    PWM           EPCA_CEX3  D6                 */
    PMAP_ROW(&gpioe,   2, &timer1,  3,  NULL,  ADCx,   0), /* D33/PE2    PWM           EPCA_CEX2  D9                 */
    PMAP_ROW(&gpioe,   1, &timer1,  2,  NULL,  ADCx,   0), /* D34/PE1    PWM           EPCA_CEX1  D10                */
    PMAP_ROW(&gpioe,   0, &timer1,  1,  NULL,  ADCx,   0), /* D35/PE0    PWM           EPCA_CEX0  D11                */
    PMAP_ROW(&gpioc,   0,   NULL,  0,  &adc2,     2,   1), /* D36/PC0                                                */
    PMAP_ROW(&gpioc,   1,   NULL,  0,  &adc2,     1,   2), /* D37/PC1                                                */
    PMAP_ROW(&gpioc,   2,   NULL,  0,  &adc2,     0,   3), /* D38/PC2                                                */
    PMAP_ROW(&gpioc,   3,   NULL,  0,  NULL,  ADCx,   4), /* D39/PC3                                                */

    PMAP_ROW(&gpioc,   4,   NULL,  0,  NULL,  ADCx,   5), /* D40/PC4                                                */
    PMAP_ROW(&gpioc,   5,   NULL,  0,  NULL,  ADCx,   6), /* D41/PC5                                                */
    PMAP_ROW(&gpioc,   6,   NULL,  0,  NULL,  ADCx,   7), /* D42/PC6    SPI_SCK      SPI1_SCK                       */
    PIN_NOT_USED                                          /* D43    ~ Pin Not Used ~                                */
    PIN_NOT_USED                                          /* D44    ~ Pin Not Used ~                                */
    PMAP_ROW(&gpioc,   7,   NULL,  0,  NULL,  ADCx,   8), /* D45/PC7    SPI_MISO     SPI1_MISO                      */
    PMAP_ROW(&gpioc,   8,   NULL,  0,  NULL,  ADCx,   0), /* D46/PC8    SPI_MOSI     SPI1_MOSI                      */
    PIN_NOT_USED                                          /* D47    ~ Pin Not Used ~                                */
    PIN_NOT_USED                                          /* D48    ~ Pin Not Used ~                                */
    PMAP_ROW(&gpioc,  11,   NULL,  0,  NULL,  ADCx,   0), /* D49/PC11                                               */

    PMAP_ROW(&gpioc,  12,   NULL,  0,  NULL,  ADCx,   0), /* D50/PC12                                               */
    PMAP_ROW(&gpioc,  13,   NULL,  0,  NULL,  ADCx,   0), /* D51/PC13                                               */
    PMAP_ROW(&gpioc,  14,   NULL,  0,  NULL,  ADCx,   0), /* D52/PC14                                               */
    PIN_NOT_USED                                          /* D53    ~ Pin Not Used ~                                */

    // 54 .. 70 - Analog pins
    // ----------------------
    PMAP_ROW(&gpioa,   8,   NULL,  0,  &adc1,     7,   0), /* A0/PA8     ADC0          ADC0.7                        */
    PMAP_ROW(&gpioa,  11, &timer2,  1,  &adc1,     9,   0), /* A1/PA11    ADC1          ADC0.9             PCA0_CEX0  */
    PMAP_ROW(&gpiob,   1,   NULL,  0,  &adc1,    11,   0), /* A2/PB1     ADC2          ADC0.11                       */
    PMAP_ROW(&gpiob,   3,   NULL,  0,  &adc1,    12,   0), /* A3/PB3     ADC3          ADC0.12                       */
    PMAP_ROW(&gpiob,   4,   NULL,  0,  &adc1,    13,   0), /* A4/PB4     ADC4/SDA      ADC0.13            I2C0_SDA   */
    PMAP_ROW(&gpiob,   5,   NULL,  0,  &adc1,    14,   0), /* A5/PB5     ADC5/SCL      ADC0.14            I2C0_SCL   */
    PMAP_ROW(&gpiob,   6,   NULL,  0,  &adc1,    15,   0), /* A6/PB6     ADC6          ADC0.15                       */
    PMAP_ROW(&gpiob,   7,   NULL,  0,  &adc2,    11,   0), /* A7/PB7     ADC7          ADC1.11                       */
    PMAP_ROW(&gpiob,   8, &timer4,  1,  &adc2,    10,   0), /* A8/PB8     ADC8          ADC1.10            TIMER0_CT  */
    PMAP_ROW(&gpiob,   9, &timer4,  2,  &adc2,     9,   0), /* A9/PB9     ADC9          ADC1.9             TIMER0_EX  */
    PMAP_ROW(&gpiob,  10, &timer5,  1,  &adc2,     8,   0), /* A10/PB10   ADC10         ADC1.8             TIMER1_CT  */
    PMAP_ROW(&gpiob,  11, &timer5,  2,  &adc2,     7,   0), /* A11/PB11   ADC11         ADC1.7             TIMER1_EX  */
    PMAP_ROW(&gpiob,  12,   NULL,  0,  &adc2,     6,   0), /* A12/PB12   ADC12         ADC1.6             UART0_TX   */
    PMAP_ROW(&gpiob,  13,   NULL,  0,  &adc2,     5,   0), /* A13/PB13   ADC13         ADC1.5             UART0_RX   */
    PMAP_ROW(&gpiob,  14,   NULL,  0,  &adc2,     4,   0), /* A14/PB14   ADC14         ADC1.4                        */
    PMAP_ROW(&gpiob,  15,   NULL,  0,  &adc2,     3,   0), /* A15/PB15   ADC15         ADC1.3                        */
    PMAP_ROW(&gpioa,  12,   NULL,  0,  NULL,  ADCx,   0), /* AREF/PA12  AREF          VREF                          */
};

uint32_t analogPinMaping(uint32_t pin){
    uint32_t analogPins[] = {54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 16, 17, 18, 19, 20, 21, 22, 23, 24};
    return analogPins[pin];
}


// Array of pins you can use for pwmWrite(). Keep it in Flash because
// it doesn't change, and so we don't waste RAM.
const uint8_t boardPWMPins[] = {
    PIN_D30_SHORTED, PIN_D31_SHORTED, PIN_D32_SHORTED, PIN_D33_SHORTED, PIN_D34_SHORTED, PIN_D35_SHORTED, A1, D22, D23, D24, A9, A11
};

// Array of pins you can use for analogRead().
const uint8_t boardADCPins[] = {
    A0, A2, A3, A4, A5, A6, A7, A12, A13, A14, A15
};

// Array of pins that the board uses for something special. Other than
// the button and the LED, it's usually best to leave these pins alone
// unless you know what you're doing.
const uint8_t boardUsedPins[] = {
D27,D28,D29,D43,D44,D47,D48,D53
};


#define PIN_TO_PB_MASK(pin)                                 (pin == 0xff || pin == 0xfe ? 0 : PIN_MAP[pin].gpio_device == GPIOA || PIN_MAP[pin].gpio_device == GPIOC ? \
                                                                (uint32_t)1 << PIN_MAP[pin].gpio_bit : (uint32_t)1 << (PIN_MAP[pin].gpio_bit + 16))
#define PIN_TO_PB_MASK2(pin1, pin2)                         (PIN_TO_PB_MASK(pin1) | PIN_TO_PB_MASK(pin2))
#define PIN_TO_PB_MASK3(pin1, pin2, pin3)                   (PIN_TO_PB_MASK(pin1) | PIN_TO_PB_MASK2(pin2, pin3))
#define PIN_TO_PB_MASK4(pin1, pin2, pin3, pin4)             (PIN_TO_PB_MASK(pin1) | PIN_TO_PB_MASK3(pin2, pin3, pin4))
#define PIN_TO_PB_MASK5(pin1, pin2, pin3, pin4, pin5)       (PIN_TO_PB_MASK(pin1) | PIN_TO_PB_MASK4(pin2, pin3, pin4, pin5))
#define PIN_TO_PB_MASK6(pin1, pin2, pin3, pin4, pin5, pin6) (PIN_TO_PB_MASK(pin1) | PIN_TO_PB_MASK5(pin2, pin3, pin4, pin5, pin6))
#define XBAR_NUM(pin, xlow_offset) (pin == 0xff ? XBAR_NUM_NULL : pin == 0xfe ? XBAR_NUM_GPIOE : \
                        PIN_MAP[pin].gpio_device == GPIOC || PIN_MAP[pin].gpio_device == GPIOD ? XBAR_NUM_1 : \
                                xlow_offset + XBAR_NUM_0L)
#define XBAR_ROW(array, xbar_num) {(sizeof(array) / sizeof(si_xbar_info)), xbar_num, (si_xbar_info *) &array}

// Device crossbar info. The index number is used to specify what part of the 
//        device goes on the xbar, using the xbar_set_dev function. 
//        Example: xbar_set_dev(i2s.., 1, 0, 1); // Enable I2S TX.
//        Example: xbar_set_dev(i2s.., 1, 1, 1); // Enable I2S RX
static const si_xbar_info xbar_usart1[] = {
    XBAR_UART0_ROW(                           // Index 0 
        PIN_TO_PB_MASK2(
            BOARD_USART1_TX_PIN, 
            BOARD_USART1_RX_PIN), 
        XBAR_NUM(BOARD_USART1_TX_PIN, 1))
};
static const si_xbar_info xbar_usart2[] = {
      XBAR_UART1_ROW(                         // Index 0
        PIN_TO_PB_MASK2(
            BOARD_USART2_TX_PIN, 
            BOARD_USART2_RX_PIN), 
        XBAR_NUM(BOARD_USART2_TX_PIN, 1))
};
static const si_xbar_info xbar_usart3[] = {
      XBAR_USART0_ROW(                        // Index 0
        PIN_TO_PB_MASK2(
            BOARD_USART3_TX_PIN, 
            BOARD_USART3_RX_PIN), 
        XBAR_NUM(BOARD_USART3_TX_PIN, 0))
};
static const si_xbar_info xbar_usart4[] = {
      XBAR_USART1_ROW(                        // Index 0
        PIN_TO_PB_MASK2(
            BOARD_USART4_TX_PIN, 
            BOARD_USART4_RX_PIN), 
        XBAR_NUM(BOARD_USART4_TX_PIN, 0))
};
static const si_xbar_info xbar_spi1[] = {
    XBAR_SPI0_ROW(                            // Index 0
        PIN_TO_PB_MASK3(
            BOARD_SPI1_SCK_PIN, 
            BOARD_SPI1_MISO_PIN, 
            BOARD_SPI1_MOSI_PIN), 
        XBAR_NUM(BOARD_SPI1_MISO_PIN, 0)),
    XBAR_SPI0NSS_ROW(                         // Index 1 
        PIN_TO_PB_MASK(
            BOARD_SPI1_NSS_PIN), 
        XBAR_NUM(BOARD_SPI1_NSS_PIN, 0))
};
static const si_xbar_info xbar_spi2[] = {
    XBAR_SPI1_ROW(                            // Index 0   
        PIN_TO_PB_MASK3(
            BOARD_SPI2_SCK_PIN, 
            BOARD_SPI2_MISO_PIN, 
            BOARD_SPI2_MOSI_PIN), 
        XBAR_NUM(BOARD_SPI2_MISO_PIN, 1)),
    XBAR_SPI1NSS_ROW(                        // Index 1  
        PIN_TO_PB_MASK(
            BOARD_SPI2_NSS_PIN),   
        XBAR_NUM(BOARD_SPI2_NSS_PIN, 1))
};
static const si_xbar_info xbar_spi3[] = {
    XBAR_SPI2_ROW(                            // Index 0 
        PIN_TO_PB_MASK3(
            BOARD_SPI3_SCK_PIN, 
            BOARD_SPI3_MISO_PIN, 
            BOARD_SPI3_MOSI_PIN),  
        XBAR_NUM(BOARD_SPI3_MISO_PIN, 1)),
    XBAR_SPI2NSS_ROW(                         // Index 1 
        PIN_TO_PB_MASK(
            BOARD_SPI3_NSS_PIN),      
        XBAR_NUM(BOARD_SPI3_NSS_PIN, 1))
};
static const si_xbar_info xbar_timer1[] = {
    XBAR_EPCA0_ROW(                           // Index 0   
        PIN_TO_PB_MASK6(
            BOARD_TIMER1C1_PIN, 
            BOARD_TIMER1C2_PIN, 
            BOARD_TIMER1C3_PIN, 
            BOARD_TIMER1C4_PIN, 
            BOARD_TIMER1C5_PIN, 
            BOARD_TIMER1C6_PIN),     
        XBAR_NUM(BOARD_USART1_TX_PIN, 0))
};
static const si_xbar_info xbar_timer2[] = {
    XBAR_PCA0_ROW(                            // Index 0   
        PIN_TO_PB_MASK2(
            BOARD_TIMER2C1_PIN, 
            BOARD_TIMER2C2_PIN),    
    XBAR_NUM(BOARD_TIMER2C1_PIN, 0))
};
static const si_xbar_info xbar_timer3[] = {
    XBAR_PCA1_ROW(                            // Index 0 
        PIN_TO_PB_MASK2(
            BOARD_TIMER3C1_PIN, 
            BOARD_TIMER3C2_PIN), 
        XBAR_NUM(BOARD_TIMER3C1_PIN, 0))
};
static const si_xbar_info xbar_timer4[] = {
    XBAR_TIMER0CT_ROW(                        // Index 0 
        PIN_TO_PB_MASK(
            BOARD_TIMER4CX_PIN), 
        XBAR_NUM(BOARD_TIMER4CX_PIN, 0)),
    XBAR_TIMER0EX_ROW(                        // Index 1 
        PIN_TO_PB_MASK(
            BOARD_TIMER4EX_PIN), 
        XBAR_NUM(BOARD_TIMER4EX_PIN, 0))
};
static const si_xbar_info xbar_timer5[] = {
    XBAR_TIMER1CT_ROW(                        // Index 0 
        PIN_TO_PB_MASK(
            BOARD_TIMER5CX_PIN), 
        XBAR_NUM(BOARD_TIMER5CX_PIN, 0)),
    XBAR_TIMER1EX_ROW(                        // Index 1
        PIN_TO_PB_MASK(
            BOARD_TIMER5EX_PIN), 
        XBAR_NUM(BOARD_TIMER5EX_PIN, 0))
};
static const si_xbar_info xbar_i2s1[] = {
    XBAR_I2S0TX_ROW(                          // Index 0   
        PIN_TO_PB_MASK3(
            BOARD_I2S1TX_WS_PIN, 
            BOARD_I2S1TX_SCK_PIN, 
            BOARD_I2S1TX_SD_PIN), 
        XBAR_NUM(BOARD_I2S1TX_WS_PIN, 0)),
    XBAR_I2S0RX_ROW(                          // Index 1
        PIN_TO_PB_MASK3(
            BOARD_I2S1RX_WS_PIN, 
            BOARD_I2S1RX_SCK_PIN, 
            BOARD_I2S1RX_SD_PIN), 
    XBAR_NUM(BOARD_I2S1RX_WS_PIN, 0))
};
static const si_xbar_info xbar_i2c1[] = {
    XBAR_I2C0_ROW(                            // Index 0
        PIN_TO_PB_MASK2(
            BOARD_I2C1_SDA_PIN, 
            BOARD_I2C1_SCL_PIN), 
    XBAR_NUM(BOARD_I2C1_SDA_PIN, 0))
};
static const si_xbar_info xbar_i2c2[] = {
    XBAR_I2C1_ROW(                            // Index 0
        PIN_TO_PB_MASK2(
            BOARD_I2C2_SDA_PIN, 
            BOARD_I2C2_SCL_PIN), 
    XBAR_NUM(BOARD_I2C2_SDA_PIN, 0))
};
static const si_xbar_info xbar_ahb_out[] = {
    XBAR_AHB_OUT_ROW(                         // Index 0
        PIN_TO_PB_MASK(
            BOARD_AHB_OUT_PIN), 
    XBAR_NUM(BOARD_AHB_OUT_PIN, 1))
};

const xbar_dev_info XBAR_MAP[XBAR_NULL] = {
    // USART
    XBAR_ROW(xbar_usart1, XBAR_NUM(BOARD_USART1_TX_PIN, 1)),
    XBAR_ROW(xbar_usart2, XBAR_NUM(BOARD_USART2_TX_PIN, 1)),
    XBAR_ROW(xbar_usart3, XBAR_NUM(BOARD_USART3_TX_PIN, 0)),
    XBAR_ROW(xbar_usart4, XBAR_NUM(BOARD_USART4_TX_PIN, 0)),

    // SPI
    XBAR_ROW(xbar_spi1, XBAR_NUM(BOARD_SPI1_MISO_PIN, 0)),
    XBAR_ROW(xbar_spi2, XBAR_NUM(BOARD_SPI2_MISO_PIN, 1)),
    XBAR_ROW(xbar_spi3, XBAR_NUM(BOARD_SPI3_MISO_PIN, 1)),

    // Timers
    XBAR_ROW(xbar_timer1, XBAR_NUM(BOARD_TIMER1C1_PIN, 0)),
    XBAR_ROW(xbar_timer2, XBAR_NUM(BOARD_TIMER2C1_PIN, 0)),
    XBAR_ROW(xbar_timer3, XBAR_NUM(BOARD_TIMER3C1_PIN, 0)),
    XBAR_ROW(xbar_timer4, XBAR_NUM(BOARD_TIMER4CX_PIN, 0)),
    XBAR_ROW(xbar_timer5, XBAR_NUM(BOARD_TIMER5CX_PIN, 0)),

    // I2S
    XBAR_ROW(xbar_i2s1, XBAR_NUM(BOARD_I2S1TX_WS_PIN, 0)),

    // I2C
    XBAR_ROW(xbar_i2c1, XBAR_NUM(BOARD_I2C1_SDA_PIN, 0)),
    XBAR_ROW(xbar_i2c2, XBAR_NUM(BOARD_I2C2_SDA_PIN, 0)),

    // AHB out
    XBAR_ROW(xbar_ahb_out, XBAR_NUM(BOARD_AHB_OUT_PIN, 1)),
};


/* Description: Returns the corresponding shorted pin (if there is one) or the pin itself. */
uint8_t board_get_short_num(uint8_t pin)
{
    switch (pin) {
#if defined(PIN_D30_SHORTED)
    case PIN_D30_SHORTED:
        return 30;
#endif // defined(PIN_D30_SHORTED)
#if defined(PIN_D31_SHORTED)
    case PIN_D31_SHORTED:
        return 31;
#endif // defined(PIN_D31_SHORTED)
#if defined(PIN_D32_SHORTED)
    case PIN_D32_SHORTED:
        return 32;
#endif // defined(PIN_D32_SHORTED)
#if defined(PIN_D33_SHORTED)
    case PIN_D33_SHORTED:
        return 33;
#endif // defined(PIN_D33_SHORTED)
#if defined(PIN_D34_SHORTED)
    case PIN_D34_SHORTED:
        return 34;
#endif // defined(PIN_D34_SHORTED)
#if defined(PIN_D35_SHORTED)
    case PIN_D35_SHORTED:
        return 35;
#endif // defined(PIN_D35_SHORTED)
    default:
        return pin;
    }
}

/* Description: Returns 1 if a secondary shorted pin (e.g. D33). */
uint8_t board_pin_invalid(uint8_t pin)
{
    if (pin >= BOARD_NR_GPIO_PINS ||
#if defined(PIN_D30_SHORTED)
    pin == 30 ||
#endif // defined(PIN_D30_SHORTED)
#if defined(PIN_D31_SHORTED)
    pin == 31 ||
#endif // defined(PIN_D31_SHORTED)
#if defined(PIN_D32_SHORTED)
    pin == 32 ||
#endif // defined(PIN_D32_SHORTED)
#if defined(PIN_D33_SHORTED)
    pin == 33 ||
#endif // defined(PIN_D33_SHORTED)
#if defined(PIN_D34_SHORTED)
    pin == 34 ||
#endif // defined(PIN_D34_SHORTED)
#if defined(PIN_D35_SHORTED)
    pin == 35 ||
#endif // defined(PIN_D35_SHORTED)
    0) {
        return 1;
    }
    return 0;
}

// ----------------------------------------------------------------------------
/*
 * USART objects
 */
#define DEFINE_HWSERIAL(name, buff, size, n)    \
            UARTClass name(USART##n,            \
                buff,                           \
                size,                           \
                BOARD_USART##n##_TX_PIN,        \
                BOARD_USART##n##_RX_PIN)



#define USART_RING_BUFF_SIZE 64
struct rbuffTag {
    uint8_t buff[USART_RING_BUFF_SIZE];
}usart_rbuffers[4];

DEFINE_HWSERIAL(Serial1, usart_rbuffers[0].buff, USART_RING_BUFF_SIZE, 1);
DEFINE_HWSERIAL(Serial2, usart_rbuffers[1].buff, USART_RING_BUFF_SIZE, 2);
DEFINE_HWSERIAL(Serial3, usart_rbuffers[2].buff, USART_RING_BUFF_SIZE, 3);
DEFINE_HWSERIAL(Serial4, usart_rbuffers[3].buff, USART_RING_BUFF_SIZE, 4);
UARTClass &Serial = Serial2;


// ----------------------------------------------------------------------------
void __libc_init_array(void);
static void setup_flash(void);
static void setup_clocks(void);
static void setup_nvic(void);
static void setup_adcs(void);
static void setup_timers(void);
void board_setup_clock_prescalers(uint32_t sys_freq);
void board_setup_rtc(void);
void disable_watchdog(void);

void init( void )
{
    disable_watchdog();
    gpio_init_all();
    setup_flash();
    setup_clocks();
    setup_nvic();
    systick_init(clk_get_sys_freq() / 1000 - 1);
    setup_adcs();
    setup_timers();
}

void disable_watchdog(void)
{
    // Turn off watchdog
    *((volatile uint32_t*)0x4002D020) = 0;
    clk_enable_dev(CLK_MISC1);
    *((volatile uint32_t*)0x40030030) = 0xA5;
    *((volatile uint32_t*)0x40030030) = 0xDD;
}

/*
 * Auxiliary routines
 */

static void setup_flash(void) {
    // Enable flash controller clock
    clk_enable_dev(CLK_FLCTRL);

    // Turn on as many Flash "go faster" features as
    // possible. flash_enable_features() just ignores any flags it
    // can't support.
    flash_enable_features(FLASH_PREFETCH | FLASH_ICACHE | FLASH_DCACHE);

    // Erase a page at address
    //void flash_erase_page(uint32 address);

    // Writes 16 bits to flash
    //void flash_write_data(uint32 address, uint16 data[], int32 count);
}


static void setup_clocks(void) {
    uint32 clk_freq = VARIANT_MCK;
    clk_sysclk_src src;

    // Overclock guard
    clk_freq = clk_freq > 80000000 ? 80000000 : clk_freq;

    if (CYCLES_PER_MICROSECOND == 2.5) {
        clk_freq = 2500000;
        src = CLK_SRC_LP_DIV;
    }
    else if (CYCLES_PER_MICROSECOND > 23) {
        // If using pll, then calculate actual frequency changed from bit truncation
        clk_freq = (clk_freq >= 23000000) ? pll_get_actl_freq(RTC_XTAL_HZ, clk_freq) : clk_freq;
        src = CLK_SRC_PLL;
    }
    else {
        clk_freq = 20000000;
        src = CLK_SRC_LP;
    }


    // Init pll and rtc
    board_setup_rtc();
    clk_enable_dev(CLK_PLL);
    pll_set_ref(PLL_SRC_RTC);

    board_setup_clock_prescalers(clk_freq);

/*
 * To change system frequency, call following in order:
 *  1) pll_set_freq  - (if using pll)
 *  2) Get the last clock freqency
 *  3) clk_set_clk_variable
 *  4) clk_switch_sysclk/clk_rcfg_devices - order depends on if we scale up or down.
 */

    if (src == CLK_SRC_PLL) {
        pll_set_freq(clk_freq);
    }
    uint32 last_clk_freq = clk_get_sys_freq();
    clk_set_clk_variable(clk_freq);
    // If new clock is faster, then reconfigure first. This way an under clocked flash speed mode won't cause a crash.
    last_clk_freq < clk_freq ? clk_rcfg_devices() : clk_switch_sysclk(src);
    !(last_clk_freq < clk_freq) ? clk_rcfg_devices() : clk_switch_sysclk(src);
}

/*
 * These addresses are where usercode starts when a bootloader is
 * present.
 */
extern uint32 _sfixed;
#define USER_ADDR_ROM ((uint32)&_sfixed)
#define USER_ADDR_RAM 0x20000000

static void setup_nvic(void) {
    nvic_init(USER_ADDR_ROM, 0);
}

static void adc_default_config(const adc_dev *dev) {
    adc_enable_single_swstart(dev);
    // Default Group Configuration:
    //  Grp 0: 10Bit, Seq Len 1;    Grp 1: 10Bit, Seq Len 16
    //  Grp 2: 12Bit, Seq Len 1;    Grp 3: 12Bit, Seq Len 16
    adc_grp_num w_adc_grp = (adc_grp_num)2;
    for (int i = 0; i < 8; i++) {
        adc_set_tslot_grp(dev, i, w_adc_grp); /**< Associate a timeslot with a group characteristic */
    }
}

static void setup_adcs(void) {
    adc_foreach(adc_default_config);
}

static void timer_default_config(timer_dev *dev) {
    timer_init(dev);
    timer_pause(dev);

    uint32_t period_cyc = 1000 * VARIANT_MCK / 1000000 / 2;
    uint16_t prescaler = (uint16)(period_cyc / 65535 + 1);
    uint16_t overflow = (uint16)((period_cyc + (prescaler / 2)) / prescaler);

    uint32 chnl = 1;
    timer_set_reload(dev, overflow);
    timer_set_prescaler(dev, prescaler);
    while (timer_has_cc_channel(dev, chnl)) {
        // Set channel polarities to 0
        timer_cc_set_pol(dev, chnl, 0);
        timer_set_compare(dev, chnl, 0);
        timer_set_mode(dev, chnl, TIMER_PWM);
        chnl += 1;
    }

    timer_resume(dev);
}

static void setup_timers(void) {

    timer_foreach(timer_default_config);
}

void board_setup_clock_prescalers(uint32_t sys_freq) {
    uint32 apb_div = CLK_APB_HCLK_DIV_1;
    uint32 ahb_div = CLK_AHB_SYSCLK_DIV_1;

    // Set limit on apb bus to 50 MHz
    apb_div = (sys_freq / (1 << ahb_div)) > 50000000 ? CLK_APB_HCLK_DIV_2 : CLK_APB_HCLK_DIV_1;
    clk_set_prescalers(CLK_PRESCALE_APB, apb_div);
    clk_set_prescalers(CLK_PRESCALE_AHB, ahb_div);
}

void board_setup_rtc(void) {
    volatile uint32_t *rtc_base = (volatile uint32 *)0x40029000;

    // Set RTC pins as analog
    gpio_set_modef(GPIOA, 9, GPIO_ANALOG, GPIO_DRIVE_WEAK);
    gpio_set_modef(GPIOA, 10, GPIO_ANALOG, GPIO_DRIVE_WEAK);

    // Enable clock
    clk_enable_dev(CLK_MISC0);

    // Clear interrupts
    nvic_clr_pending_irq(NVIC_RTC0ALRM);
    nvic_irq_enable(NVIC_RTC0ALRM);

    // enable high speed mode
    REG_SET_CLR(*(volatile uint32 *)((uint32)rtc_base + 0x10), 1, 1 << 7);

    // disable auto gain control
    REG_SET_CLR(*rtc_base, 0, 0x00040000);
    // enable bias doubler
    REG_SET_CLR(*rtc_base, 1, 1 << 16);
    // enable auto load cap stepping
    REG_SET_CLR(*rtc_base, 1, 1 << 3);
    // set clk source as rtc
    REG_SET_CLR(*rtc_base, 0, 1 << 30);
    // set as crystal oscillator
    REG_SET_CLR(*rtc_base, 1, 0x00020000);
    // enable module
    REG_SET_CLR(*rtc_base, 1, 1 << 31);

    // Wait at least 20 ms
    delay(20);

    // Poll clock until stable
    while (!((*(volatile uint32 *)((uint32)rtc_base + 0x10)) & 0x20));

    // Poll load capacitance ready
    while (!((*(volatile uint32 *)((uint32)rtc_base + 0x10)) & 0x100));

    // Wait at least 2 ms
    delay(2);
}
