#include<stdio.h>
#include"hash.h"

#define Test_Header \
    printf("\n==========%s==========\n",__FUNCTION__);

int Hash_func(KeyType key)
{
    return key%max_size;
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
        ht->data[i].stat = Empty;
    }
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
    //先将表中的每一个位置都置为无效状态
    int i = 0;
    for(;i < max_size;i++)
    {
        ht->data[i].stat = Empty;
    }
    //再将有效元素个数清0
    ht->size = 0;
    //哈希函数指向空
    ht->func = NULL;
}
//插入数据
void HashInsert(HashTable *ht,KeyType key,ValType value)
{
    if(ht == NULL)
    {
        //非法输入
        return;
    }
    //判定当前的hash表能否继续插入
    //假设负载因子为0.8
    if(ht->size >= 0.8*max_size)
    {
        //当前hash表已经达到负载因子的上限，不能再继续插入
        return;
    }
    //由key计算offset(由hash函数计算出的存放位置的下标)
    int offset = ht->func(key);
    //但是该位置可能之前已经被别的数据占据了
    //所以我们需要先判断当前计算出的位置是否能放入当前数据
    //如果不能就从offset位置往后查找
    while(1)
    {
        //先判断当前计算出的位置是否能放入当前数据
        if(ht->data[offset].stat != Valid)
        {
            //一旦找到一个位置不是有效位置
            //就可以将该数据插入
            //这就是处理哈希冲突的线性探测法
            ht->data[offset].key = key;
            ht->data[offset].value = value;
            //插入完成以后将该位置置成有效状态
            ht->data[offset].stat = Valid;
            //哈希表有效元素个数+1
            ++ht->size;
            return;
        }
        //走到这里说明当前计算出的位置
        //不能放置当前待插入的数据
        //判断当前位置的元素是否和待插入的元素一样
        else if(ht->data[offset].stat == Valid \
                && ht->data[offset].key == key)
        {
            //说明存在相同元素
            //我们这里约定该哈希表中不存在重复元素
            //则直接插入失败返回
            return;
        }
        //则更新offset值继续下一次循环往后查找
        else
        {
            ++offset;
            if(offset >= max_size)
            {
                //如果查找时offset走到了哈希表的末尾
                //还没有找到一个可插入的位置
                //则将其置为0，从头开始往后继续查找
                offset = 0;
            }
        }
    }
}
void HashPrint(HashTable *ht,const char *msg)
{
    printf("[%s]\n",msg);
    int i = 0;
    for(;i < max_size;i++)
    {
        if(ht->data[i].stat == Valid)
        {
            printf("(%d:%d,%d) ",i,ht->data[i].key,ht->data[i].value);
        }
    }
    printf("\n");
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
    if(ht == NULL)
    {
        //非法输入
        return 0;
    }
    //判断当前hash表中是否有有效元素
    if(ht->size == 0)
    {
        //空哈希表
        return 0;
    }
    //由key值计算出offset
    int offset = ht->func(key);
    //从offset开始往后查找
    while(1)
    {
        //在当前位置存放的是有效数据的前提下
        if(ht->data[offset].stat == Valid)
        {
            if(ht->data[offset].key == key)
            {
                //找到了
                *value = ht->data[offset].value;
                return 1;
            }
            //当前位置不是待查找的元素
            //则更新offset的值继续查找
            else
            {
                ++offset;
                if(offset >= max_size)
                {
                    offset = 0;
                }
            }
        }
        else if(ht->data[offset].stat == Empty)
        {
            //说明带查找的元素不存在与hash表中
            //查找失败返回
            return 0;
        }
    }//while循环结束
    return 0;
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
    //由key值计算出offset
    int offset = ht->func(key);
    //从offset开始往后找
    while(1)
    {
        if(ht->data[offset].stat == Valid \
           && ht->data[offset].key == key)
        {
            //找到了待删除的元素
            //直接将该位置的状态置为被删除状态即可
            ht->data[offset].stat = Deleted;
            //将hash表中有效元素个数-1
            --ht->size;
            return;
        }
        else if(ht->data[offset].stat == Empty)
        {
            //走到这里说明该元素不存在
            return;
        }
        else
        {
            //走到这里说明当前offset位置的值不是我们想要删除的
            //则更新offset值继续查找
            ++offset;
            if(offset >= max_size)
            {
                offset = 0;
            }
        }
    }//while循环结束
    return;
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
