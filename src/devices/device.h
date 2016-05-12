#ifndef DEVICES_DEVICE_H_
#define DEVICES_DEVICE_H_

#include "../interfaces/interface.h"
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
   * @protected
   */
protected:
  /**
   * Port of the used interface
   */
  std::unique_ptr<Interface> m_interface_port;
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
  virtual int
    read (unsigned char* buf, int length) =0;
  /**
   * Writes data from a device for a given length
   * @param buf is the buffer with the data to write
   * @param length is the length of the written bytes
   * @return length on success, otherwise -1 on an Error
   */
  virtual int
    write (unsigned char* buf, int length) =0;
  /**
   * Default Destructor
   */
  virtual
  ~Device ()
  {
  }
};

#endif /* DEVICES_DEVICE_H_ */
