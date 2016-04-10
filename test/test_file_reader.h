#ifndef SRC_TEST_TESTFILEREADER_H_
#define SRC_TEST_TESTFILEREADER_H_

#include <iostream>
#include <fstream>
#include <vector>

/**
 * @file
 * @class TestFileReader
 * @brief TestFileReader is a class to read a file with results of tests to check a
 * unit test of a module against the test results in a file
 * @author Rene Kremer
 * @version 0.2
 */
class TestFileReader
{
  /**
   * @private
   */
private:
  /**
   * Name of the file containing the test results
   */
  char* m_file_name;
  /**
   * Input file stream
   */
  std::ifstream m_input;
  /**
   * Number of the last line that was read
   */
  int m_current_line;
  /**
   * Gets the current line
   * @param line is a vector of characters containing the test results as single
   * characters
   * @return the vector of characters of the results
   */
  std::vector<char> &
  get_line (std::vector<char> &line);

  /**
   * @public
   */
public:
  /**
   * Constructor
   * @param file_name is the name of the file containing the test results
   */
  TestFileReader (char* file_name);
  /**
   * Asserts if the given data is the same as the excepted result as defined in
   * the test file
   * @param data is a pointer to characters which shall be the result of a test
   * @param length is the length of characters of data
   * @return true if the assert passes, otherwise false
   */
  bool
  assert (char* data, int length);
  /**
   * Checks if all asserts passed and write to the standard output a message
   * which assert failed or if all passed.
   * @param asserts is a vector of bools which contain the single assert results
   * of the tests
   * @param n_tests is the number of test cases
   * @return true if all asserts passed, otherwise false
   */
  bool
  check_asserts (std::vector<bool> asserts, int n_tests);
  /**
   * Gets the last line that was read
   * @return the number of the current line
   */
  int
  get_current_line ();
  /**
   * Gets the name of the file containing the results of the tests
   * @return a pointer of chars containing the name of the file
   */
  char*
  get_file_name ();
  /**
   * Destructor
   */
  ~TestFileReader ();

};

#endif /* SRC_TEST_TESTFILEREADER_H_ */
