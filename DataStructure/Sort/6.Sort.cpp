#include <iostream>
#include <stdlib.h>

using namespace std;

#define LIST_INIT_SIZE 100 // 存储空始分配量
#define LISTINCREMENT 10   // 纯粹空配增量
#define MAX_NUM_OF_KEY 7   // 关键字的最大值
#define RADIX         10   // 关键字基数，此时是十进制整数的基数
#define MAX_SPACE  10000



#define OVERFLOW 0
#define OK 1
#define ERROR -1

#define ElemType int
#define Status   int
#define KeysType int

using namespace std;

typedef struct
{

    ElemType *elem; // 存储空间基地址
    int length;     // 当前长度
    int listsize;   // 当前分配的存储空间

} SqList;

typedef SqList HeapType; // 堆采用顺序表存储
typedef SqList RcdType;
 

RcdType TR2;            // 用于实现归并排序


typedef struct 
{

    KeysType keys[MAX_NUM_OF_KEY];  // 关键字
    
    int next;                       // 静态链表的节点类型

} SLCell;

typedef struct 
{
    SLCell r[MAX_SPACE];            // 静态链表的可利用空间,r[0]为头节点
    int keynum;                     // 记录的当前关键字个数
    int recnum;                     // 静态链表的当前长度
} SLList;                           // 静态链表类型
typedef int ArrType[RADIX];         // 指针数组类型





Status InitList_Sq(SqList &L);

Status ListInsert_Sq(SqList &L, int i, ElemType e);

// 起泡排序
void BubbleSort(SqList &L);
// 快速排序
int Partition(SqList &L, int low, int high);

void QSort(SqList &L, int low, int high);

void Print(SqList L);

// 直接插入排序

void InsertSort(SqList &L);

// 折半插入排序

void BInsertSort(SqList &L);

// 二路插入排序

// 希尔排序
void ShellInsert(SqList &L, int dk);

void ShellSort(SqList &L, int dlta[], int t);

// 简单选择排序
void SelectSort(SqList &L);

int SelectMinKey(SqList L, int i);

// 堆排序
void HeapAdjust(HeapType &H, int s, int m);

void HeapSort(HeapType &H);

// 归并排序

void Merge(RcdType SR, RcdType &TR, int i, int m, int n);

void MSort(RcdType SR, RcdType &TR1, int s, int t);

void MergeSort(SqList &L);

// 基数排序

void Distribute(SLCell &r, int i, ArrType &f, ArrType &e);

void Collect(SLCell &r, int i, ArrType f, ArrType e);

void RadixSort(SLList &L);

int main()
{
    TR2.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));

    return 0;
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

void InsertSort(SqList &L)
{
    // 对顺序表L作直接插入排序
    int i, j;
    for (i = 2; i <= L.length; ++i)
    {
        if (L.elem[i] < L.elem[i - 1])
        {

            L.elem[0] = L.elem[i];
            L.elem[i] = L.elem[i - 1];
            for (j = i - 2; L.elem[0] < L.elem[j]; --j)
                L.elem[j + 1] = L.elem[j];
            L.elem[j + 1] = L.elem[0];
        }
    }
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

int Partition(SqList &L, int low, int high)
{
    // 交换顺序表L中子表L.elem[low...high]的记录,枢轴记录到位，并返回其所在位置，此时
    // 在它之前(后)的记录均不大（小）于它。

    ElemType pivotkey = L.elem[low]; // 枢轴记录关键字
    while (low < high)
    { // 从表的两端交替地向中间扫描
        while (low < high && L.elem[high] >= pivotkey)
            --high;
        L.elem[low] = L.elem[high]; //	将比枢轴记录小的记录移动到低端
        while (low < high && L.elem[low] <= pivotkey)
            ++low;
        L.elem[high] = L.elem[low];
    }
    L.elem[low] = pivotkey;
    return low;
} // Partition

void QSort(SqList &L, int low, int high)
{
    // 对顺序表L中的子序列L.elem[low..high]作快速排序
    if (low < high)
    { // 长度大于1
        ElemType pivotloc;
        pivotloc = Partition(L, low, high); // 将L.elem[row...high]一分为二
        QSort(L, low, pivotloc - 1);        // 对低子表递归排序，pivotloc是枢轴位置
        QSort(L, pivotloc + 1, high);       // 对稿子表进行排序
    }

} // QSort

void Print(SqList L)
{
    for (int i = 0; i < L.length; i++)
    {
        cout << L.elem[i] << " ";
    }
    cout << endl;
}

void BInsertSort(SqList &L)
{
    // 对顺序表L作折半插入排序
    int i, j;
    for (i = 2; i <= L.length; ++i)
    {
        L.elem[0] = L.elem[i];
        int low = 1, high = i - 1;
        while (low <= high)
        {

            int m = (low + high) / 2;
            if (L.elem[0] < L.elem[m])
                high = m - 1;
            else
                low = m + 1;
        } // while
        for (j = i - 1; j >= high + 1; --j)
            L.elem[j + 1] = L.elem[j];
        L.elem[high + 1] = L.elem[0];
    } // for
} // BInsertSort

void ShellInsert(SqList &L, int dk)
{

    // 对顺序表L作一趟希尔排序。本算法是和一趟直接插入排序相比，作了一下修改:
    //  1.前后记录位置的增量是dk,而不是1;
    //  2.elem[0]只是暂存单元，不是哨兵。当j<=0时,插入位置已找到。
    int i, j;

    for (i = dk + 1; i <= L.length; ++i)
    {

        if (L.elem[i] < L.elem[i - dk])
        {                          // 需要将L.elem[i]插入有序增量子表
            L.elem[0] = L.elem[i]; // 暂存在L.elem[0]
            for (j = i - dk; j > 0 && L.elem[0] < L.elem[j]; j -= dk)
                L.elem[j + dk] = L.elem[j]; // 记录后移，查找插入位置
            L.elem[j + dk] = L.elem[0];     // 插入
        }
    }

} // ShellInsert

void ShellSort(SqList &L, int dlta[], int t)
{
    // 按照增量序列 dlta[0..t-1] 对顺序表L作希尔排序
    int k;
    for (k = 0; k < t; ++k)
    {
        ShellInsert(L, dlta[k]);
    }
} // ShellSort

void BubbleSort(SqList &L)
{
    int i, j;
    for (i = 1; i <= L.length; i++)
    {
        for (j = 1; j <= L.length - i; i++)
        {
            if (L.elem[j] > L.elem[j + 1])
            {

                L.elem[0] = L.elem[j];
                L.elem[j + 1] = L.elem[j];
                L.elem[j] = L.elem[0];
            }
        }
    }

} // BubbleSort

int SelectMinKey(SqList L, int i)
{
    int j, pos = 1;
    L.elem[0] = L.elem[1];
    for (j = i; j <= L.length; j++)
    {
        if (L.elem[j] < L.elem[0])
        {

            L.elem[0] = L.elem[j];
            pos = j;
        }
    }

    return pos;
}

void SelectSort(SqList &L)
{
    // 对顺序表L作简单选择排序
    int i, j;
    for (i = 1; i < L.length; ++i)
    {
        j = SelectMinKey(L, i);
        if (i != j)
            L.elem[i] = L.elem[j];
    }
} // SelectSort

void HeapAdjust(HeapType &H, int s, int m)
{
    // 已知H.elem[s...m]中记录的关键词除H.elem[s]之外均满足堆的定义，本函数调整H.elem[s]
    // 的关键词,使H.r[s...m]成为一个大顶堆(对其中记录的关键词而言)

    int rc = H.elem[s], j;
    for (j = 2 * s; j <= m; j *= 2)
    { // 沿key较大的孩子节点向下筛选
        if (j < m && H.elem[j] < H.elem[j + 1])
            ++j; // j为key较大的记录的下标
        if (!(rc < H.elem[j]))
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
        H.elem[i] = H.elem[1]; // 最后一个记录相互交换
        HeapAdjust(H, 1, i - 1);
    }

} // HeapSort

void Merge(RcdType SR, RcdType &TR, int i, int m, int n)
{
    // 将有序的SR[i...m]和SR[m+1...n]归并为有序的TR[1...n]
    int j, k;
    for (j = m + 1, k = i; i <= m && j <= n; ++k)
    { // 将SR中记录由小到大地并入TR

        if (SR.elem[i] <= SR.elem[j])
            TR.elem[k] = SR.elem[i++];
        else
            TR.elem[k] = SR.elem[j++];
    }

    if (j <= m)
        TR.elem[k++] = SR.elem[i++];
    if (j <= n)
        TR.elem[k++] = SR.elem[j++];

} // Merge

void MSort(RcdType SR, RcdType &TR1, int s, int t)
{
    // 将SR[s....t] 归并排序为TR1[s...t]
    if (s == t)
        TR1.elem[s] = SR.elem[s];
    else
    {

        int m = (s + t) / 2; // 将SR[s...t]平分为SR[s...m]和SR[m+1...t]
        MSort(SR, TR1, s, m);
        MSort(SR, TR1, m + 1, t);
        Merge(TR1, TR2, s, m, t);
    }
} // MSort

void MergeSort(SqList &L)
{
    // 对顺序表L作归并排序
    MSort(L, L, 1, L.length);
}

void Distribute(SLCell (&r)[], int i, ArrType &f, ArrType &e) {

    // 静态链表L的r域中记录已按(keys[0],......,keys[i-1])有序
    // 本算法按第i个关键字keys[i]建立RADIX个子表,使同一子表记录的keys[i]相同。
    // f[0.. RADIX-1]和e[0...RADIX-1]分别指向各子表中第一个和最后一个记录。
    int j,p;
    for (j = 0; j < RADIX; ++j) f[j] = 0;
    for (p = r[0].next; p; p =r[p].next ) { 


    }

}

void Collect(SLCell &r, int i, ArrType f, ArrType e) {}

void RadixSort(SLList &L) {}



