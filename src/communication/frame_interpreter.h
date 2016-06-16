#ifndef COMMUNICATION_FRAME_INTERPRETER_H_
#define COMMUNICATION_FRAME_INTERPRETER_H_

#include "frame.h"
#include "data_structure_identifier.h"
#include "../devices/device.h"
#include "component_descriptor_enum.h"
#include "../devices/stream_generator.h"
#include <memory>
#include <map>

/*
 * Forward Declaration because of recursive include of header files
 */
class StreamGenerator;
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
   * Pointer to the StreamGenerator. Needed as it is no Device but has commands
   */
  std::shared_ptr<StreamGenerator> m_stream_generator;
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
   * @param device is a pointer to the device mentioned in the frame
   * @param frame is a pointer to the Frame to interprets
   * @return a frame with data to send or NULL if no frame has to be sent
   */
  virtual Frame*
  interpret_frame (Device* device, Frame* frame) = 0;
  /**
   * Virtual Desctructor
   */
  virtual
  ~FrameInterpreter ()
  {
  }
};

#endif /* COMMUNICATION_FRAME_INTERPRETER_H_ */
