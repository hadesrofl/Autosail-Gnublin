
#ifdef _TEST
#include "i2c_test.h"

// public functions
I2CTest::I2CTest ()
{

}
bool
I2CTest::test_cases ()
{
  std::vector<bool> passed;
  Asserter assert;
  passed.push_back (i2c_teensy_test ());
  return assert.check_asserts (passed, 1);
}
I2CTest::~I2CTest ()
{

}

// private functions
bool
I2CTest::i2c_teensy_test ()
{
  std::cout << "---------------------------------" << std::endl;
  std::cout << "Starting Teensy I2C Test" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  std::unique_ptr<Asserter> asserter (new Asserter ());
  std::vector<bool> asserts;
  bool passed = false;
  I2C* i2c_interface = new I2C ((char*) GNUBLIN_DEFAULT_I2C, TEENSY_I2C_);
  uint8_t tx[2] =
    { 0x36, 0x56 };
  uint8_t rx[2] =
    { 0 };
  std::cout << "Send: " << static_cast<int32_t> (tx[0]) << " "
      << static_cast<int32_t> (tx[1]) << std::endl;
  i2c_interface->send (tx, 2);
  i2c_interface->receive (rx, 2);
  std::cout << "Received: " << static_cast<int32_t> (rx[0]) << " "
      << static_cast<int32_t> (rx[1]) << std::endl;
  asserts.push_back (asserter->assert (tx, rx, 2));
  tx[0] = 0x22;
  tx[1] = 0x33;
  std::cout << "Send: " << static_cast<int32_t> (tx[0]) << " "
      << static_cast<int32_t> (tx[1]) << std::endl;
  i2c_interface->send (tx, 2);
  i2c_interface->receive (rx, 2);
  std::cout << "Receive: " << static_cast<int32_t> (rx[0]) << " "
      << static_cast<int32_t> (rx[1]) << std::endl;
  asserts.push_back (asserter->assert (tx, rx, 2));
  tx[0] = 0x44;
  tx[1] = 0x55;
  std::cout << "Send: " << static_cast<int32_t> (tx[0]) << " "
      << static_cast<int32_t> (tx[1]) << std::endl;
  i2c_interface->send (tx, 2);
  i2c_interface->receive (rx, 2);
  std::cout << "Receive: " << static_cast<int32_t> (rx[0]) << " "
      << static_cast<int32_t> (rx[1]) << std::endl;
  asserts.push_back (asserter->assert (tx, rx, 2));
  tx[0] = 0x66;
  tx[1] = 0x77;
  std::cout << "Send: " << static_cast<int32_t> (tx[0]) << " "
      << static_cast<int32_t> (tx[1]) << std::endl;
  i2c_interface->send (tx, 2);
  i2c_interface->receive (rx, 2);
  std::cout << "Receive: " << static_cast<int32_t> (rx[0]) << " "
      << static_cast<int32_t> (rx[1]) << std::endl;
  asserts.push_back (asserter->assert (tx, rx, 2));
  tx[0] = 0x53;
  tx[1] = 0x69;
  std::cout << "Send: " << static_cast<int32_t> (tx[0]) << " "
      << static_cast<int32_t> (tx[1]) << std::endl;
  i2c_interface->send (tx, 2);
  i2c_interface->receive (rx, 2);
  std::cout << "Receive: " << static_cast<int32_t> (rx[0]) << " "
      << static_cast<int32_t> (rx[1]) << std::endl;
  asserts.push_back (asserter->assert (tx, rx, 2));
  tx[0] = 0x31;
  tx[1] = 0x50;
  std::cout << "Send: " << static_cast<int32_t> (tx[0]) << " "
      << static_cast<int32_t> (tx[1]) << std::endl;
  i2c_interface->send (tx, 2);
  i2c_interface->receive (rx, 2);
  std::cout << "Receive: " << static_cast<int32_t> (rx[0]) << " "
      << static_cast<int32_t> (rx[1]) << std::endl;
  asserts.push_back (asserter->assert (tx, rx, 2));
  passed = asserter->check_asserts (asserts, asserts.size ());
  std::cout << "---------------------------------" << std::endl;
  return passed;
}
#endif

