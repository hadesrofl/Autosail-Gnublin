#ifndef COMMUNICATION_PROTOCOL_ENGINE_H
#define COMMUNICATION_PROTOCOL_ENGINE_H

#include <vector>
#include "component_descriptor_builder.h"
#include "frame_interpreter.h"
#include <memory>
#include <map>
#include "communication_protocols.h"

/**
 * Max Communication Numbers to determine array length
 */
#define MAX_COMMUNICATION_NUMBER 31
/**
 * Bitmask to extract the Communication Number out of the Attribute byte
 */
#define COMMUNICATION_NUMBER_BITMASK 0x1F
/*
 * Forward Declaration because of recursive include of header files
 */
class FrameInterpreter;
/*
 * Forward Declaration because of recursive include of header files
 */
class AutoPilot;
/*
 * Forward Declaration because of recursive include of header files
 */
class StreamGenerator;
/**
 * @file
 * @class ProtocolEngine
 * @ingroup Communication
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
   * ID of the boat
   */
  uint8_t m_boat_id;
  /**
   * Vector of the numbers of the protocol version.
   * First byte of the vectory is the major version number. The
   * second byte is the higher number of the minor version number.
   * The third byte is the lower number of the minor version number.
   * 0x04 0x01 0x05 = Version 4.15
   */
  std::vector<uint8_t> m_protocol_version;
  /**
   * Control Mode of the boat as described in the protocol.
   */
  uint8_t m_control_mode;
  /**
   * Builder for the component descriptors
   */
  std::shared_ptr<ComponentDescriptorBuilder> m_descriptor_builder;
  /**
   * Map to assign a ComponentDescriptor to a communication number
   */
  std::map<std::shared_ptr<ComponentDescriptor>, uint8_t> m_communication_table_forward;
  /**
   * Array where each index is a communication number mapping to a Device pointer
   */
  std::shared_ptr<Device> m_communication_table_backward[MAX_COMMUNICATION_NUMBER];
  /**
   * Interpreter for the Frames
   */
  std::unique_ptr<FrameInterpreter> m_interpreter;
  /**
   * Constructor needed for class hierarchy purposes. Shouldn't be called
   */
  ProtocolEngine ()
  {
    m_control_mode = 0x00;
    m_boat_id = 0;
  }
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param protocol_version is a list of bytes determining the protocol_version
   * @param boat_id is the ID of this boat
   */
  ProtocolEngine (std::vector<int8_t> protocol_version, uint8_t boat_id)
  {
    m_control_mode = 0x00;
    m_boat_id = boat_id;
  }
  /**
   * Starts and sets the interpreter to this engine
   * @param generator is a pointer to the StreamGenerator
   * @param autopilot is a pointer to the AutoPilot
   */
  virtual void
  start_interpreter (std::shared_ptr<StreamGenerator> generator,
		     std::shared_ptr<AutoPilot> autopilot) = 0;
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
  create_frame (TagEnum tag, uint8_t attribute, uint8_t length,
		std::vector<uint8_t> payload) = 0;
  /**
   * Creates a Frame and returns a pointer to it
   * @param tag is the value of the tag field
   * @param attribute is the value of the attribute field
   * @param length is the amount of bytes of the payload field
   * @return a Frame packed with the data
   */
  virtual Frame*
  create_frame (TagEnum tag, uint8_t attribute, uint8_t length) = 0;
  /**
   * Creates a Frame and returns a pointer to it
   * @param tag is the value of the tag field
   * @param length is the amount of bytes of the payload field
   * @return a Frame packed with the data
   */
  virtual Frame*
  create_frame (TagEnum tag, uint8_t length) =0;
  /**
   * Creates an empty Frame and returns a pointer to it
   * @return an empty Frame
   */
  virtual Frame*
  create_frame () = 0;
  /**
   * Sends a frame of a Stream
   * @param device is a pointer to the device where the data comes from
   * @param data is a list of data from the Device
   */
  virtual void
  send_stream (std::shared_ptr<Device> device, std::vector<int8_t> data) = 0;
  /**
   * Sends a frame to the receiver
   * @param frame is a pointer to the Frame
   */
  virtual void
  send_frame (Frame* frame) =0;
  /**
   * Creates a ComponentDescriptor and returns it. After creation it will be stored
   * in the private vector list of this class.
   * @param component_class is the class of the component
   * @param component_attribute is the attribute of the component
   * @param component_number is the number of the component
   * @return a a pointer to a ComponentDescriptor
   */
  inline ComponentDescriptor*
  create_descriptor (uint8_t component_class, uint8_t component_attribute,
		     uint8_t component_number)
  {
    return m_descriptor_builder->create_descriptor (component_class,
						    component_attribute,
						    component_number);;
  }
  /**
   * Calls the FrameInterpreter and interprets the frame. The FrameInterpreter
   * calls the function described by the command in the Frame.
   * @param frame is a pointer to the frame which shall be interpreted
   */
  virtual void
  interpret_frame (Frame* frame) = 0;
  /**
   * Gets the forward communication table
   * @return the communication table mapping ComponentDescriptor to communication number
   */
  inline std::map<std::shared_ptr<ComponentDescriptor>, uint8_t>
  get_communication_table_forward () const
  {
    return m_communication_table_forward;
  }
  /**
   * Inserts a ComponentDescriptor with a communication number into the forward
   * communication table (Key: ComponentDescriptor, Value: Communication Number)
   * @param descriptor is the ComponentDescriptor as key to the communication table
   * @param communication_number is the communication number and value of the table
   */
  inline void
  insert_communication_table_forward (ComponentDescriptor* descriptor,
				      uint8_t communication_number)
  {
    m_communication_table_forward.insert (
	std::make_pair (std::shared_ptr<ComponentDescriptor> (descriptor),
			communication_number));

  }
  /**
   * Returns the communication number matching to a ComponentDescriptor
   * @param descriptor is a pointer to the ComponentDescriptor
   * @return the communication number matched to this ComponentDescriptor.
   * Returns 0 if the ComponentDescriptor is not found in the communication table
   */
  inline uint8_t
  get_communication_number (ComponentDescriptor* descriptor)
  {
    std::shared_ptr<ComponentDescriptor> key = std::shared_ptr<
	ComponentDescriptor> (descriptor);
    if (m_communication_table_forward.count (key) > 0)
      {
	return m_communication_table_forward.at (key);
      }
    return 0;
  }
  /**
   * Inserts a communication number with a pointer to a Device into the backward
   * communication table (array where the index is the communication number)
   * @param communication_number is the index of the array
   * @param device is a pointer to the Device assigned to the communication_number
   */
  inline void
  insert_communication_table_backward (uint8_t communication_number,
				       Device* device)
  {
    if (communication_number <= MAX_COMMUNICATION_NUMBER)
      {
	m_communication_table_backward[communication_number] = std::shared_ptr<
	    Device> (device);
      }
  }
  /**
   * Returns a device mapped to a specific communication number.
   * Does not work with Devices which have a communication number of 0.
   * @param communication_number is the communication number of the Device
   * @return a pointer to the device or NULL if
   * communication number is > MAX_COMMUNICATION_NUMBER or the
   * communication number is not set to a device
   */
  inline std::shared_ptr<Device>
  get_device (uint8_t communication_number)
  {
    if (communication_number
	== 0|| communication_number > MAX_COMMUNICATION_NUMBER)
      {
	return NULL;
      }
    else
      {
	return m_communication_table_backward[communication_number];
      }
  }
  /**
   * Returns the current control mode
   * @return the control mode currently active
   */
  inline uint8_t
  get_control_mode () const
  {
    return m_control_mode;
  }
  /**
   * Sets a new control mode and checks if the mode is valid.
   * Returns 1 on success, otherwise -1 (non valid mode)
   * @param control_mode is the new control mode
   * @return 1 on success, otherwise -1
   */
  virtual int8_t
  set_control_mode (uint8_t control_mode) = 0;
  /**
   * Returns the 3 bytes list for the major and minor version number of the protocol.
   * @return a 3 byte list where the first byte is the major version number, the second
   * byte is the first decimal of the minor version number and the third byte is
   * the second decimal of the minor version number
   */
  inline std::vector<uint8_t>
  get_protocol_version () const
  {
    return m_protocol_version;
  }
  /**
   * Gets the boat id
   * @return the id of this boat
   */
  inline uint8_t
  get_boat_id () const
  {
    return m_boat_id;
  }
  /**
   * Fuses the DataStructureIdentifier with a communication number as mentioned in
   * TLVE4.
   * @param dsid is the DataStructureIdentifier
   * @param comm_no is the communication number of the Device
   * @return an uint8_t as the fused attribute
   */
  inline uint8_t
  tlve4_attribute (DataStructureIdentifier dsid, uint8_t comm_no)
  {
    uint8_t fused_attribute = static_cast<uint8_t> (dsid) << 5
	| (comm_no & 0x1F);
    return fused_attribute;
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
