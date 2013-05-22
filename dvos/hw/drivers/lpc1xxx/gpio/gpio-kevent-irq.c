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
#include "../../kernel/include/kernel-dvos.h"
#include "../include/libs-hardware.h"

//----------------------------- private objects:



// Manage the input/output interrupt for the KEvent manager
void keventGpioIrqCallback(UInt32 event, UInt32 edge)
{
    PostEventFromIrq(KEVENT_GPIO_MASK | event, edge );
}
