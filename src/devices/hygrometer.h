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

#ifndef DEVICES_HYGROMETER_H
#define DEVICES_HYGROMETER_H

#include "../interfaces/i2c.h"
#include "device.h"
#include "i2c_parameter.h"

/**
 * @file
 * @class Hygrometer
 * @ingroup Devices
 * XXX NOT SUPPORTED YET
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
   * @return 1 on success, otherwise -1
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
   * XXX NOT YET SUPPORTED
   */
  std::vector<int8_t> read_data();
  /**
   * Destructor
   */
  ~Hygrometer ();

};
#endif
