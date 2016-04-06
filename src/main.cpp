#include <iostream>

#include "../gnublin_wo_smtp.h"
#include "adapter/xbee.hpp"
using namespace std;

/**
 * @mainpage Robotic-Sailing --- Port from a microprocess to the gnublin platform
 *
 * Bachelor Thesis by Rene Kremer
 *
 */
int
main (void)
{
  char* device_file = (char*) "/dev/ttyUSB0";
  Xbee *xbee = new Xbee (device_file, 38400);
  int i = 0, max = 5, second = 1, result = 0;
  unsigned char txbuf[2] = {'T','X'};
  unsigned char rxbuf[2] = {0};
  while (i != max)
    {
      result = xbee->send (txbuf, 2);
      if (result == 2)
	{
	  cout << "Sending ok" << endl;
	  for(int k = 0; k < 2; k++){
	      cout << "Sent: " << txbuf[0] << txbuf[1] << endl;
	  }
	}
      else
	{
	  cout << "Sending failed" << endl;
	}
      result = xbee->receive (rxbuf, 2);
      if (result == 2)
	{
	  cout << "Receiving ok" << endl << "Receiving: " << rxbuf[0] << rxbuf[1] << endl;
	  i++;
	}
      else
	{
	  cout << "Receiving failed" << endl;
	}
      sleep (second * 4);
    }
  return 0;
}
