#include "component_descriptor.h"


ComponentDescriptor::ComponentDescriptor(unsigned char component_class, unsigned char attribute, unsigned char number){
  m_component_class = component_class;
  m_component_attribute = attribute;
  m_component_number = number;
}

unsigned char ComponentDescriptor::get_component_class() const{
  return m_component_class;
}

unsigned char ComponentDescriptor::get_component_attribute() const{
  return m_component_attribute;
}

unsigned char ComponentDescriptor::get_component_number() const{
  return m_component_number;
}
ComponentDescriptor::~ComponentDescriptor(){}
