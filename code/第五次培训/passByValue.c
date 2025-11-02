#include <stdio.h>

void f(int x) { 
    x = 10;
    printf("%d\n", x);
}

int main() {
    int a = 5;
    f(a);
    printf("%d\n", a); // 输出 5
}