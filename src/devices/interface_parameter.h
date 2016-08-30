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

#ifndef DEVICES_INTERFACE_PARAMETER_H_
#define DEVICES_INTERFACE_PARAMETER_H_

/**
 * @file
 * @class InterfaceParameter
 * @ingroup Devices
 * @brief Class for Parameters of the Interfaces the Devices use. Parameters might be needed values for the used interfaces.
 * @author Rene Kremer
 * @version 0.3
 */
class InterfaceParameter
{
  /**
   * @protected
   */
protected:
  /**
   * Name of the device file
   */
  char* m_device_file;
  /**
   * @public
   */
public:
  /**
   * Getter for the name of the device file
   * @return the name of the device file
   */
  inline char*
  get_device_file () const
  {
    return m_device_file;
  }
  virtual ~InterfaceParameter(){}
};

#endif /* DEVICES_INTERFACE_PARAMETER_H_ */
