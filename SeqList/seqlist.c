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
//判断线性表是否为满，满则返回1，不满返回0，非法输入返回-1
int ifFull(SeqList *seqlist){
	if(seqlist == NULL)
        //非法输入
		return -1;
	if(seqlist->size >= seqlistMaxNum)
        return 1;
    return 0;
}
//判断线性表是否为空，为空返回1，不为空返回0,非法输入返回-1
int ifEmpty(SeqList *seqlist){
	if(seqlist == NULL)
		return -1;
	if(seqlist->size == 0)
		return 1;
    return 0;
}

void seqlistPrint(SeqList *seqlist){
	int i = 0;
	if(seqlist == NULL){
		//非法输入
        return;
	}
    //如果为空则不需要打印
	if(ifEmpty(seqlist) == 1)
        return;
	for(;i < seqlist->size;i++){
		printf("%d ",seqlist->data[i]);
	}
	printf("\n");
}

//尾插
void seqlistPushBack(SeqList *seqlist,int data){
	if(seqlist == NULL){
		return;
	}
    //如果线性表满了则不能插入
	if(ifFull(seqlist) == 1)
        return;
    //可以插入    则将线性表的有效元素个数+1
	++seqlist->size;
    //在尾插一个元素
	seqlist->data[seqlist->size-1] = data;
}
//尾删
void seqlistPopBack(SeqList *seqlist){
	if(seqlist == NULL){
		return;
	}
    //如果线性表是空的则没有元素可以删除
	if(ifEmpty(seqlist) == 1)
        return;
    //可以删除则就将线性表中的有效元素个数-1即可
	--seqlist->size;
}
//头插
void seqlistPushFront(SeqList *seqlist,int data){
	int i = 0;
	if(seqlist == NULL){
		return;
	}
    //如果线性表满了则不能插入
	if(ifFull(seqlist) == 1)
        return;
	//先将所有元素往后移动一个位置
    for(i = seqlist->size-1;i >= 0;i--){
		seqlist->data[i+1] = seqlist->data[i];
	}
    //再将有效元素个数+1
	++seqlist->size;
    //进行头插
	seqlist->data[0] = data;
}
//头删
void seqlistPopFront(SeqList *seqlist){
	int i = 0;
	if(seqlist == NULL){
		return;
	}
    //如果线性表为空则没有元素可以删除
	if(ifEmpty(seqlist) == 1)
        return;
    //可以删除
    //则将首元素之后的所有元素往前移动一个位置
	for(;i < seqlist->size-1;i++){
		seqlist->data[i] = seqlist->data[i+1];
	}
    //在将有效元素个数-1即可
	--seqlist->size;
}
//插入
void seqlistInsert(SeqList *seqlist,int pos,int data){
	size_t i = 0;
	if(seqlist == NULL){
		return;
	}
    //如果线性表满了则不能插入
	if(ifFull(seqlist) == 1)
        return;
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
	printf("%d\n",seqlist.size);
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
