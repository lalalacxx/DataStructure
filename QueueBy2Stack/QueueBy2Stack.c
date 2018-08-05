#include<stdio.h>
#include<stdlib.h>
#include"QueueBy2Stack.h"

#define Test_Header printf("\n==========%s==========\n",__FUNCTION__);

//栈初始化
void StackInit(Stack *stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    stack->size = 0;
    stack->capacity = 1000;
    stack->data = (DataType*)malloc(stack->capacity * sizeof(DataType));
}
//栈销毁函数
void StackDestroy(Stack *stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    free(stack->data);
    stack->data = NULL;
    stack->size = 0;
    stack->capacity = 0;
}
//入栈操作
void StackPush(Stack *stack,DataType value)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->size >= stack->capacity)
    {
        //栈满了
        return;
    }
    //栈没满
    stack->data[stack->size++] = value;
}
//出栈操作
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
    stack->size--;
}
//取栈顶元素函数
int StackGetTop(Stack *stack,DataType *value)
{
    if(stack == NULL)
    {
        //非法输入
        return 0;
    }
    if(stack->size == 0)
    {
        //空栈
        return 0;
    }
    *value = stack->data[stack->size-1];
    return 1;
}

void Print(Stack *stack)
{
    if(stack == NULL)
    {
        return;
    }
    if(stack->size == 0)
    {
        //空栈
        return;
    }
    int i = 0;
    for(;i < stack->size;i++)
    {
        printf("%c ",stack->data[i]);
    }
    printf("\n\n");
}
//队列初始化函数
void QueueInit(Queue *queue)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    StackInit(&queue->input);
    StackInit(&queue->output);
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
    StackDestroy(&queue->input);
    StackDestroy(&queue->output);
    queue->size = 0;
}
//入队列函数
void QueuePush(Queue *queue,DataType value)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    //将output（用于出队列的栈）中的元素倒腾到input（用于入队列的栈）中
    while(1)
    {
        DataType front;
        int ret = StackGetTop(&queue->output,&front);
        //如果取栈顶元素返回了0，则说明output(用于出队列的栈)中已经没有元素了
        if(ret == 0)
        {
            break;
        }
        //将output中的元素出栈
        StackPop(&queue->output);
        //将output的栈首元素插入到input中
        StackPush(&queue->input,front);
    }
    //倒腾完成以后再将要插入的新元素插入到input栈中
    StackPush(&queue->input,value);
    //将队列元素个数+1
    queue->size++;
}
//出队列函数
void QueuePop(Queue *queue)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    //将input（用于入队列的栈）中的元素倒腾到output（用于出队列的栈）中
    while(1)
    {
        DataType front;
        int ret = StackGetTop(&queue->input,&front);
        //如果取栈顶元素返回了0，则说明该栈中已经没有元素了
        if (ret == 0)
        {
            break;
        }
        //将input中的元素出栈
        StackPop(&queue->input);
        //将input（用于出队列的栈）中的栈顶元素插入到output（用于入队列的栈）中 
        StackPush(&queue->output,front);
    }
    //倒腾完成以后将output（用于出队列的栈）中的栈首元素出栈（即出队列操作）
    StackPop(&queue->output);
    //队列元素个数-1
    queue->size--;
}
//取队首元素函数
int QueueFront(Queue *queue,DataType *front)
{
    if(queue == NULL)
    {
        //非法输入
        return 0;
    }
    //将input（用于入队列的栈）中的元素倒腾到output（用于出队列的栈）中
    while(1)
    {
        DataType front;
        int ret = StackGetTop(&queue->input,&front);
        //如果取栈顶元素返回了0，则说明该栈中已经没有元素了
        if(ret == 0)
        {
            break;     
        }
        //将input中的元素出栈
        StackPop(&queue->input);
        //将input（用于入队列的栈）中的栈顶元素插入到output（用于出队列的栈）中 
        StackPush(&queue->output,front);
    }
    //取用于出队列的栈的栈首元素（即取出队首元素）
    int ret = StackGetTop(&queue->output,front);
    return ret;
}
//打印队列元素以便观察函数测试结果(其中思路不再详述，与之前函数思路一致)
void PrintQueueElem(Queue *queue,const char *msg)
{
    printf("[%s]\n",msg);
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
    while(1)
    {
        DataType front;
        int ret = StackGetTop(&queue->output,&front);
        if(ret == 0)
        {
            break;
        }
        StackPop(&queue->output);
        StackPush(&queue->input,front);
    }
    int i = 0;
    for(;i < queue->input.size;i++)
    {
        printf("%c ",queue->input.data[i]);
    }
    printf("\n\n");
   // Print(&queue->input);
}
//以下为测试函数
void TestQueueBy2Stack()
{
    Test_Header;
    
    Queue queue;
    //队列初始化
    QueueInit(&queue);
    //入队列函数测试
    QueuePush(&queue,'a');
    QueuePush(&queue,'b');
    QueuePush(&queue,'c');
    QueuePush(&queue,'d');
    PrintQueueElem(&queue,"入队列4个元素：a b c d");
    //以下为取队首元素函数测试1
    DataType front;
    int ret = QueueFront(&queue,&front);
    printf("expected ret = 1,actual ret = %d\n",ret);
    printf("expected front = a,actual front = %c\n",front);
    //出队列函数测试
    QueuePop(&queue);
    QueuePop(&queue);
    PrintQueueElem(&queue,"出队列两个元素");
    //取队首元素测试2
    ret = QueueFront(&queue,&front);
    printf("expected ret = 1,actual ret = %d\n",ret);
    printf("expected front = c,actual front = %c\n",front);

    QueuePop(&queue);
    QueuePop(&queue);
    PrintQueueElem(&queue,"将最后两个元素也出队列");
    //取队首元素函数测试3（空队列）
    ret = QueueFront(&queue,&front);
    printf("expected ret = 0,actual ret = %d\n",ret);
    QueueDestroy(&queue);
}
//主函数调用测试函数
int main()
{
    TestQueueBy2Stack();
    return 0;
}




