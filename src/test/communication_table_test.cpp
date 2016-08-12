#ifdef _TEST
#include "communication_table_test.h"

#define ACC_COMM_NUMBER 0x05
#define COMPASS_COMM_NUMBER 0x06
#define GYRO_COMM_NUMBER 0x07

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
  uint8_t result, expected;
  std::shared_ptr<Device> device_a = dmanager->get_device (
      ComponentDescriptorEnum::ACCELEROMETER);
  std::shared_ptr<Device> device_b = dmanager->get_device (
      ComponentDescriptorEnum::GYROSCOPE);
  std::shared_ptr<Device> device_c = dmanager->get_device (
      ComponentDescriptorEnum::COMPASS);
  std::cout << "Communication Number: " << "\nAccelerometer: "
      << static_cast<int> (engine->get_communication_number (
	  device_a->get_component_descriptor ())) << "\nGyroscope: "
      << static_cast<int> (engine->get_communication_number (
	  device_b->get_component_descriptor ())) << "\nCompass: "
      << static_cast<int> (engine->get_communication_number (
	  device_c->get_component_descriptor ())) << std::endl;
  result = engine->get_communication_number (
      device_a->get_component_descriptor ());
  expected = ACC_COMM_NUMBER;
  std::cout << "\nAssert Communication Table forward..." << std::endl;
  std::cout << "Accelerometer: " << "\texpected: "
      << static_cast<int> (expected) << "\tresult: "
      << static_cast<int> (result) << std::endl;
  asserts.push_back (asserter.assert (result, expected));
  result = engine->get_communication_number (
      device_b->get_component_descriptor ());
  expected = GYRO_COMM_NUMBER;
  std::cout << "Gyroscope: " << "\texpected: " << static_cast<int> (expected)
      << "\tresult: " << static_cast<int> (result) << std::endl;
  asserts.push_back (
      asserter.assert (
	  engine->get_communication_number (
	      device_b->get_component_descriptor ()),
	  expected));
  result = engine->get_communication_number (
      device_c->get_component_descriptor ());
  expected = COMPASS_COMM_NUMBER;
  std::cout << "Compass: " << "\texpected: " << static_cast<int> (expected)
      << "\tresult: " << static_cast<int> (result) << std::endl;
  asserts.push_back (
      asserter.assert (
	  engine->get_communication_number (
	      device_c->get_component_descriptor ()),
	  expected));
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
  std::cout << "\nAssert Communication Table backward..." << std::endl;
  std::cout << "Accelerometer expected: " << "\nClass: "
      << static_cast<int> (device_a->get_component_descriptor ()->get_component_class ())
      << "\tAttribute: "
      << static_cast<int> (device_a->get_component_descriptor ()->get_component_attribute ())
      << "\tNumber: "
      << static_cast<int> (device_a->get_component_descriptor ()->get_component_number ())
      << std::endl;
  std::cout << "Accelerometer result: " << "\nClass: "
      << static_cast<int> (dev_a->get_component_descriptor ()->get_component_class ())
      << "\tAttribute: "
      << static_cast<int> (dev_a->get_component_descriptor ()->get_component_attribute ())
      << "\tNumber: "
      << static_cast<int> (dev_a->get_component_descriptor ()->get_component_number ())
      << std::endl;
  std::cout << "Gyroscope expected: " << "\nClass: "
      << static_cast<int> (device_b->get_component_descriptor ()->get_component_class ())
      << "\tAttribute: "
      << static_cast<int> (device_b->get_component_descriptor ()->get_component_attribute ())
      << "\tNumber: "
      << static_cast<int> (device_b->get_component_descriptor ()->get_component_number ())
      << std::endl;
  std::cout << "Gyroscope result: " << "\nClass: "
      << static_cast<int> (dev_b->get_component_descriptor ()->get_component_class ())
      << "\tAttribute: "
      << static_cast<int> (dev_b->get_component_descriptor ()->get_component_attribute ())
      << "\tNumber: "
      << static_cast<int> (dev_b->get_component_descriptor ()->get_component_number ())
      << std::endl;
  std::cout << "Compass expected: " << "\nClass: "
      << static_cast<int> (device_c->get_component_descriptor ()->get_component_class ())
      << "\tAttribute: "
      << static_cast<int> (device_c->get_component_descriptor ()->get_component_attribute ())
      << "\tNumber: "
      << static_cast<int> (device_c->get_component_descriptor ()->get_component_number ())
      << std::endl;
  std::cout << "Compass result: " << "\nClass: "
      << static_cast<int> (dev_c->get_component_descriptor ()->get_component_class ())
      << "\tAttribute: "
      << static_cast<int> (dev_c->get_component_descriptor ()->get_component_attribute ())
      << "\tNumber: "
      << static_cast<int> (dev_c->get_component_descriptor ()->get_component_number ())
      << std::endl;
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
