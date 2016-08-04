#include <gps.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdint.h>

/**
 * Timeout in microseconds for retrieving new data (set for 2 Hz as
 * double timeout is needed for updates)
 */
#define TIMEOUT 1000000
/**
 * @file
 * @brief Sub Program to set up a gpsd client to get the gps data.
 * @author Rene Kremer
 * @version 0.2
 */
int main() {
	int8_t ret, stop, counter;
	struct timeval tv;
	struct gps_data_t gps_data;
	if ((ret = gps_open("127.0.0.1", "2947", &gps_data)) == -1) {
		printf("code: %d, reason: %s\n", ret, gps_errstr(ret));
		return EXIT_FAILURE;
	}
	stop = 0;
	counter = 0;
	gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);
	while (stop != 1) {
		counter++;
		/* wait for TIMEOUT to receive data */
		if (gps_waiting(&gps_data, TIMEOUT)) {
			/* read data */
			if ((ret = gps_read(&gps_data)) == -1) {
				printf("error occured reading gps data. code: %d, reason: %s\n",
						ret, gps_errstr(ret));
			} else {
				/* Display data from the GPS receiver. */
				if ((gps_data.status == STATUS_FIX)
						&& (gps_data.fix.mode == MODE_2D
								|| gps_data.fix.mode == MODE_3D)
						&& !isnan(gps_data.fix.latitude)
						&& !isnan(gps_data.fix.longitude)) {
					gettimeofday(&tv, NULL);
					printf("Fix: %d \n", gps_data.fix.mode);
					printf("Latitude: %f \n",gps_data.fix.latitude);
					printf("Longitude: %f \n", gps_data.fix.longitude);
					printf("Speed: %f \n", gps_data.fix.speed);
					printf("Direction: %f \n", gps_data.fix.track);
					printf("Timestamp: %ld \n", tv.tv_sec);
					stop = 1;
				} else {
					printf("no GPS data available\n");
				}
			}
		}
	}

	/* When you are done... */
	gps_stream(&gps_data, WATCH_DISABLE, NULL);
	gps_close(&gps_data);

	return EXIT_SUCCESS;
}
