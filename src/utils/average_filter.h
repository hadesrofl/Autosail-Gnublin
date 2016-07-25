#ifndef UTILS_AVERAGE_FILTER_H_
#define UTILS_AVERAGE_FILTER_H_

#include "filter.h"
/**
 * @file
 * @class AverageFilter
 * @ingroup Utils
 * @brief Class for a AverageFilter. Filters Values via average calculation.
 * @note Idea for Filters mentioned in Bachelor Thesis "Entwurf, Implementierung
 * und Test eines Autopiloten für die Steuerung eines Modellsegelbootes
 * mit einem Android-Smartphone" by Hannes Range (October 2015)
 * @author Rene Kremer
 * @version 0.2
 */
class AverageFilter : virtual public Filter
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
  AverageFilter();
  /**
   * Destructor
   */
  ~AverageFilter();
};



#endif /* UTILS_AVERAGE_FILTER_H_ */
