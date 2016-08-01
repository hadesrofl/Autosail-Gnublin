#ifndef DEVICES_BATTERY_H_
#define DEVICES_BATTERY_H_

#include "../interfaces/spi_master_select.h"
#include "device.h"
#include "spi_parameter.h"

/**
 * Gets the current of the Battery
 */
#define IP_TAG_GET_CURRENT 0x06

/**
 * @file
 * @class Battery
 * @ingroup Devices
 * @brief Class for the battery on the actor plattform.
 * @author Rene Kremer
 * @version 0.2
 */
class Battery : virtual public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the Battery, setting the configuration for the device
   * @return 1 on success, otherwise -1
   */
  int8_t
  init ();
  /**
   * Value of the current of the Battery
   */
  int16_t m_current;
  /**
   * Value of the voltage of the Battery
   */
  int16_t m_voltage;
  /**
   * @protected
   */
protected:
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param interface_parameter are the parameters for the SPI Interface
   * @param descriptor is a pointer to the ComponentDescriptor of this device
   */
  Battery (SPIParameter *interface_parameter, ComponentDescriptor* descriptor);
  /**
   * Reads the voltage and current of the Battery and returns them in a vector.
   * Voltage and current are int16_t values.
   * @return vector of int8_t containing 4 bytes for voltage and current (each 2 byte)
   */
  std::vector<int8_t>
  read_data ();
  /**
   * Gets the current of the Battery
   * @return the current as int16_t
   */
  inline int16_t
  get_current ()
  {
    return m_current;
  }
  /**
   * Gets the voltage of the Battery
   * @return the current as int16_t
   */
  inline int16_t
  get_voltage ()
  {
    return m_voltage;
  }

  /**
   * Destructor
   */
  ~Battery ();
};

#endif /* DEVICES_BATTERY_H_ */
