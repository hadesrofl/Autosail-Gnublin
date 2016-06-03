#ifndef DEVICES_SERIAL_PARAMETER_H_
#define DEVICES_SERIAL_PARAMETER_H_

#define GNUBLIN_DEFAULT_SERIAL "/dev/ttyUSB0"

/**
 * @file
 * @class SerialParameter
 * @brief Class for Parameters of Serial Devices. Contains the baudrate of the Serial Interface.
 * @version 0.3
 */
class SerialParameter : virtual public InterfaceParameter
{
  /**
   * @private
   */
private:
  /**
   * Baudrate of the serial interface.
   */
  uint32_t m_baudrate;
  /**
   * @protected
   */
protected:
  /**
   * @public
   */
public:
  /**
   * Constructor for a Serial Parameter
   * @param device_file is the name of the device in linux.
   * @param baudrate is the address of the device.
   */
  SerialParameter (char* device_file, uint32_t baudrate)
  {
    m_device_file = device_file;
    m_baudrate = baudrate;
  }
  /**
   * Constructor for a Serial Parameter (called with default device file of gnublin)
   * @param baudrate is the address of the device.
   */
  SerialParameter (uint32_t baudrate)
  {
    m_device_file = (char*) GNUBLIN_DEFAULT_SERIAL;
    m_baudrate = baudrate;
  }
  /**
   * Getter for the baudraute of the serial interface
   * @return the baudrate of the serial interface
   */
  inline uint32_t
  get_baudrate () const
  {
    return m_baudrate;
  }
};

#endif /* DEVICES_SERIAL_PARAMETER_H_ */
