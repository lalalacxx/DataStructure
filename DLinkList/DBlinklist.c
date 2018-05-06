#include<stdlib.h>
#include<stdio.h>
#include<stddef.h>
#include"DBlinklist.h"

#define Test_Header  printf("\n============%s============\n",__FUNCTION__);


void DLinkListPrint(DLinkNode *head,const char *msg)
{
	printf("[%s]\n",msg);
	if(head == NULL)
	{
		printf("非法输入\n");
		return;
	}
	if(head->prev == head)
	{
		printf("空链表\n");
		return;
	}
	DLinkNode *cur = head->next;
	for(;cur != head;cur = cur->next)
	{
		printf("[%c|%p] ",cur->data,cur);
	}
	printf("\n");
	DLinkNode *pre = head->prev;
	for(;pre != head;pre = pre->prev)
	{
		printf("[%c|%p] ",pre->data,pre);
	}
	printf("\n");
}
DLinkNode* Creat(DLinkType value)
{
	DLinkNode *new_node = (DLinkNode*)malloc(sizeof(DLinkNode));
	new_node->data = value;
	new_node->prev = new_node;
	new_node->next = new_node;
	return new_node;
}
void DLinkListInit(DLinkNode **head)
{
	if(head == NULL)
	{
		return;
	}
	*head = Creat(0);
}

DLinkNode* DLinkListPushBack(DLinkNode* head, DLinkType value)
{
	if(head == NULL)
	{
		return NULL;
	}

	DLinkNode *last_node = head->prev;
	DLinkNode *new_node = Creat(value);
	//last_node VS new_node
	last_node->next = new_node;
	new_node->prev = last_node;
	//head VS new_node
	head->prev = new_node;
	new_node->next = head;

	return new_node;
}
void DLinkListPopBack(DLinkNode* head)
{
	if(head == NULL)
	{
		return;
	}
	if(head->prev == head)
	{
		return;
	}
	DLinkNode *to_delete = head->prev;
	DLinkNode *last_node = to_delete->prev;
	
	last_node->next = head;
	head->prev = last_node;

	free(to_delete);
	return;
}

void DLinkListPushFront(DLinkNode* head, DLinkType value)
{
	if(head == NULL)
	{
		return;
	}
	DLinkNode *new_node = Creat(value);
	DLinkNode *first_node = head->next;
	//head VS new_node
	head->next = new_node;
	new_node->prev = head;
	//new_node VS first_node
	new_node->next = first_node;
	first_node->prev = new_node;
	
	return;
}
void DLinkListPopFront(DLinkNode* head)
{
	if(head == NULL)
	{
		return;
	}
	if(head->prev == head)
	{
		return;
	}
	DLinkNode *to_delete = head->next;
	DLinkNode *next_first_node = to_delete->next;

	head->next = next_first_node;
	next_first_node->prev = head;

	free(to_delete);

	return;
}

DLinkNode* DLinkListFind(DLinkNode* head, DLinkType to_find)
{
	if(head == NULL)
	{
		return NULL;
	}
	DLinkNode *cur = head->next;
	for(;cur->next != head;cur = cur->next)
	{
		if(cur->data == to_find)
		{
			return cur;
		}
	}
	return NULL;
}

/** 
 * * @brief 往指定位置之前插入一个元素 
 * */
void DLinkListInsert(DLinkNode *head,DLinkNode* pos, DLinkType value)
{
	if(head == NULL || pos == NULL)
	{
		return;
	}
	DLinkNode *before_pos_node = pos->prev;
	DLinkNode *new_node = Creat(value);
	//new_node VS before_pos_node
	new_node->prev = before_pos_node;
	before_pos_node->next = new_node;
	//new_node VS pos
	new_node->next = pos;
	pos->prev = new_node;

	return;
}
//往指定位置之后插入一个元素 
void DLinkListInsertAfter(DLinkNode *head,DLinkNode* pos, DLinkType value)
{
	if(head == NULL || pos == NULL)
	{
		return;
	}
	DLinkNode *next_pos_node = pos->next;
	DLinkNode *new_node = Creat(value);

	//new_node VS next_pos_node
	new_node->next = next_pos_node;
	next_pos_node->prev = new_node;
	//new_node VS pos
	pos->next = new_node;
	new_node->prev = pos;

	return;
}

void DLinkListErase(DLinkNode *head,DLinkNode *pos)
{
	if(head == NULL || pos == NULL || pos == head)
	{
		return;
	}
	if(head->prev == head)
	{
		return;
	}
	DLinkNode *before_pos_node = pos->prev;
	DLinkNode *next_pos_node = pos->next;
	//before_pos_node VS next_pos_node
	before_pos_node->next = next_pos_node;
	next_pos_node->prev = before_pos_node;

	return;
}

void DLinkListRemove(DLinkNode *head,DLinkType to_remove)
{
	if(head == NULL)
	{
		return;
	}
	DLinkNode *cur = head->next;
	for(;cur->next != head && cur->data != to_remove;cur = cur->next)
		;
	if(cur->next == head && cur->data != to_remove)
		return;
	DLinkListErase(head,cur);
}
void DLinkListRemoveAll(DLinkNode *head,DLinkType to_remove)
{
	if(head == NULL)
	{
		return;
	}
	DLinkNode *cur = head->next;
	while(1)
	{
		for(cur = head->next;cur->next != head && cur->data != to_remove;cur = cur->next)
			;
		if(cur->next == head && cur->data != to_remove)
			//this value is non-existence
			return;
		DLinkListErase(head,cur);
	}
}

size_t DLinkListSize(DLinkNode *head)
{
	if(head == NULL)
	{
		return 0;
	}
	if(head->prev == head)
	{
		return 0;
	}
	size_t count = 1;
	DLinkNode *cur = head->next;
	for(;cur->next != head;cur = cur->next)
	{
		count++;
	}
	return count;
}

int DLinkListEmpty(DLinkNode *head)
{
	if(head == NULL)
	{
		return 0;
	}
	if(head->prev != head)
		return 1;
	else
		return 0;
}
void DLinkListDestroy(DLinkNode **head)
{
	if(head == NULL)
	{
		return;
	}
	DLinkNode *cur = (*head)->next;
	while(cur != *head)
	{
		DLinkNode *next = cur->next;
		free(cur);
		cur = next;
	}
	free(*head);
	*head = NULL;
}
///////////////////////////////////////////
void TestInit()
{
	Test_Header;
	DLinkListInit(&head);
	printf("expected:0 actual:%d\n",(int)head->data);
}
void TestPushBack()
{
	Test_Header;
	DLinkListInit(&head);
	DLinkListPushBack(head,'a');
	DLinkListPushBack(head,'b');
	DLinkListPushBack(head,'c');
	DLinkListPushBack(head,'d');
	DLinkListPrint(head,"尾插四个元素");
}
void TestPopBack()
{
	Test_Header;
	DLinkListPopBack(head);
	DLinkListPopBack(head);
	DLinkListPrint(head,"尾删两个元素");
	DLinkListPopBack(head);
	DLinkListPopBack(head);
	DLinkListPrint(head,"再尾删两个元素");
	DLinkListPopBack(head);
	DLinkListPrint(head,"尝试对空链表删除");
}
void TestPushFront()
{
	Test_Header;
	DLinkListPushFront(head,'a');
	DLinkListPushFront(head,'b');
	DLinkListPushFront(head,'c');
	DLinkListPushFront(head,'d');
	DLinkListPrint(head,"头插四个元素");
}
void TestPopFront()
{
	Test_Header;
	DLinkListPopFront(head);
	DLinkListPopFront(head);
	DLinkListPrint(head,"头删两个元素");
	DLinkListPopFront(head);
	DLinkListPopFront(head);
	DLinkListPrint(head,"再头删两个元素");
	DLinkListPopFront(head);
	DLinkListPrint(head,"尝试对空链表删除");
}
void TestFind()
{
	Test_Header;

	DLinkListPushBack(head,'a');
	DLinkListPushBack(head,'b');
	DLinkListPushBack(head,'c');
	DLinkListPushBack(head,'d');
	DLinkListPrint(head,"先尾插四个元素");
	DLinkNode *ret1 = DLinkListFind(head,'b');
	printf("元素b的地址为：%p\n",ret1);
	DLinkNode *ret2 = DLinkListFind(head,'e');
	printf("元素e的地址为：%p\n",ret2);
	DLinkListPopFront(head);
	DLinkListPopFront(head);
	DLinkListPopFront(head);
	DLinkListPopFront(head);
	DLinkListPrint(head,"头删四个元素形成空链表");
	DLinkNode *ret3 = DLinkListFind(head,'b');
	printf("元素b的地址为：%p\n",ret3);
}
void TestErase()
{
	Test_Header;
	DLinkListPushBack(head,'a');
	DLinkListPushBack(head,'b');
	DLinkListPushBack(head,'c');
	DLinkListPushBack(head,'d');
	DLinkListPrint(head,"先尾插四个元素");
	DLinkNode *pos = DLinkListFind(head,'b');
	DLinkListErase(head,pos);
	DLinkListPrint(head,"尝试删除b位置的元素");
	DLinkListErase(head,NULL);
	DLinkListErase(head,head);
	DLinkListPrint(head,"pos为空或者为head时删除之后的链表元素");
}
void TestInsert()
{
	Test_Header;
	DLinkNode *pos = DLinkListFind(head,'c');
	DLinkListInsert(head,pos,'b');
	DLinkListPrint(head,"c之前插入b之后的链表元素");
	DLinkListInsert(head,head->next,'A');
	DLinkListPrint(head,"a之前插入A之后的链表元素");
}
void TestInsertAfter()
{
	Test_Header;
	
	DLinkNode *pos = DLinkListFind(head,'a');
	DLinkListInsertAfter(head,pos,'B');
	DLinkListPrint(head,"a后面插入B之后的链表元素");
	DLinkListInsertAfter(head,head->prev,'e');
	DLinkListPrint(head,"d后面插入e之后的链表元素");
}
void TestRemove()
{
	Test_Header;
	DLinkListPushBack(head,'c');
	DLinkListPushBack(head,'d');
	DLinkListPrint(head,"先尾插两个元素");
	DLinkListRemove(head,'a');
	DLinkListPrint(head,"先删除一个出现一次的元素a");
	DLinkListRemove(head,'d');
	DLinkListPrint(head,"再删除一个出现两次的元素d");
	DLinkListRemove(head,'d');
	DLinkListPrint(head,"再删除一个出现一次的元素d");
}

void TestRemoveAll()
{
	Test_Header;
	DLinkListRemoveAll(head,'e');
	DLinkListPrint(head,"先删除一个出现一次的元素e");
	DLinkListRemoveAll(head,'c');
	DLinkListPrint(head,"再删除一个出现两次的元素c");
}
void TestSize()
{
	Test_Header;
	size_t ret = DLinkListSize(head);
	DLinkListPrint(head,"链表中的元素为");
	printf("链表中共有：%lu 个元素\n",ret);
}
void TestEmpty()
{
	Test_Header;
	DLinkListPrint(head,"链表中的元素为");
	int ret = DLinkListEmpty(head);
	printf("判空返回值为：%d\n",ret);
	DLinkListPopFront(head);
	DLinkListPopFront(head);
	DLinkListPopFront(head);
	DLinkListPrint(head,"删除三个元素后链表中的元素为");
	ret = DLinkListEmpty(head);
	printf("判空返回值为：%d\n",ret);
}
void TestDestroy()
{
	Test_Header;
	DLinkListDestroy(&head);
	DLinkListPrint(head,"尝试对一个已经被销毁的链表进行打印");
}
///////////////////////////////////////////
int main()
{
	TestInit();
	TestPushBack();
	TestPopBack();
	TestPushFront();
	TestPopFront();
	TestFind();
	TestErase();
	TestInsert();
	TestInsertAfter();
	TestRemove();
	TestRemoveAll();
	TestSize();
	TestEmpty();
	TestDestroy();
	printf("\n\n");
	return 0;
}
