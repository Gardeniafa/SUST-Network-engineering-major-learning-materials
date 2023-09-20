#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree CreatBinTree(); /* 实现细节忽略 */
void InorderTraversal( BinTree BT );
void PreorderTraversal( BinTree BT );
void PostorderTraversal( BinTree BT );
void LevelorderTraversal( BinTree BT );

int main()
{
    BinTree BT = CreatBinTree();
    printf("Inorder:");    InorderTraversal(BT);    printf("\n");
    printf("Preorder:");   PreorderTraversal(BT);   printf("\n");
    printf("Postorder:");  PostorderTraversal(BT);  printf("\n");
    printf("Levelorder:"); LevelorderTraversal(BT); printf("\n");
    return 0;
}
/* 你的代码将被嵌在这里 */
void InorderTraversal( BinTree BT )
{
    if(BT != NULL)
    {
        InorderTraversal(BT->Left);
        printf(" %c",BT->Data);
        InorderTraversal(BT->Right);
    }
}
void PreorderTraversal( BinTree BT )
{
    if(BT != NULL)
    {
        printf(" %c",BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}
void PostorderTraversal( BinTree BT )
{
    if(BT != NULL)
    {
        PostorderTraversal(BT->Left);
        PostorderTraversal(BT->Right);
        printf(" %c",BT->Data);
    }
}
void LevelorderTraversal( BinTree BT )
{
    int  i=0,j=0;
    BinTree arr[100]={NULL},p=NULL;
    if(BT!=NULL)
    {
        arr[i]=BT;
        i += 1;
        while(i>j)
        {
            p=arr[j];
            j += 1;
            printf(" %c",p->Data);
            if(p->Left!=NULL) {
                arr[i++]=p->Left;
            }
            if(p->Right!=NULL)
            {
                arr[i++]=p->Right;
            }
        }
    }
}

