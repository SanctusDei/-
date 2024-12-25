#include <iostream>
#include <string.h>
#include <cmath>

using namespace std;

#define MAX_NUM_OF_KEY   8       // 关键字项数的最大相
#define RADIX         10   // 关键字基数，此时是十进制整数的基数
#define MAX_SPACE  10000

int countcomp = 0;
int countmov = 0;
int count = 0;

typedef char KeysType;           
typedef int IofoType;

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
typedef int ArrType[RADIX+2];         // 指针数组类型


int ord(char c) {

    // 返回k的映射(各位整数)
    return c-'0';

}

void Print2(SLList L)
{  
	//按数组序号输出静态链表
    int i,j;
    for(i=0;i < L.recnum;i++ )
    {
		for(j=L.keynum-1;j>=0;j--)
			cout<<L.r[i].keys[j];
        cout<<" ";    
    }

    cout << endl;
}

void Print(SLList L)
{  
	//按数组序号输出静态链表
    int i,j;
    for(i=L.r[0].next;i!=0;i = L.r[i].next)
    {
		for(j=L.keynum-1;j>=0;j--)
			cout<<L.r[i].keys[j];
        cout<<" ";    
    }

    cout << endl;
}


void Distribute(SLCell *r, int i ,ArrType &f, ArrType &e) {
    // 静态链表L的r域中记录已按(keys[0],......,keys[i-1])有序
    // 本算法按第i个关键字keys[i]建立RADIX个子表,使同一子表记录的keys[i]相同。
    // f[0.. RADIX-1]和e[0...RADIX-1]分别指向各子表中第一个和最后一个记录。
    int j,p;
    for (j = 0; j < RADIX+2; ++j) f[j] = 0;                   // 各子表初始化为空表
    for (p = r[0].next;(countcomp++||1) && p; p =r[p].next ) {

        j = ord(r[p].keys[i]);                              // ord将记录第i各关键词映射到[0...RADIX-1]
        if(!f[j]) f[j] = p;
        else r[e[j]].next=p;
        countmov++; 
        e[j]=p;                                             // 将p所指的结点插入第j各子表中
        countmov++;
    }//for

}//Distribute

int succ(int i) {

    //求后继函数
    return ++i;

}

void Collect(SLCell *r, int i, ArrType &f, ArrType &e) {
    // 本算法按keys[i]自小到大地将[0..RADIX-1]所指各子表依次链接成一个链表
    // e[0..RADIX-1] 为各子表的尾指针
    int j,t;
    for (j=0; (countcomp++||1) &&!f[j];j=succ(j));                                 // 找第一个非空子表,succ为求后继函数
    r[0].next = f[j]; t = e[j];
    countmov += 2;
                                     // r[0].next指向第一个非空子表中第一个节点

    while(j<RADIX) {

        for(j = succ(j); j < RADIX-1&&(countcomp++||1) &&!f[j]; j =succ(j));       // 找到下一个非空子表
        

        if(f[j]) {
            r[t].next = f[j]; t = e[j];
            countmov+=2;
        }
        
    
    }
    r[t].next = 0;                                            // t指向最后一个非空子表中的最后一个结点
    countmov++;
}// Collect

void RadixSort(SLList &L) {

    // L是采用静态链表表示的顺序表
    // 对L作基数排序，使得L成为按关键词自小到大的有序静态链表, L.r[0]为头结点
    int i;
    ArrType f ,e ;
    for (i = 0;i < L.recnum;++i) L.r[i].next = i+1;
    L.r[L.recnum].next = 0;                     //将L改造成为静态链表
    for (i = 0;i < L.keynum;++i) {
        //按最低位优先依次对各关键词进行分配和收集
        Distribute(L.r,i,f,e);                   //第i次分配
        
        Collect(L.r,i,f,e);                      //第i次收集

    }//for

} // RadixSort

void InitList(SLList *L)
{ 
	//初始化静态链表L（把数组D中的数据存于L中）

	char c[MAX_SPACE],c1[MAX_SPACE];
    int i,j,n,max;
    max = -1000000;						
    cout<<"请输入数据个:"<<endl;
    cin>>n;
    int *D=new int[n];
	cout<<"请输入排排序的数据：\n";
    for(i=0;i<n;i++)
    {
	    cin>>D[i];
	    if(max<D[i])
			max=D[i];
    }

    (*L).keynum=(int)(ceil(log10(max)));
    (*L).recnum=n;

    for(i=1;i<=n;i++)
    {
        itoa(D[i-1],c,10);					//将10进制整型转化为字符型,存入c 
		for(j=strlen(c);j<(*L).keynum;j++)  //若c的长度<max的位数,在c前补'0' 
		{
		   strcpy(c1,"0");
		   strcat(c1,c);
		   strcpy(c,c1);        
		}
		for(j=0;j<(*L).keynum;j++)
			(*L).r[i].keys[j]=c[(*L).keynum-1-j];
    }
}



int main() {

    SLList L;
    InitList(&L);
    cout << "基数排序前序列:"<<endl;
    Print2(L);
    cout << "基数排序后序列:" <<endl;
    RadixSort(L);
    Print(L);

    count = countcomp + countmov;
    cout << "移动次数:"<<countmov<<endl; 
    cout << "比较次数:"<<countcomp<<endl;
    cout <<"操作总次数:"<<count<<endl;    


    return 0;
}