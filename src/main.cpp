#include "../gnublin_wo_smtp.h"
#include "devices/device_manager.h"
#include "devices/device.h"

#ifdef _TEST
#define TEENSY_I2C_ 0x55
#include "interfaces/serial.h"
#include "interfaces/spi.h"
#include "interfaces/i2c.h"
#include "test/asserter.h"
#include <vector>
#endif

/**
 * @mainpage Robotic-Sailing --- Port from a microprocessor to the gnublin platform
 *
 * Bachelor Thesis by Rene Kremer
 *
 */

#ifdef _TEST
int
i2c_teensy_test ()
  {
    std::unique_ptr<Asserter> asserter (new Asserter ());
    std::vector<bool> asserts;
    bool passed = false;
    I2C* i2c_interface = new I2C (TEENSY_I2C_);
    unsigned char tx[2] =
      { 0x36, 0x56};
    unsigned char rx[2] =
      { 0};
    i2c_interface->send (tx, 2);
    i2c_interface->receive (rx, 2);
    asserts.push_back (asserter->assert (tx, rx, 2));
    tx[0] = 0x22;
    tx[1] = 0x33;
    i2c_interface->send (tx, 2);
    i2c_interface->receive (rx, 2);
    asserts.push_back (asserter->assert (tx, rx, 2));
    tx[0] = 0x44;
    tx[1] = 0x55;
    i2c_interface->send (tx, 2);
    i2c_interface->receive (rx, 2);
    asserts.push_back (asserter->assert (tx, rx, 2));
    tx[0] = 0x66;
    tx[1] = 0x77;
    i2c_interface->send (tx, 2);
    i2c_interface->receive (rx, 2);
    asserts.push_back (asserter->assert (tx, rx, 2));
    tx[0] = 0x53;
    tx[1] = 0x69;
    i2c_interface->send (tx, 2);
    i2c_interface->receive (rx, 2);
    asserts.push_back (asserter->assert (tx, rx, 2));
    tx[0] = 0x31;
    tx[1] = 0x50;
    i2c_interface->send (tx, 2);
    i2c_interface->receive (rx, 2);
    asserts.push_back (asserter->assert (tx, rx, 2));
    passed = asserter->check_asserts (asserts, asserts.size ());
    if (passed == true)
      {
	return 1;
      }
    else
      {
	return 0;
      }
  }
#endif
int
main (void)
{
#ifdef _TEST
  if (i2c_teensy_test () == 1)
    {
      std::cout << "Test passed. I2C works fine!" << std::endl;
    }
  else
    {
      std::cout << "Test failed. I2C has errors while sending/receiving!"
      << std::endl;
    }
#endif
  DeviceManager dmanager;
  Device* device = dmanager.get_sensor (Device_ID::ACCELEROMETER);
  unsigned char tx[1] =
    { 0 };
  std::cout << tx[0] << " " << std::endl;
  std::cout << "TX ok" << std::endl;
  unsigned char rx[4] =
    { 0 };
  std::cout << rx[0] << " " << rx[1] << std::endl;
  std::cout << "RX ok" << std::endl;
  while (true)
    {
      //Set Register Pointer to first Data Register
      tx[0] = 0x32;
      device->write (tx, 1);
      for (int i = 0; i < 6; i++)
	{
	  device->read (rx, 1);
	  int k = rx[0];
	  //int y = rx[1];
	  std::cout << "Values: " << k << " "
	      //<< y
	      << std::endl;
	}

      //std::cout << "Read: " << rx[0] << " " << rx[1] << std::endl;
      std::cout << "Cycle done" << std::endl;
      sleep (1);
    }
  return 0;
}
