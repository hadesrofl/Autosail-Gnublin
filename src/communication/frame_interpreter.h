#ifndef COMMUNICATION_FRAME_INTERPRETER_H_
#define COMMUNICATION_FRAME_INTERPRETER_H_

#include "frame.h"
#include "data_structure_identifier.h"
/**
 * @file
 * @class FrameInterpreter
 * @brief Class for a virtual Frame Interpreter. Interprets Frames and calls
 * the specific function as described in the command of the frame.
 *
 * FrameInterpreter is developed to be extended by specific protocols like TLVE4 or JSON.
 * @author Rene Kremer
 * @version 0.2
 */
class FrameInterpreter
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
   */
  FrameInterpreter ()
  {

  }
  /**
   * Virtual Function to interpret a frame.
   * Has to be implemented for a Frame Interpreter
   */
  virtual void
  interpret_frame (Frame* frame) = 0;
  /**
   * Virtual Desctructor
   */
  virtual
  ~FrameInterpreter ()
  {
  }
};

#endif /* COMMUNICATION_FRAME_INTERPRETER_H_ */
