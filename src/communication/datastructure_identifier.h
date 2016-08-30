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

#ifndef COMMUNICATION_DATA_STRUCTURE_IDENTIFIER_H_
#define COMMUNICATION_DATA_STRUCTURE_IDENTIFIER_H_

/**
 * @file
 * @enum mapper::DataStructureIdentifier
 * @ingroup Enums
 * @brief Enums for the DataStructureIdentifier described in TLVE4 Protocol
 * @author Rene Kremer
 * @version 0.2
 */
enum class DataStructureIdentifier
{
  /**
   * unsigned 8 bit integer
   */
  UINT8 = 0x0,
  /**
   * signed 8 bit integer
   */
  INT8 = 0x1,
  /**
   * signed 16 bit integer
   */
  INT16 = 0x2,
  /**
   * signed 32 bit integer
   */
  INT32 = 0x3,
  /**
   * ASCII coded String
   */
  STRING = 0x4,
  /**
   * Number of DataStructureIdentifiers for iteration purposes
   */
  NUM_IDENTIFIERS
};

#endif /* COMMUNICATION_DATA_STRUCTURE_IDENTIFIER_H_ */
