#include "servo_motor.h"

// Private Functions
int8_t
ServoMotor::init ()
{
  return -1;
}
// Public Functions
ServoMotor::ServoMotor (SPIParameter *interface_parameter, Descriptor desc)
{
  m_interface_port = std::unique_ptr<SPIMasterSelect> (
      new SPIMasterSelect (interface_parameter->get_device_file(), interface_parameter->get_speed(), false));
  set_device_id (desc);
  m_descriptor = desc;
  m_device_parameter = std::unique_ptr<SPIParameter> (interface_parameter);
  init();
}
uint8_t*
ServoMotor::read_data ()
{
  uint8_t* data_ptr = NULL;
  return data_ptr;
}
ServoMotor::~ServoMotor ()
{
}
