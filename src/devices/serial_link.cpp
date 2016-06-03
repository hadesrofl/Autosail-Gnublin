#include "serial_link.h"

// Private Functions
int8_t
SerialLink::init ()
{
  return -1;
}
// Public Functions
SerialLink::SerialLink (SerialParameter *interface_parameter)
{
  m_interface_port = std::unique_ptr<SPIMasterSelect> (
      new SPIMasterSelect (interface_parameter->get_device_file (),
			   interface_parameter->get_baudrate()));
  set_device_id (Descriptor::SERIAL_LINK);
  m_device_parameter = std::unique_ptr<SerialParameter> (interface_parameter);
  init();
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
