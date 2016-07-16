#include "serial_link.h"

// Private Functions
int8_t
SerialLink::init ()
{
  return -1;
}
// Public Functions
SerialLink::SerialLink (SPIParameter *interface_parameter, ComponentDescriptor* descriptor)
{
  m_interface_port = std::unique_ptr<SPIMasterSelect> (
      new SPIMasterSelect (interface_parameter->get_device_file (),
			   interface_parameter->get_speed(),true));
  set_component_descriptor (descriptor);
  m_device_parameter = std::unique_ptr<SPIParameter> (interface_parameter);
  init();
}
int8_t*
SerialLink::read_data ()
{
  int8_t* data_ptr = NULL;
  return data_ptr;
}
SerialLink::~SerialLink ()
{
}
