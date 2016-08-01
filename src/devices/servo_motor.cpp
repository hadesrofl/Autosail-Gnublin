#include "servo_motor.h"

// Private Functions
int8_t
ServoMotor::init ()
{
  return 1;
}
// Public Functions
ServoMotor::ServoMotor (SPIParameter *interface_parameter,
			ComponentDescriptor* descriptor, uint8_t mechanic)
{
  m_interface_port = std::unique_ptr<SPIMasterSelect> (
      new SPIMasterSelect (interface_parameter->get_device_file (),
			   interface_parameter->get_speed (), false));
  set_component_descriptor (descriptor);
  m_device_parameter = std::unique_ptr<SPIParameter> (interface_parameter);
  m_mechanic = mechanic;
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
  uint8_t* angle_split = IntConverter::uint16_to_uint8 (angle);
  uint8_t* buf = new uint8_t[4];
  switch (m_mechanic)
    {
    case MECHANIC_RUDDER:
      buf[0] = IP_TAG_SET_RUDDER;
      break;
    case MECHANIC_MS:
      buf[0] = IP_TAG_SET_MS;
      break;
    case MECHANIC_FS:
      buf[0] = IP_TAG_SET_FS;
      break;
    case MECHANIC_HOOK:
      buf[0] = IP_TAG_SET_HOOK;
      break;
    }
  // Length of values for the angle
  buf[1] = 2;
  buf[2] = angle_split[0];
  buf[3] = angle_split[1];
#ifdef _DEBUG
  int16_t fused = IntConverter::int8_to_int16 ((int8_t*) angle_split);
  std::cout << "Angle set to: " << m_angle << " uint8_t: "
      << static_cast<int> (buf[2]) << " and " << static_cast<int> (buf[3])
      << " fused again: " << fused << std::endl;
  std::cout << "Tag: " << static_cast<int> (buf[0]) << "\tLength: "
      << static_cast<int> (buf[1]) << "\nPayload: " << static_cast<int> (buf[2])
      << " and " << static_cast<int> (buf[3]) << std::endl;
#endif
    m_interface_port->send(buf, 4);
  delete[] angle_split;
  delete[] buf;
}
ServoMotor::~ServoMotor ()
{
}
