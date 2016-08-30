/**
 * Copyright 2016 Rene Kremer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef COMMUNICATION_COMPONENT_DESCRIPTOR_H
#define COMMUNICATION_COMPONENT_DESCRIPTOR_H

#include <stdint.h>

/**
 * @file
 * @class ComponentDescriptor
 * @ingroup Communication
 * @brief Container Class for the Component Descriptor used for the initial
 * communication via TLVE4-Protocol.
 * @author Rene Kremer
 * @version 0.2
 */
class ComponentDescriptor
{
  /**
   * @private
   */
private:
  /**
   * Byte containing the component class as specified in the TLVE4-Protocol
   */
  uint8_t m_component_class;
  /**
   * Byte containing the component attribute as specified in the TLVE4-Protocol
   */
  uint8_t m_component_attribute;
  /**
   * Byte containing the component number as specified in the TLVE4-Protocol
   */
  uint8_t m_component_number;
  /**
   * @public
   */
public:
  /**
   * Default Constructor
   */
  ComponentDescriptor();
  /**
   * Constructor
   * @param component_class byte of the class field
   * @param attribute byte of the attribute field
   * @param number byte of the number field
   */
  ComponentDescriptor (uint8_t component_class, uint8_t attribute,
		       uint8_t number);
  /**
   * Gets the class of the component according to the TLVE Protocol
   * @return the byte of the class of the component
   */
  inline uint8_t
  get_component_class () const
  {
    return m_component_class;
  }
  /**
   * Sets the component class
   * @param component_class is the new component class of this descriptor
   */
  inline void set_component_class(uint8_t component_class){
    m_component_class = component_class;
  }
  /**
   * Gets the attribute of the component according to the TLVE Protocol
   * @return the byte of the attribute of the component
   */
  inline uint8_t
  get_component_attribute () const
  {
    return m_component_attribute;
  }
  /**
   * Sets the component attribute
   * @param component_attribute is the new component attribute of this descriptor
   */
  inline void set_component_attribute(uint8_t component_attribute){
    m_component_attribute = component_attribute;
  }
  /**
   * Gets the number of the component according to the TLVE Protocol
   * @return the byte of the number of the component
   */
  inline uint8_t
  get_component_number () const
  {
    return m_component_number;
  }
  /**
   * Sets the component number
   * @param component_number is the new component number of this descriptor
   */
  inline void set_component_number(uint8_t component_number){
    m_component_number = component_number;
  }
  /**
   * Destructor
   */
  ~ComponentDescriptor ();
};
#endif
