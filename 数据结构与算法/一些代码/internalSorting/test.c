#include "stdio.h"
int main(){
    int arr[] = {2, 1, 7, 4, 0, 5, 8, 3, 6};
    for(int i = 0;i < sizeof(arr)/sizeof(typeof(arr[0]));i += 1){
        for(int j = i+1;j < sizeof(arr)/sizeof(typeof(arr[0]));j += 1){
            if(arr[i] > arr[j]){
                int cache = arr[i];
                arr[i] = arr[j];
                arr[j] = cache;
            }
        }
    }
    for(int i = 0;i < sizeof(arr)/sizeof(typeof(arr[0]));i += 1){
        printf("%d  ", arr[i]);
    }
}