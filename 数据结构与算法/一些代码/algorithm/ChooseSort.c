#include "stdio.h"
#include "stdlib.h"
typedef struct listStruct{
    int *data;
    int length;
} *list;
void chooseSort(list);
void listPrinter(list);
int main(){
    printf("输入记录的长度：");
    int length;
    scanf("%d", &length);
    int data[length];
    for (int i = 0; i < length; i += 1){
        printf("输入第%d个记录：", i+1);
        scanf("%d", &data[i]);
    }
    list array = (list) malloc(sizeof(struct listStruct));
    array->length = length;
    array->data = data;
    printf("\n输入的记录为：");
    listPrinter(array);
    chooseSort(array);
    printf("\n排完的记录为：");
    listPrinter(array);
}
void chooseSort(list array){
    for(int i = 0; i < array->length; i += 1){
        int minNumIndex = i;
        for (int j = i+1; j < array->length; j += 1){
            if(array->data[minNumIndex] > array->data[j]){
                minNumIndex = j;
            }
        }
        int cache = array->data[i];
        array->data[i] = array->data[minNumIndex];
        array->data[minNumIndex] = cache;
    }
}
void listPrinter(list array){
    printf("[");
    for (int i = 0; i < array->length; i += 1){
        printf(" %d", array->data[i]);
        if(i == array->length-1){
            printf("]");
        } else{
            printf(",");
        }
    }
}