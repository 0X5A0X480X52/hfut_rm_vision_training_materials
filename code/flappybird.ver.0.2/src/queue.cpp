#include "queue.hpp"
#include <malloc.h>
#include <stdio.h>

/* 
*   \brief 判断队列是否为空
*   \param[0] Queue Q 操作的队列
*   \return 1为空，0为非空
*/   
int queue_isEmpty( Queue Q )
{
    return Q->size == 0;
}

/* 
*   \brief 判断队列是否已满
*   \param[0] Queue Q 操作的队列
*   \return 1为已满，0为未满
*/   
int queue_isFull( Queue Q )
{
    return Q->size >= Q->capacity;
}

/*
*   \brief 创建队列
*   \param[0] int maxElement 队列的容量
*   \return 创建好的新队列
*/
Queue queue_createQueue( int maxElement )
{
    Queue Q = (Queue)malloc( sizeof(QueueRecord) );
    Q->capacity = maxElement;
    Q->front = 0;
    Q->rear = 0;
    Q->size = 0;
    Q->array = (ElementType*)calloc( maxElement, sizeof(ElementType) );
    if ( Q->array == NULL )
    	return NULL;
    return Q;
}

/*
*   \brief 销毁队列
*   \attention 不释放队列中各个元素的空间
*   \param[0] Queue Q 操作的队列
*/
void queue_dispose( Queue Q )
{
    free(Q->array);
    free(Q);
}

/*
*   \brief  清空队列
*   \param[0] Queue Q 操作的队列
*/
void queue_makeEmpty( Queue Q )
{
    Q->front = 0;
    Q->rear = 0;
    Q->size = 0;
}

/*
*   \brief  新元素入列：
            如果队列未满，插入队列尾部；
            如果队列已满，不进行插入操作
*   \param[0] ElementType X 待插入的元素
*   \param[1] Queue Q 操作的队列
*   \return 1为插入成功，0为插入不成功
*/
int queue_enqueue( ElementType X, Queue Q )
{
    int flag_enqueue_succ  = !queue_isFull(Q); 
    if ( flag_enqueue_succ ) {
        Q->size += 1;
        *(Q->array + Q->rear) = X;
        Q->rear += 1;
        if ( Q->rear >= Q->capacity )  // 如果 rear 越过数组开头，将其绕回尾端
            Q->rear = 0;
    }
    return flag_enqueue_succ;
}

/*
*   \brief  查看首元素
*   \param[0] Queue Q 操作的队列
*   \return 首元素
*   \warning 队列为空时会返回不确定值，应在使用检查队列是否非空
*/
ElementType queue_fornt( Queue Q )
{
    return *(Q->array + Q->front);
}

/*
*   \brief  首元素出列，且不返回首元素
            如果队列非空，首元素出列；
            如果队列为空，不进行出列操作
*   \param[0] Queue Q 操作的队列
*   \return 1为插入出列，0为出列不成功
*   \attention 首元素出列时不释放首元素指向的空间
*/
int queue_dequeue( Queue Q )
{
    int flag_dequeue_succ  = !queue_isEmpty(Q); 
    if ( flag_dequeue_succ ) {
        Q->size -= 1;
        *(Q->array + Q->front) = NULL;
        Q->front += 1;
        if ( Q->front >=  Q->capacity )  // 如果 front 越过数组尾端，将其绕回开头
            Q->front = 0;
    }
    return flag_dequeue_succ;
}

/*
*   \brief  首元素出列，且返回首元素
*   \param[0] Queue Q 操作的队列
*   \return 首元素
*   \warning 队列为空时会返回不确定值，应在使用检查队列是否非空
*/
ElementType queue_forntAndDequeue( Queue Q )
{
    ElementType fornt = queue_fornt(Q);
    queue_dequeue(Q);
    return fornt;
}