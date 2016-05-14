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
 * Enums of the Sensors
 */
enum class Device_ID
{
  ACCELEROMETER, COMPASS, GPS, GYROSCOPE, HYGROMETER, WIND_SENSOR,
#ifdef _TEST
  TEENSY_I2C,
#endif
  NUM_DEVICES
};

/**
 * Addresses of the Sensors
 */
enum class Sensor_Params
{
#ifdef _TEST
  TEENSY_ADDR = 0x55, 		// Teensy Slave Address for I2C
#endif
  ACC_ADDR = 0x53,		// Address of Accelerometer ADXL345
  ACC_READ_LENGTH = 6,		// FILLER VALUE: Length for reading a value of the Accelerometer ADXL345
  COMPASS_ADDR = 0x1E,		// Address of Digital Compass HMC5883L
  COMPASS_READ_LENGTH = 0,	// FILLER VALUE: Length for reading a value of the Compass HMC5883L
  GYRO_ADDR = 0x68,		// Address of Gyroscope ITG-3200
  GYRO_READ_LENGTH = 0,		// FILLER VALUE: Length for reading a value of the Gyroscope ITG-3200
  GPS_BAUD = 38400,		// Baudrate of GPS
  GPS_READ_LENGTH = 0,		// FILLER VALUE: Length for reading a value of the GPS
  HYGRO_ADDR = 0x00,		// FILLER VALUE Address of Hygrometer
  HYGRO_READ_LENGTH = 0,	// FILLER VALUE: Length for reading a value of the Compass HMC5883L
  WIND_SENSOR_ADDR = 0x00,	// FILLER VALUE: Address of Wind Sensor
  WIND_SENSOR_READ_LENGTH = 0	// FILLER VALUE: Length for reading a value of the Compass HMC5883L
};

enum class Sensor_Values
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
