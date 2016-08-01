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
