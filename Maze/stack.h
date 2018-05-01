#pragma once

typedef struct Point
{
    int row;
    int col;
}Point;

typedef Point DataType;
typedef struct Stack
{
    DataType *data;
    int size;
    int capacity;
}Stack;


//栈初始化函数
void StackInit(Stack *stack);
//栈销毁函数
void StackDestroy(Stack *stack);
//入栈操作函数
void StackPush(Stack *stack,DataType value);
//出栈操作函数
void StackPop(Stack *stack);
//取栈顶元素操作函数
int StackTop(Stack *stack,DataType *value);
