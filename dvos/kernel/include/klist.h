
#ifndef DVOS_KERNEL_LIST_H
#define DVOS_KERNEL_LIST_H

/*********************
 
 Difference entre les objets klist et slist :
 - klist consomme un peu plus de mémoire par element
 - slist ne que ajouter en début de list

 - lorsque on ajoute : slist est plus rapide que klist
 - lorsque on enleve : klist est BEAUCOUP plus rapide que slist
 
 - Utilisé slist lorsque les elements ne sont que RAREMENT retiré
 - Utilisé klist lorsque les elements sont en permanence retiré / ajouté
 
 
 **********************/



/** @brief A link to something.
 */
typedef void KLink;

/** @brief A double linked list.
 */
typedef struct _knode_
{
    struct _knode_ * next;
    struct _knode_ * prev;
} KNode;

/** @brief A list has a head and an end.
 */
typedef struct _klist_
{
    KLink * next;   /**< head of list */
    KLink * prev;   /**< end of list */
} KList;


/** @brief Initialize an empty list
 *
 * @param l		Pointer to a list.
 */
extern void initKList(KList *l);


/** @brief Remove the node from the list.
 *
 * @param p		element
 */
extern void removeKNode(KNode *p);


/** @brief Add node at the end of list.
 *
 * @param l     A pointer to a valid list.
 * @param node  Node to be added.
 */
extern void insertKNodeToEnd(KList *l, KNode *node);


/** @brief A simple node */
typedef struct _snode_
{
    struct _snode_ * next;
} SNode;

/** @brief A simple list */
typedef struct _slist_
{
    KLink * next;        /**< Next node in the list */
} SList;

/** @brief Initialize a simple list as empty.
 * 
 * @param l     Pointer to a simple list.
 */
extern void initSList(SList *l);

/** @brief Insert a node to the list
 *
 * @param l     A pointer to a valid list.
 * @param node  Node to be added.
 */
extern void insertSNodeToStart(SList *l, SNode *node);

/** @brief Remove a node from the list
 *
 * @param l     A pointer to a valid list.
 * @param node  Node to be removed.
 */
extern void removeSNode(SList *l, SNode *node);

#endif
