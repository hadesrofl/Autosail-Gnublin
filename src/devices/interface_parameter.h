#ifndef DEVICES_INTERFACE_PARAMETER_H_
#define DEVICES_INTERFACE_PARAMETER_H_

/**
 * @file
 * @class InterfaceParameter
 * @brief Class for Parameters of the Interfaces the Devices use. Parameters might be needed values for the used interfaces.
 * @author Rene Kremer
 * @version 0.3
 */
class InterfaceParameter
{
  /**
   * @protected
   */
protected:
  /**
   * Name of the device file
   */
  char* m_device_file;
  /**
   * @public
   */
public:
  /**
   * Getter for the name of the device file
   * @return the name of the device file
   */
  inline char*
  get_device_file () const
  {
    return m_device_file;
  }
};

#endif /* DEVICES_INTERFACE_PARAMETER_H_ */
