#include "../loader/loader.h"

Loader::Loader ()
{
  m_stream_generator = NULL;
  m_autopilot = NULL;
  ConfReader* reader = new ConfReader (FW_CONFIG);
  m_protocol_engine = distinguish_protocol (reader->get_protocol (),
					    reader->get_protocol_version (),
					    reader->get_boat_id ());
  if (m_protocol_engine != NULL)
    {
      m_device_manager = std::shared_ptr<DeviceManager> (
	  new DeviceManager (&(*m_protocol_engine),
			     reader->get_device_configs ()));
    }
  else
    {
      exit (EXIT_FAILURE);
    }
  if (reader->get_stream_generator_config ().size () >= 3)
    {
      m_stream_generator = std::shared_ptr<StreamGenerator> (
	  new StreamGenerator (
	      get_descriptor (reader->get_stream_generator_config ()),
	      reader->get_stream_generator_config ().at (3)));

      m_protocol_engine->insert_communication_table_forward (
	  &(*m_stream_generator->get_component_descriptor ()),
	  m_stream_generator->get_communication_number ());
    }
  if (reader->get_autopilot_config ().size() >= 3)
    {

      m_autopilot = std::shared_ptr<AutoPilot> (
	  new AutoPilot (get_descriptor (reader->get_autopilot_config ()),
			 reader->get_autopilot_config ().at (3)));
      m_protocol_engine->insert_communication_table_forward (
	  &(*m_autopilot->get_component_descriptor ()),
	  m_autopilot->get_communication_number ());
    }
  m_protocol_engine->start_interpreter (m_stream_generator, m_autopilot);
  if (m_stream_generator != NULL)
    {
      m_stream_generator->set_protocol_engine (m_protocol_engine);
    }
  SerialLink* sl = dynamic_cast<SerialLink*> (&(*(m_device_manager->get_device (
      ComponentDescriptorEnum::SERIAL_LINK))));
  m_protocol_engine->set_serial_link (std::shared_ptr<SerialLink> (sl));
  if (m_stream_generator != NULL)
    {
      start_generator ();
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
	  new TLVEEngine (protocol_version, boat_id));
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
	  new TLVEEngine (protocol_version, boat_id));
      break;
    }
  return NULL;
}
std::shared_ptr<StreamGenerator>
Loader::create_stream_generator (
    std::shared_ptr<ComponentDescriptor> descriptor,
    uint8_t communication_number)
{
  return std::shared_ptr<StreamGenerator> (
      new StreamGenerator (descriptor, communication_number));
}
std::shared_ptr<AutoPilot>
Loader::create_autopilot (std::shared_ptr<ComponentDescriptor> descriptor,
			  uint8_t communication_number)
{
  return std::shared_ptr<AutoPilot> (
      new AutoPilot (descriptor, communication_number));
}
std::shared_ptr<ComponentDescriptor>
Loader::get_descriptor (std::vector<uint8_t> config)
{
  uint8_t component_class, component_attribute, component_number;
  component_class = config.at (0);
  component_attribute = config.at (1);
  component_number = config.at (2);
  return std::shared_ptr<ComponentDescriptor> (
      m_protocol_engine->create_descriptor (component_class,
					    component_attribute,
					    component_number));;
}
Loader::~Loader ()
{

}
