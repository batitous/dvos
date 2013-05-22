
#ifndef DVOS_KERNEL_MEMORY_H
#define DVOS_KERNEL_MEMORY_H

/** @brief Memory link object */
typedef struct _kernel_link_memory_
{
    UInt16 prev;        /**< previous block of memory */
    UInt16 next;        /**< next block of memory */
} KMemory;


/** @brief
 * 
 * @param mem
 * @param sizeInByte            Maximum value: 131068 bytes (127Kbytes)
 * @return 
 */
extern KMemory * initKernelMemory(const UInt8 * mem, UInt32 sizeInByte);

extern UInt32 getMemoryAvailable(KMemory * mem);

extern void * allocMemory(KMemory * mem, UInt32 sizeInBytes);

extern void freeMemory(KMemory * mem, UInt8 * ptr);



/** @brief Default memory object. */
extern KMemory * defaultMemory;

/** @brief Malloc */
#define malloc(size)     allocMemory(defaultMemory,size)
/** @brief Free */
#define free(ptr)       freeMemory(defaultMemory,ptr)


#endif

