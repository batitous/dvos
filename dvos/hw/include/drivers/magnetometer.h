
#ifndef LIB_HW_MAGNETOMETER_H
#define LIB_HW_MAGNETOMETER_H

#ifdef __cplusplus
extern "C" {
#endif
    
    
typedef struct _magnetics_raw_values_
{
    Int16       x;
    Int16       y;
    Int16       z;
    //Int32       angleNorth;
} MagneticRawValue;


extern Bool InitMagnetometer(void);

extern Bool GetMagneticValue(MagneticRawValue * rawvalue, MagneticRawValue * value/*, UInt8* calibratestate*/);

extern UInt8 getTemperature(void);


extern void StartMagnetometerCalibration(void);

extern void StopMagnetometerCalibration(void);

#ifdef __cplusplus
 }
#endif

#endif
