#include "weston_anemometer.h"

// Private Functions
int8_t
WestonAnemometer::init ()
{
  return -1;
}
// Public Functions
WestonAnemometer::WestonAnemometer (I2CParameter *interface_parameter, ComponentDescriptor* descriptor)
{
  m_device_parameter = std::unique_ptr<I2CParameter> (interface_parameter);
  m_interface_port = std::unique_ptr<I2C> (
      new I2C (interface_parameter->get_device_file (),
	       interface_parameter->get_address ()));
  set_component_descriptor (descriptor);
  m_datastructure_id = DataStructureIdentifier::INT16;
  init ();
}
std::vector<int8_t>
WestonAnemometer::read_data ()
{
  std::vector<int8_t> data;
  return data;
}
WestonAnemometer::~WestonAnemometer ()
{
}

