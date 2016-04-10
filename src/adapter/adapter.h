#ifndef SRC_ADAPTER_ADAPTER_H_
#define SRC_ADAPTER_ADAPTER_H_

/**
 * @file
 * @class Adapter
 * @brief Abstract Adapter class which needs receive, send and
 * a destructor to implement for derived classes. Some Adapters need some more
 * functionality or attributes but they all have a receive or send function
 * @author Rene Kremer
 * @version 0.2
 */
class Adapter
{
  /**
   * @public
   */
public:
  /**
   * Function to receive some data via an adapter
   * @param buf is a pointer to the target buffer
   * @param length is the length of the data to be read
   * @return on success returns the length, if there is an error -1 is returned
   */
  virtual int
  receive (unsigned char* buf, int length) =0;
  /**
   * Function to receive some data via an adapter
   * @param buf is a pointer to the target buffer
   * @param length is the length of the data to be read
   * @return on success returns the length, if there is an error -1 is returned
   */
  virtual int
  send (unsigned char* buf, int length) =0;
  /**
   * Default Destructor
   */
  virtual
  ~Adapter ()
  {
  }
};

#endif /* SRC_ADAPTER_ADAPTER_H_ */
