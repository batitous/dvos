
#ifndef DVOS_KERNEL_CHANNEL_H
#define DVOS_KERNEL_CHANNEL_H


/** @brief A channel object can be used to communicate between 2 threads
 *  whitout using synchronization or global variables.
 */
typedef struct _kernel_channel_
{
    KThread *       receiver;   /**< the receiver's thread */
    UInt32          message;    /**< the message */
    UInt8           empty;      /**< channel empty or not ? */
} KChannel;


/** @brief Create a new channel object.
 *
 * @return A new channel object.
 */
extern KChannel * newChannel(void);

/** @brief Send a message to a channel object.
 *
 * @param channel   A correct channel object.
 * @param message   A message.
 */
extern void sendMessageToChannel(KChannel * channel, UInt32 message);

/** @brief Wait a message from a channel object.
 *
 * @param channel       A correct channel object.
 * @return Message.
 */
extern UInt32 waitMessageFromChannel(KChannel * channel);

#endif
