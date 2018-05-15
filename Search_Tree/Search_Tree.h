#pragma once

typedef char DataType;
typedef struct SearchNode
{
    DataType data;
    struct SearchNode *lchild;
    struct SearchNode *rchild;
}SearchNode;

//初始化函数
void SearchTreeInit(SearchNode **root);
//销毁函数
void SearchTreeDestroy(SearchNode **root);
//插入元素
void SearchTreeInsert(SearchNode **root,DataType to_insert);
//查找元素
SearchNode *SearchTreeFind(SearchNode *root,DataType to_find);
