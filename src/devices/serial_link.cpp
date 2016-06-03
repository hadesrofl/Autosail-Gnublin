#include "serial_link.h"

// Private Functions
int8_t
SerialLink::init ()
{
  return -1;
}
// Public Functions
SerialLink::SerialLink (char* device_file, uint16_t speed)
{
  m_interface_port = std::unique_ptr<SPIMasterSelect> (
      new SPIMasterSelect (device_file, speed));
  set_device_id (Descriptor::SERIAL_LINK);
}
SerialLink::SerialLink (uint16_t speed)
{
  m_interface_port = std::unique_ptr<SPIMasterSelect> (new SPIMasterSelect (speed));
  set_device_id (Descriptor::SERIAL_LINK);
}
uint8_t*
SerialLink::read_data ()
{
  uint8_t* data_ptr = NULL;
  return data_ptr;
}
SerialLink::~SerialLink ()
{
}
