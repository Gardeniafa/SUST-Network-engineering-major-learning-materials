#include <stdio.h>
#include <malloc.h>
typedef struct node
{
    int data;
    struct node *Lson,*Rson;
}Bnode,*Bptr;

int num (Bptr p);

Bptr creat()
{
    Bptr p;
    int x;
    scanf("%d",&x);
    if(x==0)
        return NULL;
    p=(Bptr)malloc(sizeof(Bnode));
    p->data=x;
    p->Lson=creat();
    p->Rson=creat();
    return p;
}

int main()
{
    Bptr root;
    int k;
    root=creat();
    k=num(root);
    printf("%d\n", k);
    return 0;

}

/* 请在这里填写答案 */
int num(Bptr p){
    if(p == NULL){
        return 0;
    } else{
        if(p->Rson == NULL || p->Lson == NULL){
            return 1;
        } else{
            return num(p->Lson)+ num(p->Rson);
        }
    }
}