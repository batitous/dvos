
#ifndef DVOS_KERNEL_IOSTREAM_H
#define DVOS_KERNEL_IOSTREAM_H

/** @brief Input/Output Stream object
 */
typedef struct _kernel_io_stream_
{
    KThread *       receiver;   /**< receiver thread */
    UInt8 *         buffer;     /**< input/output buffer */
    UInt16          read;       /**< read index */
    UInt16 write;      /**< write index */
    UInt16          size;       /**< buffer size */
} KIOStream;


/** @brief Create a new IO Stream object.
 *
 * @param size      Size of buffer, MUST BE 8, 16, 32, 64 etc...
 * @return A new IO Stream object.
 */
extern KIOStream * newInputOutputStream(UInt32 size);

/** @brief Write a byte to an IO Stream object.
 *
 * @param stream    IO Stream object.
 * @param data      Byte to write.
 */
extern void setByteToStream(KIOStream * stream, UInt8 data);

/** @brief Wake up a task inside an IRQ.
 *
 * @warning Call this function only in an IRQ !
 *
 * @param stream    IO Stream object.
 */
extern void irqWakeUpTaskFromStream(KIOStream * stream);

/** @brief Get bytes from an IO Stream object.
 *
 * @param stream    IO Stream object.
 * @param buffer    Buffer where write the read bytes.
 * @param len       Lenght of byte to read.
 * @param timeout   Timeout in ms.
 * @return True if all bytes are read, else False (Timeout).
 */
extern Bool getBufferFromStream(KIOStream * stream, UInt8 * buffer, UInt32 len, UInt32 timeout);

/** @brief Get all data from the IO Stream object.
 *
 * @param stream        IO Stream object.
 * @param buffer        Buffer where write the read bytes.
 * @return Lenght of data received.
 */
extern UInt32 getAllBufferFromStream(KIOStream * stream, UInt8 * buffer, UInt32 len);

/** @brief Get one byte from an IO Stream object.
 *
 * @param stream    IO Stream object.
 * @param data      Pointer to a byte where write the read's byte.
 * @return False if no byte, else True.
 */
extern Bool getByteFromStream(KIOStream * stream, UInt8 * data);

/** @brief Wait data from an IO Stream object.
 *
 * @param stream    IO Stream object.
 */
extern void waitDataFromStream(KIOStream * stream);

/** @brief Is data available from an IO Stream object ?
  * @return True if data available, else False.
  */
extern Bool isDataAvailableFromStream(KIOStream * stream);

#endif
