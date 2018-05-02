#include<stdio.h>
#include"ShareStack.h"

#define Test_Header printf("\n==========%s==========\n",__FUNCTION__);

//栈1的初始化
void ShareStack1Init(ShareStack *shareSatck)
{
    if(shareSatck == NULL)
    {
        //非法输入
        return;
    }
    shareSatck->top1 = 0;
}
//栈2的初始化
void ShareStack2Init(ShareStack *shareSatck)
{
    if(shareSatck == NULL)
    {
        //非法输入
        return;
    }
    shareSatck->top2 = max_size;
}
//栈1的销毁
void ShareStack1Destroy(ShareStack *shareSatck)
{
    if(shareSatck == NULL)
    {
        //非法输入
        return;
    }
    shareSatck->top1 = 0;
    shareSatck->data[shareSatck->top1] = 0;
}
//栈2的销毁
void ShareStack2Destroy(ShareStack *shareSatck)
{
    if(shareSatck == NULL)
    {
        //非法输入
        return;
    }
    shareSatck->top2 = max_size;
}
//栈1的入栈操作函数
void ShareStack1Push(ShareStack *shareSatck,DataType value)
{
    if(shareSatck == NULL)
    {
        //非法输入
        return;
    }
    if(shareSatck->top1 == shareSatck->top2 || shareSatck->top1 == max_size)
    {
        //栈1满了
        return;
    }
    //栈1没满
    shareSatck->data[shareSatck->top1++] = value;
}
//栈2的入栈操作函数
void ShareStack2Push(ShareStack *shareSatck,DataType value)
{
    if(shareSatck == NULL)
    {
        //非法输入
        return;
    }
    if(shareSatck->top1 == shareSatck->top2 || shareSatck->top2 == 0)
    {
        //栈2满了
        return;
    }
    //栈2没满
    shareSatck->data[--shareSatck->top2] = value;
}
//栈1的出栈操作函数
void ShareStack1Pop(ShareStack *shareSatck)
{
    if(shareSatck == NULL)
    {
        //非法输入
        return;
    }
    if(shareSatck->top1 == 0 || shareSatck->top2 == 0)
    {
        //栈1是空栈
        printf("栈1是空栈\n");
        return;
    }
    //栈1内有元素，直接将top1往后移动一步
    shareSatck->top1--;
}
//栈2的出栈操作函数
void ShareStack2Pop(ShareStack *shareSatck)
{
    if(shareSatck == NULL)
    {
        //非法输入
        return;
    }
    if(shareSatck->top1 == max_size || shareSatck->top2 == max_size)
    {
        //栈2是空栈
        printf("栈2是空栈\n");
        return;
    }
    //栈2内有元素，直接将top2往前移动一步
    shareSatck->top2++;
}
//取栈1的栈顶元素操作函数，成功返回1，失败返回0
int ShareStack1Top(ShareStack *shareSatck,DataType *value)
{
    if(shareSatck == NULL)
    {
        //非法输入
        return 0;
    }
    if(shareSatck->top1 == 0 || shareSatck->top2 == 0)
    {
        //栈1是空栈
        return 0;
    }
    //栈1内有元素
    *value = shareSatck->data[shareSatck->top1-1]; 
    return 1;
}
//取栈2的栈顶元素操作函数,成功返回1，失败返回0
int ShareStack2Top(ShareStack *shareSatck,DataType *value)
{
    if(shareSatck == NULL)
    {
        //非法输入
        return 0;
    }
    if(shareSatck->top1 == max_size || shareSatck->top2 == max_size)
    {
        //栈2是空栈
        return 0;
    }
    //栈2内有元素
    *value = shareSatck->data[shareSatck->top2];
    return 1;
}
//打印栈1中的元素
void PrintStack1(ShareStack *shareSatck,const char *msg)
{
    printf("[%s]\n",msg);
    if(shareSatck == NULL)
    {
        //非法输入
        return;
    }
    if(shareSatck->top1 == 0 || shareSatck->top2 == 0)
    {
        //栈1是空栈
        return;
    }
    int i = 0;
    for(;i < shareSatck->top1;i++)
    {
        printf("%c ",shareSatck->data[i]);
    }
    printf("\n");
}
//打印栈2中的元素
void PrintStack2(ShareStack *shareSatck,const char *msg)
{
    printf("[%s]\n",msg);
    if(shareSatck == NULL)
    {
        //非法输入
        return;
    }
    if(shareSatck->top1 == max_size || shareSatck->top2 == max_size)
    {
        //栈2是空栈
        return;
    }
    int i = max_size-1;
    for(;i >= shareSatck->top2;i--)
    {
        printf("%c ",shareSatck->data[i]);
    }
    printf("\n");
}

//以下为测试函数
void TestShareStack()
{
    Test_Header;
    ShareStack shareSatck;

    //初始化栈1和栈2
    ShareStack1Init(&shareSatck);
    ShareStack2Init(&shareSatck);

    //栈1入栈函数测试
    ShareStack1Push(&shareSatck,'a');
    ShareStack1Push(&shareSatck,'b');
    ShareStack1Push(&shareSatck,'c');
    ShareStack1Push(&shareSatck,'d');
    PrintStack1(&shareSatck,"入栈1四个元素expected：a b c d");
    //栈1取栈顶元素函数测试1
    DataType top;
    int ret = ShareStack1Top(&shareSatck,&top);
    printf("expected ret = 1,actual ret = %d\n",ret);
    printf("expected top = d,actual ret = %c\n\n",top);
    //栈2入栈函数测试
    ShareStack2Push(&shareSatck,'z');
    ShareStack2Push(&shareSatck,'y');
    ShareStack2Push(&shareSatck,'x');
    ShareStack2Push(&shareSatck,'w');
    PrintStack2(&shareSatck,"入栈2四个元素expected：z y x w");
    //栈2取栈顶元素函数测试1
    ret = ShareStack2Top(&shareSatck,&top);
    printf("expected ret = 1,actual ret = %d\n",ret);
    printf("expected top = w,actual ret = %c\n\n",top);
    
    //栈1出栈函数测试
    ShareStack1Pop(&shareSatck);
    ShareStack1Pop(&shareSatck);
    PrintStack1(&shareSatck,"出栈1两个元素expected：a b");
    //栈1取栈顶元素函数测试2
    ret = ShareStack1Top(&shareSatck,&top);
    printf("expected ret = 1,actual ret = %d\n",ret);
    printf("expected top = b,actual ret = %c\n\n",top);
    //栈2出栈函数测试
    ShareStack2Pop(&shareSatck);
    ShareStack2Pop(&shareSatck);
    PrintStack2(&shareSatck,"出栈2两个元素expected：z y");
    //栈2取栈顶元素函数测试2
    ret = ShareStack2Top(&shareSatck,&top);
    printf("expected ret = 1,actual ret = %d\n",ret);
    printf("expected top = y,actual ret = %c\n\n",top);
                                     
    ShareStack1Pop(&shareSatck);                          
    ShareStack1Pop(&shareSatck);
    PrintStack1(&shareSatck,"将栈1中剩下的两个元素全部出栈");                             
    //栈1取栈顶元素函数测试3                              
    ret = ShareStack1Top(&shareSatck,&top);               
    printf("expected ret = 0,actual ret = %d\n\n",ret);     
    ShareStack2Pop(&shareSatck);
    ShareStack2Pop(&shareSatck);
    PrintStack2(&shareSatck,"将栈2中剩下的两个元素全部出栈");                             
    //栈2取栈顶元素函数测试3                              
    ret = ShareStack2Top(&shareSatck,&top);               
    printf("expected ret = 0,actual ret = %d\n\n",ret);

    //销毁栈1和栈2
    ShareStack1Push(&shareSatck,'a');
    ShareStack1Destroy(&shareSatck);
    ShareStack2Push(&shareSatck,'A');
    ShareStack2Destroy(&shareSatck);
    printf("[对销毁的栈操作，测试销毁函数]\n");
    ShareStack1Pop(&shareSatck);
    ShareStack2Pop(&shareSatck);
}
//以下为主函数调用测试函数
int main()
{
    TestShareStack();
    return 0;
}
