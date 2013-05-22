
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



