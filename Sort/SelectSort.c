#include<stdio.h>
#include"sort.h"
#include"swap.h"
//选择排序，升序排序，（从前往后遍历）
void SelectSort(int arr[],int len)
{
    if(len <= 1)
    {
        //不需要排序
        return;
    }
    //[0,bound):有序区间
    //[bound,len):待排序区间
    int bound = 0;
    for(;bound < len;bound++)
    {
        int cur = bound+1;
        for(;cur < len;cur++)
        {
            if(arr[bound] > arr[cur])
            {
                //较大的数往后移
                //每遍历完一趟，最小的数就排了在第一个位置
                swap(&arr[bound],&arr[cur]);
            }
        }
    }
    return;
}
