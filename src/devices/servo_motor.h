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

#ifndef DEVICES_SERVO_MOTOR_H_
#define DEVICES_SERVO_MOTOR_H_

#include "../interfaces/spi_master_select.h"
#include "device.h"
#include "spi_parameter.h"
#include "../utils/int_converter.h"

/**
 * Intra Protocol Tag for set rudder.
 * Parameters are: 2 byte for int16_t angle
 */
#define IP_TAG_SET_RUDDER 0x01
/**
 * Intra Protocol Tag for set rudder.
 * Parameters are: 2 byte for int16_t angle
 */
#define IP_TAG_SET_MS 0x02
/**
 * Intra Protocol Tag for set rudder.
 * Parameters are: 2 byte for int16_t angle
 */
#define IP_TAG_SET_FS 0x03
/**
 * Intra Protocol Tag for set rudder.
 * Parameters are: 2 byte for int16_t angle
 */
#define IP_TAG_SET_HOOK 0x04
/**
 * Intra Protocol Tag for setting all servos.
 * Parameters are: 4*2 byte for int16_t angle starting with
 * rudder, main sail, fore sail, hook
 * angle value 0 for not setting a servo
 */
#define IP_TAG_SET_ALL_SERVOS 0x05
/**
 * Servotype for handling the rudder
 */
#define MECHANIC_RUDDER 0x01
/**
 * Servotype for handling the main sail
 */
#define MECHANIC_MS 0x02
/**
 * Servotype for handling the fore sail
 */
#define MECHANIC_FS 0x03
/**
 * Servotype for handling the hook
 */
#define MECHANIC_HOOK 0x04

/**
 * @file
 * @class ServoMotor
 * @ingroup Devices
 * @brief Class for a ServoMotor on the actor platform. Uses a SPIMasterSelect Interface for communication and
 * has some specific functions for handling data.
 * @author Rene Kremer
 * @version 0.35
 */
class ServoMotor : virtual public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the ServoMotor, setting the configuration for the device
   * @return 1 on success, otherwise -1
   */
  int8_t
  init ();
  /**
   * The current angle of the motor
   */
  int16_t m_angle;
  /**
   * Type of mechanic handled by this servo.
   */
  uint8_t m_mechanic;
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param interface_parameter are the parameters for the SPI Interface
   * @param descriptor is a pointer to the ComponentDescriptor of this device
   * @param mechanic is the type of mechanic handled by this servo
   */
  ServoMotor (SPIParameter *interface_parameter,
	      ComponentDescriptor* descriptor, uint8_t mechanic);
  /**
   * XXX UNUSED, DO NOT CALL
   */
  std::vector<int8_t>
  read_data ();
  /**
   * Sets the motor to a specific angle
   * @param angle is the angle to set to
   */
  void
  set_angle (int16_t angle);
  /**
   * Gets the current angle set by the motor
   * @return the angle as int16_t
   */
  inline int16_t
  get_angle ()
  {
    return m_angle;
  }

  /**
   * Destructor
   */
  ~ServoMotor ();

};

#endif /* DEVICES_SERVO_MOTOR_H_ */
