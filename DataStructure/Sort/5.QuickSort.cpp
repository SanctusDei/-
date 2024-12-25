#include <iostream>
#include <stdlib.h>

using namespace std;

#define LIST_INIT_SIZE 1000// 存储空始分配量
#define LISTINCREMENT 100   // 纯粹空配增量

#define OVERFLOW 0
#define OK 1
#define ERROR -1

#define ElemType int
#define Status   int

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

// 直接插入排序 
int Partition(SqList &L, int low, int high);

void QSort(SqList &L, int low, int high);

 int main() {

    SqList L;
    InitList_Sq(L);
    int n;
    cout <<"请输入要排序数的个数:"<<endl;
    cin >> n;
    cout <<"请输入要排序数:"<<endl;
    for (int i = 1 ; i <= n; i++) {
        int data;
        cin >>data;
        ListInsert_Sq(L, i, data);
    }
    cout << "快速排序前:" << endl;
    Print(L);
    cout <<"快速排序后:"<<endl;
    QSort(L,1,L.length);
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


int Partition(SqList &L, int low, int high)
{
    // 交换顺序表L中子表L.elem[low...high]的记录,枢轴记录到位，并返回其所在位置，此时
    // 在它之前(后)的记录均不大（小）于它。

    ElemType pivotkey = L.elem[low]; // 枢轴记录关键字
    while (low < high)
    { // 从表的两端交替地向中间扫描
        while (low < high &&(countcomp++||1) && L.elem[high] >= pivotkey)
            --high;
        L.elem[low] = L.elem[high]; //	将比枢轴记录小的记录移动到低端
        countmov++;
        while (low < high && (countcomp++||1) && L.elem[low] <= pivotkey)
            ++low;
        L.elem[high] = L.elem[low];
        countmov++;
    }
    L.elem[low] = pivotkey;
    countmov++;
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