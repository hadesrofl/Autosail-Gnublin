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

#ifndef UTILS_MEDIAN_FILTER_H_
#define UTILS_MEDIAN_FILTER_H_

#include "filter.h"
/**
 * @file
 * @class MedianFilter
 * @ingroup Utils
 * XXX NOT SUPPORTED YET
 * @brief Class for a MedianFilter. Filters Values via median calculation.
 * @note Idea for Filters mentioned in Bachelor Thesis "Entwurf, Implementierung
 * und Test eines Autopiloten für die Steuerung eines Modellsegelbootes
 * mit einem Android-Smartphone" by Hannes Range (October 2015)
 * @author Rene Kremer
 * @version 0.2
 */
class MedianFilter : virtual public Filter
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
   * @public
   */
public:
  /**
   * Constructor
   */
  MedianFilter();
  /**
   * Destructor
   */
  ~MedianFilter();
};



#endif /* UTILS_MEDIAN_FILTER_H_ */
