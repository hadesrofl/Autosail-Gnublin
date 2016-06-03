#include "gps.h"

// Private Functions
int8_t
GPS::init ()
{
  return -1;
}
// Public Functions
GPS::GPS (SerialParameter *interface_parameter)
{
  m_interface_port = std::unique_ptr<Serial> (
      new Serial (interface_parameter->get_device_file(), interface_parameter->get_baudrate()));
  set_device_id (Descriptor::GPS);
  m_device_parameter = std::unique_ptr<SerialParameter> (interface_parameter);
  init();
}
uint8_t*
GPS::read_data ()
{
  uint8_t* data_ptr = NULL;
  return data_ptr;
}
GPS::~GPS ()
{
}

