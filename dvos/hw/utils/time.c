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
#include "../include/types.h"

// c'est pas fait pour faire des trucs précis, juste à placer delais !

#ifdef MCU_IS_LPC13XX
#       define LOOP_DELAY      2
#endif

#ifdef MCU_IS_LPC17XX
#       define LOOP_DELAY       4
#endif

void  waitUs(UInt32  delay)
{
    volatile  UInt32  i;

    for (i = 0; i < (LOOP_DELAY * delay); i++)
    {
        ;
    }
}
