#pragma once 


typedef char DataType;
typedef struct Stack
{
    DataType *data;
    //有效元素个数
    int size;
    //表示data段内存中能容纳的元素个数
    int capacity;
}Stack;

typedef struct Queue
{
    Stack input;
    Stack output;
    //队列的有效元素个数
    int size;
}Queue;


//初始化函数
void QueueInit(Queue *queue);
//销毁函数
void QueueDestroy(Queue *queue);
//入栈函数
void QueuePush(Queue *queue,DataType value);
//出栈函数
void QueuePop(Queue *queue);
//取栈顶元素函数
int QueueFront(Queue *queue,DataType *front);

