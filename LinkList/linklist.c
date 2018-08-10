#include<stdio.h>
#include<stdlib.h>
#include"linklist.h"


#define Test_Header printf("\n-------%s-------\n",__FUNCTION__);


void linklistInit(LinkNode **head)
{
	*head = NULL;
}

LinkNode *CreateNode(LinkType value)
{
	LinkNode *new_node = (LinkNode*)malloc(sizeof(LinkNode));
	new_node->data = value;
	new_node->next = NULL;
	return new_node;
}
void DestroyNode(LinkNode *node)
{

	free(node);
}
void linklistPrint(LinkNode *head)
{
	if(head == NULL)
	{
		return;
	}
	LinkNode *cur = head;
	while(cur != NULL)
	{
		printf("%c|%p\n",cur->data,cur);
		cur = cur->next;
	}
	printf("\n\n");
}
void linklistReversePrint(LinkNode *head)
{
	if(head == NULL)
	{
		return;
	}	
	linklistReversePrint(head->next);
	printf("%c|%p ",head->data,head);
	printf("\n");
}

LinkNode *linklistPushBack(LinkNode **head,LinkType value)
{
	if(head == NULL)
	{
		return NULL;
	}
	if(*head == NULL)
	{
		*head = CreateNode(value);
		return *head;
	}
	LinkNode *cur = *head;
	while(cur->next != NULL)
	{
		cur = cur->next;
	}
	LinkNode *new_node = CreateNode(value);
	cur->next = new_node;
	return new_node;
}
void linklistPopBack(LinkNode **head)
{
	if(head == NULL)
	{
		return;
	}
	if(*head == NULL)
	{
		printf("this linklist is empty ");
		return;
	}
	if((*head)->next == NULL)
	{
		DestroyNode(*head);
		*head = NULL;
		return;
	}
	else
	{
		LinkNode *cur = *head;
		while(cur->next->next != NULL)
		{
			cur = cur->next;
		}
		LinkNode *to_delete = cur->next;
		DestroyNode(to_delete);
		cur->next = NULL;
	}
	return;
}

void linklistPushFront(LinkNode **head,LinkType value)
{
	if(head == NULL)
	{
		return;
	}
	if(*head == NULL)
	{
		*head = CreateNode(value);
		return;
	}
	else
	{
		LinkNode *new_node = *head;
		*head = CreateNode(value);
		(*head)->next = new_node;
	}
	return;
}
void linklistPopFront(LinkNode **head)
{
	if(head == NULL)
	{
		return;
	}
	if(*head == NULL)
	{
		printf("this linklist is empty\n");
	}
	else
	{
		LinkNode *new_node = (*head)->next;
		(*head)->next = NULL;
		DestroyNode(*head);
		*head = new_node;
	}
	return;
}

LinkNode *linklistFind(LinkNode *head,LinkType to_find)
{
	int count = 0;
	LinkNode *find = head;
	if(head == NULL)
	{
		return NULL;
	}
	else
	{
		for(;find->next != NULL;find = find->next)
		{
			if(find->data == to_find)
			{
 				count++;

				return find;
			}
		}
	}
	if(count == 0)
	{
		printf("this value is non-existence\n");
	}
	return NULL;
}

void linklistInsertBefore(LinkNode **head,LinkNode *pos,LinkType value)
{
	if(head == NULL)
	{
		return;
	}
	if(*head == NULL)
	{
		*head = CreateNode(value);
		return;
	}
	if(pos == *head)
	{
		linklistPushFront(head,value);
		return;
	}
	if(pos == NULL)
	{
		linklistPushBack(head,value);
		return;
	}
	else
	{
		LinkNode *cur = *head;
		while(cur->next != NULL)
		{
			if(cur->next == pos)
			{
				LinkNode *pre = CreateNode(value);
				cur->next = pre;
				pre->next = pos;
				return;
			}
			cur = cur->next;
		}
	}
}
void linklistInsertBefore1(LinkNode **head,LinkNode *pos,LinkType value)
{
	if(head == NULL)
	{
		return;
	}
	if(*head == NULL)
	{
		*head = CreateNode(value);
		return;
	}
	if(pos == *head)
	{
		linklistPushFront(head,value);
		return;
	}
	if(pos == NULL)
	{
		linklistPushBack(head,value);
		return;
	}
	else
	{
		LinkNode *cur = pos->next;
		LinkNode *new_node = CreateNode(pos->data);
		pos->data = value;
		pos->next = new_node;
		new_node->next = cur;
	}

}
void linklistInsertAfter(LinkNode **head,LinkNode *pos,LinkType value)
{
	if(head ==NULL)
	{
		return;
	}
	if((*head) == NULL)
	{
		*head = CreateNode(value);
		return;
	}
	if(pos == NULL)
	{
		linklistPushBack(head,value);
		return;
	}
	if(pos == *head)
	{
		linklistPushFront(head,value);
		return;
	}
	else
	{
		LinkNode *cur = *head;
		while(cur->next != NULL)
		{
			if(cur->next == pos)
			{
				LinkNode *new_node = CreateNode(value);
				new_node->next = pos->next;
				pos->next = new_node;
			}
			cur = cur->next;

		}
	}
}

void linklistErase(LinkNode **head,LinkNode *pos)
{
	if(head == NULL)
	{
		return;
	}
	if(*head == NULL)
	{
		printf("this linklist is empty\n");
		return;
	}
	if(pos == NULL)
	{
		linklistPopBack(head);
		return;
	}
	if(pos == *head)
	{
		linklistPopFront(head);
		return;
	}
	else
	{
		LinkNode *cur = *head;
		while(cur->next != pos)
		{
			cur = cur->next;
		}
	//	LinkNode *new_node = pos;
		//cur->next = new_node->next;
	//	DestroyNode(new_node);
		cur->next = pos->next;
		DestroyNode(pos);

	}
}
void linklistErase2(LinkNode **head,LinkNode *pos)
{
	if(head == NULL)
	{
		return;
	}
	if(*head == NULL)
	{
		printf("this linklist is empty\n");
		return;
	}
	if(pos == NULL)
	{
		linklistPopBack(head);
		return;
	}
	if(pos == *head)
	{
		linklistPopFront(head);
		return;
	}
	else
	{
		LinkNode *to_delete = pos->next;
		pos->data = to_delete->data;
		pos->next = to_delete->next;
		DestroyNode(to_delete);
	}

}

void linklistRemove(LinkNode **head,LinkType to_delete)
{
	if(head == NULL)
	{
		return;
	}
	if(*head == NULL)
	{
		return;
	}
	if((*head)->data == to_delete)
	{
		linklistPopFront(head);
		return;
	}
	LinkNode *cur = *head;
	while(cur != NULL && cur->next != NULL)
	{
		if(cur->next->data == to_delete)
		{
			LinkNode *to_remove = cur->next;
			cur->next = to_remove->next;
			DestroyNode(to_remove);
			return;
		}
		cur = cur->next;
	}
}
void linklistRemoveAll(LinkNode **head,LinkType value)
{
	if(head == NULL)
	{
		return;
	}
	if(*head == NULL)
	{
		return;
	}
	LinkNode *cur = *head;
	while(1)
	{
		if(cur != NULL && cur->next != NULL)
		{
			if(cur->data == value)
			{
 				if(cur == *head)
				{
					linklistPopFront(head);
				}
				else
				{
 					LinkNode *to_delete = cur->next;
					cur->next = to_delete->next;
					DestroyNode(to_delete);
				}
			}
		}
		else
			return;
		cur = cur->next;
	}
}

int linklistEmpty(LinkNode *head)
{
	return head == NULL?0:1;
}
size_t linklistSize(LinkNode *head)
{
	if(head == NULL)
	{
		return 0;
	}
	size_t count = 0;
	LinkNode *cur = head;
	for(;cur != NULL;cur = cur->next)
	{
		count++;
	}
	return count;
}
///////////////////////////
void linklistRerverse(LinkNode **head)
{
	if(head == NULL)
	{
		return;
	}
	if(*head == NULL)
	{
		return;
	}
	if((*head)->next == NULL)
	{
		return;
	}
	else
	{
		LinkNode *cur = *head;
		while(cur->next != NULL)
		{
			LinkNode *to_delete = cur->next;
			cur->next = to_delete->next;
			to_delete->next = *head;
			*head = to_delete;
		}
	}
	return;
}
void linklistBubbleSort(LinkNode *head)
{
	if(head == NULL)
	{
		return;
	}
	if(head->next == NULL)
	{
		return;
	}
	LinkNode *cur = head;
	LinkNode *tail = NULL;
	for(;cur != NULL;cur = cur->next)
	{
		LinkNode *pre = head;
		for(;pre->next != tail;pre = pre->next)
		{
			if(pre->data > pre->next->data)
			{
				LinkType tmp = pre->data;
				pre->data = pre->next->data;
				pre->next->data = tmp;
			}
		}
		tail = pre;
	}
}

LinkNode *FindMidNode(LinkNode *head)
{
	if(head == NULL)
	{
		return NULL;
	}
	LinkNode *fast = head;
	LinkNode *slow = head;
	while(fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}

LinkNode *FindLastKNode(LinkNode *head,size_t k)
{
	if(head == NULL)
	{
		return NULL;
	}
	if(k > linklistSize(head))
	{
		return NULL;
	}
	LinkNode *front = head;
	LinkNode *back = head;
	size_t i = 0;
	for(;i < k-1;i++)
	{
		front = front->next;
	}
	for(;front->next != NULL;front = front->next,back = back->next)
		;
	return back;
}
void EraseLastKNode(LinkNode **head,size_t k)
{
	if(head == NULL)
	{
		return;
	}
	if((*head) == NULL)
	{
		return;
	}
	if(k > linklistSize(*head))
	{
		return;
	}
	LinkNode *to_delete = FindLastKNode(*head,k);
	LinkNode *cur = *head;
	for(;cur->next != to_delete;cur = cur->next)
		;
	cur->next = to_delete->next;
	DestroyNode(to_delete);
}

LinkNode *linklistMerge(LinkNode *head1,LinkNode *head2)
{
	LinkNode *new_head = NULL;
	LinkNode *new_tail = NULL;
	LinkNode *cur = head1;
	LinkNode *pre = head2;
	if(head1 == NULL)
	{
		return head2;
	}
	if(head2 == NULL)
	{
		return head1;
	}
	if(cur->data < pre->data)
	{
		new_head = cur;
		cur = cur->next;
		new_tail = new_head;
	}
	else
	{
		new_head = pre;
		pre = pre->next;
		new_tail = new_head;
	}
	while(cur != NULL && pre != NULL)
	{
		if(cur->data < pre->data)
		{
			new_tail->next = cur;
			cur = cur->next;
			new_tail = new_tail->next;
		}
		else
		{
			new_tail->next = pre;
			pre = pre->next;
			new_tail = new_tail->next;
		}
	}
	if(cur == NULL)
	{
		new_tail->next = pre;
	}
	else
	{
		new_tail->next = cur;
	}

	return new_head;
}

LinkNode *HasCycle(LinkNode *head)
{
	if(head == NULL)
	{
		return NULL;
	}
	LinkNode *fast = head;
	LinkNode *slow = head;
	while(fast != NULL && fast->next->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
		if(slow == fast)
		{
			return slow;
		}
	}
	return NULL;
}
size_t GetCycleLen(LinkNode *head)
{
	if(head == NULL)
	{
		return 0;
	}
	LinkNode *meet_node = HasCycle(head);
	if(meet_node ==NULL)
	{
		return 0;
	}
	LinkNode *cur = meet_node;
	size_t count = 1;
	for(cur = cur->next;cur != meet_node;cur = cur->next)
	{
		count++;
	}
	return count;
}
LinkNode *GetCycleEntry(LinkNode *head)
{
	if(head == NULL)
	{
		return NULL;
	}
	LinkNode *meet_node = HasCycle(head);
	if(meet_node == NULL)
	{
		return NULL;
	}
	LinkNode *cur = meet_node;
	LinkNode *start = head;
	while(start != cur)
	{
		start = start->next;
		cur = cur->next;
	}
	return cur;
}
int HasCross(LinkNode *head1,LinkNode *head2)
{
	if(head1 == NULL || head2 == NULL)
	{
		return 0;
	}
	LinkNode *cur1 = head1;
	LinkNode *cur2 = head2;
	for(;cur1->next != NULL;cur1 = cur1->next)
		;
	for(;cur2->next != NULL;cur2 = cur2->next)
		;
	if(cur1 == cur2)
	{
		return 1;
	}
	return 0;
}
LinkNode *HasCrossNode(LinkNode *head1,LinkNode *head2)
{
	if(head1 == NULL || head2 == NULL)
	{
		return NULL;
	}
	LinkNode *cur1 = head1;
	LinkNode *cur2 = head2;

	size_t size1 = linklistSize(head1);
	size_t size2 = linklistSize(head2);
	
	if(size1 > size2)
	{
		size_t i = 0;
		for(;i < size1-size2;i++)
		{
			cur1 = cur1->next;
		}
	}
	else if(size1 < size2)
	{
		size_t j = 0;
		for(;j < size2-size1;j++)
		{
			cur2 = cur2->next;
		}
	}

	for(;cur1->next != NULL && cur2->next != NULL;cur1 = cur1->next,cur2 = cur2->next)
	{
		if(cur1 == cur2)
		{
			return cur1;
		}
	}
	return NULL;
}
int HasCrossWithCycle(LinkNode *head1,LinkNode *head2)
{
	if(head1 == NULL || head2 == NULL)
	{
		return 0;
	}
	LinkNode *meet_node1 = HasCycle(head1);
	LinkNode *meet_node2 = HasCycle(head2);
	if(meet_node1 == NULL && meet_node2 == NULL)
	{
		int ret = HasCross(head1,head2);
		return ret;
	}
	else if(meet_node1 != NULL && meet_node2 != NULL)
	{
		LinkNode *fast = meet_node1;
		LinkNode *slow = meet_node1;
		while(fast != NULL && fast->next->next != NULL)
			{
 				fast = fast->next->next;
				slow = slow->next;
				if(fast == meet_node2)
				{
					return 1;
				}
				if(fast == slow)
				{
					return 0;
				}
			}
		}
		else 
			return 0;
		return 0;
}
LinkNode *HasCrossWithCycleNode(LinkNode *head1,LinkNode *head2)
{
	if(head1 == NULL || head2 == NULL)
	{
		return NULL;
	}
	LinkNode *cur1 = head1;
	LinkNode *cur2 = head2;
	LinkNode *Entry1 = GetCycleEntry(head1);
	LinkNode *Entry2 = GetCycleEntry(head2);
	
	size_t size1 = 1;
	for(;cur1->next != Entry1;cur1 = cur1->next)
	{
		size1++;
	}
	size1 = size1 + GetCycleLen(head1);
	size_t size2 = 1;
	for(;cur2->next != Entry2;cur2 = cur2->next)
	{
		size2++;
	}
	size2 = size2 + GetCycleLen(head2);
	
	LinkNode *start1 = head1;
	LinkNode *start2 = head2;
	if(size1 > size2)
	{
		size_t i = 0;
		for(;i < size1-size2;i++)
		{
			start1 = start1->next;
		}
	}
	else if(size1 < size2)
	{
		size_t j = 0;
		for(;j < size2-size1;j++)
		{
			start2 = start2->next;
		}
	}
	
	while(start1 != start2)
	{
		start1 = start1->next;
		start2 = start2->next;
	}
	if(start1 != Entry1 || start1 != Entry2)
	{
		return start1;
	}
	else
		return Entry1;
	return NULL;
}
LinkNode *UnionSet(LinkNode *head1,LinkNode *head2)
{
	if(head1 == NULL || head2 == NULL)
	{
		//此时两个链表其中一个为空链表或者两个都为空链表
		//那么就没有交集，返回NULL即可
		return NULL;
	}
	LinkNode *cur1 = head1;
	LinkNode *cur2 = head2;
	LinkNode *new_head = NULL;
	LinkNode *new_tail = NULL;
	while(cur1 != NULL && cur2 != NULL)
	{
		if(cur1->data > cur2->data)
		{
			cur2 = cur2->next;
		}
		else if(cur1->data < cur2->data)
		{
			cur1 = cur1->next;
		}
		else
		{
			LinkNode *new_node = CreateNode(cur1->data);
			if(new_head == NULL)
			{
				new_head = new_node;
				new_tail = new_node;
				cur1 = cur1->next;
				cur2 = cur2->next;
			}
			else
			{
				new_tail->next = new_node;
				new_tail = new_node;
				cur1 = cur1->next;
				cur2 = cur2->next;
			}
		}
	}
	return new_head;
}
LinkNode *JosephCycle(LinkNode *head,size_t food)
{
	if(head == NULL)
	{
		//
		return NULL;
	}
	size_t count = 1;
	LinkNode *cur = head;
	while(cur->next != cur) 
	{
		count++;
		cur = cur->next;
		if(count == food)
		{
			printf("[%c]\n",cur->data);
			cur->data = cur->next->data;
			LinkNode *to_delete = cur->next;
			cur->next = to_delete->next;
			DestroyNode(to_delete);
			count = 1;
		}
	}
	//
	return cur;
}
void TestJosephCycle()
{
	Test_Header;
	LinkNode *new_head;
	linklistInit(&new_head);
	LinkNode *a = CreateNode('a');
	LinkNode *b = CreateNode('b');
	LinkNode *c = CreateNode('c');
	LinkNode *d = CreateNode('d');
	LinkNode *e = CreateNode('e');
	new_head = a;
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
	e->next = a;
	printf("\n");
	LinkNode *ret = JosephCycle(new_head,2);
	printf("survivor:%c|%p \n",ret->data,ret);
}
void TestPushBack()
{
	Test_Header;
	printf("a b c d\n");
	linklistInit(&head);
	linklistPushBack(&head,'a');
	linklistPushBack(&head,'b');
	linklistPushBack(&head,'c');
	linklistPushBack(&head,'d');
	linklistPrint(head);
}
void TestPopBack()
{
	Test_Header;
	printf("expected:a,actual:");
	linklistPopBack(&head);
	linklistPopBack(&head);
	linklistPopBack(&head);
	linklistPrint(head);
}
void TestPushFront()
{
	Test_Header;
	printf("d c b a\n");
	linklistPushFront(&head,'b');
	linklistPushFront(&head,'c');
	linklistPushFront(&head,'d');
	linklistPrint(head);
}
void TestPopFront()
{
	Test_Header;
	printf("a\n");
	linklistPopFront(&head);
	linklistPopFront(&head);
	linklistPopFront(&head);
	linklistPrint(head);
}
void TestFind()
{
	Test_Header;
	linklistPushBack(&head,'b');
	linklistPrint(head);
	LinkNode *ret1 = linklistFind(head,'a');
	LinkNode *ret2 = linklistFind(head,'c');
	printf("find address:a->%p c->%p\n",ret1,ret2);

}
void TestInsertBefore()
{
	Test_Header;
	printf("A a b x c d e\n");
	linklistPushBack(&head,'c');
	linklistPushBack(&head,'d');
	linklistInsertBefore(&head,NULL,'e');
	linklistInsertBefore(&head,head,'A');
	LinkNode *pos = linklistFind(head,'c');
	linklistInsertBefore(&head,pos,'x');
	linklistPrint(head);

}
void TestInsertBefore1()
{
	Test_Header;
	printf("m A a b x n c d e o\n");
	linklistInsertBefore1(&head,NULL,'o');
	linklistInsertBefore1(&head,head,'m');
	LinkNode *pos = linklistFind(head,'c');
	linklistInsertBefore1(&head,pos,'n');
	linklistPrint(head);
}
void TestInsertAfter()
{
	Test_Header;
	printf("B m A a b x n c y d e o E\n");
	linklistInsertAfter(&head,NULL,'E');
	linklistInsertAfter(&head,head,'B');
	LinkNode *pos = linklistFind(head,'c');
	linklistInsertAfter(&head,pos,'y');
	linklistPrint(head);
}
void TestErase()
{
	Test_Header;
	printf("m A a b x n y d e o\n");
	linklistErase(&head,NULL);
	linklistErase(&head,head);
	LinkNode *pos = linklistFind(head,'c');
	linklistErase(&head,pos);
	linklistPrint(head);
}
void TestErase2()
{
	Test_Header;
	printf("A a b x y d e\n");
	linklistErase2(&head,NULL);
	linklistErase2(&head,head);
	LinkNode *pos = linklistFind(head,'n');
	linklistErase2(&head,pos);
	linklistPrint(head);
}
void TestReversePrint()
{
	Test_Header;
	linklistReversePrint(head);
}
void TestRemove()
{
	Test_Header;
	printf("a x y b d\n");
	LinkNode *pos = linklistFind(head,'y');
	linklistInsertAfter(&head,pos,'b');
	linklistRemove(&head,'e');
	linklistRemove(&head,'A');
	linklistRemove(&head,'b');
	linklistPrint(head);
}

void TestRemoveAll()	
{
	Test_Header;
	printf("x y b d m\n");
	LinkNode *pos = linklistFind(head,'y');
	linklistInsertAfter(&head,pos,'c');
	linklistPushBack(&head,'c');
	linklistPushBack(&head,'m');
	linklistPushBack(&head,'z');
	linklistRemoveAll(&head,'a');
	linklistRemoveAll(&head,'z');
	linklistRemoveAll(&head,'c');
	linklistPrint(head);
}
void TestSize()
{
	Test_Header;
	size_t size = linklistSize(head);
	linklistPrint(head);
	printf("size:%lu\n",size);
}
void TestEmpty()
{
	Test_Header;
	int ret1 = linklistEmpty(head);
	printf("%d\n",ret1);
}

void TestRerverse()
{
	Test_Header;
	linklistRerverse(&head);
	linklistPrint(head);
	TestSize();
}

void TestBubbleSort()
{
	Test_Header;
	linklistBubbleSort(head);
	linklistPrint(head);
}
void TestFindMidNode()
{
	Test_Header;
	linklistPrint(head);
	LinkNode *ret =	FindMidNode(head);
	printf("MidNode:%c\n\n",ret->data);
}

void TestFindLastKNode()
{
	Test_Header;
	linklistPrint(head);
	LinkNode *ret = FindLastKNode(head,2);
	printf("LastK(2)Node:%c\n\n",ret->data);
}
void TestEraseLastKNode()
{
	Test_Header;
	linklistPrint(head);
	EraseLastKNode(&head,2);
	linklistPrint(head);
}
void TestMerge()
{
	Test_Header;
	LinkNode *head1;
	LinkNode *head2;
		
	linklistInit(&head1);
	linklistPushBack(&head1,'a');
	linklistPushBack(&head1,'c');
	linklistPushBack(&head1,'e');
	linklistPrint(head1);
		
	linklistInit(&head2);
	linklistPushBack(&head2,'b');
	linklistPushBack(&head2,'d');
	linklistPushBack(&head2,'f');
	linklistPushBack(&head2,'h');
	linklistPrint(head2);
	LinkNode *ret = linklistMerge(head1,head2);
	linklistPrint(ret);
}
void TestHasCycle()
{
	Test_Header;
	linklistPrint(head);
	LinkNode *ret1 = HasCycle(head);
	if(ret1 != NULL)
	printf("ret1: = [%c|%p]\n\n",ret1->data,ret1);
	printf("new_head:a->b->c->d->e->c\n");
	LinkNode *new_head;
	linklistInit(&new_head);
	LinkNode *a = CreateNode('a');
	LinkNode *b = CreateNode('b');
	LinkNode *c = CreateNode('c');
	LinkNode *d = CreateNode('d');
	LinkNode *e = CreateNode('e');
	new_head = a;
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
	e->next = c;
	LinkNode *ret2 = HasCycle(new_head);
	if(ret2 != NULL)
	printf("ret2: = [%c|%p]\n\n",ret2->data,ret2);
}
void TestGetCycleLen()
{
	Test_Header;
	size_t ret1 = GetCycleLen(head);
	printf("CycleLen = %lu\n",ret1);
	printf("new_head:a->b->c->d->e->c\n");
	LinkNode *new_head;
	linklistInit(&new_head);
	LinkNode *a = CreateNode('a');
	LinkNode *b = CreateNode('b');
	LinkNode *c = CreateNode('c');
	LinkNode *d = CreateNode('d');
	LinkNode *e = CreateNode('e');
	new_head = a;
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
	e->next = c;
	size_t ret2 = GetCycleLen(new_head);
	printf("CycleLen = %lu\n",ret2);
}
void TestGetCycleEntry()
{
	Test_Header;
	LinkNode *ret1 = GetCycleEntry(head);
	if(ret1 != NULL)
	printf("ret1:[%c|%p]\n",ret1->data,ret1);
	printf("new_head:a->b->c->d->e->c\n");
	LinkNode *new_head;
	linklistInit(&new_head);
	LinkNode *a = CreateNode('a');
	LinkNode *b = CreateNode('b');
	LinkNode *c = CreateNode('c');
	LinkNode *d = CreateNode('d');
	LinkNode *e = CreateNode('e');
	new_head = a;
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
	e->next = c;
	LinkNode *ret2 = GetCycleEntry(new_head);
	if(ret2 != NULL)
	printf("ret2:[%c|%p]\n",ret2->data,ret2);
}
void TestHasCross()
{
	Test_Header;
	printf("new_head:a->b->c->d->(head->next)\n");
	LinkNode *new_head;
	linklistInit(&new_head);
	LinkNode *a = CreateNode('a');
	LinkNode *b = CreateNode('b');
	LinkNode *c = CreateNode('c');
	LinkNode *d = CreateNode('d');
	new_head = a;
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = head->next;
	int ret1 = HasCross(head,new_head); 
	printf("ret1 = %d\n",ret1);
	printf("new_head:a->b->c->d->NULL\n");
	d->next = NULL;
	int ret2 = HasCross(head,new_head); 
	printf("ret2 = %d\n",ret2);
}
void TestHasCrossNode()
{
	Test_Header;

	printf("new_head:a->b->c->d->(head->next)\n");
	LinkNode *new_head;
	linklistInit(&new_head);
	LinkNode *a = CreateNode('a');
	LinkNode *b = CreateNode('b');
	LinkNode *c = CreateNode('c');
	LinkNode *d = CreateNode('d');
	new_head = a;
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = head->next;

	LinkNode *ret1 = HasCrossNode(head,new_head);
	printf("expected [%c|%p],actual ",head->next->data,head->next);
	if(ret1 != NULL)
		printf("ret1: = [%c|%p]\n\n",ret1->data,ret1);
	else
		printf("null\n");
}
void TestHasCrossWithCycle()
{
	Test_Header;

	printf("new_head1:a->b->c->b\n");
	LinkNode *new_head1;
	linklistInit(&new_head1);
	LinkNode *a = CreateNode('a');
	LinkNode *b = CreateNode('b');
	LinkNode *c = CreateNode('c');
	new_head1 = a;
	a->next = b;
	b->next = c;
	c->next = b;

	printf("new_head2:x->y->z->y\n");
	LinkNode *new_head2;
	linklistInit(&new_head2);
	LinkNode *x = CreateNode('x');
	LinkNode *y = CreateNode('y');
	LinkNode *z = CreateNode('z');
	new_head2 = x;
	x->next = y;
	y->next = z;
	z->next = y;

	int ret1 = HasCrossWithCycle(new_head1,new_head2);
	printf("expected 0,actual %d\n",ret1);

	printf("new_head3:d->e->f->(new_head1->next)\n");
	LinkNode *new_head3;
	linklistInit(&new_head3);
	LinkNode *d = CreateNode('d');
	LinkNode *e = CreateNode('e');
	LinkNode *f = CreateNode('f');
	new_head3 = d;
	d->next = e;
	e->next = f;
	f->next = new_head1->next;

	int ret2 = HasCrossWithCycle(new_head1,new_head3);
	printf("expected 1,actual %d\n",ret2);
}
void TestHasCrossWithCycleNode()
{
	Test_Header;

	printf("new_head1:a->b->c->d->e->f->c\n");
	LinkNode *new_head1;
	linklistInit(&new_head1);
	LinkNode *a = CreateNode('a');
	LinkNode *b = CreateNode('b');
	LinkNode *c = CreateNode('c');
	LinkNode *d = CreateNode('d');
	LinkNode *e = CreateNode('e');
	LinkNode *f = CreateNode('f');
	new_head1 = a;
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
	e->next = f;
	f->next = c;

	printf("new_head2:h->i->j->(new_head1->next)\n");
	LinkNode *new_head2;
	linklistInit(&new_head2);
	LinkNode *h = CreateNode('h');
	LinkNode *i = CreateNode('i');
	LinkNode *j = CreateNode('j');
	new_head2 = h;
	h->next = i;
	i->next = j;
	j->next = new_head1->next;

	LinkNode *ret1 = HasCrossWithCycleNode(new_head1,new_head2);
	printf("expected:[%c|%p],actual ",new_head1->next->data,new_head1->next);
	if(ret1 != NULL)
		printf("ret1 == [%c|%p]\n",ret1->data,ret1);
	else
		printf("null\n");

	LinkNode *pos = linklistFind(new_head1,'e');
	printf("new_head3:x->y->z->(new_head1->next->next->next)\n");
	LinkNode *new_head3;
	linklistInit(&new_head3);
	LinkNode *x = CreateNode('x');
	LinkNode *y = CreateNode('y');
	LinkNode *z = CreateNode('z');
	new_head3 = x;
	x->next = y;
	y->next = z;
	z->next = pos;

	LinkNode *ret2 = HasCrossWithCycleNode(new_head1,new_head3);
	printf("expected:[%c|%p],actual ",pos->data,pos);
	if(ret2 != NULL)
		printf("ret2 == [%c|%p]\n",ret2->data,ret2);
	else
		printf("null\n");
}
void TestUnionSet()
{
	Test_Header;
	LinkNode *new_head1;
	linklistInit(&new_head1);
	LinkNode *a = CreateNode('a');
	LinkNode *d = CreateNode('d');
	LinkNode *f = CreateNode('f');
	LinkNode *i = CreateNode('i');
	new_head1 = a;
	a->next = d;
	d->next = f;
	f->next = i;
	i->next = NULL;
	linklistPrint(new_head1);

	LinkNode *new_head2;
	linklistInit(&new_head2);
	LinkNode *b = CreateNode('b');
	LinkNode *dd = CreateNode('d');
	LinkNode *h = CreateNode('h');
	LinkNode *ii = CreateNode('i');
	new_head2 = b;
	b->next = dd;
	dd->next = h;
	h->next = ii;
	ii->next = NULL;
	linklistPrint(new_head2);
	
	LinkNode *new_head = UnionSet(new_head1,new_head2);
	linklistPrint(new_head);

}
LinkNode *removeNthFromEnd(LinkNode *head,int n)
{
    if(head == NULL)
    {
        return NULL;
    }
    LinkNode *front = head;
    LinkNode *back = head;
    int  i = 0;
    for(i = n-1;i > 0;i--)
    {
        front = front->next;
    }
    LinkNode *front_back = NULL;
    while(front->next != NULL)
    {
        front = front->next;
        front_back = back;
        back = back->next;
    }
    LinkNode *to_remove = back;
    front_back->next = to_remove->next;
    return head;
}
void TestremoveNthFromEnd()
{
	Test_Header;
	LinkNode *new_head1;
	linklistInit(&new_head1);
	LinkNode *a = CreateNode('a');
	LinkNode *d = CreateNode('d');
	LinkNode *f = CreateNode('f');
	LinkNode *i = CreateNode('i');
	new_head1 = a;
	a->next = d;
	d->next = f;
	f->next = i;
	i->next = NULL;
	linklistPrint(new_head1);
    LinkNode *ret = removeNthFromEnd(new_head1,2);
    linklistPrint(ret);
}


LinkNode *rotateRight(LinkNode *head, int k)
{
    if(head == NULL)
    {
        return NULL;
    }
    LinkNode *last_node = head;
    LinkNode *new_head = head;
    int i = 0;
    for(;i < k-1;i++)
    {
        //先将last_node移动k-1步
        last_node = last_node->next;
    }
    //定义一个变量用于保存最终的链表的最后一个节点
    //也就是新链表的头结点的前一个
    LinkNode *new_tail = NULL;
    while(last_node->next !=  NULL)
    {
        //在循环中，将last_node一步一步往后移
        //同时将new_head往后移，并且在移动之前把节点保存到new_tail
        last_node = last_node->next;
        new_tail = new_head;
        new_head = new_head->next;
    }
    //循环结束，new_head就到达了倒数第k个节点，
    //该节点也就是我们新链表的头结点
    //此时new_tail在new_head的前一个节点，
    //该节点就是最终新链表的最后一个节点
    //此时last_node在旧链表的最后一个节点
    //该位置也就是我们需要将其指向旧链表的头部
    //从而完成翻转的效果
    
    //将last_node的next指向旧链表的头部
    last_node->next = head;
    //更换链表的头节点为我们找到的新的头节点
    head = new_head;
    //将我们找到的新链表的尾节点的next指向空
    new_tail->next = NULL;
    //至此翻转功能完成
    return head;
}
void TestrotateRight()
{
	Test_Header;
	LinkNode *new_head1;
	linklistInit(&new_head1);
	LinkNode *a = CreateNode('a');
	LinkNode *b = CreateNode('b');
	LinkNode *c = CreateNode('c');
	LinkNode *d = CreateNode('d');
	LinkNode *e = CreateNode('e');
	new_head1 = a;
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
    e->next = NULL;
	linklistPrint(new_head1);
    LinkNode *ret = rotateRight(new_head1,2);
    linklistPrint(ret);
}

int main()
{
	TestPushBack();
	TestPopBack();
	TestPushFront();
	TestPopFront();
	TestFind();
	TestInsertBefore();
	TestInsertBefore1();
	TestInsertAfter();
	TestErase();
	TestErase2();
	TestReversePrint();
	TestRemove();
	//TestRemoveAll();
	TestSize();
	TestEmpty();
	TestRerverse();
	TestBubbleSort();
	TestFindMidNode();
	TestFindLastKNode();
	TestEraseLastKNode();
	TestMerge();
	TestHasCycle();
	TestGetCycleLen();
	TestGetCycleEntry();
	TestHasCross();
	TestHasCrossNode();
	TestHasCrossWithCycle();
	//TestHasCrossWithCycleNode();
	TestUnionSet();
	TestJosephCycle();

    TestremoveNthFromEnd();
    
    TestrotateRight();

	return 0;
}
