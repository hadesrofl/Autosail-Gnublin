#ifndef DEVICES_DEVICE_PARAMS_H_
#define DEVICES_DEVICE_PARAMS_H_
/**
 * @file
 * @class Device Config
 * @brief Enum for the params of the devices
 * @details
 * <ul>
 * <li> ACC_ADDR - Address of the Accelerometer ADXL345</li>
 * <li> ACC_DATA_LENGTH - Length of byte to read to get sensor data of the accelerometer</li>
 * <li> COMPASS_ADDR - Address of Digital Compass HMC5883L </li>
 * <li> COMPASS_DATA_LENGTH - Length of byte to read to get sensor data of the compass</li>
 * <li> COMPASS_GAIN_DEFAULT - Default Value of the Gain Range for the Compass </li>
 * <li> GYRO_ADDR - Address of Gyroscope ITG-3200 </li>
 * <li> GPS_BAUD - Baudrate of GPS </li>
 * <li> HYGRO_ADDR - FILLER VALUE Address of Hygrometer </li>
 * <li> WIND_SENSOR_ADDR - FILLER VALUE: Address of WindSensor </li>
 * </ul>
 * @author Rene Kremer
 * @version 0.3
 */
enum class Device_Config
{
#ifdef _TEST
  TEENSY_ADDR = 0x55, 		// Teensy Slave Address for I2C
#endif
  /**
   * Address of the Accelerometer ADXL345
   */
  ACC_ADDR = 0x53,
  /**
   * Length of byte to read to get sensor data of the accelerometer
   */
  ACC_DATA_LENGTH = 6,
  ACC_RANGE_2G = 2,
  ACC_RANGE_4G = 4,
  ACC_RANGE_8G = 8,
  ACC_RANGE_16G = 16,
  /**
   * Address of Digital Compass HMC5883L
   */
  COMPASS_ADDR = 0x1E,
  /**
   * Length of byte to read to get sensor data of the compass
   */
  COMPASS_DATA_LENGTH = 6,
  /**
   * Defaul Value for Gain of Compass
   */
  COMPASS_GAIN_DEFAULT = 0x40,
  /**
   * Address of Gyroscope ITG-3200
   */
  GYRO_ADDR = 0x68,
  /**
   * Length of byte to read to get sensor data of the gyroscope
   */
  GYROSCOPE_DATA_LENGTH = 6,
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

#endif /* DEVICES_DEVICE_PARAMS_H_ */
