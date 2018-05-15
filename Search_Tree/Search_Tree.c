#include<stdio.h>
#include<stdlib.h>
#include"Search_Tree.h"

#define Test_Header printf("\n==========%s==========\n",__FUNCTION__);

void SearchTreePreOrder(SearchNode *root)
{
    if(root == NULL)
    {
        return;
    }
    printf("%c ",root->data);
    SearchTreePreOrder(root->lchild);
    SearchTreePreOrder(root->rchild);
}
void SearchTreeInOrder(SearchNode *root)
{
    if (root == NULL)
    {
        return;
    }
    SearchTreeInOrder(root->lchild);
    printf("%c ",root->data);
    SearchTreeInOrder(root->rchild);
}
SearchNode *CreateNode(DataType value)
{
    SearchNode *new_node = (SearchNode *)malloc(sizeof(SearchNode));
    new_node->data = value;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    return new_node;
}
void DestroyNode(SearchNode *node)
{
    free(node);
    return;
}
//初始化函数
void SearchTreeInit(SearchNode **root)
{
    if(root == NULL)
    {
        //非法输入
        return;
    }
    *root = NULL;
}
//销毁函数
void SearchTreeDestroy(SearchNode **root)
{
    if(root == NULL)
    {
        //非法输入
        return;
    }
    if(*root == NULL)
    {
        //空树
        return;
    }
    //不是空树
    //以后序遍历的顺序递归销毁
    //1、递归销毁左子树
    SearchTreeDestroy(&(*root)->lchild);
    //2、递归销毁右子树
    SearchTreeDestroy(&(*root)->rchild);
    //3、销毁根节点
    DestroyNode(*root);
    *root = NULL;
}
//插入元素（递归版本）
void SearchTreeInsert(SearchNode **root,DataType to_insert)
{
    if(root == NULL)
    {
        //非法输入
        return;
    }
    if(*root == NULL)
    {
        //空树
        //此时待插入的元素直接插到根节点的位置
        SearchNode *new_node = CreateNode(to_insert);
        *root = new_node;
        return;
    }
    //不是空树
    SearchNode *cur = *root;
    if(to_insert < cur->data)
    {
        //待插入的元素比当前根结点的值小
        //则递归的往左子树插入
        SearchTreeInsert(&cur->lchild,to_insert);
    }
    else if(to_insert > cur->data)
    {
        //待插入的元素比当前根节点的值大
        //则递归的往右子树插入
        SearchTreeInsert(&cur->rchild,to_insert);
    }
    else
    {
        //待插入的元素和当前根节点的值相等
        //我们约定该二叉搜索树中不能有重复的值
        //则直接返回
        return;
    }
}
//插入（非递归版本）
void SearchTreeInsert1(SearchNode **root,DataType to_insert)
{
    if(root == NULL)
    {
        //非法输入
        return;
    }
    if(*root == NULL)
    {
        //空树
        SearchNode *new_node = CreateNode(to_insert);
        *root = new_node;
        return;
    }
    //不是空树
    //要放置的位置
    SearchNode *cur = *root;
    //新元素的父节点
    SearchNode *pre = NULL;
    //循环找到要插入的位置
    while(1)
    {
        if(cur == NULL)
        {
            //找到了要插入的位置
            break;
        }
        if(to_insert > cur->data)
        {
            //保存父节点的位置（即当前节点）
            pre = cur;
            //去当前节点的右子树找
            cur = cur->rchild;
        }
        else if(to_insert < cur->data)
        {
            //保存父节点的位置（即当前节点）
            pre = cur;
            //取当前节点的左子树找
            cur = cur->lchild;
        }
        else
        {
            //规定不允许有重复的值
            //所以直接插入失败函数退出
            return;
        }
    }
    //找到位置以后就可以进行插入
    //首先我们要以待插入的值创建一个新的节点
    SearchNode *new_node = CreateNode(to_insert);
    //判断该值是其父节点的左子树还是右子树
    if(to_insert > pre->data)
    {
        //是右子树
        pre->rchild = new_node;
    }
    else
    {
        //是左子树
        pre->lchild = new_node;
    }
    //注意这里根本不会有与其父节点相等的情况发生
}
//查找元素（递归版本）
SearchNode *SearchTreeFind(SearchNode *root,DataType to_find)
{
    if(root == NULL)
    {
        //空树肯定没有带查找的值
        return NULL;
    }
    //不是空树
    //从根节点开始查找
    if(to_find == root->data)
    {
        //待查找的元素刚好就是根节点
        return root;
    }
    else if(to_find < root->data)
    {
        //待查找的元素比当前根节点的值小
        //则递归式的去当前根节点的左子树找
        SearchTreeFind(root->lchild, to_find);
    }
    else if(to_find > root->data)
    {
        //待查找的元素比当前根节点的值大
        //则递归式的去当前根节点的右子树找
        SearchTreeFind(root->rchild,to_find);
    }
    //走到了这里就说明没有找到
    return NULL;
}
//查找元素（非递归版本）
SearchNode *SearchTreeFind1(SearchNode *root,DataType to_find)
{
    if(root == NULL)
    {
        //空树
        return NULL;
    }
    //不是空树
    SearchNode *cur = root;
    while(cur != NULL)
    {
        if(to_find < cur->data)
        {
            //去当前节点的左子树中找
            cur = cur->lchild;
        }
        else if(to_find > cur->data)
        {
            //去当前节点的右子树找
            cur = cur->rchild;
        }
        else
        {
            //找到了
            return cur;
        }
    }
    //走到这一步，说明是将这颗树找完了
    //但是没有找到待查找的元素
    return NULL;
}
//删除(递归版本)
void SearchTreeRemove(SearchNode **proot, DataType to_remove)
{
    if(proot == NULL)
    {
        //非法输入
        return;
    }
    if(*proot == NULL)
    {
        //空树
        return;
    }
    SearchNode *cur = *proot;
    //先找到to_remove的位置
    if(to_remove > cur->data)
    {
        //比当前根节点的值大
        //则递归的往右子树删除
        SearchTreeRemove(&cur->rchild,to_remove);
    }
    else if(to_remove < cur->data)
    {
        //比当前根节点的值小
        //则递归的往左子树删除
        SearchTreeRemove(&cur->lchild,to_remove);
    }
    //如果走到这里说明就找到了to_remove的位置
    //接下来就分情况讨论如何删除
    else
    {
        SearchNode *to_remove_node = cur;
        if(to_remove_node->lchild == NULL && to_remove_node->rchild == NULL)
        {
            //1、to_remove_node没有左右子树
            //则直接将to_remove_node的父节点空:
            *proot = NULL;
            DestroyNode(to_remove_node);
            return;
        }
        else if(to_remove_node->lchild == NULL && to_remove_node->rchild != NULL)
        {
            //2、to_remove只有右子树
            *proot = to_remove_node->rchild;
            DestroyNode(to_remove_node);
            return;
        }
        else if(to_remove_node->lchild != NULL && to_remove_node->rchild == NULL)
        {
            //3、to_remove只有左子树
            *proot = to_remove_node->lchild;
            DestroyNode(to_remove_node);
            return;
        }
        else
        {
            //4、to_remove_node左右子树都有
            //需要先找到当前节点（to_remove_node）的右子树中最小的节点
            //把要删除的节点的值与该节点的值交换
            //从当前节点的右子树出发
            //尝试递归删除刚刚被交换的值
            SearchNode *min = to_remove_node->rchild;
            while(min->lchild != NULL)
            {
                min = min->lchild;
            }
            //此时min就是右子树中值最小的节点
            //交换两个节点的值
            //(其实此处只需要将min的值赋给to_remove_node即可
            //不管min处的值是什么，我们最终都会将这个min删掉
            //并且就可以达到我们的目的)
            to_remove_node->data = min->data;
            //尝试递归删除min->data
            SearchTreeRemove(&to_remove_node->rchild,min->data);
            return;
        }
    }
    return;
}
//删除(非递归版本)
void SearchTreeRemove1(SearchNode **proot, DataType to_remove)
{
    if(proot == NULL)
    {
        //非法输入
        return;
    }
    if(proot == NULL)
    {
        //空树
        return;
    }
    //不是空树的情况
    //先找到要删除的节点
    SearchNode *to_remove_node = *proot;
    SearchNode *parent = NULL;
    while(1)
    {
        if(to_remove_node == NULL)
        {
            //没找到要删除的元素，直接函数终止
            return;
        }
        if(to_remove < to_remove_node->data)
        {
            //待删除的元素值比当前的待删除的节点处的元素值小
            //说明当前带删除的节点不是我们要删除的节点
            //则我们就去左子树找
            parent = to_remove_node;
            to_remove_node = to_remove_node->lchild;
        }
        else if(to_remove > to_remove_node->data)
        {
            //待删除的元素值比当前的待删除的节点处的元素值大
            //说明当前带删除的节点不是我们要删除的节点
            //则我们就去右子树找
            parent = to_remove_node;
            to_remove_node = to_remove_node->rchild;
        }
        else
        {
            //待删除的元素值等于当前的待删除的节点处的元素值
            //说明当前带删除的节点就是我们要删除的节点
            //即我们找到了要删除的节点
            //跳出循环
            break;
        }
    }
    //找到位置以后就需要分情况讨论
    //情况1:待删除的节点没有左右子树
    if(to_remove_node->lchild == NULL && to_remove_node->rchild == NULL)
    {
        //分情况处理
        //先判断待删除的节点是否为根节点
        if(to_remove_node == *proot)
        {
            //待删除的节点是根节点
            //那我们就直接将根节点指向空即可
            *proot = NULL;
            //释放待删除的节点
        }
        //待删除的节点不是根节点
        else
        {
            //需要知道我们要删除的是当前根节点的右子树还是左子树
            if(to_remove_node->data > parent->lchild->data)
            {
                //待删除的节点是当前根节点的右子树
                parent->rchild = NULL;
                //释放待删除的节点
            }
            else
            {
                //待删除的节点是当前根节点的左子树
                parent->lchild = NULL;
                //释放待删除的节点
            }
        }
        //统一释放节点
        DestroyNode(to_remove_node);
    }
    //情况2：待删除的节点只有左子树
    else if(to_remove_node->lchild != NULL && to_remove_node->rchild == NULL)
    {
        //先判断待删除的节点是否为根节点
        if(to_remove_node == *proot)
        {
            //是根节点
            *proot = to_remove_node->lchild;
            //销毁待删除的节点
        }
        //不是根节点
        else
        {
            //判断待删除的节点是当前根节点的左子树还是右子树
            if(to_remove_node->data > parent->data)
            {
                //是当前根节点的右子树
                parent->rchild = to_remove_node->lchild;
                //销毁待删除的节点
            }
            else
            {
                //是当前根节点的左子树
                parent->lchild = to_remove_node->lchild;
                //销毁待删除的节点
            }
        }
        //统一释放待删除的节点
        DestroyNode(to_remove_node);
    }
    //情况3：待删除的节点只有右子树
    else if(to_remove_node->lchild == NULL && to_remove_node->rchild != NULL)
    {
        //先判断待删除的节点是否为根节点
        if(to_remove_node == *proot)
        {
            //是根节点
            *proot = to_remove_node->rchild;
            //销毁待删除的节点
        }
        //不是根节点
        else
        {
            //判断待删除的节点是当前根节点的左子树还是右子树
            if(to_remove_node->data > parent->data)
            {
                //是右子树
                parent->rchild = to_remove_node->rchild;
                //销毁待删除的节点
            }
            else
            {
                //是左子树
                parent->lchild = to_remove_node->rchild;
                //销毁待删除的节点
            }
        }
        //统一释放待删除的节点
        DestroyNode(to_remove_node);
    }
    //情况4：待删除的节点左右子树均存在
    else
    {
       SearchNode *min = to_remove_node->rchild;
       SearchNode *min_parent = to_remove_node;
       //该循环结束以后min就指向了to_remove_node右子树的最小值
       while(min->lchild != NULL)
       {
           min_parent = min;
           min = min->lchild;
       }
       //将该最小值赋给待删除的节点
       to_remove_node->data = min->data;
       //
       if(min->data < min_parent->data)
       {
           //min是min_parent的左子树
           //min一定没有左子树
           //就将min_parent的左子树指向min的右子树
           //无论右子树存在还是为空
           min_parent->lchild = min->rchild;
           //最后将min节点释放掉
       }
       else
       {
           //通常情况下，min是min_parent的左子树
           //但是初始情况下例外
           //就将min_parent的右子树指向min的右子树
           min_parent->rchild = min->rchild;
           //最后将min节点释放掉
       }
       //统一释放节点
       DestroyNode(min);
    }
}
////////////////////////////////////////
//以下为测试函数
////////////////////////////////////////
void TestInit()
{
    Test_Header;
    SearchNode *root;
    SearchTreeInit(&root);
    printf("expected *root = null,actual *root = %p\n",root);
}
void TestInsert()
{
    Test_Header;
    SearchNode *root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'e');
    printf("先序遍历结果为：");
    SearchTreePreOrder(root);
    printf("\n");
    printf("中序遍历结果为：");
    SearchTreeInOrder(root);
    printf("\n");
}
void TestInsert1()
{
    Test_Header;
    SearchNode *root;
    SearchTreeInit(&root);
    SearchTreeInsert1(&root,'c');
    SearchTreeInsert1(&root,'a');
    SearchTreeInsert1(&root,'d');
    SearchTreeInsert1(&root,'b');
    SearchTreeInsert1(&root,'e');
    printf("先序遍历结果为：");
    SearchTreePreOrder(root);
    printf("\n");
    printf("中序遍历结果为：");
    SearchTreeInOrder(root);
    printf("\n");
}
void TestFind()
{
    Test_Header;
    SearchNode *root;
    SearchTreeInit(&root);
    SearchNode *a = CreateNode('a');
    SearchNode *b = CreateNode('b');
    SearchNode *c = CreateNode('c');
    SearchNode *d = CreateNode('d');
    root = a;
    a->lchild = b;
    a->rchild = c;
    c->lchild = d;

    SearchNode *res1 = SearchTreeFind(root,'a');
    SearchNode *res2 = SearchTreeFind(root,'A');
    printf("expected res1 = %p,actual res1 = %p\n",a,res1);
    printf("expected res2 = null,actual res2 = %p\n",res2);
}
void TestFind1()
{
    Test_Header;
    SearchNode *root;
    SearchTreeInit(&root);
    SearchNode *a = CreateNode('a');
    SearchNode *b = CreateNode('b');
    SearchNode *c = CreateNode('c');
    SearchNode *d = CreateNode('d');
    root = a;
    a->lchild = b;
    a->rchild = c;
    c->lchild = d;

    SearchNode *res1 = SearchTreeFind1(root,'a');
    SearchNode *res2 = SearchTreeFind1(root,'A');
    printf("expected res1 = %p,actual res1 = %p\n",a,res1);
    printf("expected res2 = null,actual res2 = %p\n",res2);
}
void TestRemove()
{
    Test_Header;
    SearchNode *root;
    SearchTreeInit(&root);
    SearchNode *a = CreateNode('a');
    SearchNode *b = CreateNode('b');
    SearchNode *c = CreateNode('c');
    SearchNode *d = CreateNode('d');
    SearchNode *e = CreateNode('e');
    SearchNode *f = CreateNode('f');
    SearchNode *g = CreateNode('g');
    root = d;
    d->lchild = b;
    d->rchild = f;
    b->lchild = a;
    b->rchild = c;
    f->lchild = e;
    f->rchild = g;

    printf("[情况1：待删除的节点(e)没有左右子树]\n");
    SearchTreeRemove(&root,'e');
    printf("先序遍历结果为：");
    SearchTreePreOrder(root);
    printf("\n");
    printf("中序遍历结果为：");
    SearchTreeInOrder(root);
    printf("\n");
    printf("[情况2：待删除的节点(f)只有右子树]\n");
    SearchTreeRemove(&root,'f');
    printf("先序遍历结果为：");
    SearchTreePreOrder(root);
    printf("\n");
    printf("中序遍历结果为：");
    SearchTreeInOrder(root);
    printf("\n");
    printf("[情况3：待删除的节点(b)有左右子树]\n");
    SearchTreeRemove(&root,'b');
    printf("先序遍历结果为：");
    SearchTreePreOrder(root);
    printf("\n");
    printf("中序遍历结果为：");
    SearchTreeInOrder(root);
    printf("\n");
    printf("[情况4：待删除的节点(c)只有左子树]\n");
    SearchTreeRemove(&root,'c');
    printf("先序遍历结果为：");
    SearchTreePreOrder(root);
    printf("\n");
    printf("中序遍历结果为：");
    SearchTreeInOrder(root);
    printf("\n");
}
void TestRemove1()
{
    Test_Header;
    SearchNode *root;
    SearchTreeInit(&root);
    SearchNode *a = CreateNode('a');
    SearchNode *b = CreateNode('b');
    SearchNode *c = CreateNode('c');
    SearchNode *d = CreateNode('d');
    SearchNode *e = CreateNode('e');
    SearchNode *f = CreateNode('f');
    SearchNode *g = CreateNode('g');
    root = d;
    d->lchild = b;
    d->rchild = f;
    b->lchild = a;
    b->rchild = c;
    f->lchild = e;
    f->rchild = g;

    printf("[情况1：待删除的节点(e)没有左右子树]\n");
    SearchTreeRemove1(&root,'e');
    printf("先序遍历结果为：");
    SearchTreePreOrder(root);
    printf("\n");
    printf("中序遍历结果为：");
    SearchTreeInOrder(root);
    printf("\n");
    printf("[情况2：待删除的节点(f)只有右子树]\n");
    SearchTreeRemove1(&root,'f');
    printf("先序遍历结果为：");
    SearchTreePreOrder(root);
    printf("\n");
    printf("中序遍历结果为：");
    SearchTreeInOrder(root);
    printf("\n");
    printf("[情况3：待删除的节点(b)有左右子树]\n");
    SearchTreeRemove1(&root,'b');
    printf("先序遍历结果为：");
    SearchTreePreOrder(root);
    printf("\n");
    printf("中序遍历结果为：");
    SearchTreeInOrder(root);
    printf("\n");
    printf("[情况4：待删除的节点(c)只有左子树]\n");
    SearchTreeRemove1(&root,'c');
    printf("先序遍历结果为：");
    SearchTreePreOrder(root);
    printf("\n");
    printf("中序遍历结果为：");
    SearchTreeInOrder(root);
    printf("\n");
}

int main()
{
    TestInit();
    TestInsert();
    TestInsert1();
    TestFind();
    TestFind1();
    TestRemove();
    TestRemove1();
    return 0;
}
