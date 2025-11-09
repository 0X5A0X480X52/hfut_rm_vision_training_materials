#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int *p = (int*)malloc(sizeof(int) * 5);
    if (p != NULL) {
        for (int i = 0; i < 5; i++) p[i] = i * i;
    }
    printf("动态分配的数组元素:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", p[i]);
    }
    free(p);
    return 0;
}
