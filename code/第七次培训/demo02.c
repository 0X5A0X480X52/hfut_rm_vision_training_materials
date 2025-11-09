#include <stdio.h>

typedef int Map[3][3]; // 定义二维数组类型：地图

int main(int argc, char const *argv[])
{
    Map map = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 0, 0},
    }; // 定义一个地图变量

    Map *pMap = &map; // 定义指向整个二维数组的指针，等价于 int (*pMap)[3][3] = &map;

    // 通过指针访问地图元素
    printf("地图位置 (2,3) 的值: %d\n", (*pMap)[2][2]);  // 输出 0

    // 打印整个地图
    printf("地图内容:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", (*pMap)[i][j]);
        }
        printf("\n");
    }

    return 0;
}