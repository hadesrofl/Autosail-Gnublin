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
bool
StreamGeneratorTest::stream_test ()
{
  uint8_t comm_number;
  Loader* loader = new Loader ();
  std::shared_ptr<DeviceManager> dmanager = loader->get_device_manager ();
  std::shared_ptr<Device> device_a = dmanager->get_device (
      ComponentDescriptorEnum::GYROSCOPE);
  std::shared_ptr<Device> device_b = dmanager->get_device (
      ComponentDescriptorEnum::ACCELEROMETER);
  std::shared_ptr<Device> device_c = dmanager->get_device (
      ComponentDescriptorEnum::COMPASS);
  std::shared_ptr<Device> device_d = dmanager->get_device (
      ComponentDescriptorEnum::GPS_POSITION);
  std::shared_ptr<StreamGenerator> generator = loader->get_stream_generator ();
  stream_generator_thread_param_t* generator_params =
      new stream_generator_thread_param_t;

  generator_params->generator_ptr = generator;

  pthread_t generator_thread = loader->start_generator ();
  sleep (2);
  comm_number = loader->get_protocol_engine ()->get_communication_number (
      device_a->get_component_descriptor ());
  generator->add_stream (device_a, comm_number, 2500);
  comm_number = loader->get_protocol_engine ()->get_communication_number (
      device_b->get_component_descriptor ());
  generator->add_stream (device_b, comm_number, 10000);
  comm_number = loader->get_protocol_engine ()->get_communication_number (
      device_c->get_component_descriptor ());
  generator->add_stream (device_c, comm_number, 5000);
  comm_number = loader->get_protocol_engine ()->get_communication_number (
      device_d->get_component_descriptor ());
  generator->add_stream (device_d, comm_number, 10000);
  sleep (2);
  comm_number = loader->get_protocol_engine ()->get_communication_number (
      device_a->get_component_descriptor ());
  generator->disable_stream (comm_number);
  sleep (6);
  comm_number = loader->get_protocol_engine ()->get_communication_number (
      device_a->get_component_descriptor ());
  generator->add_stream (device_a, comm_number, 2500);
  pthread_join (generator_thread, NULL);
  return true;
}

StreamGeneratorTest::~StreamGeneratorTest ()
{
}
#endif
