#ifdef _TEST
#include "serial_test.h"

SerialTest::SerialTest ()
{
}
bool
SerialTest::test_cases ()
{
  std::cout << "---------------------------------" << std::endl;
  std::cout << "Starting XBEE Serial Test" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  return xbee_test ();
}

bool
SerialTest::xbee_test ()
{
  SerialParameter* param = new SerialParameter (DeviceConfig::SERIAL_B38400);
  Serial* serial = new Serial (param->get_device_file (),
			       param->get_baudrate ());
  uint8_t tx[2] =
    { 0x36, 0x56 };
  uint8_t rx[2] =
    { 0 };
  int8_t received = 0, ret;
  std::cout << "Send: " << std::hex << static_cast<int32_t> (tx[0]) << " "
      << std::hex << static_cast<int32_t> (tx[1]) << std::endl;
  serial->send (tx, 2);
  tx[0] = 0x22;
  tx[1] = 0x33;
  std::cout << "Send: " << std::hex << static_cast<int32_t> (tx[0]) << " "
      << std::hex << static_cast<int32_t> (tx[1]) << std::endl;
  serial->send (tx, 2);
  tx[0] = 0x44;
  tx[1] = 0x55;
  std::cout << "Send: " << std::hex << static_cast<int32_t> (tx[0]) << " "
      << std::hex << static_cast<int32_t> (tx[1]) << std::endl;
  serial->send (tx, 2);
  tx[0] = 0x66;
  tx[1] = 0x77;
  std::cout << "Send: " << std::hex << static_cast<int32_t> (tx[0]) << " "
      << std::hex << static_cast<int32_t> (tx[1]) << std::endl;
  serial->send (tx, 2);
  tx[0] = 0x53;
  tx[1] = 0x69;
  std::cout << "Send: " << std::hex << static_cast<int32_t> (tx[0]) << " "
      << std::hex << static_cast<int32_t> (tx[1]) << std::endl;
  serial->send (tx, 2);
  tx[0] = 0x31;
  tx[1] = 0x50;
  std::cout << "Send: " << std::hex << static_cast<int32_t> (tx[0]) << " "
      << std::hex << static_cast<int32_t> (tx[1]) << std::endl;
  serial->send (tx, 2);
  while (received != 6)
    {
      ret = serial->receive (rx, 2);
      if (ret > 0)
	{
	  std::cout << "Received: " << std::hex << static_cast<int32_t> (rx[0])
	      << " " << std::hex << static_cast<int32_t> (rx[1]) << std::endl;
	  received++;
	}
    }
  return true;
}

SerialTest::~SerialTest ()
{
}
#endif

