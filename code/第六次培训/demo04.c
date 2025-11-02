#include <stdio.h>

int main() {

    // 指针数组
    int a = 10, b = 20, c = 30;
    int *p[3] = {&a, &b, &c};
    printf("%d\n", *p[1]);  // 输出20

    // 数组指针
    int z[3] = {1, 2, 3};
    int (*q)[3] = &z;
    printf("%d\n", (*q)[1]);  // 输出2

    return 0;
}