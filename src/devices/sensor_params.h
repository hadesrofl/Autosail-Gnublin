#ifndef DEVICES_SENSOR_PARAMS_H_
#define DEVICES_SENSOR_PARAMS_H_
/**
 * @file
 * @brief Header File for some Params of the Sensors. Here are the Sensors described
 * and Params like Address, Baudrate or Read / Write Length specified.
 * @author Rene Kremer
 * @version 0.2
 */
/**
 * @class Device_ID
 * @brief Enum of an ID for a device.
 * @details
 * <ul>
 * <li> ACCELEROMETER - Internal id of the accelerometer </li>
 * <li> COMPASS - Internal id of the compass </li>
 * <li> GPS - Internal id of the gps </li>
 * <li> GYROSCOPE - Internal id of the gyroscope </li>
 * <li> HYGROMETER - Internal id of the hygrometer </li>
 * <li> WIND_SENSOR - Internal id of the windsensor  </li>
 * <li> NUM_DEVICES - Enum for the number of devices to iterate over it in loops </li>
 * </ul>
 * @author Rene Kremer
 * @version 0.2
 */
enum class Device_ID
{
  /**
   * Internal id of the accelerometer
   */
  ACCELEROMETER,
  /**
   * Internal id of the compass
   */
  COMPASS,
  /**
   * Internal id of the gps
   */
  GPS,
  /**
   * Internal id of the gyroscope
   */
  GYROSCOPE,
  /**
   * Internal id of the hygrometer
   */
  HYGROMETER,
  /**
   * Internal id of the windsensor
   */
  WIND_SENSOR,
#ifdef _TEST
  TEENSY_I2C,
#endif
  /**
   * Enum for the number of devices to iterate over it in loops
   */
  NUM_DEVICES
};

/**
 * @class Sensor_Param
 * @brief Enum for the params of the sensors
 * @details
 * <ul>
 * <li> ACC_ADDR - Address of the Accelerometer ADXL345</li>
 * <li> COMPASS_ADDR - Address of Digital Compass HMC5883L </li>
 * <li> GYRO_ADDR - Address of Gyroscope ITG-3200 </li>
 * <li> GPS_BAUD - Baudrate of GPS </li>
 * <li> HYGRO_ADDR - FILLER VALUE Address of Hygrometer </li>
 * <li> WIND_SENSOR_ADDR - FILLER VALUE: Address of WindSensor </li>
 * </ul>
 * @author Rene Kremer
 * @version 0.2
 */
enum class Sensor_Param
{
#ifdef _TEST
  TEENSY_ADDR = 0x55, 		// Teensy Slave Address for I2C
#endif
  /**
   * Address of the Accelerometer ADXL345
   */
  ACC_ADDR = 0x53,
  /**
   * Address of Digital Compass HMC5883L
   */
  COMPASS_ADDR = 0x1E,
  /**
   * Address of Gyroscope ITG-3200
   */
  GYRO_ADDR = 0x68,
  /**
   * Baudrate of GPS
   */
  GPS_BAUD = 38400,
  /**
   * FILLER VALUE Address of Hygrometer
   */
  HYGRO_ADDR = 0x00,
  /**
   * FILLER VALUE: Address of WindSensor
   */
  WIND_SENSOR_ADDR = 0x00
};

/**
 * @class Sensor_Value
 * @brief Enum for the specific values of the sensors
 * @author Rene Kremer
 * @version 0.2
 */
enum class Sensor_Value
{
  ACC_X,
  ACC_Y,
  ACC_Z,
  COMPASS_X,
  COMPASS_Y,
  COMPASS_Z,
  GYRO_X,
  GYRO_Y,
  GYRO_Z,
  GPS_X,
  GPS_Y,
  GPS_Z,
  HYGRO_X,
  HYGRO_Y,
  HYGRO_Z,
  WIND_SENSOR_X,
  WIND_SENSOR_Y,
  WIND_SENSOR_Z
};

#endif /* DEVICES_SENSOR_PARAMS_H_ */
