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

#ifndef AUTOPILOT_AUTOPILOT_H_
#define AUTOPILOT_AUTOPILOT_H_

#include "sail_regulator.h"
#include "course_regulator.h"
#include <memory>
#include <stdint.h>
#include <iostream>
#include "../communication/component_descriptor.h"

/**
 * Status code for Autopilot off
 */
#define STATUS_OFF 0x0000
/**
 * Status code for hold course
 */
#define STATUS_HOLD_COURSE 0x0002
/**
 * Status code for manuever in progress
 */
#define STATUS_MANEUVER_IN_PROGRESS 0x00010
/**
 * Status code for manual override
 */
#define STATUS_MANUAL_OVERRIDE 0xFFFF
/**
 * Command from landside to turn pff the autopilot
 */
#define COMMAND_AUTOPILOT_OFF 0x0000
/**
 * Command from landside to set a course
 */
#define COMMAND_SET_COURSE 0x0001
/**
 * Command from landside to hold the current course
 */
#define COMMAND_HOLD_COURSE 0x0002
/**
 * Command from landside to set and hold a course
 */
#define COMMAND_SET_AND_HOLD 0x0003
/**
 * First padding byte for VALUE_AUTOPILOT_STATUS if there is no holding course command
 */
#define PADDING_DIRECTION_1 0x12
/**
 * Second padding byte for VALUE_AUTOPILOT_STATUS if there is no holding course command
 */
#define PADDING_DIRECTION_2 0x34

/**
 * @file
 * @class AutoPilot
 * @ingroup Autopilot
 * XXX NOT SUPPORTED YET
 * @brief Class for the Autopilot. Shall be realized in an own thread. Furthermore
 * an AutoPilot contains a SailRegulator and CourseRegulator each realized in an own
 * thread to regulate Sail and Course autonomously for setting and holding a course.
 *
 * @note Idea for AutoPilot mentioned in Bachelor Thesis "Entwurf, Implementierung
 * und Test eines Autopiloten für die Steuerung eines Modellsegelbootes
 * mit einem Android-Smartphone" by Hannes Range (October 2015)
 * @author Rene Kremer
 * @version 0.2
 */
class AutoPilot
{
  /**
   * @private
   */
private:
  /**
   * Status of the AutoPilot
   * <ul>
   * 	<li>0x0000 = AUTOPILOT OFF</li>
   * 	<li>0x0002 = HOLDING COURSE </li>
   * 	<li>0x0010 = MANOEUVER IN PROGRESS</li>
   * 	<li>0xFFFF = MANUAL OVERRIDE</li>
   * </ul>
   */
  int16_t m_status;
  /**
   * Pointer to the ComponentDescriptor of this component
   */
  std::shared_ptr<ComponentDescriptor> m_descriptor;
  /**
   * Communication number of this component
   */
  uint8_t m_communication_number;
  /**
   * SailRegulator of this AutoPilot
   */
  std::unique_ptr<SailRegulator> sail_regulator;
  /**
   * CourseRegulator of this AutoPilot
   */
  std::unique_ptr<CourseRegulator> course_regulator;
  /**
   * Direction of the course
   */
  int16_t m_direction;
  /**
   * Sets a new status to the AutoPilot
   * @param status is the new status of the pilot
   */
  inline void
  set_status (int16_t status)
  {
    m_status = status;
  }
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
   * @param descriptor is a pointer to the ComponentDescriptor of this component
   * @param communication_number is the communication number as integer
   */
  AutoPilot (std::shared_ptr<ComponentDescriptor> descriptor,
	     uint8_t communication_number);
  /**
   * Gets the current status of the AutoPilot
   * <ul>
   * 	<li>0x0000 = AUTOPILOT OFF</li>
   * 	<li>0x0002 = HOLDING COURSE </li>
   * 	<li>0x0010 = MANOEUVER IN PROGRESS</li>
   * 	<li>0xFFFF = MANUAL OVERRIDE</li>
   * </ul>
   * @return an integer as the status code
   */
  inline int16_t
  get_status () const
  {
    return m_status;
  }
  /**
   * Sets the course to the new direction
   * @param direction is the new direction of the course
   * @return 1 on success, otherwise -1
   */
  int8_t
  set_course (int16_t direction);
  /**
   * Holds the current course
   * @return 1 on success, otherwise -1
   */
  int8_t
  hold_course ();
  /**
   * Gets the direction of the course
   * @return the direction of the current course
   */
  inline int16_t
  get_course () const
  {
    return m_direction;
  }
  /**
   * Activates the AutoPilot
   * @param active is a bool determining if the autopilot shall be active or disabled
   * @return 1 on success, otherwise false
   */
  int8_t
  set_active (bool active);
  /**
   * Gets the ComponentDescriptor of this component
   * @return the descriptor of this specific device
   */
  inline std::shared_ptr<ComponentDescriptor>
  get_component_descriptor () const
  {
    return m_descriptor;
  }
  /**
   * Returns the communication number of this device
   * @return an integer with the communication number
   */
  inline uint8_t
  get_communication_number () const
  {
    return m_communication_number;
  }
  /**
   * Destructor
   */
  ~AutoPilot ();
};

#endif /* AUTOPILOT_AUTOPILOT_H_ */
