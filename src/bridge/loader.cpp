#include "loader.h"

Loader::Loader ()
{
  m_stream_generator = std::shared_ptr<StreamGenerator> (
      new StreamGenerator ());
  m_autopilot = std::shared_ptr<AutoPilot> (new AutoPilot ());
  ConfReader* reader = new ConfReader (FW_CONFIG);
  m_protocol_engine = distinguish_protocol (reader->get_protocol (),
					    reader->get_protocol_version (),
					    reader->get_boat_id ());
  if (m_protocol_engine != NULL)
    {
      m_device_manager = std::shared_ptr<DeviceManager> (
	  new DeviceManager (&(*m_protocol_engine),
			     reader->get_descriptors ()));
    }
  else
    {
      exit (EXIT_FAILURE);
    }
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

std::shared_ptr<ProtocolEngine>
Loader::distinguish_protocol (CommunicationProtocol protocol,
			      std::vector<uint8_t> protocol_version,
			      uint8_t boat_id)
{
  switch (protocol)
    {
    case CommunicationProtocol::TLVE4:
      return std::shared_ptr<ProtocolEngine> (
	  new TLVEEngine (m_stream_generator, m_autopilot, protocol_version,
			  boat_id));
      break;
    case CommunicationProtocol::TLVE5:
      break;
    case CommunicationProtocol::JSON4:
      break;
    case CommunicationProtocol::JSON5:
      break;
      // Default TLVE4
    default:
      return std::shared_ptr<ProtocolEngine> (
	  new TLVEEngine (m_stream_generator, m_autopilot, protocol_version,
			  boat_id));
      break;
    }
  return NULL;
}
Loader::~Loader ()
{

}
