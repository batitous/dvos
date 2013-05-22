
#ifndef LIB_HW_ROM_IAP_H
#define LIB_HW_ROM_IAP_H

#ifdef __cplusplus
extern "C" {
#endif

    
// Function to execute the ROM IAP code of NXP to access flash and eeprom
    

#define IAP_CCLK        KERNEL_CPU_FREQ


typedef enum _iapCommandCode_
{
        IAP_PREPARE_SECTOR_FOR_WRITE	=50,
        IAP_COPY_RAM_TO_FLASH		=51,
        IAP_ERASE_SECTOR		=52,
        IAP_BLANK_CHECK_SECTOR		=53,
        IAP_READ_PART_ID		=54,
        IAP_READ_BOOT_VER		=55,
        IAP_COMPARE			=56,
        IAP_REINVOKE_ISP		=57,
        IAP_WRITE_EEPROM                =61,
        IAP_READ_EEPROM                 =62
} iapCommandCode;


#define IAP_SUCCESS 0
#define IAP_ADDRESS 0x1FFF1FF1


extern void iapExecute(UInt32 *param_tab,UInt32 *result_tab);



#ifdef __cplusplus
 }
#endif

#endif
