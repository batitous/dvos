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
#ifndef LIBS_HW_DEVICE_H
#define	LIBS_HW_DEVICE_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _k_life_device KDevice;

typedef KDevice * (*KOpenDrv)(UInt32 name, UInt32 option);

typedef UInt32 (*KWriteDrv)(KDevice * fd, UInt8 * buffer, UInt32 size);
typedef UInt32 (*KReadDrv)(KDevice * fd, UInt8 * buffer, UInt32 size);

typedef UInt32 (*KControlDrv)(KDevice * fd, UInt32 option, UInt32 value);
typedef UInt32 (*KStatusDrv)(KDevice * fd, UInt32 option, UInt32 * result);

typedef UInt32 (*KCloseDrv)(KDevice * fd);


typedef struct _k_device_manager_
{
    KOpenDrv    open;
    KWriteDrv   write;
    KReadDrv    read;
    KControlDrv control;
    KStatusDrv  status;
    KCloseDrv   close;
} KDeviceManager;

struct _k_life_device
{
    UInt32              name;
    void *              data;
    KDeviceManager *    dev;
};

#define DEVICE_ID_MASK  0xFF000000
#define DEV_ANALOG      0x01000000 
#define DEV_GPIO        0x02000000
#define DEV_UART        0x03000000



extern KDevice * open(UInt32 name, UInt32 option);
extern UInt32 write(KDevice * fd, UInt8 * buffer, UInt32 size);
extern UInt32 read(KDevice * fd, UInt8 * buffer, UInt32 size);
extern UInt32 control(KDevice * fd, UInt32 option, UInt32 value);
extern UInt32 status(KDevice * fd, UInt32 option, UInt32 * result);
extern UInt32 close(KDevice * fd);



#ifdef	__cplusplus
}
#endif

#endif	/* KDEVICE_H */

