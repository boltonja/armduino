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
static void configure_gpios(spi_dev *dev, bool as_master);

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


void SPIClass::begin(void) {
    this->begin(this->nssPin());
}

/*
 * Set up/tear down
 */

void SPIClass::begin(uint8_t _pin) {
    spi_init(spi_d);
    configure_gpios(spi_d, true);
    pinMode(_pin, OUTPUT);

    setFrequency(_pin, 4000000);
    setDataMode(_pin, SPI_MODE0);
    setBitOrder(_pin, MSBFIRST);
}

void SPIClass::setBitOrder(uint8_t _pin, BitOrder _bitOrder) {
    uint32_t ch = BOARD_PIN_TO_SPI_CHANNEL(_pin);
    bitOrder[ch] = ((uint32_t)_bitOrder | SPI_DFF_8_BIT |
            SPI_MASTER | SPI_MODE_MST_SLV_3WIRE);
}

void SPIClass::setDataMode(uint8_t _pin, uint8_t _mode) {
    uint32_t ch = BOARD_PIN_TO_SPI_CHANNEL(_pin);
    mode[ch] = _mode;
}

void SPIClass::setFrequency(uint8_t _pin, uint32_t _frequency) {
    uint32_t ch = BOARD_PIN_TO_SPI_CHANNEL(_pin);
    frequency[ch] = _frequency;
}

void SPIClass::setClockDivider(uint8_t _pin, uint32_t divider) {
    // Assume 84MHz to be compatible with Due.
    setFrequency(_pin, 84000000 / divider);
}

void SPIClass::setBitOrder(BitOrder _bitOrder) {
    setBitOrder(this->nssPin(), _bitOrder);
}

void SPIClass::setDataMode(uint8_t _mode) {
    setDataMode(this->nssPin(), _mode);
}

void SPIClass::setFrequency(uint32_t _frequency) {
    setFrequency(this->nssPin(), _frequency);
}

void SPIClass::setClockDivider(uint32_t divider) {
    setClockDivider(this->nssPin(), divider);
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
    pinMode(pin, INPUT);
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

void SPIClass::write(const uint8 *data, uint32 length) {
    uint32 txed = 0;

    // Transfer data
    while (txed < length) {
        txed += spi_tx(this->spi_d, data + txed, length - txed);
    }
    // Wait till transfer is complete
    while (spi_is_busy(this->spi_d));
}


void SPIClass::write(const uint8 *data, uint32 length, uint8_t pin) {
    uint32 txed = 0;

    // Select chip
    digitalWrite(pin, LOW);
    // Transfer data
    while (txed < length) {
        txed += spi_tx(this->spi_d, data + txed, length - txed);
    }
    // Wait till transfer is complete
    while (spi_is_busy(this->spi_d));
    // De-select chip
    digitalWrite(pin, HIGH);
}

byte SPIClass::transfer(uint8_t _data, SPITransferMode _mode) {
    this->transfer(this->nssPin(), _data, _mode);
}

byte SPIClass::transfer(byte _pin, uint8_t _data, SPITransferMode _mode) {
    uint32_t ch = BOARD_PIN_TO_SPI_CHANNEL(_pin);
    spi_master_enable(spi_d, frequency[ch], (spi_mode)mode[ch], bitOrder[ch]);

    if (_mode == SPI_CONTINUE) {
        digitalWrite(_pin, LOW);
        this->write(&_data, 1);
    }
    else {
        this->write(&_data, 1, _pin);
    }
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
