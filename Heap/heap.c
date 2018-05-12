#include<stdio.h>
#include<string.h>
#include"heap.h"

#define Test_Header printf("\n==========%s==========\n",__FUNCTION__);

//大堆判断函数
int Greater(DataType a,DataType b)
{
    return a > b ? 1 : 0;
}
//小堆判断函数
int Less(DataType a,DataType b)
{
    return a < b ? 1 : 0;
}
//初始化
void HeapInit(Heap *heap,Compare cmp)
{
    if(heap == NULL)
    {
        //非法输入
        return;
    }
    heap->size = 0;
    heap->cmp = cmp;
}
//销毁
void HeapDestroy(Heap *heap)
{
    if(heap == NULL)
    {
        //非法输入
        return;
    }
    heap->size = 0;
    heap->cmp = NULL;
}
//元素交换函数
void swap(DataType *a,DataType *b)
{
    DataType tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}
//元素调整上浮函数
void AdjustUp(Heap *heap,int index)
{
    if(heap == NULL)
    {
        //非法输入
        return;
    }
    int child = index;
    int parent = (child-1)/2;
    while(child > 0)
    {
        if(heap->cmp(heap->data[child],heap->data[parent]))
        {
            swap(&heap->data[parent],&heap->data[child]);
        }
        else
        {
            break;
        }
        child = parent;
        parent = (child-1)/2;
    }
}
//往堆中插入元素
void HeapInsert(Heap *heap,DataType to_insert)
{
    if(heap == NULL || heap->size >= max_size)
    {
        //非法输入或者堆满了
        return;
    }
    //先直接将元素插入堆的最后一个元素
    heap->data[heap->size] = to_insert;
    heap->size++;
    //再调整元素的位置，使之符合堆的规则
    //开始调整的位置就是从刚插入的元素开始往上
    //刚插入的元素的下标就是size-1
    AdjustUp(heap,heap->size-1);
    return;
}
//取堆顶元素，取堆顶元素失败返回0,成功返回1
int HeapRoot(Heap *heap,DataType *root)
{
    if(heap == NULL)
    {
        //非法输入
        return 0;
    }
    if(heap->size == 0)
    {
        //空堆
        return 0;
    }
    *root = heap->data[0];
    return 1;
}
//元素调整函数（下沉式调整）
void AdjustDown(Heap *heap,int index)
{
    if(heap == NULL)
    {
        //非法输入
        return;
    }
    int parent = index;
    int child = 2 * parent + 1;
    //DataType *cur = heap
    while(child < heap->size)
    {
        //先找出当前根节点的左右子树较小的一个节点
        //将cur指向最小的一个字符
        if(child+1 < heap->size && heap->cmp(heap->data[child+1],heap->data[child]))
        {
            child = child+1;
        }
        if(!heap->cmp(heap->data[parent],heap->data[child]))
        {
            swap(&heap->data[parent],&heap->data[child]);
        }
        else
        {
            break;
        }
        parent = child;
        child = 2 * parent + 1;
    }
}
//删除堆顶元素
void HeapErase(Heap *heap)
{
    if(heap == NULL)
    {
        //非法输入
        return;
    }
    if(heap->size == 0)
    {
        //空堆
        return;
    }
    //交换堆顶元素和最后一个元素
    swap(&heap->data[0],&heap->data[heap->size-1]);
    //在将最后一个元素删除
    heap->size--;
    //以根节点开始调整元素使之符合堆的规则,下沉式调整
    AdjustDown(heap,0);
    return;
}
//堆的创建
void HeapCreate(Heap *heap,DataType arr[],int len)
{
    if(heap == NULL)
    {
        //非法输入
        return;
    }
    int i = 0;
    for(;i < len;i++)
    {
        HeapInsert(heap,arr[i]);
    }
    return;
}
//堆排序
void HeapSort(DataType arr[],int len)
{
    //先将数组中的元素创建成一个堆
    Heap heap;
    HeapInit(&heap,Greater);
    HeapCreate(&heap,arr,len);
    //先取到栈顶元素
    DataType get_root;
    int i = len-1;
    //如果跳出循环说明堆空了。也就说明排序完成
    while(HeapRoot(&heap,&get_root))
    {
        //取到堆顶元素之后将其赋给数组的最后一个元素（升序排序）
        arr[i] = get_root;
        //更新i的值用于下一次赋值
        i = i-1;
        //再将该堆顶元素删除
        HeapErase(&heap);
    }
    //最后将删除的元素拷贝至数组中
    //memcpy(arr,heap.data,heap.size*sizeof(DataType));
    return;
}


/////////////////////////////////////
//以下为测试函数
/////////////////////////////////////
//初始化函数测试
void TestInit()
{
    Test_Header;
    Heap heap;
    HeapInit(&heap,Greater);
    printf("expected size = 0,actual size = %d\n",heap.size);
    printf("expected &cmp = %p,actual &cmp = %p\n",Greater,heap.cmp);
}
//往堆中插入元素的函数测试
void TestInsert()
{
    Test_Header;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'d');
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'h');
    HeapInsert(&heap,'e');
    int i = 0;
    for(;i < heap.size;i++)
    {
        printf("[%c|%d] ",heap.data[i],i);
    }
    printf("\n");
}
//取堆顶元素函数测试
void TestHeapRootAndErase()
{ 
    Test_Header;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'d');
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'h');
    HeapInsert(&heap,'e');
    printf("【取堆顶元素函数测试】\n");
    DataType get_root;
    int ret = HeapRoot(&heap,&get_root);
    if(ret == 1)
    {
        printf("expected get_root = h,actual get_root = %c\n",get_root);
    }
    printf("【删除堆顶元素函数测试】\n");
    HeapErase(&heap);
    int j = 0;
    for(;j < heap.size;j++)
    {
        printf("[%c|%d] ",heap.data[j],j);
    }
    printf("\n");
}
void TestCreate()
{
    Test_Header;
    Heap heap;
    HeapInit(&heap,Greater);
    DataType arr[] = "dabhe";
    HeapCreate(&heap,arr,5);
    int j = 0;
    for(;j < heap.size;j++)
    {
        printf("[%c|%d] ",heap.data[j],j);
    }
    printf("\n");

}
//堆排序函数测试
void TestSort()
{
    Test_Header;
    DataType arr[] = "dabhe";
    HeapSort(arr,5);
    printf("期待升序排序结果：a b d e h\n实际升序排序结果：");
    int i = 0;
    for(;i < 5;i++)
    {
        printf("%c ",arr[i]);
    }
}
int main()
{
    TestInit();
    TestInsert();
    TestHeapRootAndErase();
    TestCreate();
    TestSort();
    return 0;
}
