#ifndef SRC_ADAPTER_XBEE_H_
#define SRC_ADAPTER_XBEE_H_

#include "../../gnublin_wo_smtp.h"
#include <iostream>
#include "adapter.h"

/**
 * @file
 * @class Xbee
 * @brief Adapter Class for the Xbee Module to set up a Xbee Module and provide
 * a send and receive function
 * @author Rene Kremer
 * @version 0.2
 */
class Xbee : public Adapter
{
/**
 * Private Functions
 */
private:
  /**
   * Name of the device file
   */
  const char* device_file;
  /**
   * Value of the baudrate
   */
  int baudrate;
  /**
   * @param device_file is the name of the file the device is listening to
   */
  /**
   * Serial Port of the xbee module
   */
  gnublin_serial *xbee_port;
  void
  set_device_file (char* device_file);
  /**
   * @param baudrate is the value of the baudrate
   */
  void
  set_baudrate (int baudrate);
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param device_file is the name of the file the device is listening to
   * @param baudrate is the value of the baudrate
   * @return a new Xbee Module
   */
  Xbee (char* device_file, int baudrate);
  /**
   * Function to receive data
   * @param buf is a pointer to a buffer to write to data into
   * @param length is the length of the data which shall be received
   * @return on success the length of the data, if there was an error -1 is returned
   */
  int
  receive (unsigned char* buf, int length);
  /**
   * @param buf is a pointer to a buffer with the data to be sent
   * @param length is the length of the data that shall be sent
   * @return on success the length of the data, if there was an error -1 is returned
   */
  int
  send (unsigned char* buf, int length);
  /**
   * Destructor
   */
  ~Xbee ();
};

#endif /* SRC_ADAPTER_XBEE_H_ */
