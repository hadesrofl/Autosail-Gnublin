#include "wind_vane.h"

// Private Functions
int8_t
WindVane::init ()
{
  return -1;
}
// Public Functions
WindVane::WindVane (I2CParameter *interface_parameter, ComponentDescriptor* descriptor)
{
  m_device_parameter = std::unique_ptr<I2CParameter> (interface_parameter);
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (interface_parameter->get_device_file (),
	       interface_parameter->get_address ()));
  set_component_descriptor (descriptor);
  init ();
}

int8_t*
WindVane::read_data ()
{
  int8_t* data_ptr = NULL;
  return data_ptr;
}
WindVane::~WindVane ()
{
}

