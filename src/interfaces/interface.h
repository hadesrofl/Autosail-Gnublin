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

#ifndef INTERFACES_INTERFACE_H_
#define INTERFACES_INTERFACE_H_

#include <memory>
#include <stdint.h>

/**
 * @file
 * @class Interface
 * @ingroup Interfaces
 * @brief Abstract Interface class which needs an implementation of the specific
 * receive, send and a destructor of a derived classes. Some Interfaces need some
 * more functionality or attributes but they all have a receive or send function
 * @author Rene Kremer
 * @version 0.2
 */
class Interface
{
  /**
   * @protected
   */
protected:
  /**
   * Name of the device file
   */
  const char* m_device_file;
  /**
   * Sets the name of the device file of this interface
   * @param device_file is a constant char pointer containing the name of the file
   * @return the name of the file
   */
  inline const char*
  set_device_file (const char* device_file)
  {
    m_device_file = device_file;
    return m_device_file;
  }
  /**
   * @public
   */
public:
  /**
   * Function to receive some data via an adapter
   * @param buf is a pointer to the target buffer
   * @param length is the length of the data to be read
   * @return on success returns the length, if there is an error -1 is returned
   */
  virtual int16_t
  receive (uint8_t* buf, int16_t length) =0;
  /**
   * Function to receive some data via an adapter
   * @param buf is a pointer to the target buffer
   * @param length is the length of the data to be read
   * @return on success returns the length, if there is an error -1 is returned
   */
  virtual int16_t
  send (uint8_t* buf, int16_t length) =0;
  /**
   * Gets the name of the device file of this interface
   * @return the name of the device file as char pointer
   */
  inline const char*
  get_device_file ()
  {
    return m_device_file;
  }
  /**
   * Default Destructor
   */
  virtual
  ~Interface ()
  {
  }
};

#endif /* INTERFACES_INTERFACE_H_ */
