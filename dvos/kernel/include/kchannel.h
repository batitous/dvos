/*
	Dvos - Copyright © 2013 Baptiste Burles, Christophe Casson, Sylvain Fay-Chatelard

    This file is part of Dvos.

    Dvos is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    Dvos is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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
