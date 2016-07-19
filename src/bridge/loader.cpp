#include "loader.h"

Loader::Loader ()
{
  m_stream_generator = std::shared_ptr<StreamGenerator> (
      new StreamGenerator ());
  m_protocol_engine = std::shared_ptr<ProtocolEngine> (new TLVEEngine ());
  //m_autopilot = std::unique_ptr<AutoPilot> (new AutoPilot());
  ConfReader* reader = new ConfReader (DEVICE_CONFIG);
  m_device_manager = std::shared_ptr<DeviceManager> (
      new DeviceManager (&(*m_protocol_engine), reader->get_descriptors ()));
  delete reader;
}
pthread_t
Loader::start_generator ()
{
  stream_generator_thread_param_t* generator_params =
      new stream_generator_thread_param_t;
  generator_params->generator_ptr = m_stream_generator;
  pthread_t generator_thread;
  pthread_create (&generator_thread, NULL, m_stream_generator->run_generator,
		  generator_params);
  return generator_thread;
}
Loader::~Loader ()
{

}
