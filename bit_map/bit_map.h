#pragma once

#include<stdint.h>
#define BitmapDataType uint64_t

typedef struct Bitmap
{
    BitmapDataType *data;
    BitmapDataType capacity;//位图最多能够容纳的个数
}Bitmap;

//初始化
void BitmapInit(Bitmap *bm,uint64_t capacity);
//销毁
void BitmapDestroy(Bitmap *bm);
//判断某一位是否为1
int BitmapTest(Bitmap *bm,uint64_t index);
//设置某一位为1
void BitmapSet(Bitmap *bm,uint64_t index);
//设置某一位为0
void BitmapUnset(Bitmap *bm,uint64_t index);
//将位图全部位置为1
void BitmapFill(Bitmap *bm);
//将位图全部位置为0
void BitmapClear(Bitmap *bm);
