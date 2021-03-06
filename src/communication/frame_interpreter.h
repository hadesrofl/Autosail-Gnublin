/**
 * Copyright 2016 Rene Kremer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef COMMUNICATION_FRAME_INTERPRETER_H_
#define COMMUNICATION_FRAME_INTERPRETER_H_

#include "frame.h"
#include "../devices/device.h"
#include "component_descriptor_enum.h"
#include "datastructure_identifier.h"
#include "../devices/stream_generator.h"
#include "../autopilot/autopilot.h"
#include "protocol_engine.h"

/*
 * Forward Declaration because of recursive include of header files
 */
class StreamGenerator;
/*
 * Forward Declaration because of recursive include of header files
 */
class ProtocolEngine;
/*
 * Forward Declaration because of recursive include of header files
 */
class AutoPilot;
/**
 * @file
 * @class FrameInterpreter
 * @ingroup Communication
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
   * Pointer to the StreamGenerator. Needed as it is no Device but has commands
   */
  std::shared_ptr<StreamGenerator> m_stream_generator;
  /**
   * Pointer to the AutoPilot as there are some commands he needs to execute
   */
  std::shared_ptr<AutoPilot> m_autopilot;
  /**
   * Pointer to the ProtocolEngine, as there are some commands that
   * need data from the engine
   */
  std::shared_ptr<ProtocolEngine> m_protocol_engine;
  /**
   * Constructor needed for class hierarchy purposes. Shouldn't be called
   */
  FrameInterpreter ()
  {
  }
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param generator is a pointer to the StreamGenerator
   * @param autopilot is a pointer to the AutoPilot
   * @param protocol_engine is a pointer to the ProtocolEngine
   */
  FrameInterpreter (StreamGenerator* generator, AutoPilot* autopilot,
		    ProtocolEngine* protocol_engine)
  {
  }
  /**
   * Virtual Function to interpret a frame.
   * Has to be implemented for a Frame Interpreter
   * @param device is a pointer to the device mentioned in the frame
   * @param frame is a pointer to the Frame to interprets
   */
  virtual void
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
