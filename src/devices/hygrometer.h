#ifndef DEVICES_HYGROMETER_H
#define DEVICES_HYGROMETER_H

#include "../interfaces/i2c.h"
#include "device.h"

/**
 * @file
 * @class Hygrometer
 * @brief Class for a Hygrometer module. Uses a I2C Port for communication purposes
 * and has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.3
 */
class Hygrometer : public Device
{
private:
  /**
   * I2C Interface
   */
  std::unique_ptr<I2C> m_i2c_port;
/**
 * @public
 */
public:
  /**
   * Constructor
   * @param device_file is the name of the file for the device
   * @param slave_address is the address of the Hygrometer Module
   */
  Hygrometer (char* device_file, int slave_address);
  /**
   * Constructor
   * @param slave_address is the address of the Hygrometer Module
   */
  Hygrometer(int slave_address);
  /**
   * Reads data from the hygrometer for a given length
   * @param buf is the buffer to save the data into
   * @param length is the length of byte to read
   * @return length on success, otherwise -1 on an Error
   */
  int read (unsigned char* buf, int length);
  /**
   * Writes data from the hygrometer for a given length
   * @param buf is the buffer with the data to write
   * @param length is the length of the written bytes
   * @return length on success, otherwise -1 on an Error
   */
  int write (unsigned char* buf, int length);
  /**
   * Destructor
   */
  ~Hygrometer ();

};
#endif
