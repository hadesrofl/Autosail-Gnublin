#ifndef SRC_ASSERTER_H_
#define SRC_ASSERTER_H_

#include "../src/tools/file_reader.h"
/**
 * @file
 * Simple Methods to assert some statement or check if all asserts passed
 * @author Rene Kremer
 * @version 0.2
 */
/**
 * Asserts if the given data is the same as the excepted result as defined in
 * the test file
 * @param data is a pointer to characters which shall be the result of a test
 * @param length is the length of characters of data
 * @return true if the assert passes, otherwise false
 */
bool
assert (FileReader& reader, char* data, int length);
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

#endif /* SRC_ASSERTER_H_ */
