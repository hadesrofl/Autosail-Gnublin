#ifndef DEVICES_DEVICE_H_
#define DEVICES_DEVICE_H_

#include "../interfaces/interface.h"
#include "sensor_params.h"

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
  virtual int
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
  inline void set_device_id(Device_ID id){
    m_device_id = id;
  }
  /**
   * @public
   */
public:
  /**
   * Virtual Function: Reads data from a device for a given length
   * @param buf is the buffer to save the data into
   * @param length is the length of byte to read
   * @return length on success, otherwise -1 on an Error
   */
  virtual int
  read (unsigned char* buf, int length)
  {
    return -2;
  }
  /**
   * Virtual Function: Reads all data from the device
   * @return on success returns a pointer with allocated memory leading to the data,
   * otherwise returns a null pointer.
   */
  virtual unsigned char* read_data(){
    unsigned char* data_ptr = NULL;
    return data_ptr;
  }
  /**
   * Virtual Function: Writes data from a device for a given length
   * @param buf is the buffer with the data to write
   * @param length is the length of the written bytes
   * @return length on success, otherwise -1 on an Error
   */
  virtual int
  write (unsigned char* buf, int length)
  {
    return -2;
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
