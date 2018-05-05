#include<stdio.h>
#include<stdlib.h>
#include"seqlist.h"


#define head printf("\n==========%s==========\n",__FUNCTION__);


void seqlistInit(SeqList *seqlist){
	if(seqlist == NULL){
		return;
	}
	seqlist->size = 0;
}

void ifFull(SeqList *seqlist){
	if(seqlist == NULL){
		return;
	}
	if(seqlist->size >= seqlistMaxNum){
		printf("the seqlist is full\n");
	}
}

void ifEmpty(SeqList *seqlist){
	if(seqlist == NULL){
		return;
	}
	if(seqlist->size == 0){
		printf("the seqlist is empty\n");
	}
}

void seqlistPrint(SeqList *seqlist){
	int i = 0;
	if(seqlist == NULL){
		return;
	}
	ifEmpty(seqlist);
	for(;i < seqlist->size;i++){
		printf("%d ",seqlist->data[i]);
	}
	printf("\n");
}

void seqlistPushBack(SeqList *seqlist,int data){
	if(seqlist == NULL){
		return;
	}
	ifFull(seqlist);
	++seqlist->size;
	seqlist->data[seqlist->size-1] = data;
}

void seqlistPopBack(SeqList *seqlist){
	if(seqlist == NULL){
		return;
	}
	ifEmpty(seqlist);
	--seqlist->size;
}

void seqlistPushFront(SeqList *seqlist,int data){
	int i = 0;
	if(seqlist == NULL){
		return;
	}
	ifFull(seqlist);
	for(i = seqlist->size-1;i >= 0;i--){
		seqlist->data[i+1] = seqlist->data[i];
	}
	++seqlist->size;
	seqlist->data[0] = data;
}

void seqlistPopFront(SeqList *seqlist){
	int i = 0;
	if(seqlist == NULL){
		return;
	}
	ifEmpty(seqlist);
	for(;i < seqlist->size-1;i++){
		seqlist->data[i] = seqlist->data[i+1];
	}
	--seqlist->size;
}

void seqlistInsert(SeqList *seqlist,int pos,int data){
	int i = 0;
	if(seqlist == NULL){
		return;
	}
	ifFull(seqlist);
	if(pos > seqlist->size){
		return;
	}
	if(pos == 1)
		seqlistPushFront(seqlist,data);
	else if(pos == seqlist->size)
		seqlistPushBack(seqlist,data);
	else{
		for(i = seqlist->size;i >= pos;i--){
			seqlist->data[i] = seqlist->data[i-1];
		}
		++seqlist->size;
		seqlist->data[pos-1] = data;
	}
}

void seqlistErase(SeqList *seqlist,int pos){
	int i = 0;
	if(seqlist == NULL){
		return;
	}
	ifEmpty(seqlist);
	if(pos > seqlist->size){
		return;
	}
	if(pos == seqlist->size)
		seqlistPopBack(seqlist);
	if(pos == 1)
		seqlistPopFront(seqlist);
	else{
		for(i = pos-1;i < seqlist->size-1;i++){
			seqlist->data[i] = seqlist->data[i+1];
		}
		--seqlist->size;
	}
}

void seqlistSet(SeqList *seqlist,int pos,int data){
	if(seqlist == NULL){
		return;
	}
	seqlist->data[pos-1] = data;
	return;
}

void seqlistGet(SeqList *seqlist,int pos){
	if(seqlist == NULL){
		return;
	}
	printf("%d ",seqlist->data[pos-1]);
}

void seqlistFind(SeqList *seqlist,int data){
	if(seqlist == NULL){
		return;
	}
	int i = 0;
	int count = 0;
	for(;i < seqlist->size;i++){
		if(seqlist->data[i] == data){
			printf("%d ",i);
			count++;
		}
	}
	if(count == 0){
		printf("non-existent ");
		printf("\n");
	}
}
void seqlistRemove(SeqList *seqlist,int to_delete)
{
	if(seqlist == NULL)
	{
		return;
	}
	ifEmpty(seqlist);
	int i = 0;
	int count = 0;
	for(;i < seqlist->size;i++)
	{
		while(seqlist->data[i] == to_delete)
		{
			int j = 0;
			for(j = i;j < seqlist->size;j++)
			{
				seqlist->data[j] = seqlist->data[j+1];
			}
			--seqlist->size;
			count++;
		}
		if(count == 1)
			break;
	}
	if(count == 0)
	{
		printf("this value is non-existent  ");
	}
}
void seqlistRemoveAll(SeqList *seqlist,int to_delete)
{
	if(seqlist == NULL)
	{
		return;
	}
	ifEmpty(seqlist);
	int i = 0;
	int count = 0;
	for(;i < seqlist->size;i++)
	{
		if(seqlist->data[i] == to_delete)
		{
			int j = 0;
			for(j = i;j < seqlist->size;j++)
			{
				seqlist->data[j] = seqlist->data[j+1];
			}
			--seqlist->size;
			count++;
		}
	}
	if(count == 0)
	{
		printf("this value is non-existent  ");
	}
}
size_t seqlistSize(SeqList *seqlist)
{
	return seqlist->size;
}
void seqlistBubbleSort(SeqList *seqlist)
{
	if(seqlist == NULL)
	{
		return;
	}
	ifEmpty(seqlist);
	if(seqlist->size == 1)
	{
		return;
	}
	else
	{
		int bound = 0;
		int flag = 1;
		for(;bound < seqlist->size-1;bound++)
		{
			if(flag == 0)
				break;
			int cur = 0;
			for(cur = seqlist->size-1;cur > bound;cur--)
			{
				if(seqlist->data[cur-1] > seqlist->data[cur])
				{
					int tmp = 0;
					tmp = seqlist->data[cur-1];
					seqlist->data[cur-1] = seqlist->data[cur];
					seqlist->data[cur] = tmp;
					flag = 1;
				}
			}
		}
	}
}






void TestInit()
{
	head;
	printf("expect:0\n");
	seqlistInit(&seqlist);
	printf("%lu\n",seqlist.size);
}

void TestPushBack()
{
	head;
	printf("expect:1 2 3 4\n");
	seqlistPushBack(&seqlist,1);
	seqlistPushBack(&seqlist,2);
	seqlistPushBack(&seqlist,3);
	seqlistPushBack(&seqlist,4);
	seqlistPrint(&seqlist);
}

void TestPopBack()
{
	head;
	printf("expect:1 2\n");
	int i = 0;
	for(i=1;i<=2;i++)
	{
		seqlistPopBack(&seqlist);
	}
	seqlistPrint(&seqlist);
}

void TestPushFront()
{
	head;
	printf("expect: 8 7 6 5 1 2\n");
	seqlistPushFront(&seqlist,5);
	seqlistPushFront(&seqlist,6);
	seqlistPushFront(&seqlist,7);
	seqlistPushFront(&seqlist,8);
	seqlistPrint(&seqlist);
}

void TestPopFront()
{
	head;
	printf("expect:6 5 1 2\n");
	int i = 0;
	for(i = 1;i <= 2;i++)
	{
		seqlistPopFront(&seqlist);
	}
	seqlistPrint(&seqlist);
}

void TestInsert()
{
	head;
	printf("expect:0 6 4 5 1 2\n");
	seqlistInsert(&seqlist,1,0);
	seqlistInsert(&seqlist,3,4);
	seqlistPrint(&seqlist);
}

void TestErase()
{
	head;
	printf("expect:6 4 5 2\n");
	seqlistErase(&seqlist,1);
	seqlistErase(&seqlist,4);
	seqlistPrint(&seqlist);
}

void TestSet()
{
	head;
	printf("expect:6 3 5 2\n");
	seqlistSet(&seqlist,2,3);
	seqlistPrint(&seqlist);
}

void TestGet()
{
	head;
	printf("expect:2\n");
	seqlistGet(&seqlist,4);
}
void TestFind()
{
	head;
	printf("expect:3 0 non-existent\n");
	seqlistFind(&seqlist,2);
	seqlistFind(&seqlist,6);
	seqlistFind(&seqlist,4);
}
void TestRemove()
{
	head;
	seqlistPushBack(&seqlist,3);
	printf("expect: 5 2 3\n");
	seqlistRemove(&seqlist,6);
	seqlistRemove(&seqlist,3);
	seqlistPrint(&seqlist);
}

void TestRemoveAll()
{
	head;
	seqlistPushBack(&seqlist,2);
	printf("expect:this value is non-existent  5 3\n");
	seqlistRemoveAll(&seqlist,1);
	seqlistRemoveAll(&seqlist,2);
	seqlistPrint(&seqlist);
}
void TestSize()
{
	head;
	printf("expect:2\n");
	size_t size = seqlistSize(&seqlist);
	printf("size:%d\n",size);
}
void TestBubbleSort()
{
	head;
	printf("expect:0 1 3 4 5 5\n");
	seqlistPushBack(&seqlist,4);
	seqlistPushBack(&seqlist,1);
	seqlistPushBack(&seqlist,5);
	seqlistPushBack(&seqlist,0);
	seqlistBubbleSort(&seqlist);
	seqlistPrint(&seqlist);
}

int main()
{
	TestInit();

	TestPushBack();
	TestPopBack();

	TestPushFront();
	TestPopFront();

	TestInsert();
	TestErase();

	TestSet();
	TestGet();

	TestFind();

	TestRemove();
	TestRemoveAll();

	TestSize();

	TestBubbleSort();


	return 0;
}
