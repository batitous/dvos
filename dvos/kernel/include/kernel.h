
#ifndef DVOS_KERNEL_H
#define DVOS_KERNEL_H

/** @brief Initialize kernel object.
 */
extern void initKernel(void);

/** @brief Start the kernel.
 */
extern void startKernel(void);

/** @brief Get time of kernel.
 *
 * @return Number of tick from the beginning.
 */
extern UInt32 getCurrentTimeOfKernel(void);



#ifdef KERNEL_USE_DEBUG
        extern void dumpKernel(void);
#else
#       define dumpKernel()
#endif



#endif
