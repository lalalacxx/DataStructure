#include<stdio.h>
#include"bit_map.h"
#include"bloom_filter.h"
#include"bloom_hash.h"
//初始化
void BloomFilterInit(BloomFilter *bf)
{
    if(bf == NULL)
    {
        //非法输入
        return;
    }
    //将bloom_filter中的位图初始化
    BitmapInit(&bf->bm,10000);
    //初始化两个哈希函数
    bf->bloom_hash[0] = SDBMHash;
    bf->bloom_hash[1] = BKDRHash;
    return;
}
//销毁
void BloomFilterDestroy(BloomFilter *bf)
{
    if(bf == NULL)
    {
        //非法输入
        return;
    }
    //销毁位图
    BitmapDestroy(&bf->bm);
    //将两个哈希函数指向空
    bf->bloom_hash[0] = NULL;
    bf->bloom_hash[1] = NULL;
    return;
}
//插入数据
void BloomFilterInsert(BloomFilter *bf,const char *str)
{
    if(bf == NULL || str == NULL)
    {
        //非法输入
        return;
    }
    size_t i = 0;
    for(;i < BloomHashCount;i++)
    {
        //通过循环由两个哈希函数可以算出两个哈希地址
        uint64_t hash = bf->bloom_hash[i](str)%BitmapMaxCapacity;
        //将每一个哈希地址置为1
        BitmapSet(&bf->bm,hash);
    }
    return;
}
//判断某个字符串是否存在
int BloomFilterIsExist(BloomFilter *bf,const char *str)
{
    if(bf == NULL || str == NULL)
    {
        //非法输入
        return 0;
    }
    size_t i = 0;
    for(;i < BloomHashCount;i++)
    {
        //通过循环由两个哈希函数可以算出两个哈希地址
        uint64_t hash = bf->bloom_hash[i](str)%BitmapMaxCapacity;
        //检测算出的哈希地址是否为1（即检测待判断的数据是否存在）
        int ret = BitmapTest(&bf->bm,hash);
        //如果一旦有其中一个地址不为1
        //返回了0，就说明该数据不存在
        if(ret == 0)
        {
            return 0;
        }
    }
    //走到这说明两个哈希地址处的值均为1
    //说明该数据就存在
    return 1;
}
void Test()
{
    BloomFilter bf;
    //初始化
    BloomFilterInit(&bf);
    //插入5个字符串
    BloomFilterInsert(&bf,"hello world");
    BloomFilterInsert(&bf,"hello today");
    BloomFilterInsert(&bf,"hi everybody");
    BloomFilterInsert(&bf,"how are you?");
    BloomFilterInsert(&bf,"I am fine!");
    //检测某个字符串是否存在
    int ret1 = BloomFilterIsExist(&bf,"how are you?");
    printf("\nexpected ret1 = 1,actual ret1 = %d\n",ret1);
    int ret2 = BloomFilterIsExist(&bf,"where are you?");
    printf("expected ret2 = 0,actual ret2 = %d\n\n",ret2);
}
int main()
{
    Test();
    return 0;
}
