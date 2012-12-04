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


/**
 * @brief Wirish SPI interface.
 *
 * This implementation uses software slave management, so the caller
 * is responsible for controlling the slave select line.
 */
class SPIClass {
public:
    /**
     * @param spiPortNumber Number of the SPI port to manage.
     */
    SPIClass(spi_dev *spi_device);

    /*
     * Set up/tear down
     */

    /**
     * @brief Turn on a SPI port and set its GPIO pin modes for use as master.
     *
     * SPI port is enabled in full duplex mode, with software slave management.
     *
     * @param frequency Communication frequency
     * @param bitOrder Either LSBFIRST (little-endian) or MSBFIRST (big-endian)
     * @param mode SPI mode to use, one of SPI_MODE_0, SPI_MODE_1,
     *             SPI_MODE_2, and SPI_MODE_3.
     */
    void begin(uint32 frequency, uint32 bitOrder, uint32 mode);

    /**
     * @brief Equivalent to begin(SPI_1_125MHZ, MSBFIRST, 0).
     */
    void begin(void);

    /**
     * @brief Turn on a SPI port and set its GPIO pin modes for use as a slave.
     *
     * SPI port is enabled in full duplex mode, with software slave management.
     *
     * @param bitOrder Either LSBFIRST (little-endian) or MSBFIRST(big-endian)
     * @param mode SPI mode to use
     */
    void beginSlave(uint32 bitOrder, uint32 mode);

    /**
     * @brief Equivalent to beginSlave(MSBFIRST, 0).
     */
    void beginSlave(void);

    /**
     * @brief Disables the SPI port, but leaves its GPIO pin modes unchanged.
     */
    void end(void);
    void end(uint8_t pin);
    /*
     * I/O
     */

    /**
     * @brief Return the next unread byte.
     *
     * If there is no unread byte waiting, this function will block
     * until one is received.
     */
    uint8 read(void);

    /**
     * @brief Read length bytes, storing them into buffer.
     * @param buffer Buffer to store received bytes into.
     * @param length Number of bytes to store in buffer.  This
     *               function will block until the desired number of
     *               bytes have been read.
     */
    void read(uint8 *buffer, uint32 length);

    /**
     * @brief Transmit a byte.
     * @param data Byte to transmit.
     */
    void write(uint8 data);

    /**
     * @brief Transmit multiple bytes.
     * @param buffer Bytes to transmit.
     * @param length Number of bytes in buffer to transmit.
     */
    void write(const uint8 *buffer, uint32 length);
    void write(const uint8 *data, uint32 length, uint8 slaveNum);
    /**
     * @brief Transmit a byte, then return the next unread byte.
     *
     * This function transmits before receiving.
     *
     * @param data Byte to transmit.
     * @return Next unread byte.
     */
    uint8 transfer(uint8 data);
    uint8 transfer(uint8 byte, uint8 slaveNum);

    /*
     * Pin accessors
     */

    /**
     * @brief Return the number of the MISO (master in, slave out) pin
     */
    uint8 misoPin(void);

    /**
     * @brief Return the number of the MOSI (master out, slave in) pin
     */
    uint8 mosiPin(void);

    /**
     * @brief Return the number of the SCK (serial clock) pin
     */
    uint8 sckPin(void);

    /**
     * @brief Return the number of the NSS (slave select) pin
     */
    uint8 nssPin(void);

    /* Escape hatch */

    /**
     * @brief Get a pointer to the underlying libmaple spi_dev for
     *        this SPIClass instance.
     */
    spi_dev* c_dev(void) { return this->spi_d; }

private:
    spi_dev *spi_d;
};

extern SPIClass Spi1;
extern SPIClass Spi2;
extern SPIClass Spi3;
extern SPIClass &SPI;

#endif
