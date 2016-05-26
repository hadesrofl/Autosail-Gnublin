#include "i2c.h"

I2C::I2C (char* device_file, uint8_t address)
{
  m_device_file = Interface::set_device_file(device_file);
  m_slave_address = address;
  m_i2c_port = std::unique_ptr<gnublin_i2c> (
      new gnublin_i2c (device_file, address));
}

I2C::I2C (uint8_t address)
{
  m_i2c_port = std::unique_ptr<gnublin_i2c> (new gnublin_i2c (address));
  m_device_file = Interface::set_device_file(GNUBLIN_DEFAULT_I2C);
  m_slave_address = m_i2c_port->getAddress ();
}

int16_t
I2C::receive (uint8_t* buf, int16_t length)
{
  if (buf == 0)
    {
#ifdef _DEBUG
      std::cout << "ERROR: Buffer is empty!" << std::endl;
#endif
      return -1;
    }
  if (length < 1)
    {
#ifdef _DEBUG
      std::cout << "ERROR: Length is less or equal to 0!" << std::endl;
#endif
      return -1;
    }
  int8_t ret = m_i2c_port->receive (buf, length);
#ifdef _DEBUG
  if (ret != 1)
    {
      std::cout << "I2C Receive error!" << std::endl;
      std::cout << m_i2c_port->getErrorMessage () << std::endl;
    }
  else
    {
      std::cout << "I2C Receive ok: ";
      for (int16_t i = 0; i < length; i++)
	{
	  std::cout << buf[i] << " ";
	}
      std::cout << std::endl;
    }
#endif
  return ret;
}

int16_t
I2C::send (uint8_t* buf, int16_t length)
{
  if (buf == 0)
    {
#ifdef _DEBUG
      std::cout << "ERROR: Buffer is empty!" << std::endl;
#endif
      return -1;
    }
  if (length < 1)
    {
#ifdef _DEBUG
      std::cout << "ERROR: Length is less or equal to 0!" << std::endl;
#endif
      return -1;
    }
  int8_t ret = m_i2c_port->send (buf, length);
#ifdef _DEBUG
  if (ret != 1)
    {
      std::cout << "I2C Send error!" << std::endl;
      std::cout << m_i2c_port->getErrorMessage () << std::endl;

    }
  else
    {
      std::cout << "I2C Send ok!" << std::endl;
      std::cout << "Send: ";
      for (int16_t i = 0; i < length; i++)
	{
	  std::cout << buf[i] << " ";
	}
      std::cout << std::endl;
    }
#endif
  return ret;
}

I2C::~I2C ()
{
}
