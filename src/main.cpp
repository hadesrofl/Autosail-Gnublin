#include "../gnublin_wo_smtp.h"
#include "interfaces/serial.h"
#include "interfaces/spi.h"
#include "interfaces/i2c.h"
#include "interfaces/interface_manager.h"

#define TEENSY_I2C 0x55
/**
 * @mainpage Robotic-Sailing --- Port from a microprocessor to the gnublin platform
 *
 * Bachelor Thesis by Rene Kremer
 *
 */
int
main (void)
{
  InterfaceManager imanager;
  I2C* i2c_interface = new I2C (TEENSY_I2C);
  unsigned char tx[2] =
    { 0x23, 0x25 };
  std::cout << tx[0] << " " << tx[1] << std::endl;
  std::cout << "TX ok" << std::endl;
  unsigned char rx[4] =
    { 0 };
  std::cout << rx[0] << " " << rx[1] << std::endl;
  std::cout << "RX ok" << std::endl;
  while (true)
    {
      // set Register Access Pointer to Data Output X LSB Register
      //tx[0] = 0x3C; tx[1] = 0x01;
      i2c_interface->send (tx, 2);
      i2c_interface->receive (rx, 2);
      std::cout << rx[0] << " " << rx[1] << std::endl;
      // set Register Access Pointer to Data Output X MSB Register
      //tx[0] = 0x3C; tx[1] = 0x03;
      //i2c_interface->send (tx, 2);
      // Read Data Output X LSB Register
      //i2c_interface->receive (rx, 2);
      //std::cout << rx[0] << " " << rx[1] << std::endl;
      std::cout << "Cycle done" << std::endl;
      sleep (1);
    }
  /*SPI *spi_interface = new SPI ((char*) "/dev/spidev0.11", 9600);
   std::cout << "Constructor ok" << std::endl;
   unsigned int i = 0;
   unsigned char tx[2] = {0x23, 0x25};
   std::cout << tx[0] << " " << tx[1] << std::endl;
   std::cout << "TX ok" << std::endl;
   unsigned char rx[4] = {0};
   std::cout << rx[0] << " " << rx[1] << std::endl;
   std::cout << "RX ok" << std::endl;
   while(true){
   spi_interface->send(tx, 2);
   std::cout << "Send ok" << std::endl;
   spi_interface->receive(rx,2);
   std::cout << rx[0] << " " << rx[1] << std::endl;
   std::cout << "Receive ok" << std::endl;
   i++;
   sleep(1);
   }*/
  return 0;
}
