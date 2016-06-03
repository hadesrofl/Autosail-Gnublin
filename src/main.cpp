#include "../gnublin_wo_smtp.h"
#include "devices/device_manager.h"
#include "bridge/timer.h"
//#include <math.h>

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
  Device* device_a = dmanager.get_sensor (Descriptor::GYROSCOPE);
  Device* device_b = dmanager.get_sensor (Descriptor::ACCELEROMETER);
  Device* device_c = dmanager.get_sensor(Descriptor::COMPASS);
  uint8_t *acc_data, *gyro_data, *compass_data;
  /*float roll = 0, pitch = 0, yaw = 0;
  timeval now, before;
  */
  while (true)
    {
      gyro_data = device_a->read_data ();
      sleep(1);
      acc_data = device_b->read_data ();
      sleep(1);
      compass_data = device_c->read_data();

     /* int16_t gyro_x = (gyro_data[0] << 8) | gyro_data[1];
      int16_t gyro_y = (gyro_data[2] << 8) | gyro_data[3];
      int16_t gyro_z = (gyro_data[4] << 8) | gyro_data[5];


      int16_t acc_x = (acc_data[0] << 8) | acc_data[1];
      int16_t acc_y = (acc_data[2] << 8) | acc_data[3];
      int16_t acc_z = (acc_data[4] << 8) | acc_data[5];
      gettimeofday (&now, 0);
      float delta_seconds = (static_cast<float> (now.tv_sec)
	  + static_cast<float> (now.tv_usec / (1000.0 * 1000.0)))
	  - (static_cast<float> (before.tv_sec)
	      - static_cast<float> (before.tv_usec / (1000.0 * 1000.0)));
      roll = atan2 (static_cast<double> (acc_y), static_cast<double> (acc_z))
	  * 180 / M_PI;
      pitch = atan2 (
	  -static_cast<double> (acc_x),
	  sqrt (
	      static_cast<double> (acc_y * acc_y)
		  + static_cast<double> (acc_z * acc_z))) * 180 / M_PI;
      roll += gyro_x * delta_seconds;
      pitch += gyro_y * delta_seconds;
      yaw += gyro_z * delta_seconds;

      std::cout << "Roll: " << roll << std::endl;
      std::cout << "Pitch: " << pitch << std::endl;
      std::cout << "Yaw: " << yaw << std::endl;
      */
      std::cout << "Cycle done" << std::endl;
      sleep (1);
    }
#endif
  return 0;
}
