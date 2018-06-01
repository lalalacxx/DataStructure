#include<stdio.h>
#include"sort.h"
#include"swap.h"
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
    //q取数组的最后一个元素作为基准值
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
    swap(&arr[left],&arr[right]);
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
    mid = Partion(arr,beg,mid);
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
