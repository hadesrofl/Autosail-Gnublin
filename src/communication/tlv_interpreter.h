#ifndef COMMUNICATION_TLV_INTERPRETER_H_
#define COMMUNICATION_TLV_INTERPRETER_H_

#include "frame_interpreter.h"
#include "tlv_frame.h"
#include "../devices/device_manager.h"
#include "tlve_engine.h"

/**
 * error code used in error messages for unknown tag
 */
#define ERROR_UNKNOWN_TAG 0x01
/**
 * message of the unknown tag error
 */
#define ERROR_UNKNOWN_TAG_MSG "Tag unknown!"
/**
 * length of the message for an unknown tag error
 */
#define ERROR_UNKNOWN_TAG_MSG_LENGTH 12
/**
 * error code used in error messages for unknown tag
 */
#define ERROR_NOT_SUPPORTED_TAG 0x02
/**
 * message of the not supported tag error
 */
#define ERROR_NOT_SUPPORTED_TAG_MSG "Tag not supported!"
/**
 * length of the message for an unknown tag error
 */
#define ERROR_NOT_SUPPORTED_TAG_MSG_LENGTH 18
/**
 * error code used in error messages for unknown component
 */
#define ERROR_UNKNOWN_COMP 0x03
/**
 * message of the unknown component error
 */
#define ERROR_UNKNOWN_COMP_MSG "Component unknown!"
/**
 * length of the message for an unknown component error
 */
#define ERROR_UNKNOWN_COMP_MSG_LENGTH 12
/**
 * error code used in error messages for unknown stream
 */
#define ERROR_UNKNOWN_STREAM 0x04
/**
 * message of the unknown component error
 */
#define ERROR_UNKNOWN_STREAM_MSG "Stream unknown!"
/**
 * length of the message for an unknown component error
 */
#define ERROR_UNKNOWN_STREAM_MSG_LENGTH 15

/**
 * @file
 * @class TLVInterpreter
 * @ingroup Communication
 * @brief Class for a TLV Interpreter. Interprets TLVFrames and calls
 * the specific function as described in the command of the frame.
 *
 * @author Rene Kremer
 * @version 0.2
 */
class TLVInterpreter : virtual public FrameInterpreter
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
   * Constructor needed for hierarchy purposes. Shouldn't be called
   */
  TLVInterpreter ()
  {
  }
  /**
   * public
   */
public:
  /**
   * Constructor
   * @param generator is a pointer to the StreamGenerator
   * @param autopilot is a pointer to the AutoPilot
   * @param protocol_engine is a pointer to the ProtocolEngine
   */
  TLVInterpreter (std::shared_ptr<StreamGenerator> generator,
		  std::shared_ptr<AutoPilot> autopilot,
		  ProtocolEngine* protocol_engine);
  /**
   * Interprets a TLVFrame and calls a specific function as described by the command
   * of the Frame
   * @param device a pointer to the device mentioned in the frame
   * @param frame is a pointer to the TLVFrame holding the data and command
   */
  void
  interpret_frame (Device* device, Frame* frame);
  /**
   * Destructor
   */
  ~TLVInterpreter ();

};

#endif /* COMMUNICATION_TLV_INTERPRETER_H_ */
