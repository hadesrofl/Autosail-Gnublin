#ifndef SRC_INTERFACES_SERIAL_H_
#define SRC_INTERFACES_SERIAL_H_

#include "../../gnublin_wo_smtp.h"
#include <iostream>

#include "interface.h"

/**
 * @file
 * @class Serial
 * @brief Interface Class to set up a Serial Device and provide
 * a send and receive function
 * @author Rene Kremer
 * @version 0.2
 */
class Serial : public Interface
{
  /**
   * @private
   */
private:
  /**
   * Name of the device file
   */
  //const char* m_device_file;
  /**
   * Value of the baudrate
   */
  int m_baudrate;
  /**
   * @param device_file is the name of the file the device is listening to
   */
  /**
   * Serial Port of the xbee module
   */
  gnublin_serial* m_serial_port;

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
   */
  Serial (char* device_file, int baudrate);
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
  ~Serial ();
};

#endif /* SRC_INTERFACES_SERIAL_H_ */
