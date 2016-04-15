#ifndef SRC_TOOLS_FILEREADER_H_
#define SRC_TOOLS_FILEREADER_H_

#include <iostream>
#include <fstream>
#include <vector>

/**
 * @file
 * @class FileReader
 * @brief FileReader is a class to read a file consisting the following syntax per Line:
 * [Name] : [Result] e.g. First Test Case : 25
 * This File Reader is used for reading some simple configuration files or files with test
 * results for a simple test class
 * @author Rene Kremer
 * @version 0.2
 */
class FileReader
{
  /**
   * @private
   */
private:
  /**
   * Name of the file
   */
  const char* m_file_name;
  /**
   * Input file stream
   */
  std::ifstream m_input;
  /**
   * Number of the last line that was read
   */
  int m_current_line;

  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param file_name is the name of the file to be read
   */
  FileReader (const char* file_name);
  /**
   * Gets the current line
   * @param line is a vector of characters containing the value of this line
   * @return the vector of characters of the line
   */
  std::vector<char> &
  get_line (std::vector<char> &line);
  /**
   * Gets the last line that was read
   * @return the number of the current line
   */
  int
  get_current_line ();
  /**
   * Gets the name of the file
   * @return a pointer of chars containing the name of the file
   */
  const char*
  get_file_name ();
  /**
   * Destructor
   */
  ~FileReader ();

};

#endif /* SRC_TOOLS_FILEREADER_H_ */
