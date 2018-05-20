#pragma once

#define max_size 1000


typedef int KeyType;
typedef int ValType;
typedef char DataType;
typedef int (*HashFunc)(KeyType key);

typedef enum Stat
{
    Deleted,//删除状态
    Valid,//有效状态
    Empty,//空状态（即无效状态）
}Stat;

typedef struct HashElem
{
    KeyType key;
    ValType value;
    Stat stat;
}HashElem;

typedef struct HashTable
{
    HashElem data[max_size];
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

