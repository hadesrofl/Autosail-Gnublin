#include "asserter.h"

bool
assert (FileReader& reader, char* data, int length)
{
  std::vector<char> line;
  line = reader.get_line (line);
  if(line.empty() == false){
      std::cout << "Data given for Test Case: ";
  for (int i = 0; i  < length; i++){
      std::cout << data[i];
  }
  std::cout << std::endl;
  std::cout << "Read Result from File: ";
  for (int i = 0; i < length; i++)
    {
      std::cout << line[i];
    }
  std::cout << std::endl;
  for (int i = 0; i < length; i++)
    {
      if (data[i] != line[i])
	return false;
    }
  return true;
  }else{
      return false;
  }

}

bool
check_asserts (std::vector<bool> asserts, int n_tests)
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


