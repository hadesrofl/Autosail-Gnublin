#ifndef DEVICES_WIND_SENSOR_H
#define DEVICES_WIND_SENSOR_H

#include "../interfaces/i2c.h"
#include "device.h"

/**
 * @file
 * @class WindSensor
 * @brief Class for a WindSensor module. Uses a I2C Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.2
 */
class WindSensor : public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the wind sensor, setting the configuration for the device
   */
  int
  init ();
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
  WindSensor (int slave_address);
  /**
   * TODO: Comment with windsensor specific register
   * Reads the Data X, Y and Z Register of the Accelerometer and returns them as a
   * pointer with allocated memory.
   */
  unsigned char* read_data();
  /**
   * Destructor
   */
  ~WindSensor ();

};

#endif
