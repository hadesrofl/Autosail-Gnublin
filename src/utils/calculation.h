#ifndef CALCULATION_H_
#define CALCULATION_H_

#include <stdint.h>
#include <vector>
/**
 * @file
 * @class Calculation
 * @ingroup Utils
 * @brief Class for Calculations.
 * Provides static functions to calculate e.g. the gcd (greatest common divisor)
 * @author Rene Kremer
 * @version 0.2
 */
class Calculation {
	/**
	 * @public
	 */
public:
	/**
	 * Function to get the gcd of two values
	 *
	 * @param a is the first value
	 * @param b is the second value
	 * @return the gcd of the first and second value
	 */
	static uint32_t gcd(uint32_t a, uint32_t b);
	/**
	 * Returns the gcd of the values of the vector
	 *
	 * @param vector is the vector of values
	 * @param start is the start value of the list
	 * @param end is the max value of the list (size - 1)
	 * @return the gcd of the values of the vector
	 */
	static uint32_t gcd_vector(std::vector<uint32_t> vector, uint32_t start,
			uint32_t end);

};

#endif /* CALCULATION_H_ */
