#pragma once

#define max_size 1000

typedef char DataType;
typedef int (*Compare)(DataType a,DataType b);

typedef struct Heap
{
    DataType data[max_size];
    int size;//有效元素个数
    Compare cmp;//判断大小堆的函数的函数指针
}Heap;

//初始化
void HeapInit(Heap *heap,Compare cmp);
//销毁
void HeapDestroy(Heap *heap);
//往堆中插入元素
void HeapInsert(Heap *heap,DataType to_insert);
//取堆顶元素
int HeapRoot(Heap *heap,DataType *root);
//删除堆顶元素
void HeapErase(Heap *heap);
//堆的创建
void HeapCreate(Heap *heap,DataType arr[],int len);
//堆排序
void HeapSort(DataType arr[],int len);
