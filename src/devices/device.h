#ifndef DEVICES_DEVICE_H_
#define DEVICES_DEVICE_H_

#include "../interfaces/interface.h"
#include <iostream>

#include "device_config.h"
#include "../communication/component_descriptor.h"
#include "interface_parameter.h"

/**
 * @file
 * @class Device
 * @brief Class for a Device. A device is some kind of sensor and uses some kind of interface.
 * @author Rene Kremer
 * @version 0.3
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
   * Pointer to the ComponentDescriptor of the device
   */
  std::shared_ptr<ComponentDescriptor> m_descriptor;
  /**
   * Parameter of the Devices Interface
   */
  std::unique_ptr<InterfaceParameter> m_device_parameter;
  /**
   * Sets the ComponentDescriptor of this Device
   * @param descriptor is a pointer to the ComponentDescriptor of this device
   */
  inline void
  set_component_descriptor (ComponentDescriptor* descriptor)
  {
    m_descriptor = std::shared_ptr<ComponentDescriptor> (descriptor);
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
   * Gets the ComponentDescriptor of this specific Device
   * @return the descriptor of this specific device
   */
  inline std::shared_ptr<ComponentDescriptor>
  get_component_descriptor () const
  {
    return m_descriptor;
  }
  /**
   * Gets the Parameter of the Device
   * @return the Device Parameter
   */
  inline InterfaceParameter
  get_device_parameter () const
  {
    return *m_device_parameter;
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
