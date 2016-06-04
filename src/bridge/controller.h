#ifndef BRIDGE_CONTROLLER_H_
#define BRIDGE_CONTROLLER_H_

#include <memory>
#include "../devices/stream_generator.h"
#include "../autopilot/autopilot.h"
#include "../communication/protocol_engine.h"
#include "../communication/tlve_engine.h"

class Controller
{
  /**
   * @private
   */
private:
  /**
   * StreamGenerator
   */
  std::unique_ptr<StreamGenerator> m_stream_generator;
  /**
   * ProtocolEngine
   */
  std::unique_ptr<ProtocolEngine> m_protocol_engine;
  /**
   * AutoPilot
   */
  std::unique_ptr<AutoPilot> m_autopilot;
  /**
   * @public
   */
public:
  /**
   * Constructor
   */
  Controller ();
  /**
   * Destructor
   */
  ~Controller ();
};

#endif /* SRC_BRIDGE_CONTROLLER_H_ */
