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

#ifndef UTILS_FILTER_H_
#define UTILS_FILTER_H_

#include <stdint.h>
#include <vector>
/**
 * @file
 * @class Filter
 * @ingroup Utils
 * XXX NOT SUPPORTED YET
 * @brief Virtual Class for Filter class (MedianFilter and AverageFilter).
 * @note Idea for Filters mentioned in Bachelor Thesis "Entwurf, Implementierung
 * und Test eines Autopiloten für die Steuerung eines Modellsegelbootes
 * mit einem Android-Smartphone" by Hannes Range (October 2015)
 * @author Rene Kremer
 * @version 0.2
 */
class Filter
{
  /**
   * @private
   */
private:
  /**
   * @protected
   */
protected:
  /**
   * Vector for the values that shall be filtered.
   */
  std::vector<int16_t> values;
  /**
   * @public
   */
public:
  Filter ()
  {
  }
  /**
   * Virtual Function to add a value to the filter
   */
  virtual void
  add_value (int16_t value) = 0;
  /**
   * Returns the filtered value of all values
   * @return the filtered value
   */
  virtual int16_t
  get_filtered_value () = 0;
  /**
   * Destructor
   */
  virtual ~Filter ()
  {
    values.clear ();
  }

};

#endif /* UTILS_FILTER_H_ */
