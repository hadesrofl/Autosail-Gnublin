#ifdef _TEST
#include "communication_table_test.h"

// public functions
CommunicationTableTest::CommunicationTableTest ()
{

}
bool
CommunicationTableTest::test_cases ()
{
  std::vector<bool> passed;
  Asserter asserter;
  std::cout << "---------------------------------" << std::endl;
  std::cout << "Starting Communication Table Test" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  passed.push_back (communication_table_standard_test ());
  return asserter.check_asserts (passed, 1);
}
CommunicationTableTest::~CommunicationTableTest ()
{

}

// private functions
bool
CommunicationTableTest::communication_table_standard_test ()
{
  Loader* loader = new Loader ();
  std::shared_ptr<DeviceManager> dmanager = loader->get_device_manager ();
  std::shared_ptr<ProtocolEngine> engine = loader->get_protocol_engine ();
  std::vector<bool> asserts;
  Asserter asserter;
  bool passed;
  std::shared_ptr<Device> device_a = dmanager->get_device (
      ComponentDescriptorEnum::GYROSCOPE);
  std::shared_ptr<Device> device_b = dmanager->get_device (
      ComponentDescriptorEnum::ACCELEROMETER);
  std::shared_ptr<Device> device_c = dmanager->get_device (
      ComponentDescriptorEnum::COMPASS);
  asserts.push_back (
      asserter.assert (
	  engine->get_communication_number (
	      device_a->get_component_descriptor ()),
	  0x03));
  asserts.push_back (
      asserter.assert (
	  engine->get_communication_number (
	      device_b->get_component_descriptor ()),
	  0x01));
  asserts.push_back (
      asserter.assert (
	  engine->get_communication_number (
	      device_c->get_component_descriptor ()),
	  0x02));
  std::cout << "Assert Communication Table forward..." << std::endl;
  passed = asserter.check_asserts (asserts, 3);
  if (passed == true)
    {
      std::cout << "Communication Table forward is fine!" << std::endl;
    }
  else
    {
      return -1;
    }
  passed = false;
  asserts.clear ();
  std::shared_ptr<Device> dev_a = engine->get_device (
      engine->get_communication_number (device_a->get_component_descriptor ()));
  std::shared_ptr<Device> dev_b = engine->get_device (
      engine->get_communication_number (device_b->get_component_descriptor ()));
  std::shared_ptr<Device> dev_c = engine->get_device (
      engine->get_communication_number (device_c->get_component_descriptor ()));
  asserts.push_back (asserter.assert (device_a, dev_a));
  asserts.push_back (asserter.assert (device_b, dev_b));
  asserts.push_back (asserter.assert (device_c, dev_c));
  std::cout << "Assert Communication Table backward..." << std::endl;
  passed = asserter.check_asserts (asserts, 3);
  if (passed == true)
    {
      std::cout << "Communication Table backward is fine!" << std::endl;
      std::cout << "---------------------------------" << std::endl;
      return passed;
    }
  std::cout << "---------------------------------" << std::endl;
  return passed;
}
#endif
