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
#include "../../hw/include/types.h"
#include "../include/klist.h"

void initKList(KList *l)
{
    l->next = l;
    l->prev = l;
}

void insertKNodeToEnd(KList *l, KNode *node)
{
    KNode * temp = l->prev;

    temp->next = node;

    node->next = (KNode *)l;
    node->prev = temp;

    l->prev = node;

}

void removeKNode(KNode *p)
{
    KNode * p1 = p->prev;
    KNode * p2 = p->next;

    p2->prev = p1;
    p1->next = p2;
}



