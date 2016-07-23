#ifndef GPS_DATA_H_
#define GPS_DATA_H_

#include <stdint.h>

/**
 * @file
 * @class gps_data_t
 * @brief Struct for a GPS data. Stores data from a gps update such as latitude, longitude,
 * speed and a timestamp. The timestamp is the systemtime of linux when the update
 * arrived.
 * @author Rene Kremer
 * @version 0.2
 */
struct gps_data_t
{
  //TODO: Add Fix in GPS Subprogram
  /**
   * Mode of the fix (No Fix = 0x00, 2D = 0x01, 3D = 0x02)
   */
  int32_t fix_mode;
  /**
   * latitude of the position
   */
  int32_t latitude;
  /**
   * longitude of the position
   */
  int32_t longitude;
  /**
   * speed gained from the GPS device
   */
  int32_t speed;
  /**
   * the time when the
   */
  uint32_t timestamp;
};

#endif /* GPS_DATA_H_ */
