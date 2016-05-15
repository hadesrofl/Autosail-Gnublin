#include "component_descriptor.h"


ComponentDescriptor::ComponentDescriptor(unsigned char component_class, unsigned char attribute, unsigned char number){
  m_component_class = component_class;
  m_component_attribute = attribute;
  m_component_number = number;
}
ComponentDescriptor::~ComponentDescriptor(){}
