#pragma once 


typedef char minStackType;
typedef struct minStack
{
    minStackType *data;
    //有效元素个数
    int size;
    //表示data段内存中能容纳的元素个数
    int capacity;
}minStack;
//初始化函数
void minStackInit(minStack *stack);
//销毁函数
void minStackDestroy(minStack *stack);
//入栈函数
void minStackPush(minStack *stack,minStackType value);
//出栈函数
void minStackPop(minStack *stack);
//取栈顶元素函数
int minStackGetTop(minStack *stack,minStackType *value);

