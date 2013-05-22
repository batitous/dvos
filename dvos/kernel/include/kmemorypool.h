
#ifndef DVOS_KERNEL_MEMORY_POOLS_H
#define DVOS_KERNEL_MEMORY_POOLS_H


// memory pool :
// - very fast
// - to be used for constant memory aera
// - BUT you can't free memory


extern void initMemoryPool(UInt8 * address, UInt32 size);

extern void * getMemoryPool(UInt32 size);


#endif
