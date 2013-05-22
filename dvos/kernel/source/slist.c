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
#include "../../hw/include/libs-default.h"

#include "../include/klist.h"

/**
  code takes from babvm
 */

void initSList(SList *l)
{
    l->next = 0;
}

void insertSNodeToStart(SList *l, SNode *node)
{
    node->next = (SNode *)l->next;
    l->next = node;
}

void removeSNode(SList *l, SNode *node)
{
    SNode * temp = l->next;
    SNode * previous = (SNode *)l;
    
    while(temp!=0)
    {
        if(temp==node)
        {
            previous->next = node->next;
            return;
        }
        
        previous = temp;
        temp = temp->next;
    }
    
}
