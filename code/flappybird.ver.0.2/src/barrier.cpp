#include "barrier.hpp"
#include <stdlib.h>
#include <time.h>

/*
*   \brief 初始化障碍物结构体
*   \param[0] struct barrier* barrier 指向待初始化的结构体指针
*   \param[1] int x 障碍物在整个游戏中的（最左上角）横坐标
*   \param[2] int height 障碍物的总高度
*   \retval 障碍物孔洞的（最左上角）纵坐标
*/
int barrier__init__( struct barrier* barrier, int x, int height )
{
	barrier->hole_height = BARRIER_HOLEHEIGHT;
	barrier->width = BARRIER_WIDTH;
    barrier->x = x;
    barrier->height = height;
    barrier->hole_y = barrier_getRandHole_y( barrier );
    return barrier->hole_y;
}

/*
*   \brief 随机生成障碍物孔洞的（最左上角）纵坐标
*   \retval 从 0 到 （barrier->height - barrier->hole_height ）的整数
*/
int barrier_getRandHole_y( struct barrier* barrier )
{
    int random;
    time_t t;
    srand((unsigned) time(&t));
    random = rand() % (barrier->height - barrier->hole_height );
    return random;
}