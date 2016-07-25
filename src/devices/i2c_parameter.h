#ifndef DEVICES_I2C_PARAMETER_H_
#define DEVICES_I2C_PARAMETER_H_

#define GNUBLIN_DEFAULT_I2C "/dev/i2c-1"

/**
 * @file
 * @class I2CParameter
 * @ingroup Devices
 * @brief Class for Parameters of I2C Devices. Contains a address of the slave address.
 * @version 0.3
 */
class I2CParameter : virtual public InterfaceParameter
{
  /**
   * @private
   */
private:
  /**
   * Slave Address of the devices.
   */
  uint8_t m_slave_address;
  /**
   * @protected
   */
protected:
  /**
   * @public
   */
public:
  /**
   * Constructor for a I2C Parameter
   * @param device_file is the file of the device in linux.
   * @param slave_address is the address of the device.
   */
  I2CParameter (char* device_file, uint8_t slave_address)
  {
    m_device_file = device_file;
    m_slave_address = slave_address;
  }
  /**
   * Constructor for a I2C Parameter (called with default device file of gnublin)
   * @param slave_address is the address of the device.
   */
  I2CParameter (uint8_t slave_address)
  {
    m_device_file = (char*) GNUBLIN_DEFAULT_I2C;
    m_slave_address = slave_address;
  }
  /**
   * Getter for the address of the device
   * @return the address of the device
   */
  inline uint8_t
  get_address () const
  {
    return m_slave_address;
  }
};

#endif /* DEVICES_I2C_PARAMETER_H_ */
