#ifdef _TEST
#include "stream_generator_test.h"

StreamGeneratorTest::StreamGeneratorTest ()
{
}
bool
StreamGeneratorTest::test_cases ()
{
  std::vector<bool> passed;
  Asserter asserter;
  std::cout << "---------------------------------" << std::endl;
  std::cout << "Starting Stream Test" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  passed.push_back (stream_test ());
  return asserter.check_asserts (passed, 1);
}
void
StreamGeneratorTest::eval ()
{
  Loader* loader = new Loader ();
  std::vector<uint8_t> payload;
  uint8_t comm_number, attribute;
  std::shared_ptr<Device> device;
  std::shared_ptr<ComponentDescriptor> descriptor;
  Frame* frame;
  std::shared_ptr<StreamGenerator> generator = loader->get_stream_generator ();
  stream_generator_thread_param_t* generator_params =
      new stream_generator_thread_param_t;
  generator_params->generator_ptr = generator;
  attribute = loader->get_protocol_engine ()->tlve4_attribute (
      DataStructureIdentifier::INT16,
      loader->get_stream_generator ()->get_communication_number ());
  std::cout
      << "Getting Data Stream Seconds; Getting Data Stream Milliseconds;Send Data Stream Seconds;Send Data Stream Milliseconds;Difference Stream;"
      << std::endl;
  device = loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::ACCELEROMETER);
  comm_number = loader->get_protocol_engine ()->get_communication_number (
      device->get_component_descriptor ());
  payload.push_back (0);
  payload.push_back (comm_number);
  payload.push_back (0x00); //25 ms
  payload.push_back (0x19);
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::SET_VALUE,
							attribute,
							payload.size () + 1,
							payload);
  std::cout << "Activate Accelerometer Stream" << std::endl;
  loader->get_protocol_engine ()->interpret_frame (frame);
//  device = loader->get_device_manager ()->get_device (
//      ComponentDescriptorEnum::ANEMOMETER);
//  comm_number = loader->get_protocol_engine ()->get_communication_number (
//      device->get_component_descriptor ());
//  payload.push_back (0);
//  payload.push_back (comm_number);
//  payload.push_back (0x00); //25 ms
//  payload.push_back (0x19);
////  payload.push_back (0x00); //50 ms
////  payload.push_back (0x32);
//  frame = loader->get_protocol_engine ()->create_frame (TagEnum::SET_VALUE,
//							attribute,
//							payload.size () + 1,
//							payload);
//  std::cout << "Activate Anemometer Stream" << std::endl;
//  loader->get_protocol_engine ()->interpret_frame (frame);
//  device = loader->get_device_manager ()->get_device (
//      ComponentDescriptorEnum::COMPASS);
//  comm_number = loader->get_protocol_engine ()->get_communication_number (
//      device->get_component_descriptor ());
//  payload.clear ();
//  payload.push_back (0);
//  payload.push_back (comm_number);
//  payload.push_back (0x00); //25 ms
//  payload.push_back (0x19);
////  payload.push_back (0x00); //100ms
////  payload.push_back (0x64);
//  frame = loader->get_protocol_engine ()->create_frame (TagEnum::SET_VALUE,
//							attribute,
//							payload.size () + 1,
//							payload);
//  std::cout << "Activate Compass Stream" << std::endl;
//  loader->get_protocol_engine ()->interpret_frame (frame);
//  device = loader->get_device_manager ()->get_device (
//      ComponentDescriptorEnum::WIND_VANE);
//  comm_number = loader->get_protocol_engine ()->get_communication_number (
//      device->get_component_descriptor ());
//  payload.clear ();
//  payload.push_back (0);
//  payload.push_back (comm_number);
//  payload.push_back (0x00); //25 ms
//  payload.push_back (0x19);
////  payload.push_back (0x00); //150ms
////  payload.push_back (0x96);
//  frame = loader->get_protocol_engine ()->create_frame (TagEnum::SET_VALUE,
//							attribute,
//							payload.size () + 1,
//							payload);
//  std::cout << "Activate Wind Vane Stream" << std::endl;
//  loader->get_protocol_engine ()->interpret_frame (frame);
//  device = loader->get_device_manager ()->get_device (
//      ComponentDescriptorEnum::GYROSCOPE);
//  comm_number = loader->get_protocol_engine ()->get_communication_number (
//      device->get_component_descriptor ());
//  payload.clear ();
//  payload.push_back (0);
//  payload.push_back (comm_number);
//  payload.push_back (0x00); //25 ms
//  payload.push_back (0x19);
////  payload.push_back (0x00); //250ms
////  payload.push_back (0xFA);
//  frame = loader->get_protocol_engine ()->create_frame (TagEnum::SET_VALUE,
//							attribute,
//							payload.size () + 1,
//							payload);
//  std::cout << "Activate Gyroscope Stream" << std::endl;
//  loader->get_protocol_engine ()->interpret_frame (frame);
  while (true)
    ;
}
bool
StreamGeneratorTest::stream_test ()
{
  Loader* loader = new Loader ();
  std::vector<uint8_t> payload;
  uint8_t comm_number, attribute;
  std::shared_ptr<Device> device;
  std::shared_ptr<ComponentDescriptor> descriptor;
  Frame* frame;
  std::shared_ptr<StreamGenerator> generator = loader->get_stream_generator ();
  stream_generator_thread_param_t* generator_params =
      new stream_generator_thread_param_t;
  generator_params->generator_ptr = generator;
  loader->start_generator ();
  attribute = loader->get_protocol_engine ()->tlve4_attribute (
      DataStructureIdentifier::INT16,
      loader->get_stream_generator ()->get_communication_number ());
  device = loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::ACCELEROMETER);
  comm_number = loader->get_protocol_engine ()->get_communication_number (
      device->get_component_descriptor ());
  payload.push_back (0);
  payload.push_back (comm_number);
  payload.push_back (0x09); //2500 ms
  payload.push_back (0xC4);
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::SET_VALUE,
							attribute,
							payload.size () + 1,
							payload);
  std::cout << "Activate Accelerometer Stream" << std::endl;
  loader->get_protocol_engine ()->interpret_frame (frame);
  device = loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::COMPASS);
  comm_number = loader->get_protocol_engine ()->get_communication_number (
      device->get_component_descriptor ());
  payload.clear ();
  payload.push_back (0);
  payload.push_back (comm_number);
  payload.push_back (0x13); //5000ms
  payload.push_back (0x88);
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::SET_VALUE,
							attribute,
							payload.size () + 1,
							payload);
  std::cout << "Activate Compass Stream" << std::endl;
  loader->get_protocol_engine ()->interpret_frame (frame);
  device = loader->get_device_manager ()->get_device (
      ComponentDescriptorEnum::GYROSCOPE);
  comm_number = loader->get_protocol_engine ()->get_communication_number (
      device->get_component_descriptor ());
  payload.clear ();
  payload.push_back (0);
  payload.push_back (comm_number);
  payload.push_back (0x27); //10000ms
  payload.push_back (0x10);
  frame = loader->get_protocol_engine ()->create_frame (TagEnum::SET_VALUE,
							attribute,
							payload.size () + 1,
							payload);
  std::cout << "Activate Gyroscope Stream" << std::endl;
  loader->get_protocol_engine ()->interpret_frame (frame);
  loader->start_generator ();
  while (true)
    ;
  return true;
}

StreamGeneratorTest::~StreamGeneratorTest ()
{
}
#endif
