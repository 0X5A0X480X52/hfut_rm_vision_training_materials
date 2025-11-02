#include <stdio.h>

int a = 1;

void foo() {
    printf("%d\n", a); // 输出 1
    int a = 2;   // 局部变量遮蔽全局变量
    printf("%d\n", a); // 输出 2
}

int main() {
    foo();
    return 0;
}