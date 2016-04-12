#ifndef KLASSENDIAGRAMM_INTERFACES_HYGROMETER_H
#define KLASSENDIAGRAMM_INTERFACES_HYGROMETER_H

#include "i2c.h"
/**
 * @file
 * @class Hygrometer
 * @brief Class for a Hygrometer module. Uses a I2C Port for communication purposes
 * and has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.2
 */
class Hygrometer
{
private:
  /**
   * I2C Interface
   */
  I2C* m_i2c_port;

public:
  /**
   * Constructor
   * @param device_file is the name of the file for the device
   * @param slave_address is the address of a connected slave
   */
  Hygrometer (char* device_file, int slave_address);
  /**
   * Destructor
   */
  ~Hygrometer ();

};
#endif
