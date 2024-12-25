#include <iostream>
#include <stdlib.h>

using namespace std;

#define LIST_INIT_SIZE 1000 // 存储空始分配量
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

int dlta[] = {50,25,12,6,3,1};

typedef struct
{

    ElemType *elem; // 存储空间基地址
    int length;     // 当前长度
    int listsize;   // 当前分配的存储空间

} SqList;

Status InitList_Sq(SqList &L);

Status ListInsert_Sq(SqList &L, int i, ElemType e);

void Print(SqList L);

// 希尔排序 

void ShellInsert(SqList &L, int dk);

void ShellSort(SqList &L, int dlta[], int t);

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
    cout << "希尔排序前:" << endl;
    Print(L);
    cout <<"希尔排序后:"<<endl;
    ShellSort(L,dlta,6);
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



void ShellInsert(SqList &L, int dk)
{

    // 对顺序表L作一趟希尔排序。本算法是和一趟直接插入排序相比，作了一下修改:
    //  1.前后记录位置的增量是dk,而不是1;
    //  2.elem[0]只是暂存单元，不是哨兵。当j<=0时,插入位置已找到。
    int i, j;

    for (i = dk + 1; i <= L.length; ++i)
    {

        if ((countcomp++||1)&& L.elem[i] < L.elem[i - dk])
        {                          // 需要将L.elem[i]插入有序增量子表
            L.elem[0] = L.elem[i]; // 暂存在L.elem[0]
            countmov ++;
            for (j = i - dk; j > 0 && (countcomp++||1)&&L.elem[0] < L.elem[j]; j -= dk){

                L.elem[j + dk] = L.elem[j]; // 记录后移，查找插入位置
                countmov++;

            }
            L.elem[j + dk] = L.elem[0];     // 插入
            countmov++;
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
