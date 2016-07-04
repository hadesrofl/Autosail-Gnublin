#ifndef DEVICES_DEVICE_CONFIG_H_
#define DEVICES_DEVICE_CONFIG_H_
/**
 * @file
 * @class DeviceConfig
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
enum class DeviceConfig
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
  /**
   * Measurement Range for +- 2G
   */
  ACC_RANGE_2G = 0x00,
  /**
   * Measurement Range for +- 4G
   */
  ACC_RANGE_4G = 0x01,
  /**
   * Measurement Range for +- 8G
   */
  ACC_RANGE_8G = 0x02,
  /**
   * Measurement Range for +- 16G
   */
  ACC_RANGE_16G = 0x03,
  /**
   * Address of Digital Compass HMC5883L
   */
  COMPASS_ADDR = 0x1E,
  /**
   * Length of byte to read to get sensor data of the compass
   */
  COMPASS_DATA_LENGTH = 6,
  /**
   * Gain of Compass (+- 0.88 Ga)
   */
  COMPASS_GAIN_0_8_8_GA = 0x00,
  /**
   * Default Value for Gain of Compass (+- 1.3 Ga)
   */
  COMPASS_GAIN_1_3_GA = 0x20,
  /**
   * Gain of Compass (+- 1.9 Ga)
   */
  COMPASS_GAIN_1_9_GA = 0x40,
  /**
   * Gain of Compass (+- 2.5 Ga)
   */
  COMPASS_GAIN_2_5_GA = 0x60,
  /**
   * Gain of Compass (+- 4.0 Ga)
   */
  COMPASS_GAIN_4_GA = 0x80,
  /**
   * Gain of Compass (+- 4.7 Ga)
   */
  COMPASS_GAIN_4_7_GA = 0xA0,
  /**
   * Gain of Compass (+- 5.6 Ga)
   */
  COMPASS_GAIN_5_6_GA = 0xC0,
  /**
   * Gain of Compass (+- 8.1 Ga)
   */
  COMPASS_GAIN_8_1_GA = 0xE0,
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

#endif /* DEVICES_DEVICE_CONFIG_H_ */
