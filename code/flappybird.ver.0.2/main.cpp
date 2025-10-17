/*
*   coding = UTF-8
*   project flappybird.ver.2.0
*   \author 张恒睿 2023211145
*   \date 2024/05/29
*/

#include "mainwindow.hpp"
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#define FILENAME "data.txt"
#define USERNAME 100

void readData( int *temReadScore, char userName[], int *year, int *month, int *day, int *hour, int *min, int *sec);
void printData();
void writeData( int score, char userName[] );

int main(int argc, char const *argv[])
{
    int score, maxScore = 0, flag = 1;
    char userName[USERNAME] = "NULL";
    char maxUserName[USERNAME] = "NULL";
    SetConsoleOutputCP(65001); // 设置控制台编码格式为 UTF-8

    int year, month, day, hour, min, sec;
    readData(&maxScore, maxUserName, &year, &month, &day, &hour, &min, &sec );

    printf("====[flappybird.ver.2.0]====\n\n");
    
    printf("【高手请留名】 取个名字吧：");
    scanf("%s", userName);
    
    printf("\n【游戏说明】\n");
    printf("按下空格键让小鸟飞起来，不要碰到墙壁和障碍物！\n");
    printf("-------------------\n");
    system("pause");

    while (flag == 1)
    {
        system("cls");
        printf("====[flappybird.ver.2.0]====\n\n");
        printf("【游戏开始】\n");
        printf("-------------------\n");
        system("pause");

        system("cls");
        score = mainLoop();
        
        system("cls");
        printf("====[flappybird.ver.2.0]====\n\n");
        printf("【历史最高分数】MAXSCORE %d USERNAME %s\n", maxScore, maxUserName);
        printf("【本局分数】SCORE %d USERNAME %s\n", score, userName);
        
        if (score > maxScore) {
            maxScore = score;
            printf("【您已打破最高分！】");
            strcpy(maxUserName,userName);
            printf("【目前最高分数】MAXSCORE %d USERNAME %s\n", maxScore, maxUserName);
        }
        printf("-------------------\n");
        system("pause");

        writeData( score, userName );

        while (flag == 1)
        {
            system("cls");
            printf("====[flappybird.ver.2.0]====\n\n");
            printf("\n【是否再来一局？】\n 输入 1 重新开始 \n 输入 2 查看历史记录 \n 其他输入退出\n");
            printf("请选择：");
            scanf("%d", &flag);

            switch (flag) {
            case 2:
                system("cls");
                printf("====[flappybird.ver.2.0]====\n\n");
                printf("【开始输出历史数据】\n");
                printData();
                printf("【历史数据输出结束】\n");
                printf("-------------------\n");
                system("pause");
                flag = 1;
                break;
            default:
                flag = -1;
                break;
            }
        
        }
    }

    system("cls");
    printf("====[flappybird.ver.2.0]====\n\n");
    printf("【程序已退出】\n");
    printf("-------------------\n");
    system("pause");
    return 0;
}

void readData( int *maxScore, char userName[], int *year, int *month, int *day, int *hour, int *min, int *sec)
{
    int temReadScore = 0;
    int flag_endFile;
    FILE * fp;
    fp = fopen (FILENAME, "rw+");
    if (fp != NULL)
        do {
            flag_endFile = fscanf(fp, "SCORE %d USERNAME %s DATE %d/%d/%d %d:%d:%d \n", &temReadScore, userName, year, month, day, hour, min, sec );
            *maxScore = (*maxScore < temReadScore) ? temReadScore : *maxScore;
        } while ( flag_endFile != EOF );
    fclose( fp );
}

void printData()
{
    int cnt = 0;
    int year, month, day, hour, min, sec;
    int score = 0;
    char userName[USERNAME] = "NULL";
    int flag_endFile;
    FILE * fp;
    fp = fopen (FILENAME, "rw+");
    if (fp != NULL)
        do {
            flag_endFile = fscanf(fp, "SCORE %d USERNAME %s DATE %d/%d/%d %d:%d:%d \n", &score, userName, &year, &month, &day, &hour, &min, &sec );
            printf("[%d] SCORE %d USERNAME %s DATE %d/%d/%d %d:%d:%d \n", cnt++, score, userName, year, month, day, hour, min, sec );
        } while ( flag_endFile != EOF );
    fclose( fp );
}

void writeData( int score, char userName[] )
{
    system("cls");
    printf("====[flappybird.ver.2.0]====\n\n");
    printf("【正在保存】 请稍等...\n");
    
    struct tm t;   //tm结构指针
	time_t now;  //声明time_t类型变量
	time(&now);      //获取系统日期和时间
	localtime_s(&t, &now);   //获取当地日期和时间
    int year = 1900 + t.tm_year;
    int month = t.tm_mon + 1;
    int day = t.tm_mday;
    int hour = t.tm_hour;
    int min = t.tm_min;
    int sec = t.tm_sec;

    FILE * fp;
    fp = fopen (FILENAME, "a");
    if (fp != NULL)
        fprintf(fp, "SCORE %d USERNAME %s DATE %d/%d/%d %d:%d:%d \n", score, userName, year, month, day, hour, min, sec );
    fclose( fp );

    printf("【保存完成】\n");
    printf("-------------------\n");
    system("pause");
}