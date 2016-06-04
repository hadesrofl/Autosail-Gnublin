#ifndef UTILS_AVERAGE_FILTER_H_
#define UTILS_AVERAGE_FILTER_H_

#include "filter.h"
/**
 * @file
 * @class AverageFilter
 * @brief Class for a AverageFilter. Filters Values via average calculation.
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
