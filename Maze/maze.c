#include <stdio.h>
#include<stdlib.h>
#include "stack.h"

#define Test_Header printf("\n==========%s==========\n",__FUNCTION__);

#define max_row 6
#define max_col 6

typedef struct Maze
{
    int map[max_row][max_col];
}Maze;

//迷宫地图初始化函数
void MazeMapInit(Maze *maze)
{
    if(maze == NULL)
    {
        return;
    }
    int map[max_row][max_col] = 
    {
        {0,1,0,0,0,0},
        {0,1,1,1,0,0},
        {0,1,0,1,1,0},
        {1,1,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
    };
    int i = 0;
    for(;i < max_row;i++)
    {
        int j = 0;
        for(;j < max_col;j++)
        {
            maze->map[i][j] = map[i][j];
        }
    }
}
//打印迷宫地图函数
void PrintMap(Maze *maze)
{
    if(maze == NULL)
    {
        return;
    }
    int i = 0;
    for(;i < max_row;i++)
    {
        printf("{");
        int j = 0;
        for(;j < max_col;j++)
        {
            printf("%2d ",maze->map[i][j]);
        }
        printf("}\n");
    }
}
//////////////////////////////////////////
//方法一：使用函数栈帧实现递归方法走迷宫
//////////////////////////////////////////
//判断当前点是否能落脚的函数，能则返回1，否则返回0
int CanStay(Maze *maze,Point cur)
{
    //在地图外的点都不能落脚
    if(cur.row < 0 || cur.row >= max_row || cur.col < 0 || cur.col >= max_col)
    {
        return 0;
    }
    //在地图内的点，且值为1就能落脚，为0或2都不能落脚
    int value = maze->map[cur.row][cur.col];
    if(value == 1)
    {
        return 1;
    }
    return 0;
}
//标记能落脚的点的函数
void Mark(Maze *maze,Point cur)
{
    maze->map[cur.row][cur.col] = 2;
}
//判断当前点是否为出口,是出口返回1，不是出口返回0
int IsExit(Maze *maze,Point cur,Point entry)
{
    (void)maze;
    //如果当前点是入口则不能当做出口
    if(cur.row == entry.row && cur.col == entry.col)
    {
        return 0;
    }
    //如果当前点在边界上则当前点就是出口
    if(cur.row == 0 || cur.row == max_row-1 || cur.col == 0 || cur.col == max_col-1)
    {
        return 1;
    }
    return 0;
}
//每次走到下一个点，都会递归的调用下面这个函数
void _GetPath(Maze *maze,Point cur,Point entry)
{
    printf("cur:(%d,%d)\n",cur.row,cur.col);
    if(maze == NULL)
    {
        return;
    }
    //判定当前点是否能落脚
    if(!CanStay(maze,cur))
    {
        return;
    }
    //如果能落脚，就给当前位置做一个标记
    Mark(maze,cur);
    //判断当前点是否为出口
    if(IsExit(maze,cur,entry))
    {
        //如果当前点是一个出口，说明就找到了一条路，探测就结束
        printf("找到了一条出路\n");
        return;
    }
    //如果不是出口，就按照顺时针的方向探测周围相邻的四个点
    Point up = cur;
    up.row--;
    _GetPath(maze,up,entry);

    Point right = cur;
    right.col++;
    _GetPath(maze,right,entry);

    Point down = cur;
    down.row++;
    _GetPath(maze,down,entry);
    
    Point left = cur;
    left.col--;
    _GetPath(maze,left,entry);
    //递归的调用函数自身，递归时，更新cur点
    //（每次递归的点就是下一次要走的点，这个点究竟能不能走交给递归
}
///////////////////////////////////////////////////
//方法二：非递归，自己创建一个栈手动维护，实现迷宫
///////////////////////////////////////////////////
void _GetPath2(Maze *maze,Point entry)
{
    if(maze == NULL)
    {
        return;
    }
    //创建一个栈，并且初始化，这个栈保存着走过的路径
    Stack stack;
    StackInit(&stack);
    //判断当前点是否能落脚，如果不能说明参数非法
    if(!CanStay(maze,entry))
    {
        return;
    }
    //如果能落脚标记入口点，并且将该入口点入栈
    Mark(maze,entry);
    StackPush(&stack,entry);
    Point cur;
    while(1)
    {
        //进入循环，获取到当前栈的栈顶元素
        StackTop(&stack,&cur);
        //判定这个点是不是出口，如果是出口，直接函数返回
        if(IsExit(maze,cur,entry))
        {
            printf("找到了一条路\n");
            return;
        }
        //如果不是出口，就按照顺时针的方向探测周围相邻的四个点,判定相邻点是否能落脚
        //如果能落脚，就标记并且入栈，立刻进入下一轮循环
        Point up = cur;
        up.row--;
        if(CanStay(maze,up))
        {
            Mark(maze,up);
            StackPush(&stack,up);
            continue;
        }
    
        Point right = cur;
        right.col++;
        if(CanStay(maze,right))
        {
            Mark(maze,right);
            StackPush(&stack,right);
            continue;
        }
    
        Point down = cur;
        down.row++;
        if(CanStay(maze,down))
        {
            Mark(maze,down);
            StackPush(&stack,down);
            continue;
        }
        
        Point left = cur;
        left.col--;
        if(CanStay(maze,left))
        {
            Mark(maze,left);
            StackPush(&stack,left);
            continue;
        }
        //如果4个相邻点都不能落脚，则出栈当前点，相当于进行回溯
        StackPop(&stack);
    }
}

//////////////////////////////////////////
//迷宫求最短路径问题
//////////////////////////////////////////
//创建一个有最短路径的迷宫地图
void MazeMapShortPathInit(Maze *maze)
{
    int map[max_row][max_col] = 
    {
        {0,1,0,0,0,0},
        {0,1,1,1,0,0},
        {0,1,0,1,0,0},
        {1,1,0,1,1,1},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0}
    };
    int i = 0;
    for(;i < max_row;i++)
    {
        int j = 0;
        for(;j < max_col;j++)
        {
            maze->map[i][j] = map[i][j];
        }
    }
}
//将short_path替换为当前找到的最短的路径函数
void StackAssign(Stack *from,Stack *to)
{
    if(from == NULL || to == NULL)
    {
        return;
    }
    //为了保证to的内存能够容纳下from中的所有元素
    //采用以下方法
    //1、释放to中的原有内存
    StackDestroy(to);
    //2、根据from的元素个数，给to申请内存空间
    to->size = from->size;
    to->capacity = from->capacity;
    to->data = (DataType*)malloc(to->capacity * sizeof(DataType));
    //在将from中的数据拷贝到to中
    int i = 0;
    for(;i < from->size;i++)
    {
        to->data[i] = from->data[i];
    }
    return;
}
void _GetShortPath(Maze *maze,Point cur,Point entry,Stack *cur_path,Stack *short_path) 
{
    if(maze == NULL)
    {
        return;
    }
    //判断当前点是否能落脚
    if(!CanStay(maze,cur))
    {
        return;
    }
    //如果能落脚，就对当前点进行标记，同时把当前点插入到cur_path中
    Mark(maze,cur);
    StackPush(cur_path,cur);
    //判断当前点是否为出口
    if(IsExit(maze,cur,entry))
    {
        //是出口说明找到了一条路径（拿当前路径与最短路径相比较：
        printf("找到了一条路径\n");
        //如果当前路径比最短路径短，或者short_path本身是一个空栈
        //就用当前路径替换short_path
        if(short_path->size == 0 || cur_path->size < short_path->size)
        {
            printf("找到了一条比较短的路径\n");
            StackAssign(cur_path,short_path);
        }
        //如果当前路径没有比short_path短，就要尝试去找其他路径 
        //在回溯之前也要把cur_path的栈顶元素出栈
        StackPop(cur_path);
        return;
    }
    //如果当前点不是出口，尝试探测4个方向
    Point up = cur;
    up.row--;
    _GetShortPath(maze,up,entry,cur_path,short_path);

    Point right = cur;
    right.col++;
    _GetShortPath(maze,right,entry,cur_path,short_path);

    Point down = cur;
    down.row++;
    _GetShortPath(maze,down,entry,cur_path,short_path);

    Point left = cur;
    left.col--;
    _GetShortPath(maze,left,entry,cur_path,short_path);
    //如果4个方向都探测过了，就可以进行出栈（cur_path short_path的栈顶元素的出栈）
    //回溯到上一个点
    StackPop(cur_path);
    return;
}
//打印最短路径函数（原则上来讲栈是不允许被遍历的，这里是为了观察测试结果）
void PrintShortPath(Stack *short_path,const char *msg)
{
    printf("[%s]\n",msg);
    if(short_path == NULL)
    {
        return;
    }
    int i = 0;
    for(;i < short_path->size;i++)
    {
        printf("{%d,%d}\n",short_path->data[i].row,short_path->data[i].col);
    }
    printf("\n");
}

//////////////////////////////////////////
//多通路带环迷宫求最短路径问题
//////////////////////////////////////////
//创建一个有最短路径的多通路带环的迷宫地图
void MazeMapShortPathWithCycleInit(Maze *maze)
{
    int map[max_row][max_col] = 
    {
        {0,1,0,0,0,0},
        {0,1,1,1,0,0},
        {1,1,0,1,0,0},
        {0,1,1,1,1,1},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0}
    };
    int i = 0;
    for(;i < max_row;i++)
    {
        int j = 0;
        for(;j < max_col;j++)
        {
            maze->map[i][j] = map[i][j];
        }
    }
}
//判断是否能落脚的函数
int CanStayWithCycle(Maze *maze,Point cur,Point pre)
{
    //在地图外的点都不能落脚
    if(cur.row < 0 || cur.row >= max_row || cur.col < 0 || cur.col >= max_col)
    {
        return 0;
    }
    //在地图内的点，且值为1就能直接落脚
    int cur_value = maze->map[cur.row][cur.col];
    int pre_value = maze->map[pre.row][pre.col];
    if(cur_value == 1)
    {
        return 1;
    }
    //当前点如果已经走过了，比较cur对应的值和pre对应的值
    //cur-value = 7，pre-value = 5应该落脚
    //cur-value = 6，pre-value = 5不应该落脚
    //cur-value = 5，pre-value = 5不应该落脚
    //cur-value = 4，pre-value = 5不应该落脚
    //cur-value > pre-value+1就应该落脚
    if(cur_value > pre_value+1)
    {
        return 1;
    }
    return 0;
}
//标记函数
void MarkWithCycle(Maze *maze,Point cur,Point pre)
{
    if(pre.row == -1 && pre.col == -1)
    {
        //针对入口点进行标记，此时的pre是一个非法点
        //不能根据pre_value+1的方法进行标记
        maze->map[cur.row][cur.col] = 2;
        return;
    }
    int pre_value = maze->map[pre.row][pre.col];
    maze->map[cur.row][cur.col] = pre_value+1;
}

void _GetPathWithCycleShort(Maze *maze,Point cur,Point pre,Point entry,Stack *cur_path,Stack *short_path)
{
    if(maze == NULL || cur_path == NULL || short_path == NULL)
    {
        return;
    }
    //判断当前点是否能落脚(判定规则改变了)
    if(!CanStayWithCycle(maze,cur,pre))
    {
        //不能落脚就直接返回
        return;
    }
    //能落脚就把当前点标记（标记规则也改变了）并且入cur_path栈，cur_path栈保存着我们走过的路径
    MarkWithCycle(maze,cur,pre);
    StackPush(cur_path,cur);
    pre = cur;
    //判定当前点是否为出口
    if(IsExit(maze,cur,entry))
    {
        //是出口说明找到了一条路
        printf("找到了一条路\n");
        //将cur_path与short_path进行比较
        //把比较短的路径保存到short_path栈中
        if(short_path->size == 0 || cur_path->size < short_path->size)
        {
            printf("找到了一条比较短的路\n");
            StackAssign(cur_path,short_path);
        }
        StackPop(cur_path);
        return;
    }
    //如果不是出口，以当前点为基准点，探测相邻的四个点
    Point up = cur;
    up.row--;
    _GetPathWithCycleShort(maze,up,pre,entry,cur_path,short_path);
    Point right = cur;
    right.col++;
    _GetPathWithCycleShort(maze,right,pre,entry,cur_path,short_path);
    Point down = cur;
    down.row++;
    _GetPathWithCycleShort(maze,down,pre,entry,cur_path,short_path);
    Point left = cur;
    left.col--;
    _GetPathWithCycleShort(maze,left,pre,entry,cur_path,short_path);
    //如果四个方向都探测过了，就出栈回溯
    StackPop(cur_path);
    return;
}









//以下为测试函数
void Test1()
{
    Test_Header;
    Maze maze;
    MazeMapInit(&maze);
    Point entry = {0,1};
    _GetPath(&maze,entry,entry);
    PrintMap(&maze);
}
void Test2()
{
    Test_Header;
    Maze maze;
    MazeMapInit(&maze);
    Point entry = {0,1};
    _GetPath2(&maze,entry);
    PrintMap(&maze);
}
void Test3()
{
    Test_Header;
    Maze maze;
    MazeMapShortPathInit(&maze);
    Point entry = {0,1};
    Stack cur_path,short_path;
    StackInit(&cur_path);
    StackInit(&short_path);
    _GetShortPath(&maze,entry,entry,&cur_path,&short_path);
    PrintMap(&maze);
    PrintShortPath(&short_path,"最短路径是");
}
void Test4()
{
    Test_Header;
    Maze maze;
    Stack cur_path,short_path;
    MazeMapShortPathWithCycleInit(&maze);
    StackInit(&cur_path);
    StackInit(&short_path);
    Point entry = {0,1};
    Point pre = {-1,-1};
    _GetPathWithCycleShort(&maze,entry,pre,entry,&cur_path,&short_path);
    PrintMap(&maze);
    PrintShortPath(&short_path,"最短路径为");
}
int main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    return 0;
}
