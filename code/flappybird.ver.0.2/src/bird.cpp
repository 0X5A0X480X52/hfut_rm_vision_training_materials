#include "bird.hpp"

/*
*   \brief 基于输入初始化 bird 结构体
*   \param[0] struct bird * bird 指向待初始化的结构体指针
*   \param[1] int x 结构体 bird 在整个游戏中的横坐标
*   \param[2] int y 结构体 bird 在整个游戏中的纵坐标
*/
void bird__init__( struct bird * bird, int x, int y )
{
    bird->x = x;
    bird->screen_x = x;
    bird->y = y;
}

/*
*   \brief 响应键盘输入, 使 bird 在整个游戏中的横坐标加 BIRD_MOVE_UP_KEYBOARD
*   \param[0] struct bird * bird 指向待初始化的结构体指针
*/
void bird_responseKeyBoard( struct bird * bird )
{
    bird->y += BIRD_MOVE_UP_KEYBOARD;
}

/*
*   \brief  基于自身参数移动 bird
*   \param[0] struct bird * bird 指向待初始化的结构体指针
*/
void bird_move( struct bird * bird )
{
    bird->x++;
    bird->y += BIRD_MOVE_DOWN;
}