#include "test_file_reader.h"

std::vector<char> &
TestFileReader::get_line (std::vector<char> &line)
{
  int length = 20, ignore = 30;
  char* temp = new char[length] ();
  m_input.open (m_file_name);
  if (m_input.is_open () == true)
    {
      //get to current line and skip all before
      for (int i = 0; i < m_current_line; i++)
	{
	  m_input.ignore (ignore, '\n');
	}
      //ignore name of result
      m_input.ignore (ignore, ':');
      m_input.getline (temp, '\n');
      for (int i = 0; i < length; i++)
	{
	  if (!(isspace (temp[i])) && temp[i] != 0)
	    {
	      line.push_back (temp[i]);

	    }
	}
      m_current_line++;
      m_input.close ();
    }
  else
    {
      std::cout << "Error while opening file!" << std::endl;
    }

  return line;
}

TestFileReader::TestFileReader (char* file_name)
{
  m_current_line = 0;
  m_file_name = file_name;
}

bool
TestFileReader::assert (char* data, int length)
{
  std::vector<char> line;
  line = get_line (line);
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
}

bool
TestFileReader::check_asserts (std::vector<bool> asserts, int n_tests)
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
int
TestFileReader::get_current_line ()
{
  return m_current_line;
}
char*
TestFileReader::get_file_name ()
{
  return m_file_name;
}
TestFileReader::~TestFileReader ()
{

}
