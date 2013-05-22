
#ifndef LIBS_HW_LIBC_H
#define LIBS_HW_LIBC_H

#ifdef __cplusplus
extern "C" {
#endif

// libc function


extern void * memcpy(void *pDestination, const void *pSource, UInt32 size);

extern void * memset(void *pBuffer, int value, UInt32 size);

extern Int32 memcmp(const void *pBuffer1, const void *pBuffer2, UInt32 size);

extern UInt32 strlen(const Int8 *string);


/* Return 0 if equals
 *  Return >0 if 1st string > 2nd string
 *  Return <0 if 1st string < 2nd string
 */
extern Int32 strncmp(const Int8 *pString1, const Int8 *pString2, UInt32 count);

extern Int32 strcmp(const Int8 *pString1, const Int8 *pString2);


/* 
 * Copy 'count' byte of pSource into pDestination
 */
extern Int8 * strncpy(Int8 *pDestination, const Int8 *pSource, UInt32 count);

extern Int8 * strcpy(Int8 *pDestination, const Int8 *pSource);


extern signed int sprintf(char *pStr, const char *pFormat, ...);


#ifdef __cplusplus
 }
#endif

#endif