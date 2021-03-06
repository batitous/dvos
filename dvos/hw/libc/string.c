
#include "../../hw/include/libs-default.h"


/*
 * Software License Agreement (BSD License)
 *
 * Based on original stdio.c released by Atmel
 * Copyright (c) 2008, Atmel Corporation
 * All rights reserved.
 *
 * Modified by Roel Verdult, Copyright (c) 2010
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor the
 * names of its contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

void * memcpy(void *pDestination, const void *pSource, UInt32 num)
{
    unsigned char *pByteDestination;
    unsigned char *pByteSource;
    unsigned int *pAlignedSource = (unsigned int *) pSource;
    unsigned int *pAlignedDestination = (unsigned int *) pDestination;

    if ((((unsigned int) pAlignedDestination & 0x3) == 0)
        && (((unsigned int) pAlignedSource & 0x3) == 0)
        && (num >= 4)) 
    {

        while (num >= 4)
        {
            *pAlignedDestination++ = *pAlignedSource++;
            num -= 4;
        }
    }

    // Copy remaining bytes
    pByteDestination = (unsigned char *) pAlignedDestination;
    pByteSource = (unsigned char *) pAlignedSource;
    while (num--) 
    {
        *pByteDestination++ = *pByteSource++;
    }

    return pDestination;
}

void * memset(void *pBuffer, int value, UInt32 num)
{
    unsigned char *pByteDestination;
    unsigned int  *pAlignedDestination = (unsigned int *) pBuffer;
    unsigned int  alignedValue = (value << 24) | (value << 16) | (value << 8) | value;

    if ((((unsigned int) pAlignedDestination & 0x3) == 0) && (num >= 4)) 
    {
        while (num >= 4)
        {
            *pAlignedDestination++ = alignedValue;
            num -= 4;
        }
    }
    
    pByteDestination = (unsigned char *) pAlignedDestination;
    while (num--)
    {
        *pByteDestination++ = value;
    }
    return pBuffer;
}

Int32 memcmp(const void *av, const void *bv, UInt32 len)
{
  const unsigned char *a = av;
  const unsigned char *b = bv;
  UInt32 i;

  for (i=0; i<len; i++) 
  {
    if (a[i] != b[i]) 
    {
      return (int)(a[i] - b[i]);
    }
  }
  return 0;
}

char * strcpy(char *dest, const char *source)
{
    char *begin = dest;

    for(; (*dest = *source) != 0; ++source, ++dest);
    
    return begin;
}


UInt32 strlen(const char *string)
{
    UInt32 length = 0;

    while(*string++ != 0)
    {
        length++;
    }
    
    return length;
}

Int32 strncmp(const Int8 *pString1, const Int8 *pString2, UInt32 count)
{
    int r;

    while(count) 
    {
        r = *pString1 - *pString2;
        if (r == 0) {
            if (*pString1 == 0)
            {
                break;
            }
            pString1++;
            pString2++;
            count--;
            continue;
        }
        return r;
    }
    return 0;
}

Int8 * strncpy(Int8 *pDestination, const Int8 *pSource, UInt32 count)
{
    char *pSaveDest = pDestination;

    while (count) 
    {
        *pDestination = *pSource;
        if (*pSource == 0) 
        {
            break;
        }
        pDestination++;
        pSource++;
        count--;
    }
    return pSaveDest;
}

// Following code is based on the BSD licensed code released by UoC 
// Copyright (c) 1988 Regents of the University of California

Int32 strcmp(const Int8 *s1, const Int8 *s2)
{
  while (*s1 == *s2++)
    if (*s1++ == 0)
      return (0);
  return (*(unsigned char *)s1 - *(unsigned char *)--s2);
}
