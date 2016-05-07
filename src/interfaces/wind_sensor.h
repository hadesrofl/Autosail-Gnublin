#ifndef INTERFACES_WIND_SENSOR_H
#define INTERFACES_WIND_SENSOR_H

#include "i2c.h"

/**
 * @file
 * @class WindSensor
 * @brief Class for a WindSensor module. Uses a I2C Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.2
 */
class WindSensor
{
  /**
   * @private
   */
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
   * @param device_file is the name of the I2C Interface this devices listens to
   * @param slave_address is the address of the Windsensor Module
   */
  WindSensor (char* device_file, int slave_address);
  /**
   * Constructor
   * @param slave_address is the address of the Windsensor Module
   */
  WindSensor(int slave_address);
  /**
   * Destructor
   */
  ~WindSensor ();

};

#endif
