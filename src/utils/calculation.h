#ifndef CALCULATION_H_
#define CALCULATION_H_

#include <stdint.h>
#include <vector>
/**
 * @file
 * @class Calculation
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
	static uint16_t gcd(uint16_t a, uint16_t b);
	/**
	 * Returns the gcd of the values of the vector
	 *
	 * @param vector is the vector of values
	 * @param start is the start value of the list
	 * @param end is the max value of the list (size - 1)
	 * @return the gcd of the values of the vector
	 */
	static uint16_t gcd_vector(std::vector<uint16_t> vector, uint16_t start,
			uint16_t end);

};

#endif /* CALCULATION_H_ */
