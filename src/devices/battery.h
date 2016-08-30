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

#ifndef DEVICES_BATTERY_H_
#define DEVICES_BATTERY_H_

#include "../interfaces/spi_master_select.h"
#include "device.h"
#include "spi_parameter.h"

/**
 * Gets the current of the Battery
 */
#define IP_TAG_GET_CURRENT 0x06

/**
 * @file
 * @class Battery
 * @ingroup Devices
 * @brief Class for the battery on the actor plattform.
 * @author Rene Kremer
 * @version 0.2
 */
class Battery : virtual public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the Battery, setting the configuration for the device
   * @return 1 on success, otherwise -1
   */
  int8_t
  init ();
  /**
   * Value of the current of the Battery
   */
  int16_t m_current;
  /**
   * Value of the voltage of the Battery
   */
  int16_t m_voltage;
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
   * @param interface_parameter are the parameters for the SPI Interface
   * @param descriptor is a pointer to the ComponentDescriptor of this device
   */
  Battery (SPIParameter *interface_parameter, ComponentDescriptor* descriptor);
  /**
   * Reads the voltage and current of the Battery and returns them in a vector.
   * Voltage and current are int16_t values.
   * @return vector of int8_t containing 4 bytes for voltage and current (each 2 byte)
   */
  std::vector<int8_t>
  read_data ();
  /**
   * Gets the current of the Battery
   * @return the current as int16_t
   */
  inline int16_t
  get_current ()
  {
    return m_current;
  }
  /**
   * Gets the voltage of the Battery
   * @return the current as int16_t
   */
  inline int16_t
  get_voltage ()
  {
    return m_voltage;
  }

  /**
   * Destructor
   */
  ~Battery ();
};

#endif /* DEVICES_BATTERY_H_ */
