#include "gps.h"

GPS::GPS (char* device_file, int baudrate)
{
  m_interface_port = std::unique_ptr<Serial> (
      new Serial (device_file, baudrate));
}
GPS::GPS (int baudrate){
  m_interface_port = std::unique_ptr<Serial>(new Serial(baudrate));
}
int GPS::read(unsigned char* buf, int length){
  return -1;
}
int GPS::write(unsigned char* buf, int length){
  return -1;
}
GPS::~GPS ()
{
}

