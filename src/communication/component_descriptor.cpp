#include "component_descriptor.h"

ComponentDescriptor::ComponentDescriptor ()
{
  m_component_class = 0;
  m_component_attribute = 0;
  m_component_number = 0;
}
ComponentDescriptor::ComponentDescriptor (uint8_t component_class,
					  uint8_t attribute, uint8_t number)
{
  m_component_class = component_class;
  m_component_attribute = attribute;
  m_component_number = number;
}
ComponentDescriptor::~ComponentDescriptor ()
{
}
