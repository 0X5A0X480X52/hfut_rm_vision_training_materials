#ifndef BIRD_H
#define BIRD_H       

#define BIRD_CHAR 'O' ///< 用于表示 bird 的字符
#define BIRD_MOVE_DOWN 1 ///< bird 默认的下降速度
#define BIRD_MOVE_UP_KEYBOARD -2 ///< 键盘敲击后 bird 默认的上升速度

struct bird
{
    int x; ///< bird 在整个游戏中的横坐标
    int screen_x; ///< bird 在显示区域中的横坐标
    int y; ///<  bird 在整个游戏中的纵坐标
};

void bird__init__( struct bird *, int x, int y ); ///< 初始化 bird 结构体
void bird_responseKeyBoard( struct bird * bird ); ///< 响应键盘输入
void bird_move( struct bird * bird ); ///< 基于自身参数移动 bird

#endif // BIRD_H