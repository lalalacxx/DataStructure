#pragma once

#include<stddef.h>

typedef char LinkType;

typedef struct LinkNode
{
	LinkType data;
	struct LinkNode* next;
}LinkNode;

LinkNode *head;

void DestroyNode(LinkNode *node);
void linklistPrint(LinkNode *head);

void linklistInit(LinkNode **head);

LinkNode *linklistPushBack(LinkNode **head,LinkType value);
void linklistPopBack(LinkNode **head);

void linklistPushFront(LinkNode **head,LinkType value);
void linklistPopFront(LinkNode **head);

LinkNode *linklistFind(LinkNode *head,LinkType to_find);

void linklistInsertBefore(LinkNode **head,LinkNode *pos,LinkType value);
void linklistInsertAfter(LinkNode **head,LinkNode *pos,LinkType value);

void linklistErase(LinkNode **head,LinkNode *pos);
void linklistErase2(LinkNode **head,LinkNode *pos);

void linklistRemove(LinkNode **head,LinkType to_delete);
void linklistRemoveAll(LinkNode ** head,LinkType value);

int linklistEmpty(LinkNode *head);
size_t linklistSize(LinkNode *head);

void linklistReversePrint(LinkNode *head);

void linklistInsertBefore1(LinkNode **head,LinkNode *pos,LinkType value);

void linklistRerverse(LinkNode **head);
void linklistRerverse2(LinkNode **head);

void linklistBubbleSort(LinkNode *head);

LinkNode *FindMidNode(LinkNode *head);

LinkNode *FindLastKNode(LinkNode *head,size_t k);
void EraseLastKNode(LinkNode **head,size_t k);

LinkNode *linklistMerge(LinkNode *head1,LinkNode *head2);


LinkNode *HasCycle(LinkNode *head);
size_t GetCycleLen(LinkNode *head);
LinkNode *GetCycleEntry(LinkNode *head);

int HasCross(LinkNode *head1,LinkNode *head2);
int HasCrossWithCycle(LinkNode *head1,LinkNode *head2);

LinkNode *UnionSet(LinkNode *head1,LinkNode *head2);
LinkNode *JoserhCycle(LinkNode *head,size_t food);
