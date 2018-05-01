#pragma once

#define max_size 1000

typedef char DataType;

typedef struct Queue
{
    DataType data[max_size];
    int head;
    int tail;
    int size;
}Queue;

typedef struct Stack
{
    Queue queue1;
    Queue queue2;
    int size;
}Stack;
//初始化函数
void StackInit(Stack *stack);
//销毁函数
void StackDestroy(Stack *stack);
//入栈操作函数
void StackPush(Stack *stack,DataType value);
//出栈操作函数
void StackPop(Stack *stack);
//取栈顶元素函数
int StackGetTop(Stack *stack,DataType *value);
