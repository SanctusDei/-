#include <iostream>

using namespace std;

typedef struct BinaryTree
{

    char data;          //	数据域
    BinaryTree *rchild; //  左孩子
    BinaryTree *lchild; //  右孩子

} *BiTree, BiTreeNode;
// 二叉树定义

void InitBiTree(BiTree &T)
{

    // 初始化二叉树
    T = (BiTreeNode *)malloc(sizeof(BiTreeNode));
    T->lchild = NULL;
    T->rchild = NULL;
}

void CreateBiTree(BiTree &T)
{
    // 按先序次序依次输入二叉树中节点的值（一个字符）,空格字符表示空树.
    // 构造二叉链表的二叉树T.
    char ch;
    scanf("%c", &ch);
    if (ch == ' ')
        T = NULL;
    else
    {
        T = (BiTreeNode *)malloc(sizeof(BiTreeNode));
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

void InOrderTraverse(BiTree T)
{
    // 中序遍历(递归)
    if (T != NULL)
    {

        InOrderTraverse(T->lchild);
        printf("%c", T->data);
        InOrderTraverse(T->rchild);
    }
}

void PreOrderTraverse(BiTree T)
{
    // 先序遍历(递归)
    if (T != NULL)
    {

        printf("%c", T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

void PostOrderTraverse(BiTree T)
{
    // 后序遍历(递归)
    if (T != NULL)
    {

        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%c", T->data);
    }
}

void print(BiTree T,int n)
{
    int i;
    if(T)
      {
        print(T->rchild,n+1);
        for(i=0;i<n;i++)
        {
         printf("\t");
         }
         printf("%2c\n",T->data);
         print(T->lchild,n+1);
       }
}
int main()
{
    BiTree T;
    InitBiTree(T);
    CreateBiTree(T);
    cout << "凹入表打印二叉树" <<endl;
    print(T,0);
    cout << "先序遍历顺序:" << endl;
    PreOrderTraverse(T);
    cout << endl;
    cout << "中序遍历顺序:" << endl;
    InOrderTraverse(T);
    cout << endl;
    cout << "后序遍历顺序:" << endl;
    PostOrderTraverse(T);

    return 0;
}
