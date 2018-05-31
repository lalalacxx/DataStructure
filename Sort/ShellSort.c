#include <stdio.h>
#include"sort.h"
//希尔排序
void ShellSort(int arr[],int len)
{
    if(len <= 1)
    {
        //不需要排序
        return;
    }
    int gap = len/2;
    //第一重循环，用于生成步长序列
    for(;gap > 0;gap /= 2)
    {
        //此处相当于插入排序中的bound= 1
        int bound = gap;
        //第二重循环进行插入排序
        for(;bound < len;bound++)
        {
            //bound_value为待插入元素
            int bound_value = arr[bound];
            //第三重循环，线性表的查找和搬运
            int cur = bound;
            //cur-=gap就是在找到同组元素的上一个元素
            for(;cur >= gap;cur -= gap)
            {
                if(arr[cur-gap] > bound_value)
                {
                    //搬运
                    arr[cur] = arr[cur-gap];
                }
                else
                {
                    //找到了合适的位置存放bound_value
                    break;
                }
            }//第三重循环结束
            arr[cur] = bound_value;
        }//第二重循环结束
    }//第一重循环结束
    return;
}
