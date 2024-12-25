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
#define RcdType int

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

// 归并排序
void MSort(RcdType SR[], RcdType TR1[], int s, int t);

void Merge(RcdType SR[], RcdType TR[], int i, int m, int n);

void MergeSort(SqList &L);

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
    cout << "归并排序前:" << endl;
    Print(L);
    cout << "归并排序后:" << endl;
    MergeSort(L);
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

void Merge(RcdType SR[], RcdType TR[], int low, int mid, int high)
{
    // 将有序的SR[i...m]和SR[m+1...n]归并为有序的TR[1...n]
    int i,j,k;
	i=low; j=mid+1;k=low; 
    while(i<=mid&&j<=high)
	{                 	
		//将R中记录由小到大地并入T中

		if((countcomp++||1) &&SR[i]<=SR[j]) TR[k++]=SR[i++];

        else TR[k++]=SR[j++];

        countmov++; 
	} 
	while(i<=mid)                            		//将剩余的R[low..mid]复制到T中 
		{TR[k++]=SR[i++];countmov++;}                 
	while(j<=high)                           		//将剩余的R[j.high]复制到T中 
		{TR[k++]=SR[j++];countmov++;} 

} // Merge

void MSort(RcdType SR[], RcdType TR1[], int s, int t)
{
    // 将SR[s....t] 归并排序为TR1[s...t]
    RcdType *S = new RcdType[LIST_INIT_SIZE];
    if (s == t){

        TR1[s] = SR[s];
        countmov++;

    }
    else
    {

        int m = (s + t) / 2; // 将SR[s...t]平分为SR[s...m]和SR[m+1...t]
        MSort(SR, S, s, m);

        MSort(SR, S, m + 1, t);

        Merge(S, TR1, s, m, t);
    }
} // MSort

void MergeSort(SqList &L)
{
    // 对顺序表L作归并排序
    MSort(L.elem, L.elem, 1, L.length);
}