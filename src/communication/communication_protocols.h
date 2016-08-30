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

#ifndef COMMUNICATION_PROTOCOLS_H_
#define COMMUNICATION_PROTOCOLS_H_

/**
 * @file
 * @enum mapper::CommunicationProtocol
 * @ingroup Enums
 * @brief Enum class to switch at start of the firmware to the specified protocol
 * mentioned in the conf file
 *
 * @author Rene Kremer
 * @version 0.2
 */
enum class CommunicationProtocol
{
  /**
   * The given protocol isn't supported by this firmware
   */
  UNSUPPORTED_PROTOCOL = 0x00,
  /**
   * TLVE4 Protocol Version
   */
  TLVE4 = 0x01,
  /**
   * TLVE5 Protocol Version
   */
  TLVE5 = 0x02,
  /**
   * JSON4 Protocol Version
   */
  JSON4 = 0x03,
  /**
   * JSON5 Protocol Version
   */
  JSON5 = 0x04
};

#endif /* COMMUNICATION_PROTOCOLS_H_ */
