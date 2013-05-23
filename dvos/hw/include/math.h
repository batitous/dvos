/*
	Dvos - Copyright (C) 2013 Baptiste Burles, Christophe Casson, Sylvain Fay-Chatelard

    This file is part of Dvos.

    Dvos is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    Dvos is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef LIBS_HW_MATH_H
#define LIBS_HW_MATH_H

#ifdef __cplusplus
extern "C" {
#endif
    
// code comes from the DSP Lib from ARM and Freescale App Notes.
    
    
#define TABLE_SPACING_Q15	0x80

/** @brief A IntQ15 is a number between -1.00 and 0.99 */
typedef Int16   IntQ15;
    
typedef Int16   RadianQ15;


/** @brief Get degree value from radian.
 * 
 * @param radian        A Q15 value in radian
 * @return Degree value (between 0 and 360) from the radian value.
 */
extern Int16 getDegreeFromRadian(IntQ15 radian);


/** @brief Get radian value from degree value.
 * 
 * @param degree        A degree value.
 * @return A radian value
 */
extern RadianQ15 getRadianQ15FromDegree(Int16 degree);


/** @brief Fast approximation to the trigonometric cosine function for Q15 data. 
 *
 * The Q15 input value is in the range [0 +1) and is mapped to a radian value in the range [0 2*pi). 
 * 
 * @param[in] x Scaled input value in radians. 
 * @return  cos(x). 
 */ 
extern IntQ15 getCosFromRadianQ15( RadianQ15 x);


/** @brief Fast approximation to the trigonometric sine function for Q15 data.
 * 
 * The Q15 input value is in the range [0 +1) and is mapped to a radian value in the range [0 2*pi).  
 * 
 * @param[in] x Scaled input value in radians.  
 * @return  sin(x).
 */
extern IntQ15 getSinFromRadianQ15(RadianQ15 x);


/** @brief Get cosine from opposed and adjacent axis.
 * 
 * ATTENTION C'EST BIEN OPPOSE ET ADJACENT ! on ne calcule pas le cos depuis l'hypothénuse
 * 
 * @param opposed       X    
 * @param adjacent      Y
 * @return Q15 value.
 */
extern IntQ15 getCosFromXY(Int16 opposed, Int16 adjacent );


/** @brief Get sine from opposed and adjacent axis.
 *   
 * ATTENTION C'EST BIEN OPPOSE ET ADJACENT ! on ne calcule pas le sin depuis l'hypothénuse
 * 
 * @param opposed       X
 * @param adjacent      Y
 * @return Q15 value.
 */
extern IntQ15 getSinFromXY(Int16 opposed, Int16 adjacent);


/** Get Atan
 * 
 * @param iy    iy must be positive.
 * @param ix
 * @return degrees times 100 (0.0 to 90.0 degrees)
 */
extern Int16 getAtan(Int16 iy, Int16 ix);

/** Get Atan2
 * 
 * @param iy
 * @param ix
 * @return degrees times 100 (0.0 to 90.0 degrees)
 */
extern Int16 getAtan2(Int16 iy, Int16 ix) ;


extern UInt32 getSqrt(UInt32 x);


extern Int32 iTrig(Int32 ix, Int32 iy); 

#ifdef __cplusplus
 }
#endif

#endif
