#include <stdio.h>
#include <stdlib.h>
typedef enum { false, true } bool;

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
    int flag;
};

/*------堆栈的定义-------*/
typedef Position SElementType;
typedef struct SNode *PtrToSNode;
struct SNode {
    SElementType Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;

/* 裁判实现，细节不表 */
Stack CreateStack();
bool IsEmpty( Stack S );
bool Push( Stack S, SElementType X );
SElementType Pop( Stack S ); /* 删除并仅返回S的栈顶元素 */
SElementType Peek( Stack S );/* 仅返回S的栈顶元素 */
/*----堆栈的定义结束-----*/

BinTree CreateBinTree(); /* 裁判实现，细节不表 */
void InorderTraversal( BinTree BT );
void PreorderTraversal( BinTree BT );
void PostorderTraversal( BinTree BT );

int main()
{
    BinTree BT = CreateBinTree();
    printf("Inorder:");    InorderTraversal(BT);    printf("\n");
    printf("Preorder:");   PreorderTraversal(BT);   printf("\n");
    printf("Postorder:");  PostorderTraversal(BT);  printf("\n");
    return 0;
}
/* 你的代码将被嵌在这里 */
void InorderTraversal( BinTree BT )
{
    BinTree T = BT;
    Stack S = CreateStack();
    while (T || !IsEmpty(S))
    {
        while (T)
        {
            Push(S,T);
            T = T->Left;
        }
        if (!IsEmpty(S))
        {
            T = Pop(S);
            printf(" %c",T->Data);
            T = T->Right;
        }
    }
}
void PreorderTraversal( BinTree BT )
{
    BinTree T = BT;
    Stack S = CreateStack();
    while (T || !IsEmpty(S))
    {
        while (T)
        {
            Push(S,T);
            printf(" %c",T->Data);
            T = T->Left;
        }
        if (!IsEmpty(S))
        {
            T = Pop(S);
            T = T->Right;
        }
    }
}
void PostorderTraversal( BinTree BT )
{
    BinTree T = BT;
    Stack S = CreateStack();
    while (T || !IsEmpty(S))
    {
        while (T)
        {
            Push(S,T);
            T->flag = 1;
            T = T->Left;
        }
        if (!IsEmpty(S))
        {
            T = Pop(S);
            if(T->flag == 1)
            {
                Push(S,T);
                T->flag = 2;
                T = T->Right;
            }
            else
            {

                printf(" %c",T->Data);
                T = NULL;
            }

        }
    }
}