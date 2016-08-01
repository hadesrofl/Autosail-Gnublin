#ifndef COMMUNICATION_TLVE_ENGINE_H_
#define COMMUNICATION_TLVE_ENGINE_H_

#include "protocol_engine.h"
#include "tlv_interpreter.h"
#include "tlv_frame.h"

/**
 * Priority Control Mode
 */
#define PRIORITY_MODE 0x00
/**
 * Normal Control Mode
 */
#define NORMAL_MODE 0x01
/**
 * Fail Safe Control Mode
 */
#define FAIL_SAFE_MODE 0x0F

/**
 * @file
 * @class TLVEEngine
 * @ingroup Communication
 * @brief Class for a TLVE4 Engine. Core of the TLVE4 implementation.
 * Uses a TLVInterpreter to interpret TLVFrames and a ComponentDescriptorBuilder to
 * construct descriptors for different devices.
 *
 * @author Rene Kremer
 * @version 0.3
 */
class TLVEEngine : virtual public ProtocolEngine
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
   * @public
   */
public:
  /**
   * Constructor
   * @param protocol_version is a list of bytes determining the protocol_version
   * @param boat_id is the ID of this boat
   */
  TLVEEngine (std::vector<uint8_t> protocol_version, uint8_t boat_id);

  /**
   * Starts and sets the interpreter to this engine
   * @param generator is a pointer to the StreamGenerator
   * @param autopilot is a pointer to the AutoPilot
   */
  void
  start_interpreter (std::shared_ptr<StreamGenerator> generator,
		     std::shared_ptr<AutoPilot> autopilot);
  /**
   * Creates a Frame containing the boat description
   * @return the Frame holding the boat description data
   */
  TLVFrame*
  send_boat_description ();
  /**
   * Private function for the abstract method declared in ProtocolEngine
   * Creates a TLVFrame and returns a pointer to it
   * @param tag is the value of the tag field
   * @param attribute is the attribute of this frame
   * @param length is the amount of bytes of the payload field
   * @return a TLVFrame packed with the data
   */
  TLVFrame*
  create_frame (TagEnum tag, uint8_t attribute, uint8_t length);
  /**
   * Private function for the abstract method declared in ProtocolEngine
   * Creates a TLVFrame and returns a pointer to it
   * @param tag is the value of the tag field
   * @param attribute is the attribute of this frame
   * @param length is the amount of bytes of the payload field
   * @param payload is a Byte Vector containing the data of the payload
   * @return a TLVFrame packed with the data
   */
  TLVFrame*
  create_frame (TagEnum tag, uint8_t attribute, uint8_t length,
		std::vector<uint8_t> payload);
  /**
   * Creates a Frame and returns a pointer to it
   * @param tag is the value of the tag field
   * @param length is the amount of bytes of the payload field
   * @return a Frame packed with the data
   */
  TLVFrame*
  create_frame (TagEnum tag, uint8_t length);
  /**
   * Creates an empty TLVFrame
   * @return an empty TLVFrame
   */
  TLVFrame*
  create_frame ();
  /**
   * Sends a frame of a Stream
   * @param stream is a pointer to the Stream where the data comes from
   * @param data is a list of data from the Device
   */
  void
  send_stream (Stream* stream, std::vector<int8_t> data);
  /**
   * Sends a frame to the receiver
   * @param frame is the frame to send
   */
  void
  send_frame (Frame* frame);
  /**
   * Sends a Frame with an error message
   * @param code is the error code
   * @param msg is a char pointer containing the message
   * @param msg_length is the length of the message
   */
  void
  send_error (uint8_t code, uint8_t* msg, uint8_t msg_length);
  /**
   * Calls the TLVInterpreter and interprets the frame. The TLVInterpreter
   * calls the function described by the command in the Frame.
   * @param frame is a pointer to the frame which shall be interpreted
   *
   * XXX fixed Actors as specified in protocol, needs to be the same in conf file
   * <pre>
   * 	<code>
   *       	switch (frame->get_attribute ())
   *		{
   *			// Rudder
   *			case 0x44:
   *		    		communication_number = 0x01;
   *		    		break;
   *		  	// Main Sail
   *		  	case 0x45:
   *		  		communication_number = 0x02;
   *		  		break;
   *		  	// Fore Sail
   *		  	case 0x46:
   *		  		communication_number = 0x03;
   *		  		break;
   *		 }
   *	</code>
   * </pre>
   */
  void
  interpret_frame (Frame* frame);
  /**
   * Sets a new control mode and checks if the mode is one of the three valid ones.
   * Returns 1 on success, otherwise -1 (non valide mode)
   * @param control_mode is the new control mode
   * @return 1 on success, otherwise -1
   */
  inline int8_t
  set_control_mode (uint8_t control_mode)
  {
    // 0x00 = Priority Mode, 0x01 = Normal Mode, 0x0F = Fail Safe
    if (control_mode == 0x00 || control_mode == 0x01 || control_mode == 0x0F)
      {
	m_control_mode = control_mode;
	return 1;
      }
    return -1;
  }
  /**
   * Destructor
   */
  ~TLVEEngine ();
};

#endif /* COMMUNICATION_TLVE_ENGINE_H_ */
