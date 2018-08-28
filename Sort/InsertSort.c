#include <stdio.h>
#include "swap.h"

void InsertSort(int arr[],int len)
{
    if(len <= 1)
    {
        //不需要排序
        return;
    }
    int bound = 1;
    for(;bound < len;bound++)
    {
        //此时保存当前bound的值是为了后面的搬运
        //一旦该值被保存起来，那么arr[bound]处的值就可以修改了
        int bound_value = arr[bound];
        int cur = bound;
        for(;cur > 0;cur--)
        {
            //此时初始情况下就是拿线性表的最后一个元素
            //和bound_value比较
            //因此此处arr[cur-1]的cur-1取决于cur的初始位置
            if(arr[cur-1] > bound_value)
            {
                arr[cur] = arr[cur-1];
            }
            else
            {
                //此时说明找到了合适的位置
                break;
            }
        }
        //走到这儿说明是找到了一个合适的位置
        //或者是cur回退走到了最开始（即cur=0）
        arr[cur] = bound_value;
    }
}
int main()
{
    int arr[] = {4,3,2,1};
    InsertSort(arr,4);
    int i = 0;
    for(;i < 4;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}
