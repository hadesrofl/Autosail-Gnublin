#ifndef KLASSENDIAGRAMM_TLVE_COMPONENT_DESCRIPTOR_H
#define KLASSENDIAGRAMM_TLVE_COMPONENT_DESCRIPTOR_H
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
  unsigned char m_component_class;
  /**
   * Byte containing the component attribute as specified in the TLVE4-Protocol
   */
  unsigned char m_component_attribute;
  /**
   * Byte containing the component number as specified in the TLVE4-Protocol
   */
  unsigned char m_component_number;
  /**
   * @public
   */
public:
  /**
   * Constructor
   */
  ComponentDescriptor ();
  /**
   * Destructor
   */
  ~ComponentDescriptor ();
};
#endif
