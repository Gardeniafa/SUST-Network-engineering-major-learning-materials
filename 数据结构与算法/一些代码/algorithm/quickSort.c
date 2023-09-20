#include "stdio.h"
#include "stdlib.h"
typedef struct list_struct{
    int *data;
    int length, lowPointer, highPointer;
} *list;
void printArr(list);
int singleQuicksort(list);
void quickSort(list);
int main(){
    printf("输入记录的个数：");
    int n;
    scanf("%d", &n);
    int *data = (int*)malloc(sizeof(int)*(n+1));
    for (int i = 1; i <= n; i += 1){
        printf("输入第%d个记录：", i);
        scanf("%d", data + i);
    }
    list arr = (list) malloc(sizeof(struct list_struct));
    arr->length=n;arr->data=data;arr->lowPointer=1;arr->highPointer=n;
    printf("\n输入数组为：");
    printArr(arr);
    quickSort(arr);
    printf("\n排序完成为：");
    printArr(arr);
}
void printArr(list arr){
    printf("[");
    for (int i = 1; i <= arr->length; i += 1){
        printf(" %d", arr->data[i]);
        if(i == arr->length){
            printf(" ]");
        } else{
            printf(",");
        }
    }
}
int singleQuicksort(list arr){
    arr->data[0] = arr->data[arr->lowPointer];
    int cache = arr->data[arr->lowPointer];
    while (arr->lowPointer < arr->highPointer){
        while ((arr->lowPointer < arr->highPointer) && (arr->data[arr->highPointer] >= cache)){
            arr->highPointer += -1;
        }
        arr->data[arr->lowPointer] = arr->data[arr->highPointer];
        while ((arr->lowPointer < arr->highPointer) && (arr->data[arr->lowPointer] <= cache)){
            arr->lowPointer += 1;
        }
        arr->data[arr->highPointer] = arr->data[arr->lowPointer];
    }
    arr->data[arr->lowPointer] = arr->data[0];
    return arr->lowPointer;
}
void quickSort(list arr){
    if(arr->highPointer - arr->lowPointer > 0){
        int lowPointerTemp = arr->lowPointer, highPointerTemp = arr->highPointer;
        int middle = singleQuicksort(arr);
        list Larr = malloc(sizeof(struct list_struct));
        Larr->data = arr->data;
        Larr->length = arr->length;
        Larr->lowPointer = lowPointerTemp;
        Larr->highPointer = middle -1;
        list Rarr = malloc(sizeof(struct list_struct));
        Rarr->data = arr->data;
        Rarr->length = arr->length;
        Rarr->lowPointer = middle+1;
        Rarr->highPointer = highPointerTemp;
        quickSort(Larr);
        quickSort(Rarr);
    }
}