/* ----------------------------------------------------------------------   
* Copyright (C) 2010 ARM Limited. All rights reserved.   
*   
* $Date:        15. July 2011  
* $Revision: 	V1.0.10  
*   
* Project: 	    CMSIS DSP Library 
*  ---------------------------------------------------------------------- 
*/
#include "../include/libs-hardware.h"


static const Int16 arrayCosQ15 [259] = { 
    0x7ff6, 0x7fff, 0x7ff6, 0x7fd9, 0x7fa7, 0x7f62, 0x7f0a, 0x7e9d, 
    0x7e1e, 0x7d8a, 0x7ce4, 0x7c2a, 0x7b5d, 0x7a7d, 0x798a, 0x7885, 
    0x776c, 0x7642, 0x7505, 0x73b6, 0x7255, 0x70e3, 0x6f5f, 0x6dca, 
    0x6c24, 0x6a6e, 0x68a7, 0x66d0, 0x64e9, 0x62f2, 0x60ec, 0x5ed7, 
    0x5cb4, 0x5a82, 0x5843, 0x55f6, 0x539b, 0x5134, 0x4ec0, 0x4c40, 
    0x49b4, 0x471d, 0x447b, 0x41ce, 0x3f17, 0x3c57, 0x398d, 0x36ba, 
    0x33df, 0x30fc, 0x2e11, 0x2b1f, 0x2827, 0x2528, 0x2224, 0x1f1a, 
    0x1c0c, 0x18f9, 0x15e2, 0x12c8, 0xfab, 0xc8c, 0x96b, 0x648, 
    0x324, 0x0, 0xfcdc, 0xf9b8, 0xf695, 0xf374, 0xf055, 0xed38, 
    0xea1e, 0xe707, 0xe3f4, 0xe0e6, 0xdddc, 0xdad8, 0xd7d9, 0xd4e1, 
    0xd1ef, 0xcf04, 0xcc21, 0xc946, 0xc673, 0xc3a9, 0xc0e9, 0xbe32, 
    0xbb85, 0xb8e3, 0xb64c, 0xb3c0, 0xb140, 0xaecc, 0xac65, 0xaa0a, 
    0xa7bd, 0xa57e, 0xa34c, 0xa129, 0x9f14, 0x9d0e, 0x9b17, 0x9930, 
    0x9759, 0x9592, 0x93dc, 0x9236, 0x90a1, 0x8f1d, 0x8dab, 0x8c4a, 
    0x8afb, 0x89be, 0x8894, 0x877b, 0x8676, 0x8583, 0x84a3, 0x83d6, 
    0x831c, 0x8276, 0x81e2, 0x8163, 0x80f6, 0x809e, 0x8059, 0x8027, 
    0x800a, 0x8000, 0x800a, 0x8027, 0x8059, 0x809e, 0x80f6, 0x8163, 
    0x81e2, 0x8276, 0x831c, 0x83d6, 0x84a3, 0x8583, 0x8676, 0x877b, 
    0x8894, 0x89be, 0x8afb, 0x8c4a, 0x8dab, 0x8f1d, 0x90a1, 0x9236, 
    0x93dc, 0x9592, 0x9759, 0x9930, 0x9b17, 0x9d0e, 0x9f14, 0xa129, 
    0xa34c, 0xa57e, 0xa7bd, 0xaa0a, 0xac65, 0xaecc, 0xb140, 0xb3c0, 
    0xb64c, 0xb8e3, 0xbb85, 0xbe32, 0xc0e9, 0xc3a9, 0xc673, 0xc946, 
    0xcc21, 0xcf04, 0xd1ef, 0xd4e1, 0xd7d9, 0xdad8, 0xdddc, 0xe0e6, 
    0xe3f4, 0xe707, 0xea1e, 0xed38, 0xf055, 0xf374, 0xf695, 0xf9b8, 
    0xfcdc, 0x0, 0x324, 0x648, 0x96b, 0xc8c, 0xfab, 0x12c8, 
    0x15e2, 0x18f9, 0x1c0c, 0x1f1a, 0x2224, 0x2528, 0x2827, 0x2b1f, 
    0x2e11, 0x30fc, 0x33df, 0x36ba, 0x398d, 0x3c57, 0x3f17, 0x41ce, 
    0x447b, 0x471d, 0x49b4, 0x4c40, 0x4ec0, 0x5134, 0x539b, 0x55f6, 
    0x5843, 0x5a82, 0x5cb4, 0x5ed7, 0x60ec, 0x62f2, 0x64e9, 0x66d0, 
    0x68a7, 0x6a6e, 0x6c24, 0x6dca, 0x6f5f, 0x70e3, 0x7255, 0x73b6, 
    0x7505, 0x7642, 0x776c, 0x7885, 0x798a, 0x7a7d, 0x7b5d, 0x7c2a, 
    0x7ce4, 0x7d8a, 0x7e1e, 0x7e9d, 0x7f0a, 0x7f62, 0x7fa7, 0x7fd9, 
    0x7ff6, 0x7fff, 0x7ff6 
}; 



IntQ15 getCosFromRadianQ15(RadianQ15 x) 
{ 
    Int32 cosVal;                                  /* Temporary variables output */ 
    Int16 *tablePtr;                               /* Pointer to table */ 
    Int16 fract, in, in2;                          /* Temporary variables for input, output */ 
    Int32 wa, wb, wc, wd;                          /* Cubic interpolation coefficients */ 
    Int16 a, b, c, d;                              /* Four nearest output values */ 
    Int16 fractCube, fractSquare;                  /* Temporary values for fractional value */ 
    Int16 oneBy6 = 0x1555;                         /* Fixed point value of 1/6 */ 
    Int16 tableSpacing = TABLE_SPACING_Q15;        /* Table spacing */ 
    Int32 index;                                 /* Index variable */ 
    
    in = x; 
    
    /* Calculate the nearest index */ 
    index = (Int32) in / tableSpacing; 
    
    /* Calculate the nearest value of input */ 
    in2 = (Int16) index *tableSpacing; 
    
    /* Calculation of fractional value */ 
    fract = (in - in2) << 8; 
    
    /* fractSquare = fract * fract */ 
    fractSquare = (Int16) ((fract * fract) >> 15); 
    
    /* fractCube = fract * fract * fract */ 
    fractCube = (Int16) ((fractSquare * fract) >> 15); 
    
    /* Initialise table pointer */ 
    tablePtr = (Int16 *) & arrayCosQ15[index]; 
    
    /* Cubic interpolation process */ 
    /* Calculation of wa */ 
    /* wa = -(oneBy6)*fractCube + (fractSquare >> 1u) - (0x2AAA)*fract; */ 
    wa = (Int32) oneBy6 *fractCube; 
    wa += (Int32) 0x2AAA * fract; 
    wa = -(wa >> 15); 
    wa += (fractSquare >> 1u); 
    
    /* Read first nearest value of output from the cos table */ 
    a = *tablePtr++; 
    
    /* cosVal = a * wa */ 
    cosVal = a * wa; 
    
    /* Calculation of wb */ 
    wb = (((fractCube >> 1u) - fractSquare) - (fract >> 1u)) + 0x7FFF; 
    
    /* Read second nearest value of output from the cos table */ 
    b = *tablePtr++; 
    
    /*      cosVal += b*wb */ 
    cosVal += b * wb; 
    
    /* Calculation of wc */ 
    wc = -(Int32) fractCube + fractSquare; 
    wc = (wc >> 1u) + fract; 
    
    /* Read third nearest value of output from the cos table */ 
    c = *tablePtr++; 
    
    /*      cosVal += c*wc */ 
    cosVal += c * wc; 
    
    /* Calculation of wd */ 
    /* wd = (oneBy6)*fractCube - (oneBy6)*fract; */ 
    fractCube = fractCube - fract; 
    wd = ((Int16) (((Int32) oneBy6 * fractCube) >> 15)); 
    
    /* Read fourth nearest value of output from the cos table */ 
    d = *tablePtr++; 
    
    /* cosVal += d*wd; */ 
    cosVal += d * wd; 
    
    /* Return the output value in 1.15(q15) format */ 
    return ((IntQ15) (cosVal >> 15u));     
} 
