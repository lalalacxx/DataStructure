#pragma once

#define max_size 1000

typedef int KeyType;
typedef int ValType;
typedef int (*HashFunc)(KeyType key);

typedef struct HashElem
{
    KeyType key;
    ValType value;
    struct HashElem *next;
}HashElem;

typedef struct HashTable
{
    //如果我们的hash桶上面的链表是一个不带头结点的链表
    //类型就用HashElem*
    //如果是一个带头结点的链表
    //类型就用HashElem
    HashElem *data[max_size];
    int size;//有效元素个数
    HashFunc func;//哈希函数
}HashTable;

//初始化
void HashInit(HashTable *ht,HashFunc Hash_func);
//销毁
void HashDestroy(HashTable *ht);
//插入数据
void HashInsert(HashTable *ht,KeyType key,ValType value);
//查找数据
int HashFind(HashTable *ht,KeyType key,ValType *value);
//删除数据
void HashRemove(HashTable *ht,KeyType key);
