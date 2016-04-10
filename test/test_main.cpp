#include "test_file_reader.h"
#include "../src/adapter/xbee.h"
#include <vector>

int
xbee_test (char* file_name)
{
  TestFileReader* reader = new TestFileReader (file_name);
  std::cout << "Reader Allocated" << std::endl;
  std::vector<bool> asserts;
  int n_tests = 6;
  bool passed = false;
  asserts.push_back (reader->assert ((char*) "TX", 2));
  asserts.push_back (reader->assert ((char*) "AB", 2));
  asserts.push_back (reader->assert ((char*) "TX", 2));
  asserts.push_back (reader->assert ((char*) "AB", 2));
  asserts.push_back (reader->assert ((char*) "ER", 2));
  asserts.push_back (reader->assert ((char*) "TZ", 2));
  passed = reader->check_asserts (asserts, n_tests);
  delete reader;
  if (passed == true)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

void
xbee_real_test ()
{
  char* device_file = (char*) "/dev/ttyUSB0";
  Xbee *xbee = new Xbee (device_file, 38400);
  int i = 0, max = 5, second = 1, result = 0;
  unsigned char txbuf[2] =
    { 'T', 'X' };
  unsigned char rxbuf[2] =
    { 0 };
  while (i != max)
    {
      result = xbee->send (txbuf, 2);
      if (result == 2)
	{
	  std::cout << "Sending ok" << std::endl;
	  for (int k = 0; k < 2; k++)
	    {
	      std::cout << "Sent: " << txbuf[0] << txbuf[1] << std::endl;
	    }
	}
      else
	{
	  std::cout << "Sending failed" << std::endl;
	}
      result = xbee->receive (rxbuf, 2);
      if (result == 2)
	{
	  std::cout << "Receiving ok" << std::endl << "Receiving: " << rxbuf[0]
	      << rxbuf[1] << std::endl;
	  i++;
	}
      else
	{
	  std::cout << "Receiving failed" << std::endl;
	}
      sleep (second * 4);
    }
}

int
main (void)
{
  xbee_test ((char*) "testFiles/xbee_test.txt");
  return 0;
}

