#pragma once

typedef char DLinkType;

typedef struct DLinkNode
{
	DLinkType data;
	struct DLinkNode *prev;
	struct DLinkNode *next;
}DLinkNode;

DLinkNode *head;

void DLinkListInit(DLinkNode **head);

DLinkNode *DLinkListPushBack(DLinkNode *head,DLinkType value);
void DLinkListPopBack(DLinkNode *head);

void DLinkListPushFront(DLinkNode *head,DLinkType value);
void DLinkListPopFront(DLinkNode *head);

DLinkNode* DLinkListFind(DLinkNode *head,DLinkType to_find);

void DLinkListInsert(DLinkNode *head,DLinkNode *pos,DLinkType value);
void DLinkListInsertAfter(DLinkNode *head,DLinkNode *pos,DLinkType value);

void DLinkListErase(DLinkNode *head,DLinkNode *pos);

void DLinkListRemove(DLinkNode *head,DLinkType to_remove);
void DLinkListRemoveAll(DLinkNode *head,DLinkType to_remove);

size_t DLinkListSize(DLinkNode *head);

int DLinkListEmpty(DLinkNode *head);


