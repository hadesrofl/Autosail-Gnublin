#ifndef DEVICES_FILTERED_ACCELEROMETER_H_
#define DEVICES_FILTERED_ACCELEROMETER_H_

#include "filtered_device.h"
#include "i2c_parameter.h"
#include "accelerometer.h"

class FilteredAccelerometer : virtual public FilteredDevice
{
  /**
   * @private
   */
private:
  /**
   * @protected
   */
protected:
  /**
   * @public
   */
public:
  /**
   * Constructor
   */
  FilteredAccelerometer (I2CParameter* interface_parameter, Device_Config device_config, Filter* filter);
  /**
   * Destructor
   */
  ~FilteredAccelerometer ();
};

#endif /* DEVICES_FILTERED_ACCELEROMETER_H_ */
