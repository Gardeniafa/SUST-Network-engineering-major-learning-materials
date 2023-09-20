#include "stdio.h"
int singleQuicksort(int *, int, int);
void quickSortMain(int *, int, int);
void intArrayPrinter(int*, int);
int main(){
    int recordLength;
    printf("输入待排记录的长度：");
    scanf("%d", &recordLength);
    int array[recordLength];
    for (int i = 0; i < recordLength; i += 1){
        printf("输入第%d个记录值：", i+1);
        scanf("%d", &array[i]);
    }
    printf("\n你输入的记录为：");
    intArrayPrinter(array, recordLength);
    quickSortMain(array, 0, recordLength-1);
    printf("\n排完的记录为：");
    intArrayPrinter(array, recordLength);
}
void intArrayPrinter(int *array, int arrayLength){
    printf("[");
    for (int i = 0; i < arrayLength; i += 1){
        printf("%d ", array[i]);
        if(i == arrayLength-1){
            printf("]");
        } else{
            printf(",");
        }
    }
}
int singleQuicksort(int *array, int leftPointer, int rightPointer){
    int cache = array[leftPointer];
    while (leftPointer < rightPointer){
        while ((leftPointer < rightPointer) &&(array[rightPointer] > cache) ){
            rightPointer += -1;
        }
        array[leftPointer] = array[rightPointer];
        while ((leftPointer < rightPointer) && (array[leftPointer] < cache)){
            leftPointer += 1;
        }
        array[rightPointer] = array[leftPointer];
    }
    array[leftPointer] = cache;
    return leftPointer;
}
void quickSortMain(int *array, int leftPointer, int rightPointer){
    if(rightPointer - leftPointer >= 1){
        int middle = singleQuicksort(array, leftPointer, rightPointer);
        quickSortMain(array, leftPointer, middle-1);
        quickSortMain(array, middle+1, rightPointer);
    }
}