#ifndef DEVICES_FILTERED_ACCELEROMETER_H_
#define DEVICES_FILTERED_ACCELEROMETER_H_

#include "filtered_device.h"
#include "i2c_parameter.h"
#include "accelerometer.h"
/**
 * @file
 * @class FilteredAccelerometer
 * @ingroup Devices
 * @brief Class for an Accelerometer which reads data but filters them before they
 * will be returned. Uses the data from a Device and filters it with some Filter.
 * @author Rene Kremer
 * @version 0.2
 */
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
   *
   * device needs to be initialized before it will be used in a FilteredDevice.
   * The Constructor does not initialize a Device !
   *
   * @param device is the device which data shall be filtered
   * @param filter is the filter to filter the data with
   */
  FilteredAccelerometer (Device* device, Filter* filter);
  /**
   * Gets the data of a filtered accelerometer
   * @return a pointer of data bytes from the accelerometer
   */
  uint8_t*
  get_filtered_data ();
  /**
   * Destructor
   */
  ~FilteredAccelerometer ();
};

#endif /* DEVICES_FILTERED_ACCELEROMETER_H_ */
