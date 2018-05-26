#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"bit_map.h"

#define Test_Header printf("\n==========%s==========\n",__FUNCTION__);

//初始化
void BitmapInit(Bitmap *bm,uint64_t capacity)
{
    if(bm == NULL)
    {
        //非法输入
        return;
    }
    //capacity:指定位图最多能够容纳多少位
    //比如：capacity=100，应该容纳2个元素
    //比如：capacity=200，应该容纳4个元素
    //比如：capacity=300，应该容纳5个元素
    //比如：capacity=N，N/(sizeof(uint64_t)*8)+1
    bm->capacity = capacity;
    //size表示我们申请内存时对应的数组元素个数
    uint64_t size = capacity/(sizeof(uint64_t)*8)+1;
    bm->data = (BitmapDataType*)malloc(sizeof(BitmapDataType)*size);
    memset(bm->data,0,sizeof(BitmapDataType)*size);
    return;
}
//测试一下
void TestInit()
{
    Test_Header;
    Bitmap bm;
    BitmapInit(&bm,100);
    printf("expected bm->capacity = 100,actual bm->capacity = %lu\n",bm.capacity);
}
//销毁
void BitmapDestroy(Bitmap *bm)
{
    if(bm == NULL)
    {
        //非法输入
        return;
    }
    bm->capacity = 0;
    free(bm->data);
    return;
}
void GetOffset(uint64_t index,uint64_t *n,uint64_t *offset)
{
    //n是数组中的哪一个元素
    *n = index/(sizeof(BitmapDataType)*8);
    //offset是该元素中的bit位中的哪一位
    *offset = index%(sizeof(BitmapDataType)*8);
    return;
}
//检测某一位是否为1，返回1表示该位为1，返回0表示该位为0
int BitmapTest(Bitmap *bm,uint64_t index)
{
    if(bm == NULL || index >= bm->capacity)
    {
        //非法输入
        return 0;
    }
    uint64_t n,offset;
    //找到需要判断的位置对应于我们数组中的哪一个元素的哪一位
    GetOffset(index,&n,&offset);
    //先将1左移offset位，结束以后相应位即为1
    //再将其与对应的数组中的元素按位与
    //0和1与为0,1和1与为1
    //按位与运算完毕就可以知道相应位是否为1
    uint64_t ret = bm->data[n] & (0x1ul << offset);
    return ret > 0 ? 1:0;
}
//将某一位设置为1
void BitmapSet(Bitmap *bm,uint64_t index)
{
    if(bm == NULL || index >= bm->capacity)
    {
        //非法输入
        return;
    }
    uint64_t n,offset;
    //找到需要判断的位置对应于我们数组中的哪一个元素的哪一位
    GetOffset(index,&n,&offset);
    //将1左移offset位，移动结束以后，需要设置的位置即为1，其余位置为0
    //再将其与数组中对应的元素按位或
    //0和1或是1,1和1或是1
    //有这样的规则，按位或就不会影响其他位的状态
    bm->data[n] |= (0x1ul << offset);
}
//将某一位设置为0
void BitmapUnset(Bitmap *bm,uint64_t index)
{
    if(bm == NULL || index >= bm->capacity)
    {
        //非法输入
        return;
    }
    uint64_t n,offset;
    //找到需要判断的位置对应于我们数组中的哪一个元素的哪一位
    GetOffset(index,&n,&offset);
    //先将1左移offset位，那么相应位变为1其余位为0
    //再取反，则相应位为0，其余位为1
    //在将该结果与对应的数组元素进行按位与
    //1和0与结果为0,0和0与结果为0（达到将某一位置为0的效果）
    //有这样的规则，则我们的按位与操作不会影响其他的位的状态
    bm->data[n] &= ~(0x1ul << offset);
}
//测试一下
void TestSetAndUnset()
{
    Test_Header;
    Bitmap bm;
    BitmapInit(&bm,100);
    printf("[将位图某一位置为1函数测试结果]\n");
    //将第二位设置为1
    BitmapSet(&bm,2);
    //非法测试，将第100为设置为1
    BitmapSet(&bm,100);
    int ret1 = BitmapTest(&bm,2);
    int ret2 = BitmapTest(&bm,100);
    printf("expected ret1 = 1,actual ret1 = %d\n",ret1);
    printf("expected ret2 = 0,actual ret2 = %d\n",ret2);
    printf("[将位图某一位置为0函数测试结果]\n");
    //将第二位设置为0
    BitmapUnset(&bm,2);
    //非法测试，将第100位设置为0
    BitmapUnset(&bm,100);
    int ret3 = BitmapTest(&bm,2);
    int ret4 = BitmapTest(&bm,100);
    printf("expected ret3 = 0,actual ret3 = %d\n",ret3);
    printf("expected ret4 = 0,actual ret4 = %d\n",ret4);
}
//将位图全部置为1
void BitmapFill(Bitmap *bm)
{
    if(bm == NULL)
    {
        //非法输入
        return;
    }
    uint64_t size = bm->capacity/(sizeof(BitmapDataType)*8)+1;
    memset(bm->data,0xff,sizeof(BitmapDataType)*size);
}
//将位图全部置为0
void BitmapClear(Bitmap *bm)
{
    if(bm == NULL)
    {
        //非法输入
        return;
    }
    uint64_t size = bm->capacity/(sizeof(BitmapDataType)*8)+1;
    memset(bm->data,0x0,sizeof(BitmapDataType)*size);
}
void TestClearAndFill()
{
    Test_Header;
    Bitmap bm;
    BitmapInit(&bm,100);
    printf("[将位图全部置为1函数测试结果]\n");
    //将位图全部置为1函数测试
    BitmapFill(&bm);
    int ret1 = BitmapTest(&bm,50);
    printf("expected ret1 = 1,actual ret1 = %d\n",ret1);
    ret1 = BitmapTest(&bm,0);
    printf("expected ret1 = 1,actual ret1 = %d\n",ret1);
    ret1 = BitmapTest(&bm,99);
    printf("expected ret1 = 1,actual ret1 = %d\n",ret1);
    printf("[将位图全部置为0函数测试结果]\n");
    //将位图全部清0函数测试
    BitmapClear(&bm);
    int ret2 = BitmapTest(&bm,50);
    printf("expected ret2 = 0,actual ret2 = %d\n",ret2);
    ret2 = BitmapTest(&bm,0);
    printf("expected ret2 = 0,actual ret2 = %d\n",ret2);
    ret2 = BitmapTest(&bm,99);
    printf("expected ret2 = 0,actual ret2 = %d\n",ret2);
}
int main()
{
    TestInit();
    TestSetAndUnset();
    TestClearAndFill();
    return 0;
}
