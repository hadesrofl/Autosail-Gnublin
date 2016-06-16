/*
 * component_descriptor_enum.h
 *
 *  Created on: Jun 16, 2016
 *      Author: Rene Kremer
 */

#ifndef COMMUNICATION_COMPONENT_DESCRIPTOR_ENUM_H_
#define COMMUNICATION_COMPONENT_DESCRIPTOR_ENUM_H_

/**
 * @file
 * @class ComponentDescriptorEnum
 * @brief Enums for the Devices of this system. Needed to distinguish Devices in
 * FrameInterpreter and for initialization in DeviceManager
 * @details
 * <ul>
 * <li> NUM_COMMUNICATION ( = 6) - Enum for the number of communication numbers to iterate over it in loops </li>
 * </ul>
 * @author Rene Kremer
 * @version 0.2
 */
enum class ComponentDescriptorEnum
{
  ACCELEROMETER = 0x0101,
  ANEMOMETER = 0x0202,
  COMPASS = 0x0303,
  GPS = 0x0404,
  HYGROMETER = 0x0505,
  SERIAL_LINK = 0x0606,
  SERVO_MOTOR = 0x0707,
  STREAM_GENERATOR = 0x0808,
  WESTON_ANEMOMETER = 0x0909,
  WIND_VANE = 0x0A0A
};



#endif /* COMMUNICATION_COMPONENT_DESCRIPTOR_ENUM_H_ */
