#ifndef BRIDGE_LOADER_H_
#define BRIDGE_LOADER_H_

#include <memory>
#include "../devices/stream_generator.h"
#include "../autopilot/autopilot.h"
#include "../communication/protocol_engine.h"
#include "../communication/tlve_engine.h"
#include "../utils/conf_reader.h"
#include "../devices/device_manager.h"
#include "../devices/stream_generator_thread_params.h"
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
  /**
   * Starts the StreamGenerator as a new thread
   * @return the started thread as it is needed to be joined by the caller
   */
  pthread_t
  start_generator ();
  /**
   * Gets the ProtocolEngine
   * @return a pointer to the ProtocolEngine
   */
  inline std::shared_ptr<ProtocolEngine>
  get_protocol_engine () const
  {
    return m_protocol_engine;
  }
  /**
   * Gets the StreamGenerator
   * @return a pointer to the StreamGenerator
   */
  inline std::shared_ptr<StreamGenerator>
  get_stream_generator ()
  {
    return m_stream_generator;
  }
  /**
   * Gets the DeviceManager
   * @return a pointer to the DeviceManager
   */
  inline std::shared_ptr<DeviceManager>
  get_device_manager () const
  {
    return m_device_manager;
  }
  /**
   * Destructor
   */
  ~Loader ();
};

#endif /* BRIDGE_LOADER_H_ */
