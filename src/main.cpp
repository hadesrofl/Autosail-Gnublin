#include "../gnublin_wo_smtp.h"
#include "devices/device_manager.h"

#ifdef _TEST
#define TEENSY_I2C_ 0x55
#include "interfaces/serial.h"
#include "interfaces/spi_thread_param.h"
#include "interfaces/i2c.h"
#include "test/asserter.h"
#include "devices/i2c_parameter.h"
#include <vector>
#endif

#ifdef _TEST
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
    SPIMasterSelect* spi = new SPIMasterSelect ((char*) "/dev/spidev0.0", 16000, true);
    SPIMasterSelect* spi_b = new SPIMasterSelect ((char*) "/dev/spidev0.0",
	16000, false);
    pthread_t interrupt_thread;
    struct SPIThreadParam params_t;
    params_t.spi_ptr = spi;
    int i = 0;
    while(i < 5){
    pthread_create (&interrupt_thread, NULL, spi->pin_change_interrupt,
	&params_t);

    pthread_join (interrupt_thread, NULL);
    i++;
    std::cout << "Interrupts: " << i << std::endl;
    }

    std::cout << "SPI A: " << std::endl;
    std::cout << " SPI Trigger Type Set: " << spi->get_trigger_type_set()
    << std::endl;
    std::cout << " SPI Trigger Action: "
    << static_cast<char*> (spi->get_trigger_action()) << std::endl;
    std::cout << " SPI Interrupted: " << spi->get_interrupt_state () << std::endl;

    std::cout << "SPI B: " << std::endl;
    std::cout << " SPI Trigger Type: " << spi_b->get_trigger_type_set() << std::endl;
    std::cout << " SPI Trigger Action: "
    << static_cast<char*> (spi_b->get_trigger_action()) << std::endl;
    std::cout << " SPI Interrupted: " << spi_b->get_interrupt_state ()
    << std::endl;

    std::cout << "Delete SPI A" << std::endl;
    delete spi;
    std::cout << "Delete SPI B" << std::endl;
    delete spi_b;
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

/*pthread_mutex_t region_mutex = PTHREAD_MUTEX_INITIALIZER;
 bool interrupted = false;
 struct pollfd *poll_fd;
 */

/*int
 set_trigger_type (int pin_num)
 {
 gnublin_gpio gpio;
 gpio.pinMode (pin_num, INPUT);
 char* dir = (char*) "/sys/class/gpio/gpio11/edge";
 ofstream file (dir);
 if (file < 0)
 {
 return 0;
 cout << "cannot open file: " << dir << endl;
 }
 file << "falling";
 file.close ();
 return 1;
 }*/

int
main (void)
{
#ifdef _TEST
  int8_t ret = spi_interrupt_test();
  if(ret == 1){
      std::cout << "Test passed. SPI Interrupt works fine!" << std::endl;
  }
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
  //DeviceManager dmanager;
  //Device* device_a = dmanager.get_sensor (Descriptor::GYROSCOPE);
  //Device* device_b = dmanager.get_sensor (Descriptor::ACCELEROMETER);
  //Device* device_c = dmanager.get_sensor (Descriptor::COMPASS);

  //uint8_t *acc_data, *gyro_data, *compass_data;
  //while (counter != 1)
  //{
  //gnublin_gpio gpio;
  //int value = gpio.digitalRead(11);
  //gyro_data = device_a->read_data ();
  //device_a->read_data ();
  //sleep (1);
  //acc_data = device_b->read_data ();
  //device_b->read_data ();
  //sleep (1);
  //compass_data = device_c->read_data();
  //device_c->read_data ();

  //std::cout << "Cycle done" << std::endl;
  //std::cout << "Pin 11: " << value << std::endl;
  //sleep (1);
  //}

#endif
  return 0;
}
