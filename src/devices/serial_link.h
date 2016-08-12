#ifndef DEVICES_SERIAL_LINK_H_
#define DEVICES_SERIAL_LINK_H_

#include "../interfaces/spi_master_select.h"
#include "device.h"
#include "spi_parameter.h"

#ifdef _TEST
#include "i2c_parameter.h"
#include "../interfaces/i2c.h"
#endif
/**
 * Tag for the forward frame command of the intra protocol
 */
#define FORWARD_FRAME_TAG 0x07

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
  SerialLink (SPIParameter *interface_parameter,
	      ComponentDescriptor* descriptor);
#ifdef _TEST
  /**
   * Constructor
   * @param interface_parameter are the parameters of the I2C Interface
   * @param descriptor is a pointer to the ComponentDescriptor of this device
   */
  SerialLink (I2CParameter *interface_parameter,
	      ComponentDescriptor* descriptor);
#endif
  /**
   * Reads a frame from the SPI.
   * @return a list of bytes containing the data from the frame
   */
  std::vector<int8_t>
  read_data ();
  /**
   * Sends a Frame via SPI. Wraps the Frame with an intra protocol frame
   * used on the boat as intercommunication protocol
   * @param buf is the array of bytes to send
   * @param length is the length of data
   */
  void
  send_frame (uint8_t* buf, uint8_t length);

  /**
   * Destructor
   */
  ~SerialLink ();

};

#endif /* DEVICES_SERIAL_LINK_H_ */
