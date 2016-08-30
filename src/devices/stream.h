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

#ifndef DEVICES_STREAM_H_
#define DEVICES_STREAM_H_

#include "device.h"
#include <stdint.h>
/**
 * @file
 * @class Stream
 * @ingroup Devices
 * @brief Class used in StreamGenerator. Contains a Device and the period to
 * generate new data
 * @author Rene Kremer
 * @version 0.2
 */
class Stream
{
  /**
   * @private
   */
private:
  /**
   * Pointer of the Device to watch over in this stream
   */
  std::shared_ptr<Device> m_device;
  /**
   * Time interval to generate new data
   */
  uint16_t m_period;
  /**
   * Is the Stream active or disabled?
   */
  bool m_active;
  /**
   * Communication Number of the Device
   */
  uint8_t m_communication_number;
  /**
   * @public
   */
public:
  /**
   * Constructor - Sets this Stream active for a given period and device
   * @param device is the pointer to the Device
   * @param communication_number is the communication number of the device
   * @param period is the period triggering this Stream
   */
  Stream (std::shared_ptr<Device> device, uint8_t communication_number,
	  uint32_t period)
  {
    m_device = device;
    m_period = period;
    m_communication_number = communication_number;
    m_active = true;
  }
  /**
   * Gets the Device of this Stream
   * @return a pointer to the Device
   */
  std::shared_ptr<Device>
  inline
  get_device () const
  {
    return m_device;
  }
  /**
   * Gets the period in ms triggering this Stream
   * @return period in ms to trigger the Stream
   */
  uint16_t
  inline
  get_period () const
  {
    return m_period;
  }
  /**
   * Gets the communication number of the Device of this Stream
   * @return the communication number
   */
  uint8_t inline
  get_communication_number () const
  {
    return m_communication_number;
  }

  /**
   * Sets a new period to triggering this stream.
   * @param period is the new period
   */
  void
  inline
  set_period (uint16_t period)
  {
    m_period = period;
  }
  /**
   * Sets this Stream to active (true) or disabled (false)
   * @param active is a bool determining if the Stream is active or disabled
   */
  void
  inline
  set_active (bool active)
  {
    m_active = active;
  }
  /**
   * Is the Stream active or disabled?
   * @return true if it is active, otherwise false
   */
  bool
  inline
  is_active () const
  {
    return m_active;
  }
  /**
   * Destructor
   */
  ~Stream ()
  {
  }

};

#endif /* DEVICES_STREAM_H_ */
