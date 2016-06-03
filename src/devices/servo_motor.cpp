#include "servo_motor.h"

// Private Functions
int8_t
ServoMotor::init ()
{
  return -1;
}
// Public Functions
ServoMotor::ServoMotor (char* device_file, uint16_t speed, Descriptor desc)
{
  m_interface_port = std::unique_ptr<SPIMasterSelect> (
      new SPIMasterSelect (device_file, speed));
  set_device_id (desc);
  m_descriptor = desc;
}
ServoMotor::ServoMotor (uint16_t speed, Descriptor desc)
{
  m_interface_port = std::unique_ptr<SPIMasterSelect> (new SPIMasterSelect (speed));
  set_device_id (desc);
  m_descriptor = desc;
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
