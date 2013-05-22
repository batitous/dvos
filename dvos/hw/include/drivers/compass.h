
#ifndef COMPASS_H
#define	COMPASS_H

#ifdef	__cplusplus
extern "C" {
#endif

    
#include "accelerometer.h"
#include "magnetometer.h"
    
typedef struct _Orientation_
{
    Int32 heading;
    Int32 pitch;
    Int32 roll;
} Orientation;
    
    
extern void ComputeOrientation(Orientation* out, MagneticRawValue* mag, AccelerationRawValue* accel);



#ifdef	__cplusplus
}
#endif

#endif

