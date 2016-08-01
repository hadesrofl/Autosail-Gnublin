#ifndef DEVICES_WESTON_ANEMOMETER_H_
#define DEVICES_WESTON_ANEMOMETER_H_

#include "../interfaces/i2c.h"
#include "device.h"
#include "i2c_parameter.h"

/**
 * @file
 * @class WestonAnemometer
 * @ingroup Devices
 * XXX NOT SUPPORTED YET
 * @brief Class for a WestonAnemometer module. Uses a I2C Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.2
 */
class WestonAnemometer : virtual public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the weston anemometer, setting the configuration for the device
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
  WestonAnemometer (I2CParameter *interface_parameter,
		    ComponentDescriptor* descriptor);
  /**
   * XXX NOT YET SUPPORTED
   */
  std::vector<int8_t>
  read_data ();
  /**
   * Destructor
   */
  ~WestonAnemometer ();

};

#endif /* DEVICES_WESTON_ANEMOMETER_H_ */
