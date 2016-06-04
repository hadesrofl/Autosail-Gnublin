#ifndef COMMUNICATION_PROTOCOL_ENGINE_H
#define COMMUNICATION_PROTOCOL_ENGINE_H

#include <vector>
#include <map>
#include <memory>
#include "frame.h"
#include "communication_number.h"
#include "component_descriptor_builder.h"
#include "../devices/descriptor.h"
#include "frame_interpreter.h"

/**
 * @file
 * @class ProtocolEngine
 * @brief Class for a virtual Protocol Engine. Contains the DescriptionBuilder to create
 * the payload for the BoatDescription and creates Frames for the Communication.
 *
 * To interpret frames it got a FrameInterpreter which processes the sent commands.
 *
 * ProtcolEngine is developed to be extended by specific protocols like TLVE4 or JSON.
 * @author Rene Kremer
 * @version 0.2
 */
class ProtocolEngine
{
  /**
   * @private
   */
private:
  /**
   * @protected
   */
protected:
  /**
   * Builder for the component descriptors
   */
  std::unique_ptr<ComponentDescriptorBuilder> m_descriptor_builder;
  /**
   * Datastructure to map a descriptor to a communication number
   */
  std::map<Descriptor, CommunicationNumber> m_communication_table;
  /**
   * Interpreter for the Frames
   */
  std::unique_ptr<FrameInterpreter> m_interpreter;
  /**
   * @public
   */
public:
  /**
   * Constructor
   */
  ProtocolEngine ()
  {
  }
  /**
   * Gets the description of the boat as specified in the TLVE4-Protocol and sends
   * the initial message and communication numbers
   * @return a Frame packed with the data that shall be sent
   */
  virtual Frame*
  send_boat_description () = 0;
  /**
   * Creates a Frame and returns a pointer to it
   * @param tag is the value of the tag field
   * @param attribute is the value of the attribute field
   * @param length is the amount of bytes of the payload field
   * @param payload is a Byte Vector containing the data of the payload
   * @return a Frame packed with the data
   */
  virtual Frame*
  create_frame (uint8_t tag, uint8_t attribute, uint8_t length,
		std::vector<uint8_t> payload) = 0;
  /**
   * Creates a Frame and returns a pointer to it
   * @param tag is the value of the tag field
   * @param attribute is the value of the attribute field
   * @param length is the amount of bytes of the payload field
   * @return a Frame packed with the data
   */
  virtual Frame*
  create_frame (uint8_t tag, uint8_t attribute, uint8_t length) = 0;
  /**
   * Creates an empty Frame and returns a pointer to it
   * @return an empty Frame
   */
  virtual Frame*
  create_frame () = 0;
  /**
   * Calls the FrameInterpreter and interprets the frame. The FrameInterpreter
   * calls the function described by the command in the Frame.
   * @param frame is a pointer to the frame which shall be interpreted
   */
  void
  interpret_frame (Frame* frame)
  {
    m_interpreter->interpret_frame (frame);
  }
  /**
   * Destructor
   */
  virtual
  ~ProtocolEngine ()
  {
  }

};
#endif
