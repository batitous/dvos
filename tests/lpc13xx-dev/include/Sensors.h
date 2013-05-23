#ifndef LINESENSOR_SHARP_SENSORS_H
#define LINESENSOR_SHARP_SENSORS_H


typedef struct _public_sensors_memory_
{
    UInt16 values[3];
    UInt8  rfu[2];
} sensorsMemory;

extern sensorsMemory sensorsPublic;


typedef struct _public_distmm_memory_
{
    UInt16 value;
    UInt8  rfu[2];
} distmmMemory;

extern distmmMemory distmmPublic;

#endif