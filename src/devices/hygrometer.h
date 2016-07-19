#ifndef DEVICES_HYGROMETER_H
#define DEVICES_HYGROMETER_H

#include "../interfaces/i2c.h"
#include "device.h"
#include "i2c_parameter.h"

/**
 * @file
 * @class Hygrometer
 * @brief Class for a Hygrometer module. Uses a I2C Port for communication purposes
 * and has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.3
 */
class Hygrometer : virtual public Device
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
   * @param interface_parameter are the parameters for the I2C Interface
   * @param descriptor is a pointer to the ComponentDescriptor of this device
   */
  Hygrometer (I2CParameter *interface_parameter, ComponentDescriptor* descriptor);
  /**
   * TODO: Comment with hygrometer specific register
   * Reads the Data X, Y and Z Register of the Accelerometer and returns them as a
   * pointer with allocated memory.
   */
  std::vector<int8_t> read_data();
  /**
   * Destructor
   */
  ~Hygrometer ();

};
#endif
