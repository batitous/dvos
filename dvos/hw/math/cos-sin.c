
#include "../include/libs-hardware.h"

// code cames from Freescale App Notes.

#define MINDELTATRIG    1	/* final step size for iTrig */

// x = opposed
// y = adjacent
Int32 iTrig(Int32 ix, Int32 iy) 
{
    UInt32 itmp; 
    UInt32 ixsq; 
    Int32 isignx; 
    UInt32 ihypsq; 
    Int32 ir; 
    Int32 idelta;

    if ((ix == 0) && (iy == 0)) 
    {
        ix = iy = 1;
    }
    
    /* check for -32768 which is not handled correctly */
    if (ix == -32768)
    {
        ix = -32767;
    }
    
    if (iy == -32768)
    {
        iy = -32767;
    }
    
    isignx = 1;
    if (ix < 0)
    {
        ix = -ix;
        isignx = -1;
    }
    
    /* for convenience in the boosting set iy to be positive as well as ix */
    if(iy<0)
    {
        iy = - iy;
    }
    
    while ((ix < 16384) && (iy < 16384))
    {
        ix = (ix + ix); 
        iy = (iy + iy);
    }
    
    /* calculate ix*ix and the hypotenuse squared */ 
    ixsq = (UInt32)(ix * ix);	
    
    /* ixsq=ix*ix: 0 to 32767^2 = 1073676289 */ 
    ihypsq = (UInt32)(ixsq + iy * iy);
    
    /* ihypsq=(ix*ix+iy*iy) 0 to 2*32767*32767=2147352578 */
    /* set result r to zero and binary search step to 16384 = 0.5 */
    ir = 0; 
    idelta = 16384;
	
    /* loop over binary sub-division algorithm */
    do
    {
        itmp = (UInt32)((ir + idelta) * (ir + idelta));
        itmp = (itmp >> 15) * (ihypsq >> 15); 
        
        if (itmp <= ixsq)
        {
            ir += idelta;
        }
        idelta = (idelta >> 1);
    
    } while (idelta >= MINDELTATRIG);	/* last loop is performed for idelta=MINDELTATRIG */
   
    
    return (Int32)(ir * isignx); 
}



IntQ15 getCosFromXY(Int16 opposed, Int16 adjacent )
{
    return iTrig(opposed , adjacent );
}

IntQ15 getSinFromXY(Int16 opposed, Int16 adjacent)
{
    return iTrig(adjacent , opposed );
}
