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

#ifndef DEVICES_ACCELEROMETER_H_
#define DEVICES_ACCELEROMETER_H_

#include "../interfaces/i2c.h"
#include "device.h"
#include "i2c_parameter.h"

/**
 * Address of Power CTL Register
 */
#define ACC_POWER_CTL_REGISTER_ADDR 0x2D
/**
 * Value to set Register to Link Bit, Measure Bit, and Wake Up to 8Hz
 */
#define ACC_POWER_CTL_REGISTER_VALUE 0x38
/**
 * Address of the Data Format Register
 */
#define ACC_DATA_FORMAT_REGISTER_ADDR 0x31
/**
 * Address of the first Data Register
 */
#define ACC_X_LSB_REGISTER_ADDR 0x32
/**
 * @file
 * @class Accelerometer
 * @ingroup Devices
 * @brief Class for a Accelerometer Module . Uses a I2C Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.35
 */
class Accelerometer :  public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the accelerometer, setting the configuration for the device
   * @return 1 on success, otherwise -1
   */
  int8_t
  init ();
  /**
   * Range of g for measurement
   */
  DeviceConfig m_range;
  /**
   * Scale Factor to multiply with LSB to get G value
   */
  float m_scale_factor;
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param interface_parameter are the parameters for the interface
   * @param range is the range for measurement of the accelerometer
   * @param descriptor is a pointer to the ComponentDescriptor of this device
   */
  Accelerometer (I2CParameter *interface_parameter, DeviceConfig range,
		 ComponentDescriptor* descriptor);
  /**
   * Reads the Data X, Y and Z Register of the Accelerometer and returns them as a
   * list with allocated memory. The raw values will be transformed to mg where index
   * 0 and 1 are for the x-axis, 2 and 3 for y-axis, 4 and 5 for z-axis.
   *
   * Equal index contains the msb, odd index lsb of the axis.
   *
   * Can be combined to a 2 byte value with: int16_t tsb_x = (data[0] << 8) | data[1];
   * @return list with axis values in mg as stated above.
   */
  std::vector<int8_t>
  read_data ();
  /**
   * Destructor
   */
  ~Accelerometer ();
};

#endif /* DEVICES_ACCELEROMETER_H_ */
