#include "servo_motor.h"

// Private Functions
int8_t
ServoMotor::init ()
{
  return -1;
}
// Public Functions
ServoMotor::ServoMotor (SPIParameter *interface_parameter, ComponentDescriptor* descriptor)
{
  m_interface_port = std::unique_ptr<SPIMasterSelect> (
      new SPIMasterSelect (interface_parameter->get_device_file(), interface_parameter->get_speed(), false));
  set_component_descriptor (descriptor);
  m_device_parameter = std::unique_ptr<SPIParameter> (interface_parameter);
  init();
}
std::vector<int8_t>
ServoMotor::read_data ()
{
  std::vector<int8_t> data;
  return data;
}
ServoMotor::~ServoMotor ()
{
}
