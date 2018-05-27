#pragma once

#include"bit_map.h"

//此处定义了布隆过滤器的哈希函数
//把字符串转成下标
typedef uint64_t (*BloomHash)(const char*);
#define BloomHashCount 2
#define BitmapMaxCapacity 1024

typedef struct BloomFilter
{
    Bitmap bm;
    BloomHash bloom_hash[BloomHashCount];
}BloomFilter;

//初始化
void BloomFilterInit(BloomFilter *bf);
//销毁
void BloomFilterDestroy(BloomFilter *bf);
//插入数据
void BloomFilterInsert(BloomFilter *bf,const char *str);
//判断某个字符串是否存在
int BloomFilterIsExist(BloomFilter *bf,const char *str);
