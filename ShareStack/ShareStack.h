#pragma once
#define max_size 10000

typedef char DataType;

typedef struct ShareStack
{
    DataType data[max_size];
    int top1;
    int top2;
}ShareStack;

//栈1的初始化
void ShareStack1Init(ShareStack *shareSatck);
//栈2的初始化
void ShareStack2Init(ShareStack *shareSatck);
//栈1的销毁
void ShareStack1Destroy(ShareStack *shareSatck);
//栈2的销毁
void ShareStack2Destroy(ShareStack *shareSatck);
//栈1的入栈操作函数
void ShareStack1Push(ShareStack *shareSatck,DataType value);
//栈2的入栈操作函数
void ShareStack2Push(ShareStack *shareSatck,DataType value);
//栈1的出栈操作函数
void ShareStack1Pop(ShareStack *shareSatck);
//栈2的出栈操作函数
void ShareStack2Pop(ShareStack *shareSatck);
//取栈1的栈顶元素操作函数
int ShareStack1Top(ShareStack *shareSatck,DataType *value);
//取栈2的栈顶元素操作函数
int ShareStack2Top(ShareStack *shareSatck,DataType *value);
