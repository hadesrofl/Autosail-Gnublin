#ifdef _TEST
#ifndef TEST_ASSERTER_H_
#define TEST_ASSERTER_H_

#include <vector>
/**
 * @file
 * @class Asserter
 * @brief Class for Testing Purposes. Implements some functions to assert some statements.
 * @author Rene Kremer
 * @version 0.2
 */
class Asserter
{
  /**
   * @public
   */
public:
  /**
   * Checks if two data arrays are equivalent. This is used as test for echo clients.
   * @param send_data is the data that was sent
   * @param received_data is the data that was received from the echo client
   * @param length is the length of data that was sent
   * @return true if the data is equivalent, otherwise false
   */
  bool
  assert (unsigned char* send_data, unsigned char* received_data, int length);
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
};

#endif /* TEST_ASSERTER_H_ */
#endif
