#ifndef DEVICES_WINDVANE_H_
#define DEVICES_WINDVANE_H_

#include "../interfaces/i2c.h"
#include "device.h"
#include "i2c_parameter.h"

#define WIND_VANE_DATA_REGISTER 0x80

/**
 * @file
 * @class WindVane
 * @ingroup Devices
 * @brief Class for a WindVane module. Uses a I2C Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.2
 */
class WindVane : virtual public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the wind vane, setting the configuration for the device
   * @return 1 on success, otherwise -1
   */
  int8_t
  init ();
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param interface_parameter are the parameters for the I2C Interface
   * @param descriptor is a pointer to the ComponentDescriptor of this device
   */
  WindVane (I2CParameter *interface_parameter, ComponentDescriptor* descriptor);
  /**
   * Reads the data register of the Anemometer and returns a vector of two int8_t
   * bytes containing the velocity of the wind
   * @return a vector of two int8_t bytes containing the velocity of the wind
   */
  std::vector<int8_t> read_data();
  /**
   * Destructor
   */
  ~WindVane ();

};



#endif /* DEVICES_WINDVANE_H_ */
