#include "spi_master_select.h"

SPIMasterSelect::SPIMasterSelect (char* device_file, uint16_t spi_speed)
{
  m_device_file = Interface::set_device_file(device_file);
  m_spi_port = std::unique_ptr<gnublin_spi> (new gnublin_spi ());
  // SPI Mode 1
  m_spi_port->setMode (1);
  // MSB
  m_spi_port->setLSB (0);
}
SPIMasterSelect::SPIMasterSelect (uint16_t spi_speed)
{
  m_device_file = Interface::set_device_file(GNUBLIN_SPI_DEVICE);
  m_spi_port = std::unique_ptr<gnublin_spi> (new gnublin_spi ());
  // SPI Mode 1
  m_spi_port->setMode (1);
  // MSB
  m_spi_port->setLSB (0);
}

int16_t
SPIMasterSelect::receive (uint8_t* buf, int16_t length)
{
  int result = m_spi_port->receive ((char*) buf, length);
#ifdef _DEBUG
  bool error = m_spi_port->fail ();
  std::cout << error << std::endl;
#endif
  return result;
}

int16_t
SPIMasterSelect::send (uint8_t* buf, int16_t length)
{
  int result = m_spi_port->send (buf, length);
#ifdef _DEBUG
  bool error = m_spi_port->fail ();
  std::cout << error << std::endl;
#endif
  return result;
}

SPIMasterSelect::~SPIMasterSelect ()
{
}

