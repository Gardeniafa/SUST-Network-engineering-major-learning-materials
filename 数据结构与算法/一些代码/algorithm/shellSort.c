typedef struct listStruct{
    int *data;
    int length;
} *list;
#include "stdio.h"
#include "stdlib.h"
void shellSort(list);
void shellInsert(list, int);
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
    shellSort(array);
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
void shellInsert(list array, int distance){
    for(int i = distance; i < array->length; i += 1){
        if(array->data[i-distance] > array->data[i]){
            int cache = array->data[i], insertPosition = i-distance;
            for (int j = i-distance; (j >= 0) && (array->data[j] > cache); j += -distance){
                array->data[j+distance] = array->data[j];
                insertPosition = j;
            }
            array->data[insertPosition] = cache;
        }
    }
    printf("\n");
    listPrinter(array);
}
void shellSort(list array){
    int increraseSteps[] = {3, 2, 1};
    for (int i = 0; i < 3; i += 1){
        shellInsert(array, increraseSteps[i]);
    }
}