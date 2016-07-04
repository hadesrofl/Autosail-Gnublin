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
  ACCELEROMETER = 0x550701,
  ANEMOMETER = 0x020201,
  COMPASS = 0x550601,
  GPS = 0x040401,
  GYROSCOPE = 0x550501,
  HYGROMETER = 0x050501,
  SERIAL_LINK = 0x060601,
  SERVO_MOTOR = 0x070701,
  STREAM_GENERATOR = 0x080801,
  WESTON_ANEMOMETER = 0x090901,
  WIND_VANE = 0x0A0A01
};



#endif /* COMMUNICATION_COMPONENT_DESCRIPTOR_ENUM_H_ */
