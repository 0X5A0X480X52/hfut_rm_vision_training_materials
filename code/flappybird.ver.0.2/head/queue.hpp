#ifndef QUEUE_H
#define QUEUE_H

/* 队列（循环数组描述） */

#define ELEMENTYPE void* ///< 队列中存贮的数据类型，默认为 void*

struct QueueRecord; ///< 用于记录队列基本信息
typedef struct QueueRecord *Queue; ///< 用于表示队列 
typedef ELEMENTYPE ElementType; ///< 队列中存贮的数据类型

struct QueueRecord
{
    int capacity; ///< 队列的容量
    int front ; ///< 队列首元素索引
    int rear ; ///< 队列尾元素索引
    int size ; ///< 队列内已存有元素的个数
    ElementType *array; ///< 队列中用于存放元素的数组
};

int queue_isEmpty( Queue Q ); // 判断队列是否为空
int queue_isFull( Queue Q ); // 判断队列是否已满
Queue queue_createQueue( int maxElement ); // 创建队列
void queue_dispose( Queue Q ); // 销毁队列
void queue_makeEmpty( Queue Q ); // 清空队列
int queue_enqueue( ElementType X, Queue Q ); // 新元素入列
ElementType queue_fornt( Queue Q ); // 查看首元素
int queue_dequeue( Queue Q ); // 首元素出列，且不返回首元素
ElementType queue_forntAndDequeue( Queue Q ); //  首元素出列，且返回首元素

#endif // QUEUE_H