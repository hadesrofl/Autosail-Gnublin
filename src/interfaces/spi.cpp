#include "spi.h"

SPI::SPI (char* device_file, unsigned int spi_speed)
{
  m_device_file = device_file;
  m_spi_port = std::unique_ptr<gnublin_spi> (new gnublin_spi ());
  // SPI Mode 1
  m_spi_port->setMode (1);
  // MSB
  m_spi_port->setLSB (0);
}

int
SPI::receive (unsigned char* buf, int length)
{
  int result = m_spi_port->receive ((char*) buf, length);
#ifdef _DEBUG
  bool error = m_spi_port->fail ();
  std::cout << error << std::endl;
#endif
  return result;
}

int
SPI::send (unsigned char* buf, int length)
{
  int result = m_spi_port->send (buf, length);
#ifdef _DEBUG
  bool error = m_spi_port->fail ();
  std::cout << error << std::endl;
#endif
  return result;
}

SPI::~SPI ()
{
}

