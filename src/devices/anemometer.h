#ifndef DEVICES_ANEMOMETER_H_
#define DEVICES_ANEMOMETER_H_

#include "../interfaces/i2c.h"
#include "device.h"
#include "i2c_parameter.h"

/**
 * @file
 * @class Anemometer
 * @brief Class for a Anemometer module. Uses a I2C Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.2
 */
class Anemometer : virtual public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the wind sensor, setting the configuration for the device
   */
  int8_t
  init ();
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param interface_parameter is the parameter of the I2C Interface
   * @param descriptor is the ComponentDescriptor of this device
   */
  Anemometer (I2CParameter *interface_parameter, ComponentDescriptor descriptor);
  /**
   * TODO: Comment with anemometer specific register
   * Reads the Data X, Y and Z Register of the Accelerometer and returns them as a
   * pointer with allocated memory.
   */
  uint8_t*
  read_data ();
  /**
   * Destructor
   */
  ~Anemometer ();

};

#endif /* DEVICES_ANEMOMETER_H_ */
