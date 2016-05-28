#include "../gnublin_wo_smtp.h"
#include "devices/device_manager.h"
#include "devices/device.h"
#include "bridge/timer.h"

#ifdef _TEST
#define TEENSY_I2C_ 0x55
#include "interfaces/serial.h"
#include "interfaces/spi.h"
#include "interfaces/i2c.h"
#include "test/asserter.h"
#include <vector>
#endif

/**
 * @mainpage Autosail --- Port of the firmware from a microprocessor to the gnublin platform for an autonomous sailboat
 *
 * Bachelor Thesis by Rene Kremer
 *
 */

#ifdef _TEST
/**
 * Test for the i2c interface with a Teensyduino. Sends two byte to the teensy, which is
 * configured as echo client and checks if the same bytes are recceived.
 * If all Cases pass the return value is 1 for success otherwise -1 for failure.
 * @return 1 on success otherwise -1
 */
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
	return -1;
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
#ifndef _TEST
  DeviceManager dmanager;
  Device* device_a = dmanager.get_sensor (Device_ID::COMPASS);
  while (true)
    {
      device_a->read_data ();
      std::cout << "Cycle done" << std::endl;
      sleep (1);
    }
#endif
  return 0;
}
