#ifndef COMMUNICATION_COMPONENT_DESCRIPTOR_BUILDER_H
#define COMMUNICATION_COMPONENT_DESCRIPTOR_BUILDER_H

#include "component_descriptor.h"
#include <stdint.h>
#include "../devices/device.h"
#include <map>

/**
 * @file
 * @class ComponentDescriptorBuilder
 * @brief Class for a Builder that creates Component Descriptors for the boat.
 * These Descriptors are needed for the initial communication via the TLVE4 Protocol.
 * @author Rene Kremer
 * @version 0.2
 */
class ComponentDescriptorBuilder
{
  /**
   * @private
   */
private:
  /**
   * Map to assign a ComponentDescriptor to a Device pointer. Contains all
   * Descriptors
   */
  std::map<std::shared_ptr<ComponentDescriptor>, Device*> m_communication_table_backward;
  /**
   * @public
   */
public:
  /**
   * Constructor
   */
  ComponentDescriptorBuilder ();
  /**
   * Creates a ComponentDescriptor and returns it. After creation it will be stored
   * in the private vector list of this class.
   * @param component_class is the class of the component
   * @param component_attribute is the attribute of the component
   * @param component_number is the number of the component
   * @return a a pointer to a ComponentDescriptor
   */
  ComponentDescriptor*
  create_descriptor (uint8_t component_class, uint8_t component_attribute,
		     uint8_t component_number);
  /**
   * Destructor
   */
  ~ComponentDescriptorBuilder ();
};

#endif
