/**
 * Copyright 2016 Rene Kremer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef DEVICES_FILTERED_ACCELEROMETER_H_
#define DEVICES_FILTERED_ACCELEROMETER_H_

#include "filtered_device.h"
#include "i2c_parameter.h"
#include "accelerometer.h"
/**
 * @file
 * @class FilteredAccelerometer
 * @ingroup Devices
 * XXX NOT SUPPORTED YET
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
