#include <iostream>

using namespace std;
#define QElemType int
#define Status    int
#define OVERFLOW  -1
#define OK         1
#define ERROR     -1
#define MAXQSIZE   7        // 最大队列长度
typedef struct  
{

    QElemType *base;        // 初始化的动态分配存储空间
    int front;              // 头指针，若队列不空，指向队列头元素
    int rear;               // 尾指针，若队列不空，指向队尾元素的下一个位置

} SqQueue;

Status InitQueue (SqQueue &Q) {

    // 构造一个空队列Q
    Q.base = (QElemType *) malloc (MAXQSIZE *sizeof(QElemType));
    if(!Q.base) exit(OVERFLOW);         //存储分配失败
    Q.front = Q.rear = 0;
    return OK;

}


int QueueLength(SqQueue Q) {

    // 返回Q的元素个数，即队列的长度
    return (Q.rear- Q.front + MAXQSIZE) % MAXQSIZE;
    
}

Status EnQueue (SqQueue &Q, QElemType e) {
    // 插入元素 e 为Q的新的队尾元素
    if((Q.rear+1)%MAXQSIZE == Q.front ) return ERROR;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear+1) % MAXQSIZE;
    return OK;
}


Status DeQueue(SqQueue &Q, QElemType &e) {
    // 若队列不空,则删除Q的对头元素，用e返回其值，并返回OK;
    // 否则返回ERROR
    if(Q.front == Q.rear ) return ERROR;
    e = Q.base[Q.front];
    Q.front = (Q.front+1)%MAXQSIZE;
}

void PrintQueue(SqQueue Q) {
    for (int i = 0; i < QueueLength(Q); i++) {
        cout << Q.base[(Q.front+i)%MAXQSIZE] << " ";
    }
    cout << endl;

}

int main() {
    SqQueue Q;
    InitQueue(Q);

    int data[] = {7, 5, 3, 9, 2, 4},e;
    for (int i = 0 ; i < 6; ++i) {
        EnQueue(Q,data[i]);
    }

    DeQueue(Q,e);
    DeQueue(Q,e);
    DeQueue(Q,e);

    EnQueue(Q,15);
    EnQueue(Q,18);
    PrintQueue(Q);
    
    return 0;
}
