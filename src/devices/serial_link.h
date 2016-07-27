#ifndef DEVICES_SERIAL_LINK_H_
#define DEVICES_SERIAL_LINK_H_

#include "../interfaces/spi_master_select.h"
#include "device.h"
#include "spi_parameter.h"

/**
 * @file
 * @class SerialLink
 * @ingroup Devices
 * @brief Class for a SerialLink module. Uses a SPIMasterSelect Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.3
 */
class SerialLink : virtual public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the SerialLink, setting the configuration for the device
   * @return 1 on success, otherwise -1
   */
  int8_t
  init ();
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param interface_parameter are the parameters of the SPI Interface
   * @param descriptor is a pointer to the ComponentDescriptor of this device
   */
  SerialLink (SPIParameter *interface_parameter, ComponentDescriptor* descriptor);
  /**
   * TODO: Comment with SerialLink specific register
   * Reads the Data X, Y and Z Register of the SerialLink and returns them as a
   * pointer with allocated memory.
   */
  std::vector<int8_t> read_data();
  /**
   * Destructor
   */
  ~SerialLink ();

};



#endif /* DEVICES_SERIAL_LINK_H_ */
