/*
	Dvos - Copyright © 2013 Baptiste Burles, Christophe Casson, Sylvain Fay-Chatelard

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
#include "../include/libs-hardware.h"

// Compass driver that use MAG3110 magnetometer and MMA7660 accelerometer






void computeOrientation(Orientation* out, MagneticRawValue* mag, AccelerationRawValue* accel)
{
    /* stack variables */
    /* iBpx, iBpy, iBpz: the three components of the magnetometer sensor */
    /* iGpx, iGpy, iGpz: the three components of the accelerometer sensor */

    Int32 iSin, iCos;
    Int32 iPhi, iThe, iPsi;
    Int32 iBfx, iBfy, iBfz;

    Int32 iBpx = (Int32)mag->y;
    Int32 iBpy = ((Int32)mag->x);
    Int32 iBpz = ((Int32)mag->z);
    Int32 iGpx = (Int32)accel->x;
    Int32 iGpy = ((Int32)accel->y);
    Int32 iGpz = (Int32)accel->z;

    /* calculate current roll angle Phi */
    iPhi = GetAtan2(iGpy, iGpz);/* Eq 13 */

    /* calculate sin and cosine of roll angle Phi */
    iSin = iTrig(iGpy, iGpz); /* Eq 13: sin = opposite / hypotenuse */
    iCos = iTrig(iGpz, iGpy); /* Eq 13: cos = adjacent / hypotenuse */

    /* de-rotate by roll angle Phi */
    iBfy = ((iBpy * iCos - iBpz * iSin) >> 15);/* Eq 19 y component */
    iBpz = ((iBpy * iSin + iBpz * iCos) >> 15);/* Bpy*sin(Phi)+Bpz*cos(Phi)*/
    iGpz = ((iGpy * iSin + iGpz * iCos) >> 15);/* Eq 15 denominator */


    /* calculate current pitch angle Theta */
    iThe = GetAtan2(-iGpx, iGpz);/* Eq 15 */
    
    /* restrict pitch angle to range -90 to 90 degrees */
    if (iThe > 9000) iThe =  (18000 - iThe);
    if (iThe < -9000) iThe = (-18000 - iThe);

    /* calculate sin and cosine of pitch angle Theta */
    iSin = -iTrig(iGpx, iGpz); /* Eq 15: sin = opposite / hypotenuse */
    iCos = iTrig(iGpz, iGpx); /* Eq 15: cos = adjacent / hypotenuse */
    
    /* correct cosine if pitch not in range -90 to 90 degrees */
    if (iCos < 0) iCos = -iCos;

    /* de-rotate by pitch angle Theta */
    iBfx = ((iBpx * iCos + iBpz * iSin) >> 15); /* Eq 19: x component */
    iBfz = ((-iBpx * iSin + iBpz * iCos) >> 15);/* Eq 19: z component */


    /* calculate current yaw = e-compass angle Psi */
    iPsi = GetAtan2(-iBfy, iBfx); /* Eq 22 */


    out->heading = iPsi;
    out->pitch = iThe;
    out->roll = iPhi;
}