#include "../communication/component_descriptor_builder.h"

ComponentDescriptorBuilder::ComponentDescriptorBuilder ()
{
}
ComponentDescriptor*
ComponentDescriptorBuilder::create_descriptor (uint8_t component_class,
					       uint8_t component_attribute,
					       uint8_t component_number)
{
  return new ComponentDescriptor (
      component_class, component_attribute, component_number);
}
ComponentDescriptorBuilder::~ComponentDescriptorBuilder ()
{
}

