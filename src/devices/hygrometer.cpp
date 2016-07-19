#include "hygrometer.h"

// Private Functions
int8_t
Hygrometer::init ()
{
  return -1;
}
// Public Functions
Hygrometer::Hygrometer (I2CParameter *interface_parameter, ComponentDescriptor* descriptor)
{
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (interface_parameter->get_device_file(), interface_parameter->get_address()));
  set_component_descriptor (descriptor);
  m_device_parameter = std::unique_ptr<I2CParameter>(interface_parameter);
  init();
}
std::vector<int8_t>
Hygrometer::read_data ()
{
  std::vector<int8_t> data;
  return data;
}
Hygrometer::~Hygrometer ()
{
}
