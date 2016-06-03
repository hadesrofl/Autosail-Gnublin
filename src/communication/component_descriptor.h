#ifndef COMMUNICATION_COMPONENT_DESCRIPTOR_H
#define COMMUNICATION_COMPONENT_DESCRIPTOR_H

#include <stdint.h>

/**
 * @file
 * @class ComponentDescriptor
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
   * Gets the attribute of the component according to the TLVE Protocol
   * @return the byte of the attribute of the component
   */
  inline uint8_t
  get_component_attribute () const
  {
    return m_component_attribute;
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
   * Destructor
   */
  ~ComponentDescriptor ();
};
#endif
