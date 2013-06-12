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
#ifndef FLASH_SST25_H
#define	FLASH_SST25_H

#ifdef	__cplusplus
extern "C" {
#endif


extern void SST25Init(void);

extern void SST25DisableWriteProtection(void);

extern void SST25Erase(void);

extern UInt8 SST25ReadStatus(void);

extern Bool SST25IsBusy(void);

extern void SST25EnableWrite(void);

extern void SST25DisableWrite();

extern UInt8 SST25ReadByte(UInt32 address);

extern void SST25ReadBuffer(UInt32 address, UInt8 * buffer, UInt32 size);

extern void SST25EraseSector(UInt32 address);

extern void SST25WriteBuffer(UInt32 address, UInt8 * buffer, UInt32 size);

extern UInt32 SST25GetID(UInt8 ID_addr);



#ifdef	__cplusplus
}
#endif

#endif	/* FLASH_SST25_H */

