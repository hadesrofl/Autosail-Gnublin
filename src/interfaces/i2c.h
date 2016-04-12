#ifndef KLASSENDIAGRAMM_INTERFACES_I2_C_H
#define KLASSENDIAGRAMM_INTERFACES_I2_C_H

#include "../../gnublin_wo_smtp.h"
#include "interface.h"
/**
 * @file
 * @class I2C
 * @brief Class for the I2C Interface. Implements the abstract Interface class and
 * has some more I2C specific functions.
 * @author Rene Kremer
 * @version 0.2
 */
class I2C : public Interface
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
   * Address of a connected slave
   */
  int m_slave_address;
  /**
   * I2C Port of the gnublin
   */
  gnublin_i2c* m_i2c_port;
/**
 * @public
 */
public:
  /**
   * Constructor
   * @param device_file is the name of the file of the device
   * @param address is the address of a connected slave
   */
  I2C (char* device_file, int address);
/**
 * Receives data from the I2C Port of the Gnublin and saves it into the buffer. Reads
 * only as much bytes as specified in variable length
 * @param buf is the buffer to read into
 * @param length is the amount of bytes to read
 * @return the length on success, otherwise a -1 as error
 */
  int
  receive (unsigned char* buf, int length);
/**
 * Sends data via the I2C Port of the Gnublin. The Buffer contains the bytes to write
 * and length indicates the amount of bytes to send
 * @param buf is the buffer of bytes to send
 * @param length is the amount of bytes to send
 * @return the length on success, otherwise a -1 as error
 */
  int
  send (unsigned char* buf, int length);
/**
 * Inline function to set a new slave address
 * @param address is the address of a slave
 * @return the address of the slave, otherwise -1 as error
 */
  inline int
  set_address (int address)
  {
    return 0;
  }
  ;
/**
 * Inline Function to get the address of the current slave
 * @return the address of the current slave
 */
  inline int
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
