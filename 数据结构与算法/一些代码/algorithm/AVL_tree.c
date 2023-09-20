//
// Created by ECHO on 2022/2/9.
//
#include "stdio.h"
#include "stdlib.h"

typedef struct nodeStruct{
    int value, depth;
    struct nodeStruct *leftPointer, *rightPointer;
} *node;

node createAVLtree();
void addNode(node*, int);
void adjustTheBalance(node *, int);
void dextrorotation(node *);
void sinistrogyration(node *);
void sinistrogyrationDextrorotation(node *);
void dextrorotationSinistrogyration(node *);
int getTreeDepth(node);
void renewTreeDepth(node);
void printAVLtree(node);

int main(){
    node tree = createAVLtree();
    printAVLtree(tree);
}

node createAVLtree(){
    node root = NULL;
    int n;
    printf("输入记录的个数：");
    scanf("%d", &n);
    for(int i = 0; i < n; i += 1){
        int value;
        printf("输入第%d个记录值：", i+1);
        scanf("%d", &value);
        addNode(&root, value);
    }
    return root;
}

void addNode(node *root, int value){
    if((*root) == NULL){
        (*root) = malloc(sizeof(struct nodeStruct));
        (*root)->value = value;
        (*root)->depth = 1;
        (*root)->leftPointer = NULL;
        (*root)->rightPointer = NULL;
    } else{
        if(value < (*root)->value){
            addNode(&(*root)->leftPointer, value);
        } else{
            if(value > (*root)->value){
                addNode(&(*root)->rightPointer, value);
            } else{
                printf("%d已经存在于树中，拒绝插入！\n", value);
                return;
            }
        }
    }
    renewTreeDepth(*root);
    adjustTheBalance(root, value);
}
void renewTreeDepth(node root){
    int leftDepth = getTreeDepth(root->leftPointer), rightDepth = getTreeDepth(root->rightPointer);
    root->depth = ((leftDepth > rightDepth) ? leftDepth : rightDepth) + 1;
}

int getTreeDepth(node root){
    return ((root == NULL) ? 0 : root->depth);
}

void adjustTheBalance(node *root, int value){
    if(getTreeDepth((*root)->leftPointer) - getTreeDepth((*root)->rightPointer) > 1){
        if((*root)->leftPointer->value > value){
            dextrorotation(root);
        } else{
            sinistrogyrationDextrorotation(root);
        }
    } else{
        if(getTreeDepth((*root)->leftPointer) - getTreeDepth((*root)->rightPointer) < -1){
            if((*root)->rightPointer->value < value){
                sinistrogyration(root);
            } else{
                dextrorotationSinistrogyration(root);
            }
        }
    }
}

void dextrorotation(node *root){
    node temp = (*root)->leftPointer;
    (*root)->leftPointer = temp->rightPointer;
    temp->rightPointer = (*root);
    renewTreeDepth(*root);
    renewTreeDepth(temp);
    *root = temp;
}

void sinistrogyration(node *root){
    node temp = (*root)->rightPointer;
    (*root)->rightPointer = temp->leftPointer;
    temp->leftPointer = (*root);
    renewTreeDepth(*root);
    renewTreeDepth(temp);
    *root = temp;
}

void sinistrogyrationDextrorotation(node *root){
    sinistrogyration(&(*root)->leftPointer);
    dextrorotation(root);
}

void dextrorotationSinistrogyration(node *root){
    dextrorotation(&(*root)->rightPointer);
    sinistrogyration(root);
}

void printAVLtree(node root){
    if(root == NULL){
        return;
    } else{
        printAVLtree(root->leftPointer);
        printf("%d   ", root->value);
        printAVLtree(root->rightPointer);
    }
}