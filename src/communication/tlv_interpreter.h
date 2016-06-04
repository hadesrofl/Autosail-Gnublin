#ifndef COMMUNICATION_TLV_INTERPRETER_H_
#define COMMUNICATION_TLV_INTERPRETER_H_

#include "frame_interpreter.h"
#include "tlv_frame.h"

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
   * @param frame is a pointer to the TLVFrame holding the data and command
   */
  void
  interpret_frame (TLVFrame* frame);
  /**
   * Destructor
   */
  ~TLVInterpreter ();

};

#endif /* COMMUNICATION_TLV_INTERPRETER_H_ */
