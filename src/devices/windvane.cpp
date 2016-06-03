#include "windvane.h"

// Private Functions
int8_t
WindVane::init ()
{
  return -1;
}
// Public Functions
WindVane::WindVane (I2CParameter *interface_parameter)
{
  m_device_parameter = std::unique_ptr<I2CParameter> (interface_parameter);
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (interface_parameter->get_device_file (),
	       interface_parameter->get_address ()));
  set_device_id (Descriptor::WIND_VANE);
  init ();
}

uint8_t*
WindVane::read_data ()
{
  uint8_t* data_ptr = NULL;
  return data_ptr;
}
WindVane::~WindVane ()
{
}

