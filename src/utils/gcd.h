#ifndef GCD_H_
#define GCD_H_

#include <stdint.h>
#include <vector>
/**
 * @file
 * @class GCD
 * @brief Class for calculating the greatest common divisor.
 * Implements some functions to calculate a gcd out of two values and a vector of
 * values.
 * @author Rene Kremer
 * @version 0.2
 */
class GCD {
	/**
	 * @public
	 */
public:
	/**
	 * Constructor
	 */
	GCD();
	/**
	 * Function to get the gcd of two values
	 *
	 * @param a is the first value
	 * @param b is the second value
	 * @return the gcd of the first and second value
	 */
	uint16_t gcd(uint16_t a, uint16_t b);
	/**
	 * Returns the gcd of the values of the vector
	 *
	 * @param vector is the vector of values
	 * @param start is the start value of the list
	 * @param end is the max value of the list (size - 1)
	 * @return the gcd of the values of the vector
	 */
	uint16_t gcd_vector(std::vector<uint16_t> vector, uint16_t start,
			uint16_t end);
	/**
	 * Destructor
	 */
	~GCD();

};

#endif /* GCD_H_ */
