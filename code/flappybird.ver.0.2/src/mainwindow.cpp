#include "mainwindow.hpp"

#include "bird.hpp"
#include "barrier.hpp"
#include "queue.hpp"

#include <stdio.h>
#include <conio.h>
#include <windows.h>

/*
*	\brief 游戏主循环
*	\return 返回游戏分数
*/
int mainLoop()
{
	int score;
    struct mainwindow *window = (struct mainwindow *)malloc(sizeof(struct mainwindow));
	mainwindow__init__(window);			//数据初始化    
	while(1)
	{
		mainwindow_responseKeyBoard(window); //与用户输入有关的更新 
		mainwindow_update(window);	//与用户输入无关的更新
		mainwindow_drawBackground( window );
		mainwindow_show(window); //显示界面 
		if (mainwindow_checkIsBirdHit(window))
			break;
		Sleep(window->waitTime);
	}
	mainwindow_showFinalScore(window);
	score = window->score;
    mainwindow__free__(window);
	return score;        
}

/*
*	\brief 隐藏光标 
*/
void HideCursor()
{
 	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
 	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

/*
*	\brief 光标移动到(x,y)位置
*/
void gotoxy(int x,int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

/*
*	\brief 初始化窗口，创建 bird 对象、障碍物队列、显示缓冲队列
*	\param[0] struct mainwindow *window 指向待操作的结构体指针
*/
void mainwindow__init__( struct mainwindow *window )			//数据初始化 
{

    window->waitTime = MAINWINDOW_WAITTIME;
    window->height = MAINWINDOW_HEIGHT;
    window->width = MAINWINDOW_WIDTH;
    window->x = 1;

	window->score = 0;
    
    window->bird = (struct bird *)malloc(sizeof(struct bird));
    bird__init__( window->bird, window->width / 5, window->height / 2 ); //初始化小鸟坐标

    window->barrierHoleHeight = MAINWINDOW_BARRIER_HOLEHEIGHT;
    window->barrierQueueMaxNum = MAINWINDOW_BARRIER_MAXNUM;
    window->barrierAddWaitTime = MAINWINDOW_BARRIER_ADD_WAITTIME;
    window->cnt_barrierAddWaitTime = 0;
    
	window->barrierQueue = queue_createQueue( window->barrierQueueMaxNum );	//初始化障碍物队列
	window->frontColOfCanvas = 0;
	window->canvasCache = queue_createQueue( MAINWINDOW_CANVASCACHE_MAXNUM ); //初始化显示缓冲队列

	// 初始化 window->canvas，将其中所有值置为空格
	for (int i = 0; i < window->height; i++) {
		for (int j = 0; j < window->width; j++) {
			window->canvas[i][j] = ' ';
		}	
	}
	
	HideCursor();	//隐藏光标 
}

/*
*	\brief 释放窗口的所有空间
*	\param[0] struct mainwindow *window 指向待操作的结构体指针	
*/
void mainwindow__free__( struct mainwindow *window )
{
	free(window->bird);

	//释放障碍物队列
	while (!queue_isEmpty(window->barrierQueue))
		mainwindow_deletBarrier(window);
	queue_dispose(window->barrierQueue);

	//释放显示缓冲队列
	while (!queue_isEmpty(window->canvasCache))
		free( (int*)queue_forntAndDequeue(window->canvasCache) );
	queue_dispose(window->canvasCache);
	
	free(window);
}

/*
*	\brief 更新背景画最后一列，
*			从显示缓冲队列中读入一个元素，
*			如果该元素是 -1 新显示的列没有 barrier，全部置为空格；
*			否则认为新显示的列有 barrier，将该元素解释为 barrier->hole_y，更新画布最后一列
*	\param[0] struct mainwindow *window 指向待操作的结构体指针	
*/
void mainwindow_drawBackground( struct mainwindow *window )
{
	if (queue_isEmpty(window->canvasCache)) //如果缓冲队列为空，不更新画布
		return;
	
	int rearCol = window->frontColOfCanvas++; //移动画布的首列
	if (window->frontColOfCanvas >= window->width)
		window->frontColOfCanvas = 0;
	
	int flag = *(int*)queue_forntAndDequeue(window->canvasCache);
	if (flag >= 0 && flag <= (window->height - window->barrierHoleHeight)) { //更新的列有 barrier
		for (int i = 0; i < flag; i++)
			window->canvas[i][rearCol] = BARRIER_CHAR; 
		for (int i = flag; i < (flag + window->barrierHoleHeight); i++)
			window->canvas[i][rearCol] = ' ';
		for (int i = (flag + window->barrierHoleHeight); i < window->height; i++)
			window->canvas[i][rearCol] = BARRIER_CHAR;
	} else //更新的列没有 barrier
		for (int i = 0; i < window->height; i++)
			window->canvas[i][rearCol] = ' ';
}

/*
*	\brief 在控制台输出背景画布,
*			如果某像素点与 bird 的坐标相同，输出 bird
*	\param[0] struct mainwindow *window 指向待操作的结构体指针	
*/
void mainwindow_show( struct mainwindow *window )
{
	gotoxy(0,0); 
	
	printf("得分：%d ",window->score);
	printf("km：%d\n",window->x);

	//输出上边界
	for (int j = 0; j < window->width + 2; j++)
		printf("%c", MAINWINDOW_UPANDDOWN_MARGIN_CHAR);
	printf("\n");

	for (int indexRowOfCanvas = 0; indexRowOfCanvas < window->height; indexRowOfCanvas++) {
		printf("%c", MAINWINDOW_LEFT_MARGIN_CHAR); //输出左边界
		int indexColOfCanvas = window->frontColOfCanvas;
		for (int j = 0; j < window->width; j++) {
			if ( window->bird->screen_x == j && window->bird->y == indexRowOfCanvas ) {
				printf("%c", BIRD_CHAR); //输出 bird
				indexColOfCanvas++;
			} else { //按 window->canvas 输出背景
				printf("%c", window->canvas[indexRowOfCanvas][indexColOfCanvas]);
				indexColOfCanvas++;
			}
			//window->canvas是循环列表，索引越过列表右边界时将索引重置为左边界
			if ( indexColOfCanvas >= window->width )
				indexColOfCanvas = 0;
		}
		printf("%c", MAINWINDOW_RIGHT_MARGIN_CHAR); //输出右边界
		printf("\n");	
	}

	//输出下边界
	for (int j = 0; j < window->width + 2; j++)
		printf("%c", MAINWINDOW_UPANDDOWN_MARGIN_CHAR);
	printf("\n");
} 

/*
*	\brief 控制台输出最终分数
*	\param[0] struct mainwindow *window 指向待操作的结构体指针	
*/
void mainwindow_showFinalScore( struct mainwindow *window )
{
	printf("\n【游戏结束】\n");
	printf("最终分数为\n");
	printf("得分：%d\t",window->score);
	printf("km：%d\n",window->x);
	printf("-------------------\n");
	system("pause");
}

/*
*	\brief 检验 bird 与 barrier 是否碰撞
*	\param[0] struct mainwindow *window 指向待操作的 bird 结构体指针	
*	\param[1] struct barrier *barrier 指向待操作的 barrier 结构体指针
*	\retval 没碰上返回 0；碰上返回 1
*/
int mainwindow_isBirdHitBarrier( struct bird *bird, struct barrier *barrier )
{
	if ( (bird->x < barrier->x) || (bird->x > barrier->x + barrier->width - 1) )
		return 0; // 没碰上
	
	int minHeight, maxHeight;
	minHeight = barrier->hole_y;
	maxHeight = barrier->hole_y + barrier->hole_height - 1;
	if (bird->y >= minHeight && bird->y <= maxHeight) {
		return 0; // 没碰上
	} else
		return 1; // 碰上
}

/*
*	\brief 检验 bird 与 window 是否碰撞
*	\param[0] struct mainwindow *window 指向待操作的 bird 结构体指针	
*	\param[1] struct mainwindow *window 指向待操作的 mainwindow 结构体指针
*	\retval 没碰上返回 0；碰上返回 1
*/
int mainwindow_isBirdHitMargin( struct bird *bird, struct mainwindow *window )
{
	if (bird->y >= 0 && bird->y <= window->height - 1 ) {
		return 0; // 没碰上
	} else
		return 1; // 碰上
}

/*
*	\brief 检验窗口的 bird 是否发生了碰撞
*	\param[0] struct mainwindow *window 指向待操作的结构体指针	
*	\retval 没碰上返回 0；碰上返回 1
*/
int mainwindow_checkIsBirdHit( struct mainwindow *window )
{
	int flag_isBirdHitBarrier, flag_isBirdHitMargin;
	struct bird *bird = window->bird;

	flag_isBirdHitMargin = mainwindow_isBirdHitMargin( bird, window );

	if ( queue_isEmpty(window->barrierQueue) ) {
		flag_isBirdHitBarrier = 0;
	} else {
		struct barrier *barrier = (struct barrier *)queue_fornt(window->barrierQueue);
		flag_isBirdHitBarrier = mainwindow_isBirdHitBarrier(bird,barrier);
	}

	if ( flag_isBirdHitBarrier || flag_isBirdHitMargin ) {
		return 1; // 碰上
	} else
		return 0; // 没碰上
}

/*
*	\brief 与用户输入无关的更新，更新窗口内各元素的状态
*	\param[0] struct mainwindow *window 指向待操作的结构体指针	
*/
void mainwindow_update( struct mainwindow *window )
{
	window->x++;
	mainwindow_updateBarrierQueue(window);
	bird_move(window->bird);
}

/*
*	\brief 与用户输入有关的更新，响应键盘事件
*	\param[0] struct mainwindow *window 指向待操作的结构体指针
*/
void mainwindow_responseKeyBoard( struct mainwindow *window )
{
	char input;
	
	if(kbhit())
	{
		input=getch();
		switch (input)
		{
		case ' ':
			bird_responseKeyBoard( window->bird );
			break;
		default:
			break;
		}
	}
	
	fflush(stdin);
}

/*
*	\brief 更新 barrier 队列,
*			释放已经离开屏幕的障碍，且游戏分数 window->score 加一；
*			在计时器为零时加入新障碍，并向窗口显示的缓冲空间压入新 barrier 列，
*			否则，向窗口显示的缓冲空间压入空列
*	\param[0] struct mainwindow *window 指向待操作的结构体指针
*/
void mainwindow_updateBarrierQueue( struct mainwindow *window )
{
	// 释放已经离开屏幕的障碍
	if ( !queue_isEmpty(window->barrierQueue) ) {
		struct barrier *barrier = (struct barrier *)queue_fornt(window->barrierQueue);
		if ( (barrier->x + barrier->width - 1) <= window->bird->x ) {
			mainwindow_deletBarrier(window);
			window->score++;
		}	
	}

	// 在计时器为零时加入新障碍
	int flag_newBarrier_succ = -1;
	if ( window->cnt_barrierAddWaitTime-- <= 0) {
		window->cnt_barrierAddWaitTime = window->barrierAddWaitTime;
		flag_newBarrier_succ = mainwindow_newBarrier(window);	
	} else if (flag_newBarrier_succ == -1) { //向窗口显示的缓冲空间压入空列
		int *newCanvasElement = (int*)malloc(sizeof(int));
		*newCanvasElement = -1;
		queue_enqueue( (void*)newCanvasElement, window->canvasCache );
	}
}

/*
*	\brief 新生成一个 barrier，并向窗口显示的缓冲空间压入新 barrier 列
*	\param[0] struct mainwindow *window 指向待操作的结构体指针
*	\retval 插入成功，返回生成 barrier->hole_y；失败返回 -1
*/
int mainwindow_newBarrier( struct mainwindow *window )
{
	int x = window->x + window->width - 1;
    struct barrier *barrier = (struct barrier *)malloc(sizeof(struct barrier));
	int hole_y = barrier__init__(barrier, x, window->height);
	int flag_enqueue_succ = queue_enqueue( (void*)barrier, window->barrierQueue );
	
	if ( flag_enqueue_succ == 0 ) {
		return -1; //插入失败
	}

	window->x += barrier->width - 1;
	for (int i = 0; i < barrier->width; i++) {
		int *newCanvasElement = (int*)malloc(sizeof(int));
		*newCanvasElement = hole_y;
		queue_enqueue( (void*)newCanvasElement, window->canvasCache );	
	}

	return hole_y; //插入成功
}

/*
*	\brief 释放 barrier
*	\param[0] struct mainwindow *window 指向待操作的结构体指针
*/
void mainwindow_deletBarrier( struct mainwindow *window )
{
	struct barrier *barrier = (struct barrier *)queue_forntAndDequeue(window->barrierQueue);
	free(barrier);
}