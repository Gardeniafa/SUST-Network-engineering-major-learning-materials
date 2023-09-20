#include "stdio.h"
#include "math.h"
int main(){
    int n, s;
    scanf("%d", &n);
    s = n;
    int l = 0;
    while (n >= 1 ){
        n /= 10;
        l += 1;
    }
    printf("length=%d\none by one:\n", l);
    int arr[l];
    for(int i = 0; i < l; i += 1){
        int cache = s;
        for(int j = 0; j < i; j += 1){
            cache -= arr[j]*pow(10, l-j-1);
        }
        arr[i] = cache/ pow(10, l-1-i);
    }
    for (int i = 0; i < l; i += 1){
        printf("%d\n", arr[i]);
    }
    printf("reverse:");
    for (int i = l-1; i >= 0; i -= 1){
        printf("%d", arr[i]);
    }
    return 0;
}