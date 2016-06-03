#include "gps.h"

// Private Functions
int8_t
GPS::init ()
{
  return -1;
}
// Public Functions
GPS::GPS (char* device_file, uint32_t baudrate)
{
  m_interface_port = std::unique_ptr<Serial> (
      new Serial (device_file, baudrate));
  set_device_id (Descriptor::GPS);
}
GPS::GPS (uint32_t baudrate)
{
  m_interface_port = std::unique_ptr<Serial> (new Serial (baudrate));
  set_device_id (Descriptor::GPS);
}
GPS::GPS ()
{
  m_interface_port = std::unique_ptr<Serial> (
      new Serial (static_cast<int32_t> (Device_Config::GPS_BAUD)));
  set_device_id (Descriptor::GPS);
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

