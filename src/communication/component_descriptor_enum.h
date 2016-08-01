#ifndef COMMUNICATION_COMPONENT_DESCRIPTOR_ENUM_H_
#define COMMUNICATION_COMPONENT_DESCRIPTOR_ENUM_H_

/**
 * @file
 * @enum mapper::ComponentDescriptorEnum
 * @ingroup Enums
 * @brief Enums for the Devices of this system. Needed to distinguish Devices in
 * FrameInterpreter and for initialization in DeviceManager
 * @author Rene Kremer
 * @version 0.2
 */
enum class ComponentDescriptorEnum
{
  /*------------------------------------------
   Actor
   ------------------------------------------*/
  SERVO_MOTOR_RUDDER = 0x0C4401,
  SERVO_MOTOR_MS = 0x0C4501,
  SERVO_MOTOR_FS = 0x0C4601,
  SERVO_MOTOR_HOOK = 0x0C4701,
  SERIAL_LINK = 0x0C4801,
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
  POSITION_MS = 0x510501,
  POSITION_FS = 0x510601,
  POSITION_HOOK = 0x510701,
  GPS_VALIDITY_LEA_6H = 0x510901,
  AUTOPILOT_SYSTEM_INFO = 0x510D01,
  BILGE_WATER_DETECTION = 0x510F01,
  STREAMING_SYSTEM_INFO = 0x511001,
  GPS_DOP = 0x511101,
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
