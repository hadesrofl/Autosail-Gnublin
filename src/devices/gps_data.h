#ifndef GPS_DATA_H_
#define GPS_DATA_H_

struct gps_data_t{
	float latitude;
	float longitude;
	float speed;
	timeval timestamp;
};



#endif /* GPS_DATA_H_ */
