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

typedef struct _k_device_entry_
{
    UInt32             id;
    KDeviceManager *   dev;
} KDeviceEntry;


static const KDeviceEntry devices[] =
{
    
    { 0, 0 }
};


KDevice * open(UInt32 name, UInt32 option)
{
    UInt32 i;
    UInt32 deviceId = DEVICE_ID_MASK & name;
    
    for (i=0; devices[i].id!=0;i++)
    {
        if (devices[i].id==deviceId)
        {
            return devices[i].dev->open(name,option);
        }
    }
    
    return 0;
}

UInt32 write(KDevice * fd, UInt8 * buffer, UInt32 size)
{
    return fd->dev->write(fd,buffer,size);
}

UInt32 read(KDevice * fd, UInt8 * buffer, UInt32 size)
{
    return fd->dev->read(fd,buffer,size);
}

UInt32 control(KDevice * fd, UInt32 option, UInt32 value)
{
    return fd->dev->control(fd,option,value);
}

UInt32 status(KDevice * fd, UInt32 option, UInt32 * result)
{
    return fd->dev->status(fd,option,result);
}

UInt32 close(KDevice * fd)
{
    return fd->dev->close(fd);
}

