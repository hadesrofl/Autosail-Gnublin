#ifndef INTERFACES_I2_C_H
#define INTERFACES_I2_C_H

#include "../../gnublin_wo_smtp.h"
#include "interface.h"


/**
 * @file
 * @class I2C
 * @brief Class for the I2C Interface. Implements the abstract Interface class and
 * has some more I2C specific functions.
 * @author Rene Kremer
 * @version 0.3
 */
class I2C : public Interface
{
  /**
   * @private
   */
private:
  /**
   * Address of a connected slave
   */
  uint8_t m_slave_address;
  /**
   * I2C port of the gnublin
   */
  std::unique_ptr<gnublin_i2c> m_i2c_port;
  /**
   * Inline function to set a new slave address
   * @param address is the address of a slave
   * @return the address of the slave, otherwise -1 as error
   */
    inline uint8_t
    set_address (int address)
    {
      m_slave_address = address;
      return this->m_i2c_port->setAddress(address);
    }
/**
 * @public
 */
public:
  /**
   * Constructor
   * @param device_file is the name of the file of the device
   * @param address is the address of a connected slave
   */
  I2C (char* device_file, uint8_t address);
/**
 * Receives data from the I2C Port of the Gnublin and saves it into the buffer. Reads
 * only as much bytes as specified in variable length
 * @param buf is the buffer to read into
 * @param length is the amount of bytes to read
 * @return the length on success, otherwise a -1 as error
 */
  int16_t
  receive (uint8_t* buf, int16_t length);
/**
 * Sends data via the I2C Port of the Gnublin. The Buffer contains the bytes to write
 * and length indicates the amount of bytes to send
 * @param buf is the buffer of bytes to send
 * @param length is the amount of bytes to send
 * @return the length on success, otherwise a -1 as error
 */
  int16_t
  send (uint8_t* buf, int16_t length);
/**
 * Inline Function to get the address of the current slave
 * @return the address of the current slave
 */
  inline uint8_t
  get_address () const
  {
    return 0;
  }
  ;
  /**
   * Destructor
   */
  ~I2C ();

};

#endif
