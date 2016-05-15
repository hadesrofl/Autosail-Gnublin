#include "gps.h"

// Private Functions
int GPS::init(){
  return -1;
}
// Public Functions
GPS::GPS (char* device_file, int baudrate)
{
  m_interface_port = std::unique_ptr<Serial> (
      new Serial (device_file, baudrate));
  set_device_id (Device_ID::GPS);
}
GPS::GPS (int baudrate)
{
  m_interface_port = std::unique_ptr<Serial> (new Serial (baudrate));
  set_device_id (Device_ID::GPS);
}
GPS::GPS ()
{
  m_interface_port = std::unique_ptr<Serial> (
      new Serial (static_cast<int>(Sensor_Param::GPS_BAUD)));
  set_device_id (Device_ID::GPS);
}
int
GPS::read (unsigned char* buf, int length)
{
  return -1;
}
int
GPS::write (unsigned char* buf, int length)
{
  return -1;
}
GPS::~GPS ()
{
}

