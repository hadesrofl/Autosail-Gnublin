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
std::vector<int8_t>
SerialLink::read_data ()
{
  std::vector<int8_t> frame;
  uint8_t* first_read = new uint8_t[2];
  uint8_t* frame_buf;
  uint8_t attribute, length, size;
  read (first_read, 2);
  size = first_read[1];
  frame_buf = new uint8_t[size];
  read (frame_buf, size);
  frame.push_back (frame_buf[0]);
  length = frame_buf[1];
  frame.push_back (length);
  if (length > 0)
    {
      frame.push_back (frame_buf[2]);
      for (uint8_t i = 2; i < length; i++)
	{
	  frame.push_back (frame_buf[i]);
	}
    }
  return frame;
}
void
SerialLink::send_frame (uint8_t* buf, uint8_t length)
{
  std::cout << "Sending via Serial Link:" << std::endl;
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
