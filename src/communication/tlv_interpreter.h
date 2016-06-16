#ifndef COMMUNICATION_TLV_INTERPRETER_H_
#define COMMUNICATION_TLV_INTERPRETER_H_

#include "frame_interpreter.h"
#include "tlv_frame.h"
#include "../devices/device_manager.h"
/**
 * @file
 * @class TLVInterpreter
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
   * public
   */
public:
  /**
   * Constructor
   */
  TLVInterpreter ();
  /**
   * Interprets a TLVFrame and calls a specific function as described by the command
   * of the Frame
   * @param device a pointer to the device mentioned in the frame
   * @param frame is a pointer to the TLVFrame holding the data and command
   * @return a frame with data to send or NULL if no frame has to be sent
   */
  Frame*
  interpret_frame (Device* device, TLVFrame* frame);
  /**
   * Destructor
   */
  ~TLVInterpreter ();

};

#endif /* COMMUNICATION_TLV_INTERPRETER_H_ */
