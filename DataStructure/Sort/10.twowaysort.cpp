#include <iostream>
#include <stdlib.h>

using namespace std;

#define LIST_INIT_SIZE 1000 // 存储空始分配量
#define LISTINCREMENT 100   // 纯粹空配增量

#define OVERFLOW 0
#define OK 1
#define ERROR -1

#define ElemType int
#define Status int

using namespace std;

int countcomp = 0;
int countmov = 0;
int count = 0;

typedef struct
{

    ElemType *elem; // 存储空间基地址
    int length;     // 当前长度
    int listsize;   // 当前分配的存储空间

} SqList;

Status InitList_Sq(SqList &L);

Status ListInsert_Sq(SqList &L, int i, ElemType e);

void Print(SqList L);

// 折半插入排序

void TWOWAYInsertSort(SqList &L)
{
    int length = L.length;  // 数组长度
    int temp[length] = {0}; // 辅助数组
    int first = 0;          // 开始位置
    int final = 0;          // 最后位置

    temp[first] = L.elem[1]; // 加入第一个元素
    countmov++;
    for (int i = 1; i < length; ++i)
    { // 遍历未排序序列
        if ((countcomp++||1) &&L.elem[i + 1] < temp[first])
        {

            first = (first - 1 + length) % length; // 起始位置前移
            temp[first] = L.elem[i + 1];
            countmov++;
        }
        else if (L.elem[i + 1] > temp[final])
        {

            final = (final + 1 + length) % length;
            temp[final] = L.elem[i + 1];
            countmov++;
        }
        else
        {

            int j = (final + 1 + length) % length;
            while ((countcomp++||1) &&temp[(j - 1 + length) % length] > L.elem[i + 1])
            {

                temp[(j + length) % length] = temp[(j - 1 + length) % length];
                countmov++;
                j = (j - 1 + length) % length;
            }

            temp[(j + length) % length] = L.elem[i + 1];
            final = (final + 1 + length) % length;
            countmov++;

        }
    }

    for (int i = 0; i < length; i++)
    {

        L.elem[i + 1] = temp[(first + i) % length];
        countmov++;
    }
}


int main()
{

    SqList L;
    InitList_Sq(L);
    int n;
    cout << "请输入要排序数的个数:" << endl;
    cin >> n;
    cout << "请输入要排序数:" << endl;
    for (int i = 1; i <= n; i++)
    {
        int data;
        cin >> data;
        ListInsert_Sq(L, i, data);
    }
    cout << "直接插入排序前:" << endl;
    Print(L);
    cout << "直接插入排序后:" << endl;
    TWOWAYInsertSort(L);
    Print(L);

    count = countcomp + countmov;
    cout << "移动次数:"<<countmov<<endl; 
    cout << "比较次数:"<<countcomp<<endl;
    cout <<"操作总次数:"<<count<<endl;      
}

Status InitList_Sq(SqList &L)
{
    // 构造一个空的线性表L

    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem)
        exit(OVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;

    return OK;
}

void Print(SqList L)
{
    for (int i = 1; i <= L.length; i++)
    {
        cout << L.elem[i] << " ";
    }
    cout << endl;
}

Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
    // 在顺序线性表L中第i个位置之前插入新的元素e,
    // i的合法值为 1 <= i <= ListLength_Sq(L)+1
    if (i < 1 || i > L.length + 1)
        return ERROR; // i值不合法
    if (L.length >= L.listsize)
    { // 当前存储空间已满，增加分配

        ElemType *newbase = (ElemType *)realloc(L.elem,
                                                (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            exit(OVERFLOW);          // 存储分配失败
        L.elem = newbase;            // 新基址
        L.listsize += LISTINCREMENT; // 增加存储容量
    }

    ElemType *q = &(L.elem[i]); // q为插入位置

    for (ElemType *p = &(L.elem[L.length]); p >= q; --p)

        *(p + 1) = *p;

    *q = e;     // 插入e
    ++L.length; // 表长加1
    return OK;

} // ListInsert_Sq


