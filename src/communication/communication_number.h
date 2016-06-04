#ifndef COMMUNICATION_COMMUNICATION_NUMBER_H_
#define COMMUNICATION_COMMUNICATION_NUMBER_H_

/**
 * @file
 * @class CommunicationNumber
 * @brief Enums for the communication numbers of the components.
 * @details
 * <ul>
 * <li> ACCELEROMETER ( = 0) - Descriptor of the accelerometer </li>
 * <li> NUM_COMMUNICATION ( = 6) - Enum for the number of communication numbers to iterate over it in loops </li>
 * </ul>
 * @author Rene Kremer
 * @version 0.3
 */
/**
 *
 */
enum class CommunicationNumber
{
  GPS, HYGROMETER, NUM_COMMUNICATION
};

#endif /* COMMUNICATION_COMMUNICATION_NUMBER_H_ */
