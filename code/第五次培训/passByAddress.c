#include <stdio.h>

void f(int *p) { 
    *p = 10;
    printf("%d\n", *p);
}

int main() {
    int a = 5;
    f(&a);
    printf("%d\n", a);
}