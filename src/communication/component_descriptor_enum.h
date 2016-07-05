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
  /*------------------------------------------
   Actor
   ------------------------------------------*/
  SERVO_MOTOR_RUDDER = 0x040004,
  SERVO_MOTOR_MAIN_SAIL = 0x050005,
  SERVO_MOTOR_FORE_SAIL = 0x060006,
  SERIAL_LINK = 0x080008,
  /*------------------------------------------
   Mechanical
   ------------------------------------------*/
  HULL_TYPE = 0x010102,
  /*------------------------------------------
   On-Board Software
   ------------------------------------------*/
  STREAM_CONTROL_UNIT = 0x0D0101,
  AUTOPILOT = 0x0D0201,
  /*------------------------------------------
   System Info
   ------------------------------------------*/
  POWER_SUPPLY_SENSING = 0x510301,
  POSITION_RUDDER = 0x510401,
  POSITION_MAIN_SAIL = 0x510501,
  POSITION_FORE_SAIL = 0x510601,
  GPS_VALIDITY_LEA_6H = 0x510901,
  AUTOPILOT_SYSTEM_INFO = 0x510D01,
  BILGE_WATER_DETECTION = 0x510F01,
  STREAMING_SYSTEM_INFO = 0x511001,
  GPS_SYSTEM_INFO = 0x511101,
  /*------------------------------------------
   Wind
   ------------------------------------------*/
  ANEMOMETER = 0x520301,
  WESTON_ANEMOMETER = 0x520501,
  WIND_VANE = 0x520401,
  /*------------------------------------------
   Speed
   ------------------------------------------*/
  GPS_VELOCITY = 0x530901,
  /*------------------------------------------
   Positioning
   ------------------------------------------*/
  GPS_POSITION = 0x540901,
  /*------------------------------------------
   Orientation
   ------------------------------------------*/
  ORIENTATION_COMPUTED_BOAT = 0x550101,
  GYROSCOPE = 0x550501,
  COMPASS = 0x550601,
  ACCELEROMETER = 0x550701,
  ORIENTATION_COMPUTED_9DOF = 0x550801
};

#endif /* COMMUNICATION_COMPONENT_DESCRIPTOR_ENUM_H_ */
