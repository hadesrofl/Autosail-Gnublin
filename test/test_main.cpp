#include "../src/tools/file_reader.h"
#include "../src/interfaces/serial.h"
#include "asserter.h"
#include <vector>
#include <memory>

int
xbee_test (char* file_name)
{
  std::unique_ptr<FileReader> reader (new FileReader(file_name));
  std::cout << "Reader Allocated" << std::endl;
  std::vector<bool> asserts;
  int n_tests = 6;
  bool passed = false;
  asserts.push_back (assert (*reader, (char*) "TX", 2));
  asserts.push_back (assert (*reader, (char*) "AB", 2));
  asserts.push_back (assert (*reader, (char*) "TX", 2));
  asserts.push_back (assert (*reader, (char*) "AB", 2));
  asserts.push_back (assert (*reader, (char*) "ER", 2));
  asserts.push_back (assert (*reader, (char*) "TZ", 2));
  passed = check_asserts (asserts, n_tests);
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
  Serial *xbee = new Serial (device_file, 38400);
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

