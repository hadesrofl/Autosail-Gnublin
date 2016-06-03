#ifndef DEVICES_SERVO_MOTOR_H_
#define DEVICES_SERVO_MOTOR_H_

#include "../interfaces/spi_master_select.h"
#include "device.h"

/**
 * @file
 * @class ServoMotor
 * @brief Class for a ServoMotor on the actor platform. Uses a SPIMasterSelect Interface for communication and
 * has some specific functions for handling data.
 * @author Rene Kremer
 * @version 0.2
 */
class ServoMotor : public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the ServoMotor, setting the configuration for the device
   */
  int8_t
  init ();
  /**
   * Descriptor of this ServoMotor as it could be the motor for the sail, rudder etc.
   */
  Descriptor m_descriptor;
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param device_file is the name of the SPIMasterSelect Interface this devices listens to
   * @param speed is the speed of the used SPI Bus
   * @param desc is the descriptor of this ServoMotor
   */
  ServoMotor (char* device_file, uint16_t speed, Descriptor desc);
  /**
   * Constructor
   * @param speed is the speed of the used SPI Bus
   * @param desc is the descriptor of this ServoMotor
   */
  ServoMotor (uint16_t speed, Descriptor desc);
  /**
   * TODO: Comment with SerialLink specific register
   * Reads the Data X, Y and Z Register of the SerialLink and returns them as a
   * pointer with allocated memory.
   */
  uint8_t* read_data();
  /**
   * Destructor
   */
  ~ServoMotor ();

};



#endif /* DEVICES_SERVO_MOTOR_H_ */
