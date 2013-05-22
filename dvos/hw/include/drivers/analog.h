
#ifndef LIB_HW_ANALOG_H
#define LIB_HW_ANALOG_H

#ifdef __cplusplus
extern "C" {
#endif


typedef enum ANALOG_CHANNEL_
{
	ANA0=0x01,      /**< Channel 0 */
	ANA1=0x02,      /**< Channel 1 */
	ANA2=0x04,      /**< Channel 2 */
	ANA3=0x08,      /**< Channel 3 */
	ANA4=0x10,      /**< Channel 4 */
	ANA5=0x20,      /**< Channel 5 */
	ANA6=0x40,      /**< Channel 6 */
	ANA7=0x80,      /**< Channel 7 */
} ANALOG_CHANNEL ;


extern void InitMcuAnalog(UInt32 analogChannel);

extern UInt16 GetMcuAnalog(ANALOG_CHANNEL channel);

extern ANALOG_CHANNEL GetAnalogChannel(UInt8 channel);


#ifdef __cplusplus
 }
#endif

#endif
