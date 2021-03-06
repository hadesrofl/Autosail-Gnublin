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

#ifndef DEVICES_COMPASS_H_
#define DEVICES_COMPASS_H_

#include "../interfaces/i2c.h"
#include "device.h"
#include "i2c_parameter.h"

/**
 * Address of Config A Register
 */
#define COMPASS_CONFIG_A_REGISTER_ADDR 0x00
/**
 * Set Configuration Register A (1 samples average, 15hz, normal measurement)
 */
#define COMPASS_CONFIG_A_REGISTER_VALUE 0x10
/**
 * Address of Config B Register
 */
#define COMPASS_CONFIG_B_REGISTER_ADDR 0x01
/**
 * Address of the Mode Register
 */
#define COMPASS_MODE_REGISTER_ADDR 0x02
/**
 * Set Mode Register to Continous Measurement Mode
 */
#define COMPASS_MODE_REGISTER_VALUE 0x00
/**
 * Address for the first Data Register
 */
#define COMPASS_X_MSB_REGISTER_ADDR 0x03

/**
 * @file
 * @class Compass
 * @ingroup Devices
 * @brief Class for a Compass Module . Uses a I2C Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.35
 */
class Compass : virtual public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the compass, setting the configuration for the device
   * @return 1 on success, otherwise -1
   */
  int8_t
  init ();
  /**
   * Gain value for measurement
   */
  DeviceConfig m_gain;
  /**
   * Scaling Factor to calculate LSB to mg
   */
  float m_scale_factor;
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param interface_parameter is the parameter of the I2C Interface
   * @param gain is the range of the measurements
   * @param descriptor is a pointer to the ComponentDescriptor of this device
   */
  Compass (I2CParameter *interface_parameter, DeviceConfig gain, ComponentDescriptor* descriptor);
  /**
   * Reads the Data X, Y and Z Register of the Compass and returns them as a
   * list with allocated memory.
   */
  std::vector<int8_t>
  read_data ();
  /**
   * Destructor
   */
  ~Compass ();
};

#endif /* DEVICES_COMPASS_H_ */
