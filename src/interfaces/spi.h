#ifndef INTERFACES_S_P_I_H
#define INTERFACES_S_P_I_H

#include "../../gnublin_wo_smtp.h"
#include "interface.h"

/**
 * @file
 * @class SPI
 * @brief Class for a SPI Interface. Implements the abstract Interface class and
 * adds some specific functions of a SPI Interface.
 * @author Rene Kremer
 * @version 0.2
 */
class SPI : public Interface
{
  /**
   * @private
   */
private:
  /**
   * Name of the device file
   */
  const char* m_device_file;
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
   */
  SPI (char* device_file, unsigned int spi_speed);
  /**
   * Receives data from the SPI Port and writes it into the buffer
   * Length indicates the amount of bytes to read
   * @param buf is the buffer to write the received data into
   * @param length is the amount of bytes to read
   * @return the length on success, otherwise -1 as error
   */
  int
  receive (unsigned char* buf, int length);
  /**
   * Sends data via the SPI Port
   * @param buf is the buffer containing the bytes to send
   * @param length is the length of bytes to send
   * @return the length on success, otherwise -1 as error
   */
  int
  send (unsigned char* buf, int length);

  /**
   * Inline Function to set a new SPI mode
   * @param mode is the new mode
   * @return mode on success, otherwise -1 as error
   */
  inline int
  setMode (unsigned char mode)
  {
    return 0;
  }
  ;
  /**
   * Inline Function to get the current SPI mode
   * @return the current SPI mode
   */
  inline int
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
  inline int
  setLSB (unsigned char lsb)
  {
    return 0;
  }
  ;

  /**
   * Inline Function to get the current LSB (least significant bit)
   * @return the LSB on success, otherwise -1 as error
   */
  inline int
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
  inline int
  setLength (unsigned char bits)
  {
    return 0;
  }
  ;
  /**
   * Inline Function to get the length of bits per word
   * @return the amount of bits per word
   */
  inline int
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
  inline int
  setSpeed (unsigned int speed)
  {
    return 0;
  }
  ;
  /**
   * Inline Function to get the current speed of the SPI Interface
   * @return the current speed
   */
  inline int
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
  inline int
  setCS (int cs)
  {
    return 0;
  }
  ;
  /**
   * Destructor
   */
  ~SPI ();

};
#endif
