/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include "variant.h"
#include <stdio.h>

enum SPITransferMode {
    SPI_CONTINUE,
    SPI_LAST
};
/**
 * @brief Wirish SPI interface.
 *
 * This implementation uses software slave management, so the caller
 * is responsible for controlling the slave select line.
 */
class SPIClass {
public:
    SPIClass(spi_dev *spi_device);


    void begin(uint8_t _pin);
    void begin(void);

    void end(void);
    void end(uint8_t pin);

    uint8 read(void);
    void read(uint8 *buffer, uint32 length);

    void write(uint8_t data) {this->write(&data, 1);}
    void write(const uint8 *data, uint32 length);
    void write(const uint8 *data, uint32 length, uint8_t pin);

    byte transfer(uint8_t _data, SPITransferMode _mode = SPI_LAST);
    byte transfer(byte _channel, uint8_t _data, SPITransferMode _mode = SPI_LAST);

    // These methods sets a parameter on a single pin
    void setBitOrder(uint8_t _pin, BitOrder);
    void setDataMode(uint8_t _pin, uint8_t);
    void setFrequency(uint8_t _pin, uint32_t freq);
    void setClockDivider(uint8_t _pin, uint32_t divider);

    // These methods sets the same parameters but on default pin BOARD_SPI_DEFAULT_SS
    void setBitOrder(BitOrder _order);
    void setDataMode(uint8_t _mode);
    void setFrequency(uint32_t freq);
    void setClockDivider(uint32_t divider);

    uint8 misoPin(void);
    uint8 mosiPin(void);
    uint8 sckPin(void);
    uint8 nssPin(void);

    spi_dev* c_dev(void) { return this->spi_d; }

private:
    uint32_t bitOrder[SPI_CHANNELS_NUM];
    uint32_t frequency[SPI_CHANNELS_NUM];
    uint32_t mode[SPI_CHANNELS_NUM];
    spi_dev *spi_d;
};

extern SPIClass Spi1;
extern SPIClass Spi2;
extern SPIClass Spi3;
extern SPIClass &SPI;

#endif
