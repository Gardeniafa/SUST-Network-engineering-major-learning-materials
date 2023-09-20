#include <iostream>
#define MAXQSIZE 100//队列可能达到的最大长度
#define OK 1
#define ERROR 0
#define OVERFLOW -2
using namespace std;
typedef struct {
    char name[20]; //姓名
    char sex; //性别，'F'表示女性，'M'表示男性
} Person;
//- - - - - 队列的顺序存储结构- - - - - 
typedef struct {
    Person data[MAXQSIZE];
    int front; //头指针
    int rear; //尾指针
} Queue;
typedef Queue *SqQueue;
SqQueue Mdancers, Fdancers; //分别存放男士和女士入队者队列
int InitQueue(SqQueue &Q);
void DestroyQueue(SqQueue &q);
int QueueLen(SqQueue Q);//队列长度 
int EnQueue(SqQueue &Q, Person e);//加入队列 
int QueueEmpty(SqQueue &Q);//队列是否为空 
int DeQueue(SqQueue &Q, Person &e);//出队列 
void DancePartner(Person dancer[], int num); //配对舞伴 
int main(){
    int i;
    int n;
    Person dancer[MAXQSIZE];
    cin>>n;
    for(i=0;i<n;i++) cin>> dancer[i].name >> dancer[i].sex;
    InitQueue(Mdancers); //男士队列初始化
    InitQueue(Fdancers); //女士队列初始化
    cout << "The dancing partners are:" << endl;
    DancePartner(dancer, n);
    if (!QueueEmpty(Fdancers)) {
        cout << "F:"<<QueueLen(Fdancers) ;
    } else if (!QueueEmpty(Mdancers)) {
        cout << "M:"<<QueueLen(Mdancers) ;
    }
    DestroyQueue(Fdancers);
    DestroyQueue(Mdancers);
    return 0;
}
int InitQueue(SqQueue &Q) {//构造一个空队列Q
    Q = new Queue; //为队列分配一个最大容量为MAXSIZE的数组空间
    if (!Q->data)
        exit( OVERFLOW); //存储分配失败
    Q->front = Q->rear = 0; //头指针和尾指针置为零，队列为空
    return OK;
}
void DestroyQueue(SqQueue &q)
{
    delete q;
}
/* 请在这里填写答案 */
int QueueLen(SqQueue Q){
    return (Q->rear - Q->front);
}
int EnQueue(SqQueue &Q, Person e){
    Q->rear = (Q->rear + 1) %MAXQSIZE;
    Q->data[Q->rear] = e;
    return 0;
}
int QueueEmpty(SqQueue &Q){
    if(Q->front - Q->rear == 0){
        return true;
    }else{
        return false;
    }
}
int DeQueue(SqQueue &Q, Person &e){
    Q->front=(Q->front+1)%MAXQSIZE;
    e=Q->data[Q->front];
    return 0;
}
void DancePartner(Person dancer[], int num){
    for(int i=0;i<num;i++){
        if(dancer[i].sex=='M'){
            EnQueue(Mdancers,dancer[i]);
        }else{
            EnQueue(Fdancers,dancer[i]);
        }
    }
    while(!QueueEmpty(Mdancers) && !QueueEmpty(Fdancers)){
        Person man,fam;
        DeQueue(Mdancers, man);
        DeQueue(Fdancers, fam);
        printf("%s %s\n", fam.name, man.name);
    }
}

