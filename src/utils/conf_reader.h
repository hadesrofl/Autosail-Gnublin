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

#ifndef UTILS_CONF_READER_H_
#define UTILS_CONF_READER_H_

#include <vector>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <sstream>
#include <string>
#include "../communication/communication_protocols.h"

/**
 * Name of default config file for devices
 */
#define FW_CONFIG "config/devices.conf"
/**
 * @file
 * @class ConfReader
 * @ingroup Utils
 * @brief Class for a ConfReader. Reads the config file for the devices.
 * A conf file defines the protocol type and version given via:
 *
 * <br/>
 * <br/>
 * Protocol: 0x01
 * <br/>
 * Version: 4 1 5
 * <br/>
 *
 * Where 0x01 is a protocol mentioned in Protocol. 4 1 5 is the splitted
 * version number: Major Version 4, Minor Version 15
 *
 * Also the config file contains the devices of the boat and their configuration.
 * The syntax for that is the following:
 * <br/>
 * <br/>
 * Component: [Name]
 * <br/>
 * Component-Class: 0x[First Number][Second Number]
 * <br/>
 * Component-Attribute: 0x[First Number][Second Number]
 * <br/>
 * Component-Number: 0x[First Number][Second Number]
 * <br/>
 * Communication-Number: 0x[First Number][Second Number]
 * <br/>
 * Config: [Number specified in Device_Config]
 * <br/>
 * <br/>
 * Component Class and Attribute is as specified in the protocol. Component
 * Number is a number of choosing. Communication Number is a number between 1 and 30
 * in Hex. The same number mustn't used on two devices!
 * Config is a values as specified in Device_Config.
 *
 * Example Code:
 *  <pre>
 *   <code>
 *   Boat-ID: 0x01
 *   Protocol: 0x01
 *   Version: 4 0 0
 *
 *   Component: Hull
 *   Component-Class: 0x01
 *   Component-Attribute: 0x01
 *   Component-Number: 0x02
 *   Communication-Number: 0x00
 *   Config: 0x00
 *
 *   Component: Rudder
 *   Component-Class: 0x0C
 *   Component-Attribute: 0x44
 *   Component-Number: 0x01
 *   Communication-Number: 0x01 //hardcoded in code for priority commands
 *   Config: 0x01
 *
 *   Component: Main-Sail
 *   Component-Class: 0x0C
 *   Component-Attribute: 0x45
 *   Component-Number: 0x01
 *   Communication-Number: 0x02 //hardcoded in code for priority commands
 *   Config: 0x01
 *
 *   Component: Fore-Sail
 *   Component-Class: 0x0C
 *   Component-Attribute: 0x46
 *   Component-Number: 0x01
 *   Communication-Number: 0x03 //hardcoded in code for priority commands
 *   Config: 0x01
 *
 *   Component: Serial-Link
 *   Component-Class: 0x0C
 *   Component-Attribute: 0x48
 *   Component-Number: 0x01
 *   Communication-Number: 0x04
 *   Config: 0x01
 *
 *   Component: Accelerometer
 *   Component-Class: 0x55
 *   Component-Attribute: 0x07
 *   Component-Number: 0x01
 *   Communication-Number: 0x05
 *   Config: 0x00
 *
 *   Component: Compass
 *   Component-Class: 0x55
 *   Component-Attribute: 0x06
 *   Component-Number: 0x01
 *   Communication-Number: 0x06
 *   Config: 0x20
 *
 *   Component: Gyroscope
 *   Component-Class: 0x55
 *   Component-Attribute: 0x05
 *   Component-Number: 0x01
 *   Communication-Number: 0x07
 *   Config: 0
 *
 *   Component: GPS
 *   Component-Class: 0x54
 *   Component-Attribute: 0x09
 *   Component-Number: 0x01
 *   Communication-Number: 0x08
 *   Config: 0x60
 *
 *   Component: Stream-Controlling-Unit
 *   Component-Class: 0x0D
 *   Component-Attribute: 0x01
 *   Component-Number: 0x01
 *   Communication-Number: 0x09
 *   Config: 0x00
 *
 *   Component: Autopilot
 *   Component-Class: 0x0D
 *   Component-Attribute: 0x02
 *   Component-Number: 0x01
 *   Communication-Number: 0x0A
 *   Config: 0x00
 *   </code
 *   >
 *  </pre>
 * @author Rene Kremer
 * @version 0.3
 */
class ConfReader
{
  /**
   * @private
   */
private:
  /**
   * ID of the boat
   */
  uint8_t m_boat_id;
  /**
   * List of Bytes for Devices. Will be used in DeviceManager
   */
  std::vector<uint8_t> m_device_configs;
  /**
   * List of Bytes for Protocol Type and Version Number
   */
  std::vector<uint8_t> m_protocol_config;
  /**
   * List of Bytes for the StreamGenerator
   */
  std::vector<uint8_t> m_stream_generator_config;
  /**
   * List of Bytes for the AutoPilot
   */
  std::vector<uint8_t> m_autopilot_config;
  /**
   * File to read
   */
  const char* m_file;
  /**
   * Reads a given config file
   *
   * @return on success 1, otherwise -1
   */
  int8_t
  read_config ();
  /**
   * @public
   */
public:
  /**
   * Constructor
   */
  ConfReader ();
  /**
   * Constructor
   * @param file is the file to read
   */
  ConfReader (const char* file);
  /**
   * Gets a vector with all device configs listed in the config file
   * @return a vector with all device configs of the config file in
   * 5 byte representation (component class, component attribute, component number,
   * communication number, config of device)
   * Communication Number and Config are 0 if these are not needed
   * (like for non communicating components or devices without configuration)
   */
  inline std::vector<uint8_t>
  get_device_configs () const
  {
    return m_device_configs;
  }
  /**
   * Gets the protocol type e.g. 'TLVE4' as value of the mapper::CommunicationProtocol Enum
   * @return the Protocol Enum specified in the conf file. On error returns NULL
   */
  inline CommunicationProtocol
  get_protocol () const
  {
    if (m_protocol_config.size () > 0)
      {
	return static_cast<CommunicationProtocol> (m_protocol_config.at (0));
      }
    return CommunicationProtocol::UNSUPPORTED_PROTOCOL;
  }
  /**
   * Gets the bytes of the protocol version. The first byte is the major version
   * number. The second byte the first decimal of the minor version number.
   * The third byte the second decimal of the minor version number
   * @return a vector containing the bytes of the protocol version.
   * On error returns an empty vector
   */
  inline std::vector<uint8_t>
  get_protocol_version () const
  {
    std::vector<uint8_t> protocol_version;
    if (m_protocol_config.size () == 4)
      {
	protocol_version.push_back (m_protocol_config.at (1));
	protocol_version.push_back (m_protocol_config.at (2));
	protocol_version.push_back (m_protocol_config.at (3));
      }
    return protocol_version;
  }
  /**
   * Gets the boat id
   * @return the id of this boat
   */
  inline uint8_t
  get_boat_id () const
  {
    return m_boat_id;
  }
  /**
   * Gets a vector with the config bytes of the StreamGenerator
   * @return vector containing the config bytes of the StreamGenerator
   */
  inline std::vector<uint8_t>
  get_stream_generator_config () const
  {
    return m_stream_generator_config;
  }
  /**
   * Gets a vector with the config bytes of the AutoPilot
   * @return vector containing the config bytes of the AutoPilot
   */
  inline std::vector<uint8_t>
  get_autopilot_config () const
  {
    return m_autopilot_config;
  }

};
#endif /* UTILS_CONF_READER_H_ */
