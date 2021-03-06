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

#ifndef INTERFACES_SERIAL_H_
#define INTERFACES_SERIAL_H_

#include "../../gnublin_wo_smtp.h"
#include "interface.h"

/**
 * @file
 * @class Serial
 * @ingroup Interfaces
 * @brief Interface Class to set up a Serial Device and provide
 * a send and receive function
 * @author Rene Kremer
 * @version 0.3
 */
class Serial : public Interface
{
  /**
   * @private
   */
private:
  /**
   * Name of the device file
   */
  //const char* m_device_file;
  /**
   * Value of the baudrate
   */
  uint32_t m_baudrate;
  /**
   * @param device_file is the name of the file the device is listening to
   */
  /**
   * Serial port of the gnublin
   */
  std::unique_ptr<gnublin_serial> m_serial_port;

  /**
   * @param baudrate is the value of the baudrate
   */
  inline void
  set_baudrate (uint32_t baudrate){
    m_baudrate = baudrate;
  }
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param device_file is the name of the file the device is listening to
   * @param baudrate is the value of the baudrate
   */
  Serial (char* device_file, uint32_t baudrate);
  /**
   * Function to receive data
   * @param buf is a pointer to a buffer to write to data into
   * @param length is the length of the data which shall be received
   * @return on success the length of the data, if there was an error -1 is returned
   */
  int16_t
  receive (uint8_t* buf, int16_t length);
  /**
   * @param buf is a pointer to a buffer with the data to be sent
   * @param length is the length of the data that shall be sent
   * @return on success the length of the data, if there was an error -1 is returned
   */
  int16_t
  send (uint8_t* buf, int16_t length);
  /**
   * Destructor
   */
  ~Serial ();
};

#endif /* INTERFACES_SERIAL_H_ */
