#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//////////////////////////////////////////
//递归版本
//////////////////////////////////////////

//合并区间函数
void _MergeArr(int arr[],int beg,int mid,int end,int *tmp)
{
    int cur1 = beg;
    int cur2 = mid;
    int tmp_index = beg;
    while(cur1 < mid && cur2 < end)
    {
        //此处我们需要升序排序
        //比较后将较小的一个元素放到新的区间中去
        if(arr[cur1] < arr[cur2])
        {
            //此时cur1对应的元素比较小
            //就将cur1对应的元素放到新区间中去
            tmp[tmp_index++] = arr[cur1++];
            //并且将cur1和tmp_index往后移动一步
            //用于下一次的元素比较和存放
        }
        else
        {
            //此时cur2对应的元素比较小
            //就将cur2对应的元素放到新区间中去
            tmp[tmp_index++] = arr[cur2++];
            //并且将cur2和tmp_index往后移动一步
            //用于下一次的元素比较和存放
        }
    }
    //走到这说明是某一个区间遍历完了
    //此时我们需要把剩下的没有遍历完的区间
    //中剩下的所有元素依次放入新的空间（tmp）中去
    while(cur1 < mid)
    {
        //此时是cur2走完了，cur1还剩下有元素没有处理
        //所以将cur1往后剩下的元素放到新的空间中去
        tmp[tmp_index++] = arr[cur1++];
    }
    while(cur2 < end)
    {
        //此时是cur1走完了，cur2还剩下有元素没有处理
        //所以将cur2往后剩下的元素放到新的空间中去
        tmp[tmp_index++] = arr[cur2++];
    }
    //最后把tmp中的内容拷贝到数组中去即可完成排序
    //进行归并的时候，处理的区间是[beg,end)
    //对应的会把这部分区间的元素填充到tmp[beg,end)区间上
    //此时这里的拷贝会arr的动作，要保证结果放到正确的区间上
    memcpy(arr+beg,tmp+beg,sizeof(int)*(end-beg));
    return;
}
//[beg,end)就是我们当前要处理的子数组
void _MergeSort(int arr[],int beg,int end,int *tmp)
{
    if(end - beg <= 1)
    {
        //要么只有一个元素，要么没有元素
        return;
    }
    int mid = beg+(end-beg)/2;
    //此时我们就有两个区间
    //[beg,mid),和[mid,end)
    //然后对于这两个区间都调用该函数
    //对于两个区间进行递归的处理
    //此处的处理就是划分区间
    //直到最后只剩下一个元素不能再划分为止
    _MergeSort(arr,beg,mid,tmp);
    _MergeSort(arr,mid,end,tmp);
    //合并区间,合并后的区间内的元素是有序的
    _MergeArr(arr,beg,mid,end,tmp);
    return;
}
void MergeSort(int arr[],int len)
{
    if(len <= 1)
    {
        //不需要排序
        return;
    }
    //此时我们创建一个临时空间用来合并元素
    int *tmp = (int*)malloc(sizeof(int)*len);
    _MergeSort(arr,0,len,tmp);
    free(tmp);
}

//////////////////////////////////////////
//非递归版本
//////////////////////////////////////////

void MergeSortByLoop(int arr[],int len)
{
    if(len <= 1)
    {
        //不需要排序
        return;
    }
    //创建一个临时空间用来合并元素
    int *tmp = (int*)malloc(sizeof(int)*len);
    //定义一个步长gap，初始为1，
    //相当于每次合并两个长度为gap的有序区间
    int gap = 1;
    for(;gap < len;gap*=2)
    {
        //在当前gap下用i辅助完成所有长度为gap的区间的合并
        int i = 0;
        for(;i < len;i+=2*gap)
        {
            //[beg,mid),[mid,end)
            int beg = i;
            int mid = i+gap;
            int end = i+2*gap;
            if(mid > len)
            {
                mid = len;
            }
            if(end > len)
            {
                end = len;
            }
            //排序
            _MergeArr(arr,beg,mid,end,tmp);
        }
    }
    free(tmp);
}
