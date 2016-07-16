#ifndef DEVICES_SERVO_MOTOR_H_
#define DEVICES_SERVO_MOTOR_H_

#include "../interfaces/spi_master_select.h"
#include "device.h"
#include "spi_parameter.h"

/**
 * @file
 * @class ServoMotor
 * @brief Class for a ServoMotor on the actor platform. Uses a SPIMasterSelect Interface for communication and
 * has some specific functions for handling data.
 * @author Rene Kremer
 * @version 0.3
 */
class ServoMotor : virtual public Device
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
   * @public
   */
public:
  /**
   * Constructor
   * @param interface_parameter are the parameters for the SPI Interface
   * @param descriptor is a pointer to the ComponentDescriptor of this device
   */
  ServoMotor (SPIParameter *interface_parameter, ComponentDescriptor* descriptor);
  /**
   * TODO: Comment with SerialLink specific register
   * Reads the Data X, Y and Z Register of the SerialLink and returns them as a
   * pointer with allocated memory.
   */
  int8_t* read_data();
  /**
   * Destructor
   */
  ~ServoMotor ();

};



#endif /* DEVICES_SERVO_MOTOR_H_ */
