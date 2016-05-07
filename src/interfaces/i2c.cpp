#include "i2c.h"

I2C::I2C (int address)
{
  m_i2c_port = std::unique_ptr<gnublin_i2c> (new gnublin_i2c(address));
 // m_i2c_port = new gnublin_i2c(address);
  m_device_file = GNUBLIN_DEFAULT_I2C;
  m_slave_address = m_i2c_port->getAddress();
}
I2C::I2C (char* device_file, int address)
{
  m_device_file = device_file;
  m_slave_address = address;
  m_i2c_port = std::unique_ptr<gnublin_i2c> (new gnublin_i2c(device_file, address));
 // m_i2c_port = new gnublin_i2c(device_file, address);
}

int
I2C::receive (unsigned char* buf, int length)
{
  int ret = m_i2c_port->receive(buf, length);
  if(ret == 1){
      std::cout << "I2C Receive ok: ";

  }
  else{
      std::cout << "I2C Receive error!" << std::endl;
      std::cout << m_i2c_port->getErrorMessage() << std::endl;
  }
  return ret;
}

int
I2C::send (unsigned char* buf, int length)
{
  int ret = m_i2c_port->send(buf, length);
  if(ret == 1){
      std::cout << "I2C Send ok!" << std::endl;
      std::cout << "Send: ";
      for(int i = 0; i < length; i++){
     	      std::cout << buf[i] << " ";
     	  }
     	  std::cout << std::endl;
  }
  else{
      std::cout << "I2C Send error!" << std::endl;
      std::cout << m_i2c_port->getErrorMessage() << std::endl;
  }
  return ret;
}

I2C::~I2C ()
{
}
