#include <stdio.h>

int main() {
    int m[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    printf("%d\n", m[1][2]);  // 输出6

    printf("%p %p %p\n", &m[0][0], &m[0][1], &m[0][2]);
    printf("%p %p %p\n", &m[1][0], &m[1][1], &m[1][2]);

    return 0;
}