#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int n =5;
    int *p = (int*)malloc(sizeof(int) * n);
    if (p != NULL) {
        for (int i = 0; i < n; i++) p[i] = i * i;
    }
    printf("动态分配的数组元素:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", p[i]);
    }
    free(p);
    return 0;
}
