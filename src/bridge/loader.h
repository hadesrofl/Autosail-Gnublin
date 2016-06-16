#ifndef BRIDGE_LOADER_H_
#define BRIDGE_LOADER_H_

#include <memory>
#include "../devices/stream_generator.h"
#include "../autopilot/autopilot.h"
#include "../communication/protocol_engine.h"
#include "../communication/tlve_engine.h"
#include "../utils/conf_reader.h"
#include "../devices/device_manager.h"
/**
 * @file
 * @class Loader
 * @brief Class for the System Loader . Boots the System and inits components like
 * DeviceManager, StreamGenerator, ProtocolEngine and AutoPilot
 * @author Rene Kremer
 * @version 0.2
 */
class Loader
{
  /**
   * @private
   */
private:
  /**
   * StreamGenerator
   */
  std::shared_ptr<StreamGenerator> m_stream_generator;
  /**
   * ProtocolEngine
   */
  std::shared_ptr<ProtocolEngine> m_protocol_engine;
  /**
   * AutoPilot
   */
  std::unique_ptr<AutoPilot> m_autopilot;
  /**
   * DeviceManager
   */
  std::shared_ptr<DeviceManager> m_device_manager;
  /**
   * @public
   */
public:
  /**
   * Constructor
   */
  Loader ();

  inline ProtocolEngine* get_protocol_engine() const {
    return &(*m_protocol_engine);
  }
  /**
   * Destructor
   */
  ~Loader ();
};

#endif /* BRIDGE_LOADER_H_ */
