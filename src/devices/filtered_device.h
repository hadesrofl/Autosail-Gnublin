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

#ifndef DEVICES_FILTERED_DEVICE_H_
#define DEVICES_FILTERED_DEVICE_H_

#include <memory>
#include "device.h"
#include "../utils/filter.h"

/**
 * @file
 * @class FilteredDevice
 * @ingroup Devices
 * XXX NOT SUPPORTED YET
 * @brief Class for an abstract FilteredDevice . Uses the data from a Device and filters
 * it with some Filter.
 * @author Rene Kremer
 * @note It might need some more functions and attributes to read raw data and add
 * it to the filter to improve the quality of the filtered data!
 * @version 0.2
 */
class FilteredDevice
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
   * Device
   */
  std::unique_ptr<Device*> m_device;
  /**
   * Filter
   */
  std::unique_ptr<Filter*> m_filter;
  /**
   * @public
   */
public:
  /**
   * Gets filtered data from a filtered device. The data and amount of data has to
   * be specified by the device.
   * @return a pointer of data bytes from the filtered device
   */
  virtual uint8_t*
  get_filtered_data () = 0;
  /**
   * Destructor
   */
  virtual
  ~FilteredDevice ()
  {

  }
};

#endif /* DEVICES_FILTERED_DEVICE_H_ */
