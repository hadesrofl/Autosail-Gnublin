/**
 * Copyright 2016 Rene Kremer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
