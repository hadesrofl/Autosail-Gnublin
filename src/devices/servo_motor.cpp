#include "servo_motor.h"

// Private Functions
int8_t
ServoMotor::init ()
{
  return -1;
}
// Public Functions
ServoMotor::ServoMotor (SPIParameter *interface_parameter,
			ComponentDescriptor* descriptor)
{
  m_interface_port = std::unique_ptr<SPIMasterSelect> (
      new SPIMasterSelect (interface_parameter->get_device_file (),
			   interface_parameter->get_speed (), false));
  set_component_descriptor (descriptor);
  m_device_parameter = std::unique_ptr<SPIParameter> (interface_parameter);
  init ();
}
std::vector<int8_t>
ServoMotor::read_data ()
{
  std::vector<int8_t> data;
  return data;
}
void
ServoMotor::set_angle (int16_t angle)
{
  m_angle = angle;
  uint8_t* buf = IntConverter::uint16_to_uint8 (angle);
  int16_t fused = IntConverter::int8_to_int16 ((int8_t*) buf);
  std::cout << "Angle set to: " << m_angle << " uint8_t: "
      << static_cast<int> (buf[0]) << " and " << static_cast<int> (buf[1])
      << " fused again: " << fused << std::endl;
//    m_interface_port->send(buf, 2);
  delete[] buf;
}
ServoMotor::~ServoMotor ()
{
}
