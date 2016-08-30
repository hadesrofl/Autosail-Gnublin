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

#ifndef DEVICES_SERIAL_PARAMETER_H_
#define DEVICES_SERIAL_PARAMETER_H_

#include "device_config.h"

/**
 * Default serial device file
 * XXX needs change for serial without using a usb to uart adapter
 */
#define GNUBLIN_DEFAULT_SERIAL "/dev/ttyUSB0"

/**
 * @file
 * @class SerialParameter
 * @ingroup Devices
 * @brief Class for Parameters of Serial Devices. Contains the baudrate of the Serial Interface.
 * @version 0.3
 */
class SerialParameter : virtual public InterfaceParameter
{
  /**
   * @private
   */
private:
  /**
   * Baudrate of the serial interface.
   */
  uint32_t m_baudrate;
  /**
   * @protected
   */
protected:
  /**
   * @public
   */
public:
  /**
   * Constructor for a Serial Parameter
   * @param device_file is the name of the device in linux.
   * @param baudrate is the config of the device
   */
  SerialParameter (char* device_file, DeviceConfig baudrate)
  {
    m_device_file = device_file;
    m_baudrate = distinguish_baudrate (baudrate);
  }
  /**
   * Constructor for a Serial Parameter (called with default device file of gnublin)
   * @param baudrate is the config of the device
   */
  SerialParameter (DeviceConfig baudrate)
  {
    m_device_file = (char*) GNUBLIN_DEFAULT_SERIAL;
    m_baudrate = distinguish_baudrate (baudrate);
  }
  /**
   * Check the DeviceConfig for the correct Baudrate
   * @param baudrate is the given DeviceConfig
   * @return the baudrate as uint32_t
   */
  uint32_t
  distinguish_baudrate (DeviceConfig baudrate)
  {
    uint32_t ret;
    switch (baudrate)
      {
      case DeviceConfig::SERIAL_B4800:
	ret = 4800;
	break;
      case DeviceConfig::SERIAL_B9600:
	ret = 9600;
	break;
      case DeviceConfig::SERIAL_B19200:
	ret = 19200;
	break;
      case DeviceConfig::SERIAL_B38400:
	ret = 38400;
	break;
      case DeviceConfig::SERIAL_B57600:
	ret = 57600;
	break;
      case DeviceConfig::SERIAL_B115200:
	ret = 115200;
	break;
      default:
	ret = 9600;
	break;
      }
    return ret;
  }
  /**
   * Getter for the baudraute of the serial interface
   * @return the baudrate of the serial interface
   */
  inline uint32_t
  get_baudrate () const
  {
    return m_baudrate;
  }
};

#endif /* DEVICES_SERIAL_PARAMETER_H_ */
