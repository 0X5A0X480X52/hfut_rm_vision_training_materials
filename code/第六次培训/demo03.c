#include <stdio.h>

int main() {
    int a[5] = {1, 2, 3, 4, 5};
    int *p = a;  // 等价于 p = &a[0];
    printf("%d\n", *(p + 2));  // 输出3

    return 0;
}