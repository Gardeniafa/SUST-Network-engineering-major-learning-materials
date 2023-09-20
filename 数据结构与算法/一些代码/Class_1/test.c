#include <stdio.h>

int main() {
    double x,y;
    scanf("%lf",&x);
    if (x<0) {
        y = 0;
    }else if (x <=15) {
        y = 4*x / 3;
    }
    else {
        y = 2.5*x- 10.5;
    }
    printf("%.2lf",y);
    return 0;
}