#include "../gnublin_wo_smtp.h"
#include "devices/device_manager.h"
#include "bridge/loader.h"

#ifdef _TEST
#define TEENSY_I2C_ 0x55
#include "interfaces/serial.h"
#include "interfaces/spi_thread_param.h"
#include "interfaces/i2c.h"
#include "test/asserter.h"
#include "devices/i2c_parameter.h"
#include <vector>
#include "communication/protocol_engine.h"
#endif

#ifdef _TEST

int8_t communication_table_test()
  {
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Starting Communication Table Test" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    Loader* loader = new Loader();
    DeviceManager* dmanager = loader->get_device_manager();
    ProtocolEngine* engine = loader->get_protocol_engine();
    std::vector<bool> asserts;
    std::unique_ptr<Asserter> asserter (new Asserter ());
    bool passed;
    Device* device_a = dmanager->get_device (ComponentDescriptorEnum::GYROSCOPE);
    Device* device_b = dmanager->get_device (
	ComponentDescriptorEnum::ACCELEROMETER);
    Device* device_c = dmanager->get_device (ComponentDescriptorEnum::COMPASS);
    asserts.push_back(asserter->assert(engine->get_communication_number(&(*device_a->get_component_descriptor())), 0x03));
    asserts.push_back(asserter->assert(engine->get_communication_number(&(*device_b->get_component_descriptor())), 0x01));
    asserts.push_back(asserter->assert(engine->get_communication_number(&(*device_c->get_component_descriptor())), 0x02));
    std::cout << "Assert Communication Table forward..." << std::endl;
    passed = asserter->check_asserts(asserts, 3);
    if(passed == true)
      {
	std::cout << "Communication Table forward is fine!" << std::endl;
      }
    else
      {
	return -1;
      }
    passed = false;
    asserts.clear();
    Device* dev_a = engine->get_device(engine->get_communication_number(&(*device_a->get_component_descriptor())));
    Device* dev_b = engine->get_device(engine->get_communication_number(&(*device_b->get_component_descriptor())));
    Device* dev_c = engine->get_device(engine->get_communication_number(&(*device_c->get_component_descriptor())));
    asserts.push_back(asserter->assert(device_a, dev_a));
    asserts.push_back(asserter->assert(device_b, dev_b));
    asserts.push_back(asserter->assert(device_c, dev_c));
    std::cout << "Assert Communication Table backward..." << std::endl;
    passed = asserter->check_asserts(asserts, 3);
    if(passed == true)
      {
	std::cout << "Communication Table backward is fine!" << std::endl;
	std::cout << "---------------------------------" << std::endl;
	return 1;
      }
    std::cout << "---------------------------------" << std::endl;
    return -1;
  }

/**
 * Short Test for causing an interrupt with multiple SPI Devices. As the SerialLink
 * shall check for interrupts, so that frames can be received really quick if the
 * slave wants to send something, it is essential that not all SPI Devices check for
 * interrupts and someone can distinguish between SPI Devices which check on
 * interrupts and which doesn't
 * @returns 1 on success, otherwise -1
 */
int8_t spi_interrupt_test()
  {
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Starting SPI Interrupt Test" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    SPIMasterSelect* spi_a = new SPIMasterSelect ((char*) "/dev/spidev0.0", 16000, 11);
    SPIMasterSelect* spi_b = new SPIMasterSelect ((char*) "/dev/spidev0.0",
	16000, 0);
    pthread_t interrupt_thread_a;
    struct SPIThreadParam params_a;
    params_a.spi_ptr = spi_a;
    int i = 0;
    while(i < 5)
      {
	pthread_create (&interrupt_thread_a, NULL, spi_a->pin_change_interrupt,
	    &params_a);
	pthread_join (interrupt_thread_a, NULL);
	i++;
	std::cout << "Interrupts: " << i << std::endl;
      }
    std::cout << "SPI A: " << std::endl;
    std::cout << " SPI Trigger Action: "
    << static_cast<char*> (spi_a->get_trigger_action()) << std::endl;
    std::cout << " SPI Interrupted: " << spi_a->get_interrupt_state () << std::endl;

    std::cout << "SPI B: " << std::endl;
    std::cout << " SPI Trigger Action: "
    << static_cast<char*> (spi_b->get_trigger_action()) << std::endl;
    std::cout << " SPI Interrupted: " << spi_b->get_interrupt_state ()
    << std::endl;

    std::cout << "Delete SPI A" << std::endl;
    delete spi_a;
    std::cout << "Delete SPI B" << std::endl;
    delete spi_b;
    std::cout << "---------------------------------" << std::endl;
    return 1;
  }

/**
 * Test for the i2c interface with a Teensyduino. Sends two byte to the teensy, which is
 * configured as echo client and checks if the same bytes are recceived.
 * If all Cases pass the return value is 1 for success otherwise -1 for failure.
 * @return 1 on success, otherwise -1
 */
int8_t
i2c_teensy_test ()
  {
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Starting Teeny I2C Test" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    std::unique_ptr<Asserter> asserter (new Asserter ());
    std::vector<bool> asserts;
    bool passed = false;
    I2C* i2c_interface = new I2C ((char*)GNUBLIN_DEFAULT_I2C, TEENSY_I2C_);
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
    std::cout << "---------------------------------" << std::endl;
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
  int8_t ret = communication_table_test();
  if(ret == 1)
    {
      std::cout << "Test passed. Communication Table passed!" << std::endl;
    }
  /*int8_t ret = spi_interrupt_test();
   if(ret == 1)
   {
   std::cout << "Test passed. SPI Interrupt works fine!" << std::endl;
   }
   */
  /*if (i2c_teensy_test () == 1)
   {
   std::cout << "Test passed. I2C works fine!" << std::endl;
   }
   else
   {
   std::cout << "Test failed. I2C has errors while sending/receiving!"
   << std::endl;
   }*/
#endif
#ifndef _TEST
  Loader* loader = new Loader ();
  DeviceManager* dmanager = loader->get_device_manager ();
  Device* device_a = dmanager->get_device (ComponentDescriptorEnum::GYROSCOPE);
  Device* device_b = dmanager->get_device (
      ComponentDescriptorEnum::ACCELEROMETER);
  Device* device_c = dmanager->get_device (ComponentDescriptorEnum::COMPASS);
  uint8_t *acc_data, *gyro_data, *compass_data;
  bool active = true;
  while (active)
    {
      if (device_a != NULL)
	{
	  gyro_data = device_a->read_data ();
	  sleep (1);
	}
      else
	{
	  active = false;
	}
      if (device_b != NULL)
	{
	  acc_data = device_b->read_data ();
	  sleep (1);
	}
      else
	{
	  active = false;
	}

      if (device_c != NULL)
	{
	  compass_data = device_c->read_data ();
	  sleep (1);
	}
      else
	{
	  active = false;
	}
      //std::cout << "Cycle done" << std::endl;

    }
#endif
  return 0;
}
