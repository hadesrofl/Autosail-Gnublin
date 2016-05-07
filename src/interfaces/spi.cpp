#include "spi.h"

SPI::SPI(char* device_file, unsigned int spi_speed)
{
  m_device_file = device_file;
  m_spi_port = std::unique_ptr<gnublin_spi> (new gnublin_spi());
  //m_spi_port = new gnublin_spi();
  //m_spi_port->setSpeed(spi_speed);
  // SPI Mode 1
  m_spi_port->setMode(1);
  // MSB
  m_spi_port->setLSB(0);
  //m_spi_port->setSpeed(spi_speed);
}

int SPI::receive(unsigned char* buf, int length)
{
	/*char rx[2] = {0x66, 0x77};
	std::cout << "Initial Buffer: " << rx[0] << " " << rx[1] << std::endl;
	std::cout << rx[0] << " " << rx[1] << std::endl;
	*/
	int result = m_spi_port->receive((char*) buf, length);
	/*std::cout << "Result " << result << std::endl;
	std::cout << "Buffer Ergebnisse: " << buf[0] << " " << buf[1] << std::endl;
	*/
	return result;
}

int SPI::send(unsigned char* buf, int length)
{
	int result = m_spi_port->send(buf, length);
	/*bool error = m_spi_port->fail();
	std::cout << error << std::endl;
	*/
	return result;
}

SPI::~SPI()
{
}

