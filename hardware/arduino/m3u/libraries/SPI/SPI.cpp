/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
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
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief Wirish SPI implementation.
 */

#include "SPI.h"


SPIClass Spi1(SPI1);
SPIClass Spi2(SPI2);
SPIClass Spi3(SPI3);
SPIClass &SPI = Spi3;


struct spi_pins {
    uint8 nss;
    uint8 sck;
    uint8 miso;
    uint8 mosi;
};

static const spi_pins* dev_to_spi_pins(spi_dev *dev);

static void enable_device(spi_dev *dev,
                          bool as_master,
                          uint32 frequency,
                          spi_cfg_flag endianness,
                          spi_mode mode);


static const spi_pins board_spi_pins[] = {

    {BOARD_SPI1_NSS_PIN,
     BOARD_SPI1_SCK_PIN,
     BOARD_SPI1_MISO_PIN,
     BOARD_SPI1_MOSI_PIN},
    {BOARD_SPI2_NSS_PIN,
     BOARD_SPI2_SCK_PIN,
     BOARD_SPI2_MISO_PIN,
     BOARD_SPI2_MOSI_PIN},
    {BOARD_SPI3_NSS_PIN,
     BOARD_SPI3_SCK_PIN,
     BOARD_SPI3_MISO_PIN,
     BOARD_SPI3_MOSI_PIN},

};


/*
 * Constructor
 */

SPIClass::SPIClass(spi_dev *spi_device) :
    spi_d(spi_device) {
}

/*
 * Set up/tear down
 */

void SPIClass::begin(uint32 frequency, uint32 bitOrder, uint32 mode) {

    if (mode >= 4 || frequency > 10000000) {

        ASSERT(0);
        return;
    }
    spi_cfg_flag end = bitOrder == MSBFIRST ? SPI_FRAME_MSB : SPI_FRAME_LSB;
    spi_mode m = (spi_mode)mode;
    enable_device(this->spi_d, true, frequency, end, m);
}

void SPIClass::begin(void) {

    this->begin(4000000, MSBFIRST, 0);

}

void SPIClass::beginSlave(uint32 bitOrder, uint32 mode) {
    if (mode >= 4) {
        ASSERT(0);
        return;
    }
    spi_cfg_flag end = bitOrder == MSBFIRST ? SPI_FRAME_MSB : SPI_FRAME_LSB;
    spi_mode m = (spi_mode)mode;

    enable_device(this->spi_d, false, 0, end, m);

}

void SPIClass::beginSlave(void) {
    this->beginSlave(MSBFIRST, 0);
}

void SPIClass::end(void) {
    if (!spi_is_enabled(this->spi_d)) {
        return;
    }
    while (spi_is_busy(this->spi_d))
        ;
    spi_peripheral_disable(this->spi_d);
}


void SPIClass::end(uint8_t pin) {
    // Disable spi
    this->end();

    // TODO [SPI]: Should disable multiple chip select pins when this is called.
    pinMode(this->nssPin(), INPUT);
}

/*
 * I/O
 */

uint8 SPIClass::read(void) {
    uint8 buf[1];
    this->read(buf, 1);
    return buf[0];
}

void SPIClass::read(uint8 *buf, uint32 len) {
    uint32 rxed = 0;
    while (rxed < len) {
        while (!spi_is_rx_nonempty(this->spi_d))
            ;
        buf[rxed++] = (uint8)spi_rx_reg(this->spi_d);
    }
}

void SPIClass::write(uint8 byte) {
    this->write(&byte, 1);
}

void SPIClass::write(const uint8 *data, uint32 length) {
    uint32 txed = 0;

    // Transfer data
    while (txed < length) {
        txed += spi_tx(this->spi_d, data + txed, length - txed);
    }
    // Wait till transfer is complete
    while (spi_is_busy(this->spi_d));
}

// TODO [SPI]: incorporate many slave selects for master mode.
void SPIClass::write(const uint8 *data, uint32 length, uint8 slaveNum) {
    uint32 txed = 0;

    // Select chip
    digitalWrite(this->nssPin(), LOW);
    // Transfer data
    while (txed < length) {
        txed += spi_tx(this->spi_d, data + txed, length - txed);
    }
    // Wait till transfer is complete
    while (spi_is_busy(this->spi_d));
    // De-select chip
    digitalWrite(this->nssPin(), HIGH);
}

uint8 SPIClass::transfer(uint8 byte) {
    this->write(byte);
    return this->read();
}

uint8 SPIClass::transfer(uint8 byte, uint8 slaveNum) {
    this->write(&byte, 1, slaveNum);
    return this->read();
}



/*
 * Pin accessors
 */

uint8 SPIClass::misoPin(void) {
    return dev_to_spi_pins(this->spi_d)->miso;
}

uint8 SPIClass::mosiPin(void) {
    return dev_to_spi_pins(this->spi_d)->mosi;
}

uint8 SPIClass::sckPin(void) {
    return dev_to_spi_pins(this->spi_d)->sck;
}

uint8 SPIClass::nssPin(void) {
    return dev_to_spi_pins(this->spi_d)->nss;
}

/*
 * Auxiliary functions
 */

static void configure_gpios(spi_dev *dev, bool as_master);

static const spi_pins* dev_to_spi_pins(spi_dev *dev) {
    switch (dev->clk_id) {
    case CLK_SPI1: return board_spi_pins;
    case CLK_SPI2: return board_spi_pins + 1;
    case CLK_SPI3: return board_spi_pins + 2;
    default:       return NULL;
    }
}

/* Enables the device in master or slave full duplex mode.  If you
 * change this code, you must ensure that appropriate changes are made
 * to SPIClass::end(). */
static void enable_device(spi_dev *dev,
                          bool as_master,
                          uint32 freq,
                          spi_cfg_flag endianness,
                          spi_mode mode) {
    uint32 cfg_flags = (endianness | SPI_DFF_8_BIT |
                        (as_master ?
                                SPI_MASTER | SPI_MODE_MST_SLV_3WIRE:  // Master flags
                                SPI_MODE_SLV_4WIRE | SPI_SLVNSS_LOW)); // Slave flags

    spi_init(dev);
    configure_gpios(dev, as_master);
    if (as_master) {
        spi_master_enable(dev, freq, mode, cfg_flags);
    } else {
        spi_slave_enable(dev, mode, cfg_flags);
    }
}

static void configure_gpios(spi_dev *dev, bool as_master) {
    const spi_pins *pins = dev_to_spi_pins(dev);
    if (!pins) {
        return;
    }

    // Let pinMode take care of shorted pin cases on board.
    if (as_master) {
        pinMode(pins->nss, OUTPUT);
        pinMode(pins->sck, OUTPUT);
        pinMode(pins->miso, INPUT_PULLUP);
        pinMode(pins->mosi, OUTPUT);
    }
    else {
        pinMode(pins->nss, INPUT_PULLUP);
        pinMode(pins->sck, INPUT_PULLUP);
        pinMode(pins->miso, OUTPUT);
        pinMode(pins->mosi, INPUT_PULLUP);
    }
}
