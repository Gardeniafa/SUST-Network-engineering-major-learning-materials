#include "stdio.h"
int main()
{
    struct{
        int a;
        char b;
        //float c;
        char d[7];
    }str;
    float i;
    printf("%d",sizeof str);
}