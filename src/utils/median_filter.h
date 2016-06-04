#ifndef UTILS_MEDIAN_FILTER_H_
#define UTILS_MEDIAN_FILTER_H_

#include "filter.h"
/**
 * @file
 * @class MedianFilter
 * @brief Class for a MedianFilter. Filters Values via median calculation.
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
