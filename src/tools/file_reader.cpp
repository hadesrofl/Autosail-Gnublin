#include "file_reader.h"

std::vector<char> &
FileReader::get_line (std::vector<char> &line)
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

FileReader::FileReader (const char* file_name)
{
  m_current_line = 0;
  m_file_name = file_name;
}
int
FileReader::get_current_line ()
{
  return m_current_line;
}
const char*
FileReader::get_file_name ()
{
  return m_file_name;
}
FileReader::~FileReader ()
{

}
