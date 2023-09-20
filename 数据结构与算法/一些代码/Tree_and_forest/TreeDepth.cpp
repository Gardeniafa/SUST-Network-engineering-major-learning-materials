
//头文件包含
#include <cstdlib>
#include <cstdio>
#include<malloc.h>

//函数状态码定义
#define TRUE       1
#define FALSE      0
#define OK         1
#define ERROR      0
#define OVERFLOW   -1
#define INFEASIBLE -2
#define NULL  0
typedef int Status;

//二叉链表存储结构定义
typedef int TElemType;
typedef struct BiTNode{
    TElemType data;
    struct BiTNode  *lchild, *rchild;
} BiTNode, *BiTree;

//创建二叉树各结点
//采用递归的思想创建
//递归边界：空树如何创建呢：直接输入0；
//递归关系：非空树的创建问题，可以归结为先创建根节点，输入其数据域值；再创建左子树；最后创建右子树。左右子树递归即可完成创建！
Status CreateBiTree(BiTree &T){
    TElemType e;
    scanf("%d",&e);
    if(e==0)T=NULL;
    else{
        T=(BiTree)malloc(sizeof(BiTNode));
        if(!T)exit(OVERFLOW);
        T->data=e;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return OK;
}

//下面是需要实现的函数的声明
int GetDepthOfBiTree ( BiTree T);
//下面是主函数
int main()
{
    BiTree T;
    int depth;
    CreateBiTree(T);
    depth= GetDepthOfBiTree(T);
    printf("%d\n",depth);
}

/* 请在这里填写答案 */
int GetDepthOfBiTree ( BiTree T)
{
    if(!T){
        return 0;
    }else{
        int d1=GetDepthOfBiTree(T->lchild);
        int d2=GetDepthOfBiTree(T->rchild);
        if(d1>d2){
            return d1+1;
        }else {
            return d2+1;
        }
    }
}
