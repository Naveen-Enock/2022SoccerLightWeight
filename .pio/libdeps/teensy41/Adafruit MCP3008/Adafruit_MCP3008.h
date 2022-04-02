/*!
 *  @file Adafruit_MCP3008.h
 *
 *  This is a library for the MCP3008 - 8-Channel 10-Bit ADC with SPI Interface.
 *
 *  Designed specifically to work with the Adafruit MCP3008.
 *
 *  Pick one up today in the adafruit shop!
 *  ------> https://www.adafruit.com/product/856
 *
 *  These breakout use SPI to communicate, 4 ping are required.
 *
 *  Adafruit invests time and resources providing this open source code,
 *  please support Adafruit andopen-source hardware by purchasing products
 *  from Adafruit!
 *
 *  MIT license, all text above must be included in any redistribution
 */
#ifndef Adafruit_MCP3008_h
#define Adafruit_MCP3008_h

#include <Adafruit_SPIDevice.h>
#include <Arduino.h>

#define MCP3008_SPI_MAX_5V 3600000              ///< SPI MAX Value on 5V pin
#define MCP3008_SPI_MAX_3V 1350000              ///< SPI MAX Value on 3V pin
#define MCP3008_SPI_MAX MCP3008_SPI_MAX_3V      ///< SPI MAX Value
#define MCP3008_SPI_ORDER SPI_BITORDER_MSBFIRST ///< SPI bit order
#define MCP3008_SPI_MODE SPI_MODE0              ///< SPI mode
#define MCP3008_SPI_FREQ 1000000                ///< SPI clock speed

/*!
 *  @brief  Class that stores state and functions for interacting with
 *          MCP3008 Chip
 */
class Adafruit_MCP3008 {
public:
  ~Adafruit_MCP3008();
  bool begin(uint8_t cs = SS, SPIClass *theSPI = &SPI);
  bool begin(uint8_t sck, uint8_t mosi, uint8_t miso, uint8_t cs);
  int readADC(uint8_t channel);
  int readADCDifference(uint8_t differential);

private:
  Adafruit_SPIDevice *spi_dev = NULL; ///< Pointer to SPI bus interface
  uint8_t _cs;
  uint8_t buffer[3];
  int SPIxADC(uint8_t channel, bool differential);
};

#endif
