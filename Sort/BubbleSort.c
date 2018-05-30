#include<stdio.h>
#include"sort.h"
#include"swap.h"

//升序排序
void BubbleSort(int arr[],int len)
{
    if(len <= 1)
    {
        //不需要排序
        return;
    }
    //[0,bound)为有序区间
    //[bound,len)为待排序区间
    int bound = 0;
    for(;bound < len;bound++)
    {
        int cur = len-1;
        for(;cur >= bound;cur--)
        {
            if(arr[cur] < arr[cur-1])
            {
                //升序排序，如果后面的元素比其前一个元素小
                //就让他们交换
                swap(&arr[cur],&arr[cur-1]);
            }
        }
    }
    return;
}
