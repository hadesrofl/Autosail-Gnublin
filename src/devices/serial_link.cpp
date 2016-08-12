#include "serial_link.h"

// Private Functions
int8_t
SerialLink::init ()
{
  return -1;
}
// Public Functions
SerialLink::SerialLink (SPIParameter *interface_parameter,
			ComponentDescriptor* descriptor)
{
  m_interface_port = std::unique_ptr<SPIMasterSelect> (
      new SPIMasterSelect (interface_parameter->get_device_file (),
			   interface_parameter->get_speed (), PCI_PIN));
  set_component_descriptor (descriptor);
  m_device_parameter = std::unique_ptr<SPIParameter> (interface_parameter);
  init ();
}
#ifdef _TEST
SerialLink::SerialLink (I2CParameter *interface_parameter,
			ComponentDescriptor* descriptor)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (interface_parameter->get_device_file (),
	       interface_parameter->get_address ()));
  set_component_descriptor (descriptor);
  m_device_parameter = std::unique_ptr<I2CParameter> (interface_parameter);
  init ();
}
#endif
std::vector<int8_t>
SerialLink::read_data ()
{
  std::vector<int8_t> frame;
  uint8_t* ip_frame = new uint8_t[2];
  uint8_t* frame_buf;
  uint8_t length, size;
  m_interface_port->receive (ip_frame, 2);
  size = ip_frame[1];
#ifdef _TEST
  std::cout << "\nIP Frame: " << "\nTag: " << static_cast<unsigned int> (ip_frame[0])
      << "\tLength: " << static_cast<unsigned int> (size) << std::endl;
#endif
  frame_buf = new uint8_t[size];
  m_interface_port->receive (frame_buf, size);
  frame.push_back (frame_buf[0]);
#ifdef _TEST
  std::cout << "\nTLVE Frame: " << "\nTag: " << static_cast<unsigned int> (frame.at (0));
#endif
  length = frame_buf[1];
  frame.push_back (length);
#ifdef _TEST
  std::cout << "\tLength: " << static_cast<unsigned int> (frame.at (1));
#endif
  if (length > 0)
    {
#ifdef _TEST
      std::cout << "\nData: ";
#endif
      for (uint8_t i = 2; i < size-1; i++)
	{
	  frame.push_back (frame_buf[i]);
#ifdef _TEST
	  std::cout << static_cast<unsigned int> (frame_buf[i]) << " ";
#endif
	}
    }
#ifdef _TEST
  std::cout << " Sync: " << static_cast<unsigned int> (frame_buf[size - 1]) << std::endl;
#endif
  return frame;
}
void
SerialLink::send_frame (uint8_t* buf, uint8_t length)
{
#ifdef _DEBUG
  std::cout << "Sending via Serial Link:" << std::endl;
#endif
  uint8_t* ip_frame = new uint8_t[length + 2];
  ip_frame[0] = FORWARD_FRAME_TAG;
  ip_frame[1] = length;
  for (uint8_t i = 2; i < length + 2; i++)
    {
      ip_frame[i] = buf[i - 2];
    }
#ifdef _DEBUG
  std::cout << "Tag: " << static_cast<int> (ip_frame[0]) << "\tLength: "
  << static_cast<int> (ip_frame[1]) << "\nData: ";

  for (uint8_t i = 0; i < length + 2; i++)
    {
      std::cout << static_cast<int> (ip_frame[i]) << " ";
    }
  std::cout << std::endl;
#endif
  write (ip_frame, length + 2);
  delete[] ip_frame;
}
SerialLink::~SerialLink ()
{
}
