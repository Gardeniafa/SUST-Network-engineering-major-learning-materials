typedef struct listStruct{
    int *data;
    int length;
} *list;
#include "stdio.h"
#include "stdlib.h"
void insertSort(list);
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
    insertSort(array);
    printf("\n排完的记录为：");
    listPrinter(array);
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
void insertSort(list array){
    for (int i = 0; i < array->length-1; i += 1){
        if(array->data[i] > array->data[i+1]){
            int insertPosition = i, minNum = array->data[i+1];
            for (int j = i; (j >= 0 && array->data[insertPosition] > minNum); j += -1){
                array->data[j+1] = array->data[j];
                insertPosition = j;
            }
            array->data[insertPosition] = minNum;
        }
    }
}