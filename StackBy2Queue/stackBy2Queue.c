#include<stdio.h>
#include<stdlib.h>
#include"stackBy2Queue.h"

#define Test_Header printf("\n==========%s==========\n",__FUNCTION__);

//队列初始化函数
void QueueInit(Queue *queue)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
}
//队列销毁函数
void QueueDestroy(Queue *queue)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
}
//入队列操作函数
void QueuePush(Queue *queue,DataType value)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    if(queue->size >= max_size)
    {
        //队列满了
        return;
    }
    queue->data[queue->tail++] = value;
    queue->size++;
    if(queue->tail > max_size)
    {
        //如果tail走到了队列的尾部
        queue->tail = 0;
    }
}
//出队列操作函数
void QueuePop(Queue *queue)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    if(queue->size == 0)
    {
        //空队列
        return;
    }
    if(queue->head >= max_size)
    {
        //如果head走到了队列的最后一个元素
        //呢出队列以后继续回到队列一开始的地方
        //就相当于是将最后一个元素出对队列
        queue->head = 0;
    }
    //否则直接将head往后移动一步
    queue->head++;
    //将对列元素个数-1
    queue->size--;
    if(queue->size == 0)
    {
        queue->head = 0;
        queue->tail = 0;
    }
}
//取队首元素函数
int QueueGetTop(Queue *queue,DataType *value)
{
    if(queue == NULL)
    {
        //非法输入
        return 0; 
    }
    if(queue->size == 0)
    {
        //空队列
        return 0;
    }
    *value = queue->data[queue->head];
    return 1;
}
void Print(Queue *queue)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    if(queue->size == 0)
    {
        return;
    }
    if(queue->head < queue->tail)
    {
        int i = queue->head;
        for(;i < queue->tail;i++)
        {
            printf("%c ",queue->data[i]);
        }
    }
    else
    {
        int i = queue->head;
        while(queue->head < max_size)
        {
            printf("%c ",queue->data[queue->head]);
            queue->head++;
        }
        queue->head = 0;
        for(;i < queue->tail;i++)
        {
            printf("%c ",queue->data[i]);
        }
    }
    printf("\n\n");
}

//栈初始化函数
void StackInit(Stack *stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    QueueInit(&stack->queue1);
    QueueInit(&stack->queue2);
    stack->size = 0;
}
//栈销毁函数
void StackDestroy(Stack *stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    QueueDestroy(&stack->queue1);
    QueueDestroy(&stack->queue2);
    stack->size = 0;
}
//入栈操作函数
void StackPush(Stack *stack,DataType value)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->queue1.size != 0)
    {
        QueuePush(&stack->queue1,value);
    }
    else
    {
       QueuePush(&stack->queue2,value);
    }
    stack->size++;
}
//出栈操作函数
void StackPop(Stack *stack)
{
    if(stack == NULL)
     {
         //非法输入
         return;
     }
    if(stack->size == 0)
    {
        //空栈
        return;
    }
    Queue *from = NULL;
    Queue *to = NULL;
    //将from指向有元素的队列，to指向没有元素的队列
    if(stack->queue1.size != 0)
    {
        from = &stack->queue1;
        to = &stack->queue2;
    }
    else
    {
        from = &stack->queue2;
        to = &stack->queue1;
    }
    //将from中的元素到腾到to中（但是fro中必须要留下最后一个元素用于最后的出队列也就是出栈操作）
    while(from->size != 1)
    {
        DataType top;
        QueueGetTop(from,&top);
        QueuePop(from);
        QueuePush(to,top);
    }
    //此时from中就剩下最后一个元素将其出队列也就完成出栈操作
    QueuePop(from);
    stack->size--;
}
//取栈顶元素函数
int StackGetTop(Stack *stack,DataType *value)
{
    if(stack == NULL || value == NULL)
    {
        //非法输入
        return 0;
    }
    if(stack->size == 0)
    {
        //空栈
        return 0;
    }
    Queue *from = NULL;
    Queue *to = NULL;
    //将from指向有元素的队列，to指向没有元素的队列
    if(stack->queue1.size != 0)
    {
        from = &stack->queue1;
        to = &stack->queue2;
    }
    else
    {
        from = &stack->queue2;
        to = &stack->queue1;
    }
    //将from中的元素到腾到to中（但是from中必须要留下最后一个元素用于最后的出队列也就是出栈操作）
    while(from->size != 1)
    {
        DataType top;
        QueueGetTop(from,&top);
        QueuePop(from);
        QueuePush(to,top);
    }
    int ret = QueueGetTop(from,value);
    QueuePop(from);
    QueuePush(to,*value);
    return ret;
}
//打印函数便于观察结果
void PrintStackElem(Stack *stack,const char *msg)
{
    printf("[%s]\n",msg);
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->size == 0)
    {
        //空栈
        return;
    }
    Queue *print = NULL;
    if(stack->queue1.size == 0)
    {
        print = &stack->queue2;
    }
    else
    {
        print = &stack->queue1;
    }
    Print(print);
}



//以下为测试函数
void TestStackBy2Queue()
{
    Test_Header;
    Stack stack;

    //初始化
    StackInit(&stack);
    //入栈函数测试
    StackPush(&stack,'a');
    StackPush(&stack,'b');
    StackPush(&stack,'c');
    StackPush(&stack,'d');
    PrintStackElem(&stack,"入栈4个元素expected:a b c d");
    //取栈顶元素测试
    DataType top;
    int ret = StackGetTop(&stack,&top);
    printf("expected ret = 1,actual ret = %d\n",ret);
    printf("expected top = d,actual top = %c\n",top);
    //出栈函数测试
    StackPop(&stack);
    StackPop(&stack);
    PrintStackElem(&stack,"出栈两个元素之后expected: a b");
    //取栈顶元素函数测试2  
    ret = StackGetTop(&stack,&top);
    printf("expected ret = 1,actual ret = %d\n",ret);
    printf("expected top = b,actual top = %c\n",top);
    
    StackPop(&stack);
    StackPop(&stack);
    PrintStackElem(&stack,"将剩下的两个元素出栈之后expected:");
    //取栈顶元素函数测试3
    ret = StackGetTop(&stack,&top);
    printf("expected ret = 0,actual ret = %d\n",ret);

    StackDestroy(&stack);
}




int main()
{
    TestStackBy2Queue();
    return 0;
}
