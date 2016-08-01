#ifndef DEVICES_DEVICE_CONFIG_H_
#define DEVICES_DEVICE_CONFIG_H_
/**
 * @file
 * @enum mapper::DeviceConfig
 * @ingroup Enums
 * @brief Enum for the params of the devices
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
  ACC_RANGE_2G = 0x01,
  /**
   * Measurement Range for +- 4G
   */
  ACC_RANGE_4G = 0x02,
  /**
   * Measurement Range for +- 8G
   */
  ACC_RANGE_8G = 0x03,
  /**
   * Measurement Range for +- 16G
   */
  ACC_RANGE_16G = 0x04,
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
  COMPASS_GAIN_0_8_8_GA = 0x01,
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
   * Serial Baudrate of 4800
   */
  SERIAL_B4800 = 0x01,
  /**
   * Serial Baudrate of 9600
   */
  SERIAL_B9600 = 0x02,
  /**
   * Serial Baudrate of 19200
   */
  SERIAL_B19200 = 0x03,
  /**
   * Serial Baudrate of 38400
   */
  SERIAL_B38400 = 0x04,
  /**
   * Serial Baudrate of 38400
   */
  SERIAL_B57600 = 0x05,
  /**
   * Serial Baudrate of 38400
   */
  SERIAL_B115200 = 0x06,
  /**
   * Speed of SPI of 1Mhz
   */
  SPI_SPEED_1MHZ = 0x01,
  /**
   * FILLER VALUE Address of Hygrometer
   */
  HYGRO_ADDR = 0x00,
  /**
   * Address of the WindVane
   */
  WIND_VANE_ADDRESS = 0x44,
  /**
   * Length of read data from WindVane
   */
  WIND_VANE_DATA_LENGTH = 0x02,
  /**
   * Address of the Anemometer
   */
  ANEMOMETER_ADDRESS = 0x45,
  /**
   * Length of read data from Anemometer
   */
  ANEMOMETER_DATA_LENGTH = 0x02,
  /**
   * FILLER VALUE Address of WestonAnemometer
   */
  WESTON_ANEMOMETER_ADDRESS = 0x00,
  /**
   * FILLER VALUE Data Length of WestonAnemometer
   */
  WESTON_ANEMOMETER_DATA_LENGTH = 0x00,

  NUM_CONFIGS =
#ifdef _TEST
  33
#endif
#ifndef _TEST
32
#endif
};

#endif /* DEVICES_DEVICE_CONFIG_H_ */
