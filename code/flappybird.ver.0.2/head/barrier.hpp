#ifndef BARRIER_H
#define BARRIER_H

/* 障碍物类型 */

#define BARRIER_CHAR 'H' ///< 用于表示障碍物的字符
#define BARRIER_WIDTH 4 ///< 障碍物的总宽度的默认值
#define BARRIER_HOLEHEIGHT 3 ///< 障碍物孔洞的总高度的默认值

struct barrier
{
    int x; ///< 障碍物在整个游戏中的（最左上角）横坐标
    int width; ///< 障碍物的总宽度
    int height; ///< 障碍物的总高度
    int hole_y; ///< 障碍物孔洞的（最左上角）纵坐标
    int hole_height; ///< 障碍物孔洞的总高度

};

int barrier__init__( struct barrier* barrier, int x, int height ); ///< 初始化障碍物，随机分配开口位置
int barrier_getRandHole_y( struct barrier* barrier ); ///< 随机生成障碍物孔洞的高度

#endif // BARRIER_H