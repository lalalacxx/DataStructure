#include<stdio.h>
#include<stdlib.h>
#include "hash.h"

#define Test_Header \
    printf("\n==========%s==========\n",__FUNCTION__);

int Hash_func(KeyType key)
{
    return key%max_size;
}
HashElem *CreateElem(KeyType key, ValType value)
{
    HashElem *new_elem = (HashElem *)malloc(sizeof(HashElem));
    new_elem->key = key;
    new_elem->value = value;
    new_elem->next = NULL;
    return new_elem;
}
void DestroyElem(HashElem *elem)
{
    free(elem);
    return;
}
//初始化
void HashInit(HashTable *ht,HashFunc Hash_func)
{
    if(ht == NULL)
    {
        //非法输入
        return;
    }
    ht->size = 0;
    ht->func = Hash_func;
    int i = 0;
    for(;i < max_size;i++)
    {
        ht->data[i] = NULL;
    }
    return;
}
void TestInit()
{
    Test_Header;
    HashTable ht;
    HashInit(&ht,Hash_func);
    printf("expect size = 0,actual size = %d\n",ht.size);
    printf("expect func = %p,actual func = %p\n",Hash_func,ht.func);
}
//销毁
void HashDestroy(HashTable *ht)
{
    if(ht == NULL)
    {
        //非法输入
        return;
    }
    ht->size = 0;
    ht->func = NULL;
    //遍历所有的链表并进行释放
    int i = 0;
    for(;i < max_size;i++)
    {
        HashElem *cur = ht->data[i];
        while(cur != NULL)
        {
            HashElem *next = cur->next;
            DestroyElem(cur);
            cur = next;
        }
    }
    return;
}
HashElem *HashBucketFind(HashElem *head,KeyType to_find)
{
    HashElem *cur = head;
    for(;cur != NULL;cur = cur->next)
    {
        if(cur->key == to_find)
        {
            //在当前链表中找到了该元素
            return cur;
        }
    }
    //在当前链表中没找到该元素
    return NULL;
}
//插入数据
void HashInsert(HashTable *ht,KeyType key,ValType value)
{
    if(ht == NULL)
    {
        //非法输入
        return;
    }
    if(ht->size >= 0.8*max_size)
    {
        //此时哈希表已经达到了负载因子的上限
        //不能再继续插入元素
        return;
    }
    //可以继续插入元素
    //先由key计算出offset
    int offset = ht->func(key);
    //在offset对应的链表中查找当前待插入的元素是否已经存在
    HashElem *ret = HashBucketFind(ht->data[offset],key);
    if(ret != NULL)
    {
        //走到这里说明待插入的元素已经存在
        //约定哈希表中不存在重复的元素
        //插入失败直接返回
        return;
    }
    else
    {
        //不存在重复的元素
        //可以插入（头插法）
        HashElem *new_elem = CreateElem(key,value);
        //将新的元素头插法插入当前链表中
        new_elem->next = ht->data[offset];
        //更新链表的头结点为新插入的元素
        ht->data[offset] = new_elem;
        //别忘了将哈希表的有效元素个数+1
        ++ht->size;
    }
}
void HashPrint(HashTable *ht,const char *msg)
{
    printf("[%s]\n",msg);
    int i = 0;
    for(;i < max_size;i++)
    {
        if(ht->data[i] != NULL)
        {

            printf("i = %d\n",i);
            HashElem *cur = ht->data[i];
            for(;cur != NULL;cur = cur->next)
            {
                printf("[%d,%d] ",cur->key,cur->value);
            }
            printf("\n");
        }//if结束
    }//for结束
}
void TestInsert()
{
    Test_Header;
    HashTable ht;
    HashInit(&ht,Hash_func);
    HashInsert(&ht,1,1);
    HashInsert(&ht,1,10);
    HashInsert(&ht,2,20);
    HashInsert(&ht,1000,100);
    HashInsert(&ht,2000,200);
    HashPrint(&ht,"插入5个元素");
}

//查找数据
int HashFind(HashTable *ht,KeyType key,ValType *value)
{
    if(ht == NULL || value == NULL)
    {
        //非法输入
        return 0;
    }
    if(ht->size == 0)
    {
        //空哈希表
        return 0;
    }
    //由key值计算出offset
    int offset = ht->func(key);
    //从offset指向的链表位置开始
    //遍历链表查找
    HashElem *ret = HashBucketFind(ht->data[offset],key);
    if(ret == NULL)
    {
        //没找到
        return 0;
    }
    else
    {
        //找到了
        *value = ret->value;
        return 1;
    }
}
void TestFind()
{
    Test_Header;
    HashTable ht;
    HashInit(&ht,Hash_func);
    HashInsert(&ht,1,1);
    HashInsert(&ht,1,10);
    HashInsert(&ht,2,20);
    HashInsert(&ht,1000,100);
    HashInsert(&ht,2000,200);
    ValType value;
    int ret = HashFind(&ht,1000,&value);
    printf("查找数据为1000的元素结果为：");
    printf("expect ret = 1,actual ret = %d；",ret);
    printf("expect value = 100,actual value = %d\n",value);
    ret = HashFind(&ht,3000,&value);
    printf("查找数据为3000的元素结果为：");
    printf("expect ret = 0,actual ret = %d\n",ret);
}
int HashBucketFindEx(HashElem *head,KeyType to_find,\
                     HashElem **pre_node,HashElem **cur_node)
{
    HashElem *pre = NULL;
    HashElem *cur = head;
    for(;cur != NULL;pre = cur,cur = cur->next)
    {
        if(cur->key == to_find)
        {
            //找到了，跳出循环
            break;
        }
    }
    if(cur == NULL)
    {
        //走到这儿说明是链表遍历完了
        //没找到
        return 0;
    }
    *pre_node = pre;
    *cur_node = cur;
    return 1;
}
//删除数据
void HashRemove(HashTable *ht,KeyType key)
{
    if(ht == NULL)
    {
        //非法输入
        return;
    }
    if(ht->size == 0)
    {
        //空哈希表
        return;
    }
    //由key计算出offset值
    int offset = ht->func(key);
    //在当前offset对应的链表下
    //查找待删除的元素是否存在
    HashElem *pre = NULL;
    HashElem *cur = NULL;
    int ret = HashBucketFindEx(ht->data[offset],key,&pre,&cur);
    if(ret == 0)
    {
        //当前链表下没有找到待删除的元素
        return;
    }
    else
    {
        //找到了，可以进行删除
        if(pre == NULL)
        {
            //要删除的元素是链表的头结点
            //更新当前链表的头结点
            ht->data[offset] = cur->next;
        }
        else
        {
            //pre的下一个元素本来指向的是cur(待删除的元素)
            //cur如果要被删除，则pre指向的应该是cur的下一个元素
            pre->next = cur->next;
        }
        DestroyElem(cur);
        //将哈希表的有效元素个数-1
        --ht->size;
    }//else（ret=1）结束
}
void TestRemove()
{
    Test_Header;
    HashTable ht;
    HashInit(&ht,Hash_func);
    HashInsert(&ht,1,1);
    HashInsert(&ht,1,10);
    HashInsert(&ht,2,20);
    HashInsert(&ht,1000,100);
    HashInsert(&ht,2000,200);
    HashRemove(&ht,2);
    HashPrint(&ht,"删除数据为2的元素后的结果：");
    HashRemove(&ht,20);
    HashPrint(&ht,"删除数据为20的元素后的结果：");
}
int main()
{
    TestInit();
    TestInsert();
    TestFind();
    TestRemove();
    return 0;
}
