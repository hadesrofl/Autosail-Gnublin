#ifndef DEVICES_SERVO_MOTOR_H_
#define DEVICES_SERVO_MOTOR_H_

#include "../interfaces/spi_master_select.h"
#include "device.h"
#include "spi_parameter.h"
#include "../utils/int_converter.h"

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
   * @public
   */
public:
  /**
   * Constructor
   * @param interface_parameter are the parameters for the SPI Interface
   * @param descriptor is a pointer to the ComponentDescriptor of this device
   */
  ServoMotor (SPIParameter *interface_parameter,
	      ComponentDescriptor* descriptor);
  /**
   * TODO: Comment with SerialLink specific register
   * Reads the Data X, Y and Z Register of the SerialLink and returns them as a
   * pointer with allocated memory.
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
