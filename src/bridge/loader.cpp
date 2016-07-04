#include "loader.h"

Loader::Loader ()
{
  //m_stream_generator = std::unique_ptr<StreamGenerator>(new StreamGenerator());
  m_protocol_engine = std::shared_ptr<ProtocolEngine> (new TLVEEngine());
  //m_autopilot = std::unique_ptr<AutoPilot> (new AutoPilot());
  ConfReader* reader = new ConfReader (DEVICE_CONFIG);
  m_device_manager = std::shared_ptr<DeviceManager> (new DeviceManager(&(*m_protocol_engine), reader->get_descriptors()));
  delete reader;
}
Loader::~Loader ()
{

}
