#ifndef DEVICES_DEVICE_H_
#define DEVICES_DEVICE_H_

#include "../interfaces/interface.h"
#include "sensor_params.h"
#include <iostream>

/**
 * @file
 * @class Device
 * @brief Class for a Device. A device is some kind of sensor and uses some kind of interface.
 * @author Rene Kremer
 * @version 0.2
 */
class Device
{
  /**
   * @private
   */
private:
  /**
   * Virtual Function: Inits a device.
   */
  virtual int8_t
  init () = 0;
  /**
   * @protected
   */
protected:
  /**
   * Port of the used interface
   */
  std::unique_ptr<Interface> m_interface_port;
  /**
   * Id of the Device
   */
  Device_ID m_device_id;
  /**
   * Sets the id of the device as specified in sensor params
   * @param id is the id of this specific device
   */
  inline void
  set_device_id (Device_ID id)
  {
    m_device_id = id;
  }
  /**
   * @public
   */
public:
  /**
   * Reads data from a device for a given length
   * @param buf is the buffer to save the data into
   * @param length is the length of byte to read
   * @return length on success, otherwise -1 on an Error
   */
  int8_t
  read (unsigned char* buf, int16_t length)
  {
    if (buf == 0 || length < 1)
      {
#ifdef _DEBUG
	std::cout << "ERROR: Buffer is empty!" << std::endl;
#endif
	return -1;
      }
    int8_t ret = m_interface_port->receive (buf, length);
    if (ret > 0)
      {
	return ret;
      }
#ifdef _DEBUG
    std::cout << "Read Error of the Device!" << std::endl;
#endif
    return -1;
  }
  /**
   * Virtual Function: Reads all data from the device
   * @return on success returns a pointer with allocated memory leading to the data,
   * otherwise returns a null pointer.
   */
  virtual uint8_t*
  read_data ()
  {
    uint8_t* data_ptr = NULL;
    return data_ptr;
  }
  /**
   * Writes data from a device for a given length
   * @param buf is the buffer with the data to write
   * @param length is the length of the written bytes
   * @return length on success, otherwise -1 on an Error
   */
  int8_t
  write (unsigned char* buf, int16_t length)
  {
    if (buf == 0 || length < 1)
      {
#ifdef _DEBUG
	std::cout << "ERROR: Buffer is empty!" << std::endl;
#endif
	return -1;
      }
    int8_t ret = m_interface_port->send (buf, length);
    if (ret > 0)
      {
	return ret;
      }
#ifdef _DEBUG
    std::cout << "Write Error of the Device!" << std::endl;
#endif
    return -1;
  }
  /**
   * Gets the id of this device
   * @return the id of this specific device
   */
  inline Device_ID
  get_device_id () const
  {
    return m_device_id;
  }
  /**
   * Default Destructor
   */
  virtual
  ~Device ()
  {
  }
};

#endif /* DEVICES_DEVICE_H_ */
