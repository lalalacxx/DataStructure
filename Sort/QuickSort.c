#include<stdio.h>
#include"sort.h"
#include"swap.h"
#include"stack.h"
////////////////////////////////////
//快速排序的递归版本
////////////////////////////////////
//交换法
int Partion(int arr[],int beg,int end)
{
    if(end - beg <= 1)
    {
        return beg;
    }
    int left = beg;
    int right = end-1;
    //取数组的最后一个元素作为基准值
    int key = arr[right];
    while(left < right)
    {
        //从左往右找到一个大于基准值的元素
        while(left < right && arr[left] <= key)
        {
            left++;
        }
        //从右往左找到一个小于基准值的元素
        while(left < right && arr[right] >= key)
        {
            right--;
        }
        if(left < right)
        {
            swap(&arr[left],&arr[right]);
        }
    }
    //最后把left指向的位置和基准值的位置进行交换
    swap(&arr[left],&arr[end-1]);
    return left;
}
//挖坑法
int Partion2(int arr[],int beg,int end)
{
    if(end -beg <= 1)
    {
        return beg;
    }
    int left = beg;
    int right = end-1;
    int key = arr[right];
    while(left < right)
    {
        while(left < right && arr[left] <= key)
        {
            left++;
        }
        //循环退出，意味着left就指向了一个大于基准值的位元素
        //就可以把这个值填到刚才right指向的坑里
        //一旦赋值操作完成，left自身也就成为了一个坑
        if(left < right)
        {
            arr[right--] = arr[left];
        }
        while(left < right && arr[right] >= key)
        {
            right--;
        }
        //循环退出，意味着right指向了一个小于基准值的元素
        //就可以把这个值填到刚才left指向的坑里
        //一旦赋值操作完成，right自身就又变成了一个坑
        if(left < right)
        {
            arr[left++] = arr[right];
        }
    }
    //一旦left和right相遇，那么说明整个区间就整理完毕了
    //还剩下一个坑需要填，此时就把基准值填进去就可以了
    arr[left] = key;
    return left;
}
void _QuickSort(int arr[],int beg,int end)
{
    if(end - beg <= 1)
    {
        //要么没有元素要么就只有一个元素
        return;
    }
    //[beg,mid)左区间
    //[mid+1,end)右区间
    //左区间的所有元素一定都小于等于右区间的所有元素
    int mid = 0;
    mid = Partion(arr,beg,end);
    _QuickSort(arr,beg,mid);
    _QuickSort(arr,mid+1,end);
}
//快速排序
void QuickSort(int arr[],int len)
{
    if(len <= 1)
    {
        //不需要排序
        return;
    }
    //[0,len)
    _QuickSort(arr,0,len);
}

///////////////////////////////////
//非递归版本
///////////////////////////////////
void QuickSortByLoop(int arr[],int len)
{
    if(len <= 1)
    {
        //不需要排序
        return;
    }
    Stack stack;
    StackInit(&stack);
    int beg = 0;
    int end = len;
    //需要注意的是我们这里每次入栈总是入栈两次
    //即我们入栈了一对儿值。而这一对值就是一个区间
    //[beg,end)
    StackPush(&stack,beg);
    StackPush(&stack,end);
    while(1)
    {
        //取栈顶元素
        //由于入栈时的一对值是一个区间
        //所以后入展的一定是该区间的右边范围值
        //即该区间的结束位置
        int ret = StackTop(&stack,&end);
        if(ret == 0)
        {
            //栈为空，说明快速排序就结束了
            break;
        }
        //走到这里说明有区间待排序
        //所以将该栈顶元素弹出
        StackPop(&stack);
        //再取栈顶元素就取到该区间的左边结束位置的值
        StackTop(&stack,&beg);
        //[beg,end)相当于是即将要进行快速排序
        //进行整理的区间
        if(end-beg <= 1)
        {
            //此时该区间内有吗有一个元素要么一个元素都没有
            //因此不需要排序，直接进行下一趟循环
            continue;
        }
        //整理该区间
        int mid = Partion(arr,beg,end);
        //在继续将区间压栈，然后进行下一趟循环
        //[beg,mid),[mid+1,end]
        StackPush(&stack,beg);
        StackPush(&stack,mid);
        StackPush(&stack,mid+1);
        StackPush(&stack,end);
    }
}
