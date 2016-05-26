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
   * Inits the hygrometer, setting the configuration for the device
   */
  int8_t init();
/**
 * @public
 */
public:
  /**
   * Constructor
   * @param device_file is the name of the file for the device
   * @param slave_address is the address of the Hygrometer Module
   */
  Hygrometer (char* device_file, uint8_t slave_address);
  /**
   * Constructor
   * @param slave_address is the address of the Hygrometer Module
   */
  Hygrometer(uint8_t slave_address);
  /**
   * TODO: Comment with hygrometer specific register
   * Reads the Data X, Y and Z Register of the Accelerometer and returns them as a
   * pointer with allocated memory.
   */
  uint8_t* read_data();
  /**
   * Destructor
   */
  ~Hygrometer ();

};
#endif
