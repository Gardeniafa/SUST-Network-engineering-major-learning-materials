//库函数头文件包含
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

//函数状态码定义
#define OK          1
#define OVERFLOW   -2

typedef int  Status;

//顺序表的存储结构定义
#define LIST_INIT_SIZE  100
typedef int ElemType;  //假设线性表中的元素均为整型
typedef struct{
    ElemType* elem;   //存储空间基地址
    int length;       //表中元素的个数
    int listsize;     //表容量大小
}SqList;    //顺序表类型定义

Status ListCreate_Sq(SqList *L);
void ListReverse_Sq(SqList *L);

int main() {
    SqList L;
    ElemType *p;
    ListCreate_Sq(&L);
    ListReverse_Sq(&L);

    if(L.length){
        for(p=L.elem;p<L.elem+L.length-1;++p){
            printf("%d ",*p);
        }
        printf("%d",*p);
    }
    return 0;
}
/* 请在这里填写答案 */
Status ListCreate_Sq(SqList *L)
{
    int n;
    scanf("%d\n",&n);//写入顺序表数目
    //初始化L为一个空的有序顺序表
    L->elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L->elem)exit(OVERFLOW);//异常处理
    L->listsize=LIST_INIT_SIZE;
    L->length=0;
    for(int i = 0; i < n; i ++)
    {
        scanf("%d", &L->elem[i]);
        L->length++;
    }
        return OK;
}


void ListReverse_Sq(SqList *L)//最好用指针法
{
    int m = L->length/2;
    int temp;
    for(int i = 0;i < m; i++)
    {
        temp = *(L->elem+i);
        *(L->elem+i)= *(L->elem+L->length-1-i);
        *(L->elem+L->length-1-i) = temp;
    }
}