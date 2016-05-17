#ifndef DEVICES_ACCELEROMETER_H_
#define DEVICES_ACCELEROMETER_H_

#include "../interfaces/i2c.h"
#include "device.h"
#ifdef _DEBUG
/**
 * Speed of milli g. 1G = 9.81 m / s^2
 */
#define MG_SPEED 0.00981
#endif
/**
 * @file
 * @class Accelerometer
 * @brief Class for a Accelerometer Module . Uses a I2C Interface for communication and
 * has some specific functions for handling and transforming data.
 * @author Rene Kremer
 * @version 0.2
 */
class Accelerometer : virtual public Device
{
  /**
   * @private
   */
private:
  /**
   * Inits the accelerometer, setting the configuration for the device
   */
  int
  init ();
  /**
   * Range of g for measurement
   */
  Sensor_Param m_range;
  /**
   * Scale Factor to multiply with LSB to get G value
   */
  float m_scale_factor;
  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param device_file is the name of the file for the I2C Interface
   * @param slave_address is the address of the Accelerometer Module
   * @param range is the range for measurement of the accelerometer
   */
  Accelerometer (char* device_file, int slave_address,
		 Sensor_Param range);
  /**
   * Constructor
   * @param slave_address is the address of the Accelerometer Module
   * @param range is the range for measurement of the accelerometer
   */
  Accelerometer (int slave_address, Sensor_Param range);
  /**
   * Reads the Data X, Y and Z Register of the Accelerometer and returns them as a
   * pointer with allocated memory. The raw values will be transformed to mg where index
   * 0 and 1 are for the x-axis, 2 and 3 for y-axis, 4 and 5 for z-axis.
   *
   * Equal index contains the msb, odd index lsb of the axis.
   *
   * Can be combined to a 2 byte value with: int16_t tsb_x = (data[0] << 8) | data[1];
   * @return pointer with axis values in mg as stated above.
   */
  unsigned char*
  read_data ();
  /**
   * Destructor
   */
  ~Accelerometer ();
};

#endif /* DEVICES_ACCELEROMETER_H_ */
