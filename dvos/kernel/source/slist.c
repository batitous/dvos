
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
