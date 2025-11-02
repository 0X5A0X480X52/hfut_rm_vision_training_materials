#include <stdio.h>

int main() {
    int a[5] = {1, 2, 3, 4, 5};
    printf("%d\n", a[2]);
    printf("%p %p %p\n", &a[0], &a[1], &a[2]);
    return 0;
}