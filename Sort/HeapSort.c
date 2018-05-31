#include<stdio.h>
#include<string.h>
#include"sort.h"
#include"swap.h"

//下沉式调整
void AdjustDown(int arr[],int len,int index)
{
    int parent = index;
    int child = 2*parent+1;
    while(child < len)
    {
        //由于此处我们要升序排序需要建立大堆
        if(child+1 < len && arr[child+1] > arr[child])
        {
            child = child+1;
        }
        //经历上面的判定以后，
        //child就指向了左右子树中比较大的那个
        if(arr[parent] < arr[child])
        {
            swap(&arr[parent],&arr[child]);
        }
        parent = child;
        child = 2*parent+1;
    }
    return;
}
void AdjustUp(int arr[],int len,int index)
{
    (void)len;
    int child = index;
    int parent = (child-1)/2;
    while(child > 0)
    {
        if(arr[parent] < arr[child])
        {
            swap(&arr[parent],&arr[child]);
        }
        else
        {
            break;
        }
        child = parent;
        parent = (child-1)/2;
    }
    return;
}
//创建堆
void HeapCreate(int arr[],int len)
{
    if(len <= 1)
    {
        return;
    }
    int i = (len-1-1)/2;
    for(;i > 0;i--)
    {
        AdjustDown(arr,len,i);
    }
    AdjustDown(arr,len,0);
}
//删除堆顶元素
void HeapPop(int arr[],int len)
{
    if(len <= 1)
    {
        return;
    }
    swap(&arr[0],&arr[len-1]);
    AdjustDown(arr,len-1,0);
}
//堆排序
void HeapSort(int arr[],int len)
{
    if(len <= 1)
    {
        //不需要排序
        return;
    }
    //基于数组建一个堆（升序：大堆，降序：小堆）
    HeapCreate(arr,len);
    int i = 0;
    for(;i < len-1;i++)
    {
        //第二个参数表示数组中那一部分是堆
        //例如：第一次删除之前[0，len)为堆
        //第二次删除之前[0，len-1）为堆……
        HeapPop(arr,len-i);
        //注意这里的删除其实并不是真的就将堆顶的
        //这一个元素删除掉，其实只是将较大的值（堆顶元素）
        //移动到了后面，然后修改了数组中的元素属于堆的区间
    }
    return;
}
