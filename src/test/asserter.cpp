#ifdef _TEST
#include "asserter.h"

bool
Asserter::assert (unsigned char* send_data, unsigned char* received_data, int length)
{
  bool assert = true;
  for (int i = 0; i < length; i++)
    {
      if (send_data[i] != received_data[i])
	{
	  assert = false;
	}
    }
  return assert;
}

bool
Asserter::check_asserts (std::vector<bool> asserts, int n_tests)
{
  int passed_asserts = 0;
  for (int i = 0; i < n_tests; i++)
    {
      if (asserts[i] == false)
	{
	  std::cout << "Assert " << i << " failed!" << std::endl;
	}
      else
	{
	  passed_asserts++;
	}
    }
  if (passed_asserts == n_tests)
    {
      std::cout << "All asserts passed!" << std::endl;
      return true;
    }
  else
    {
      return false;
    }
}
#endif
