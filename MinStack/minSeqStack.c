#include<stdio.h>
#include"minSeqStack.h"
#include<stdlib.h>

#define Test_Header printf("\n==========%s==========\n",__FUNCTION__);


//初始化函数
void minStackInit(minStack *stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    stack->size = 0;
    stack->capacity = 1000;
    stack->data = (minStackType*)malloc(stack->capacity * sizeof(minStackType));
}
//销毁函数
void minStackDestroy(minStack *stack)
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
//入栈函数
void minStackPush(minStack *stack,minStackType value)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    //每一次入栈前判断栈是否满了
    if(stack->size == stack->capacity)
    {
        //栈满了，没有空间可供新元素插入
        return;
    }
    //假定要插入的值就是最小的值
    minStackType min = value;
    if(stack->size == 0)
    {
        //空栈
        //每次入栈两次，最小的值总是最后入栈
        stack->data[stack->size++] = value;
        stack->data[stack->size++] = min;
    }
    //不是空栈
    else
    {
        //如果当前栈中的栈顶元素比假定的最小值还要小
        if(min > stack->data[stack->size-1])
        {
            //改变最小值
            min = stack->data[stack->size-1];
        }
        //先将value入栈，再将最小值入栈
        stack->data[stack->size++] = value;
        stack->data[stack->size++] = min;
    }
}
//出栈函数
void minStackPop(minStack *stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->size == 0)
    {
        //空栈，没有元素可以出栈
        return;
    }
    //不是空栈
    else
    {
        //此时需要出栈两个元素才会将我们最后插入的元素（包括一个新的值和最后插入的最小的值）出栈
        stack->size -= 2;
    }
}
//取栈顶元素函数，成功取到栈顶元素就返回1，否则返回0
int minStackGetTop(minStack *stack,minStackType *value)
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
    //不是空栈
    *value = stack->data[stack->size-1];
    return 1;
}
void Print(minStack *stack,const char *msg)
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
    int i = 0;
    for(;i < stack->size;i++)
    {
        printf("%c ",stack->data[i]);
    }
    printf("\n");
}


void TestMinSeqStack()
{
    Test_Header;
    minStack stack;

    minStackInit(&stack);
    printf("expected size = 0,capacity = 1000,actual size = %d,capacity = %d\n\n",stack.size,stack.capacity);

    minStackPush(&stack,'x');
    minStackPush(&stack,'y');
    Print(&stack,"入栈2个元素：x y");

    minStackType value;

    int ret = minStackGetTop(&stack,&value);
    printf("expected ret = 1,actual ret = %d\n",ret);
    printf("expected min = x,actual min = %c\n\n",value);

    minStackPush(&stack,'g');
    Print(&stack,"再入栈一个元素:g");
    ret = minStackGetTop(&stack,&value);
    printf("expected ret = 1,actual ret = %d\n",ret);
    printf("expected min = g,actual min = %c\n\n",value);
   
    minStackPush(&stack,'w');
    Print(&stack,"再入栈一个元素:w");
    ret = minStackGetTop(&stack,&value);
    printf("expected ret = 1,actual ret = %d\n",ret);
    printf("expected min = g,actual min = %c\n\n",value);
    minStackPop(&stack);
    minStackPop(&stack);
    minStackPop(&stack);
    minStackPop(&stack);
    Print(&stack,"将所有元素出栈");
    ret = minStackGetTop(&stack,&value);
    printf("expected ret = 0,actual ret = %d\n\n",ret);

    //销毁栈
    minStackDestroy(&stack);
    printf("expected size = 0,capacity = 0,actual size = %d,capacity = %d\n\n",stack.size,stack.capacity);


}

int main()
{
    TestMinSeqStack();
    return 0;
}
