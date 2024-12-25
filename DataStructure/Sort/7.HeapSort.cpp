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

typedef SqList HeapType;

Status InitList_Sq(SqList &L);

Status ListInsert_Sq(SqList &L, int i, ElemType e);

void Print(SqList L);

// 堆排序

void HeapAdjust(HeapType &H, int s, int m);

void HeapSort(HeapType &H);

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
    cout << "堆排序前:" << endl;
    Print(L);
    cout << "堆排序后:" << endl;
    HeapSort(L);
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

void HeapAdjust(HeapType &H, int s, int m)
{
    // 已知H.elem[s...m]中记录的关键词除H.elem[s]之外均满足堆的定义，本函数调整H.elem[s]
    // 的关键词,使H.r[s...m]成为一个大顶堆(对其中记录的关键词而言)

    int rc = H.elem[s], j;
    for (j = 2 * s; j <= m; j *= 2)
    { // 沿key较大的孩子节点向下筛选
        if (j < m && (countcomp++||1) && H.elem[j] < H.elem[j + 1])
            ++j; // j为key较大的记录的下标
        if (!((countcomp++||1) &&rc < H.elem[j]))
            break; // rc应插入在位置s上
        H.elem[s] = H.elem[j];
        s = j;
    }
    H.elem[s] = rc; // 插入

} // HeapAdjust

void HeapSort(HeapType &H)
{
    // 对顺序表H进行堆排序
    int i;
    for (i = H.length / 2; i > 0; --i)
    { // 把H.elem[1...H.length]建成大根堆
        HeapAdjust(H, i, H.length);
    }

    for (i = H.length; i > 1; --i)
    {
        int Temp = H.elem[1];
        H.elem[1] = H.elem[i]; // 将堆堆顶记录和当前未经排序子序列Hr[1...i]中
        H.elem[i] = Temp; // 最后一个记录相互交换
        countmov +=3;
        HeapAdjust(H, 1, i - 1);
    }

} // HeapSort
