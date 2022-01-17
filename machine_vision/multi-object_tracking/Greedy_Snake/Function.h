/*
贪吃蛇功能函数实现
*/

#pragma once
#include<iostream>
#include<stdlib.h>//随机函数就包含在这个头文件
#include<time.h>//时间函数time包含在这个头文件
#include<Windows.h>//HANDLE类（句柄类）与COORD类（坐标类）包含在这个头文件
#include"Snake.h"

using namespace std;

/**
方向控制
*/
#define UP 1
#define DOWN 2
#define LEFT 4
#define RIGHT 3

extern Snake *head, *food;//全局指针，head是永远指向第一个节点的指针，food是指向食物的指针
extern Snake *q;//遍历整个蛇所用到的指针
extern int condition;//代表按键情况，上述把按键四种情况分别赋了整数值，所以这里的情况也是int 类型
extern int end_condition;//表示结束的情况，=1，撞墙；=2，咬到自己；=3，自己结束;4 撞到障碍物而死
extern int score;//得分
extern int add;//每个食物的分数
extern Obstacle o[30];//障碍物的结构体数组,用来存放每一块障碍物的x，y坐标

inline void Green_color();//字体置绿
inline void Red_color();//字体置红
inline void Yellow_color();//字体置黄
inline void White_color();//障碍为白色

void Set_location(int x, int y);//定位函数
void Creat_obs(Obstacle o[], int n);//创建障碍物
void Initial();//初始化蛇
void creatMap();//创建地图
void creat_food();//创建食物

void pause();//暂停
void Start();//开始
void Playing();//进行游戏
void Die();//死亡
