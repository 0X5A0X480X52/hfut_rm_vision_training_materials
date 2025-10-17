#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "barrier.hpp"
#include "bird.hpp"
#include "queue.hpp"

#define MAINWINDOW_UPANDDOWN_MARGIN_CHAR 'H' ///< 用于表示窗口上下边界的字符
#define MAINWINDOW_LEFT_MARGIN_CHAR ']'  ///< 用于表示窗口左边界的字符
#define MAINWINDOW_RIGHT_MARGIN_CHAR '[' ///< 用于表示窗口右边界的字符

#define MAINWINDOW_BARRIER_HOLEHEIGHT 4 ///< 窗口内默认的 barrier->hole_height 大小
#define MAINWINDOW_BARRIER_MAXNUM 5 ///< 窗口内可存储的 barrier 的默认最大个数
#define MAINWINDOW_BARRIER_ADD_WAITTIME 20 ///< 窗口新生成 barrier 的默认间隔时间

#define MAINWINDOW_HEIGHT 15 ///< 窗口的默认高度
#define MAINWINDOW_WIDTH 80 ///< 窗口的默认宽度
#define MAINWINDOW_WAITTIME 200 ///< 窗口的默认刷新间隔

#define MAINWINDOW_CANVASCACHE_MAXNUM 500 ///< 窗口由于显示的缓冲空间大小

struct mainwindow
{
    int waitTime; ///< 窗口的刷新间隔
    int height; ///< 窗口的高度
    int width; ///< 窗口的宽度
    int x; ///< 窗口（最左上角的）坐标

    int score; ///< 游戏的分数，每越过一个 barrier 分数加一

    struct bird * bird; ///< 窗口的 bird

    int barrierHoleHeight; ///< 窗口内的 barrier->hole_height 大小
    int barrierQueueMaxNum; ///< 窗口内可存储的 barrier 的最大个数
    int barrierAddWaitTime; ///< 窗口新生成 barrier 的间隔时间
    int cnt_barrierAddWaitTime; ///< 窗口已经等待新生成 barrier 的时间
    Queue barrierQueue; // 队列中元素类型为 barrier*，用于存储生成的 barrier
    
    Queue canvasCache; // 队列中元素类型为 int*，作为窗口显示的缓冲空间
    char canvas[MAINWINDOW_HEIGHT][MAINWINDOW_WIDTH]; // 用于表述画布，且对每一列该数组是一个循环数组
    int frontColOfCanvas; ///< 画布循环数组的首列
};

void HideCursor(); ///< 隐藏光标 
void gotoxy( int x, int y ); ///< 光标移动到(x,y)位置

int mainLoop(); ///< 游戏主循环

void mainwindow__init__( struct mainwindow * ); ///< 初始化窗口
void mainwindow__free__( struct mainwindow * ); ///< 释放窗口的所有空间

void mainwindow_drawBackground( struct mainwindow * ); ///< 更新背景画布
void mainwindow_show( struct mainwindow * ); ///< 在控制台输出背景画布和 bird
void mainwindow_showFinalScore( struct mainwindow * ); ///< 控制台输出最终分数

void mainwindow_update( struct mainwindow * ); ///< 更新窗口内各元素的状态
void mainwindow_responseKeyBoard( struct mainwindow * ); ///< 响应键盘事件

int mainwindow_checkIsBirdHit( struct mainwindow * ); ///< 检验碰撞
int mainwindow_isBirdHitBarrier( struct bird *, struct barrier * ); ///< 检验 bird 与 barrier 是否碰撞
int mainwindow_isBirdHitMargin( struct bird *, struct mainwindow * ); ///< 检验  bird 与窗口边缘是否碰撞

void mainwindow_updateBarrierQueue( struct mainwindow * ); ///< 更新 barrier 队列
int mainwindow_newBarrier( struct mainwindow * ); ///< 新生成 barrier
void mainwindow_deletBarrier( struct mainwindow * ); ///< 释放 barrier
    
#endif // MAINWINDOW_H