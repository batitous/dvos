
#include "../include/libs-hardware.h"


UInt32 GetSqrt(UInt32 x)
{
   UInt32 m, y, b;

   m = 0x40000000;
   y = 0;
   while (m != 0) 
   {              // Do 16 times.
      b = y | m;
      y = y >> 1;
      if (x >= b)
      {
         x = x - b;
         y = y | m;
      }
      m = m >> 2;
   }
   
   return y;
}
