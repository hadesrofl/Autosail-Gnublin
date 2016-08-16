/*
 * battery.cpp
 *
 *  Created on: Jul 31, 2016
 *      Author: Rene Kremer
 */

#include "battery.h"

// private functions
int8_t
Battery::init ()
{
  return 1;
}

// public functions

Battery::Battery (SPIParameter *interface_parameter,
		  ComponentDescriptor* descriptor)
{
  m_interface_port = std::unique_ptr<SPIMasterSelect> (
      new SPIMasterSelect (interface_parameter->get_device_file (),
			   interface_parameter->get_speed (), false));
  set_component_descriptor (descriptor);
  m_device_parameter = std::unique_ptr<SPIParameter> (interface_parameter);
  init ();
}
std::vector<int8_t>
Battery::read_data ()
{
  std::vector<int8_t> data;
  int16_t write_length = 2;
  int16_t read_length = 4;
  uint8_t* write = new uint8_t[write_length];
  write[0] = IP_TAG_GET_CURRENT;
  write[1] = 0;
  uint8_t* read = new uint8_t[read_length];
//  dynamic_cast<SPIMasterSelect*> (&(*m_interface_port))->transfer (write,
//								   write_length,
//								   read,
//								   read_length);
  read[0] = 0x0A;
  read[1] = 0xFF;
  read[2] = 0xF5;
  read[3] = 0x01;
  m_voltage = (read[0] << 8) | read[1];
  m_current = (read[2] << 8) | read[3];
#ifdef _DEBUG
  std::cout << "Tag: " << static_cast<int> (write[0]) << "\tLength: "
      << static_cast<int> (write[1]) << std::endl;
  std::cout << "Voltage: " << static_cast<int> (read[0]) << " and "
      << static_cast<int> (read[1]) << "\nFused: " << m_voltage << std::endl;
  std::cout << "Current: " << static_cast<int> (read[2]) << " and "
      << static_cast<int> (read[3]) << "\nFused: " << m_current << std::endl;
#endif
  data.push_back (read[0]);
  data.push_back (read[1]);
  data.push_back (read[2]);
  data.push_back (read[3]);
  delete[] write;
  delete[] read;
  return data;
}

Battery::~Battery ()
{
}

