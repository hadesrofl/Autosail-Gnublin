#ifndef INTERFACES_S_P_I_MASTER_SELECT_H
#define INTERFACES_S_P_I_MASTER_SELECT_H

#include "../../gnublin_wo_smtp.h"
#include "interface.h"

#define GNUBLIN_SPI_DEVICE "/dev/spidev0.0"

/**
 * @file
 * @class SPI
 * @brief Class for a SPI Interface. Implements the abstract Interface class and
 * adds some specific functions of a SPI Interface.
 * @author Rene Kremer
 * @version 0.2
 */
class SPIMasterSelect : public Interface
{
  /**
   * @private
   */
private:
  /**
   * Gnublin SPI Port
   */
  std::unique_ptr<gnublin_spi> m_spi_port;
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param device_file is the name of the file of the device
   * @param spi_speed is the speed of the spi bus
   */
  SPIMasterSelect (char* device_file, uint16_t spi_speed);
  /**
   * Constructor
   * @param spi_speed is the speed of the spi bus
   */
  SPIMasterSelect (uint16_t spi_speed);
  /**
   * Receives data from the SPI Port and writes it into the buffer
   * Length indicates the amount of bytes to read
   * @param buf is the buffer to write the received data into
   * @param length is the amount of bytes to read
   * @return the length on success, otherwise -1 as error
   */
  int16_t
  receive (uint8_t* buf, int16_t length);
  /**
   * Sends data via the SPI Port
   * @param buf is the buffer containing the bytes to send
   * @param length is the length of bytes to send
   * @return the length on success, otherwise -1 as error
   */
  int16_t
  send (uint8_t* buf, int16_t length);

  /**
   * Inline Function to set a new SPI mode
   * @param mode is the new mode
   * @return mode on success, otherwise -1 as error
   */
  inline int8_t
  setMode (uint8_t mode)
  {
    return 0;
  }
  ;
  /**
   * Inline Function to get the current SPI mode
   * @return the current SPI mode
   */
  inline uint8_t
  getMode () const
  {
    return 0;
  }
  ;
  /**
   * Inline Function to set the LSB (least significant bit)
   * @param lsb is the least significant bit
   * @return the LSB on success, otherwise -1 as error
   */
  inline int8_t
  setLSB (uint8_t lsb)
  {
    return 0;
  }
  ;

  /**
   * Inline Function to get the current LSB (least significant bit)
   * @return the LSB on success, otherwise -1 as error
   */
  inline uint8_t
  getLSB () const
  {
    return 0;
  }
  ;

  /**
   * Sets the length of bits per word
   * @param bits is the amount of bits per word
   * @return the new bits per word on success, otherwise -1 as error
   */
  inline int8_t
  setLength (uint8_t bits)
  {
    return 0;
  }
  ;
  /**
   * Inline Function to get the length of bits per word
   * @return the amount of bits per word
   */
  inline uint16_t
  getLength () const
  {
    return 0;
  }
  ;
  /**
   * Inline Function to set the speed of the SPI
   * @param speed is the new speed of the SPI
   * @return speed on success, otherwise -1 as error
   */
  inline int8_t
  setSpeed (uint16_t speed)
  {
    return 0;
  }
  ;
  /**
   * Inline Function to get the current speed of the SPI Interface
   * @return the current speed
   */
  inline uint16_t
  getSpeed () const
  {
    return 0;
  }
  ;
  /**
   * Inline Function to set the chip select
   * @param cs is the new chip select
   * @return chip select on success, otherwise -1 as error
   */
  inline int8_t
  setCS (uint8_t cs)
  {
    return 0;
  }
  ;
  /**
   * Destructor
   */
  ~SPIMasterSelect ();

};
#endif
