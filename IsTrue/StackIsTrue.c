#include<stdio.h>
#include"stack.h"
#define Test_Header printf("\n==========%s==========\n",__FUNCTION__);

//顺序正确则返回1，错误返回0
int StackIsTrue(Stack *stack,char *arr1,char *arr2)
{
    if(stack == NULL)
    {
        //非法输入
        return 0;
    }
    //定义两个指针分别指向两个数组的第一个元素
    char *input = arr1;
    char *output = arr2;
    while(*input != '\0')
    {
        //将input当前指向的元素入栈
        StackPush(stack,*input);
        DataType top;
        //然后取到栈顶元素（就是上一步入栈的元素）
        StackTop(stack,&top);
        //将该栈顶元素与output当前所指向的元素相比较
        while(top == *output)
        {
            //如果两者相等,将该元素出栈
            StackPop(stack);
            //将output指向数组2的下一个元素
            output++;
            //然后再取数组1中的下一个栈顶元素
            //再次与output当前所指向的元素进行比较
            StackTop(stack,&top);
        }
        //走到这一步说明当前栈顶元素与output当前所指向的元素不相等
        input++;
    }
    if(*output == '\0')
    {
        return 1;
    }
    return 0;
}
//以下为测试函数
void Test()
{
    Test_Header;
    Stack stack;
    StackInit(&stack); 
    printf("入栈顺序为:a b c d e\n\n");
    char arr1[] = "abcde";
    printf("出栈顺序为:b c e d a\n");
    char arr2[] = "bceda";
    int ret = StackIsTrue(&stack,arr1,arr2);
    printf("expected ret = 1,actual ret = %d\n\n",ret);
   
    printf("出栈顺序为:b c e a d\n");
    char arr3[] = "bcead";
    ret = StackIsTrue(&stack,arr1,arr3);
    printf("expected ret = 0,actual ret = %d\n",ret);
}
int main()
{
    Test();
    return 0;
}


