#ifndef INTERFACES_HYGROMETER_H
#define INTERFACES_HYGROMETER_H

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
   * Destructor
   */
  ~Hygrometer ();

};
#endif
