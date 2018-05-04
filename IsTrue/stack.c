#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

void StackInit(Stack *stack)
{
    if(stack == NULL)
    {
        return;
    }
    stack->size = 0;
    stack->capacity = 1000;
    stack->data = (DataType*)malloc(stack->capacity * sizeof(DataType));
}
void StackDestroy(Stack *stack)
{
    if(stack == NULL)
    {
        return;
    }
    free(stack->data);
    stack->data = NULL;
    stack->size = 0;
    stack->capacity = 0;
}
void StackPush(Stack *stack,DataType value)
{
    if(stack == NULL)
    {
        return;
    }
    if(stack->size == stack->capacity)
    {
        return;
    }
    stack->data[stack->size++] = value;
}
void StackPop(Stack *stack)
{
    if(stack == NULL)
    {
        return;
    }
    if(stack->size == 0)
    {
        return;
    }
    stack->size--;
}
int StackTop(Stack *stack,DataType *value)
{
    if(stack == NULL)
    {
        return 0;
    }
    if(stack->size == 0)
    {
        return 0;
    }
    *value = stack->data[stack->size-1];
    return 1;
}


