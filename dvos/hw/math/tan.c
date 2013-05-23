
#include "../include/libs-hardware.h"

// code cames from Freescale App Notes.

#define  CMPA_MIN_DELTA_TRIG (short) 1 /* final step size for CMPA_trig */
#define  CMPA_MIN_DELTA_DIV  (short) 1 /* final step size for CMPA_divide */

/* function to calculate ir = iy / ix with iy <= ix, and ix, iy both > 0 */
short CMPA_divide(short iy, short ix)
{
	short itmp; /* scratch */
	short ir; /* result = iy / ix range 0., 1. returned in range 0 to 32767 */
	short idelta; /* delta on candidate result dividing each stage by factor of 2 */

	/* set result r to zero and binary search step to 16384 = 0.5 */
	ir = 0;
	idelta = 16384; /* set as 2^14 = 0.5 */

	/* to reduce quantization effects, boost ix and iy to the maximum signed 16 bit value */
	while ((ix < 16384) && (iy < 16384))
	{
		ix = (short)(ix + ix);
		iy = (short)(iy + iy);
	}

	/* loop over binary sub-division algorithm solving for ir*ix = iy */
	do
	{
		/* generate new candidate solution for ir and test if we are too high or too low */
		itmp = (short)((long) ir + (long) idelta); /* itmp=ir+delta, the candidate solution */
		itmp = (short)(((long) itmp * (long) ix) >> 15);
		
		if (itmp <= iy) 
					ir += idelta;
					
		idelta = (short)(idelta >> 1); /* divide by 2 using right shift one bit */
			
	} while (idelta >= CMPA_MIN_DELTA_DIV); /* last loop is performed for idelta=CMPA_MIN_DELTA_DIV */

	return (ir);
} 

/* coefficients of polynomial expansion for atan function */
const short K1 = (short) -14;
const short K2 = (short) 6113;
const short K3 = (short) -1584;

/* calculates 100*atan(iy/ix) range 0 to 9000 for all ix, iy positive in range 0 to 32767 */
Int16 getAtan(Int16 iy, Int16 ix)
{
	short iAngle; /* angle in degrees times 100 */
	short iRatio; /* ratio of iy / ix or vice versa */
	short iTmp; /* temporary variable */

	/* check for pathological cases */
	if ((ix == (short) 0) && (iy == (short) 0)) 
								return ((short) 0);
								
	if ((ix == (short) 0) && (iy != (short) 0)) 
								return ((short) 9000);
		
	/* check for non-pathological cases */
	if (iy <= ix)
		iRatio = CMPA_divide(iy, ix); /* return a fraction in range 0. to 32767 = 0. to 1. */
	else
		iRatio = CMPA_divide(ix, iy); /* return a fraction in range 0. to 32767 = 0. to 1. */
		
	/* polynomial approximation */
	iAngle = K1;
	iTmp = (short)(((long) K2 * (long) iRatio) >> 15);
	iAngle += iTmp;

	// iTmp = (short)((long) iRatio * (long) iRatio >> 15); // !!!!!
	iTmp = (short)(((long) iRatio * (long) iRatio) >> 15); // !!!!!

	iTmp = (short)(((long) iTmp * (long) K3) >> 15);
	iAngle += iTmp;

	/* check if above 45 degrees */
	if (iy > ix) 
				iAngle = (short)((long) 9000 - (long) iAngle);

	/* for tidiness, limit result to range 0 to 9000 equals 0.0 to 90.0 degrees */
	if (iAngle < (short) 0) 
					iAngle = (short) 0;
					
	if (iAngle > (short) 9000) 
					iAngle = (short) 9000;

	return (iAngle);
}

/* calculates 100*atan2(iy/ix)=100*atan2(iy,ix) in deg for ix, iy in range -32768 to 32767 */
Int16 getAtan2(Int16 iy, Int16 ix)
{
	short iResult; /* angle in degrees times 100 */

	/* check for -32768 which is not handled correctly */
	if (ix == (short) -32768) 
					ix = (short) -32767;
					
	if (iy == (short) -32768) 
					iy = (short) -32767;

	/* check for quadrants */
	if ((ix >= (short) 0) && (iy >= (short) 0)) /* range 0 to 90 degrees */
		iResult = getAtan(iy, ix);
		
	else if ((ix <= (short) 0) && (iy >= (short) 0)) /* range 90 to 180 degrees */
		iResult = (short)((long) 18000 - (long) getAtan(iy, (short)-ix));
		
	else if ((ix <= (short) 0) && (iy <= (short) 0)) /* range -180 to -90 degrees */
		iResult = (short)((long) -18000 + (long) getAtan((short)-iy, (short)-ix));
		
	else /* ix >=0 and iy <= 0 giving range -90 to 0 degrees */
		iResult = (short)(-getAtan((short)-iy, ix));

	return (iResult);
}
