#include "stdio.h"
#define MaxSize 100
int top;
int mystack[MaxSize];
typedef enum{false, true} bool;
bool isEmpty();
void Push(int x);
int getTop();
void Pop();
void dec2bin(int x) {
    top = -1;
    while (x) {
        Push(x % 2);
        x /= 2;
    }
    while (!isEmpty()) {
        int t = getTop();
        Pop();
        printf("%d", t);
    }
    printf("\n");
}
int main()
{
    int n;
    scanf("%d", &n);
    dec2bin(n);
    return 0;
}
bool isEmpty(){
    if(top == -1){
        return true;
    }
    return false;
}
void Push(int num){
    top += 1;
    mystack[top] = num;
}
int getTop(){
    return mystack[top];
}
void Pop(){
    top += -1;
}