/*
贪吃蛇功能函数实现
*/

#pragma once
class Snake//蛇类，包含了蛇的基本元素和蛇的所有活动，其中蛇是由链表构成的
{
public:

	friend void creat_food();//生成食物的函数
	friend void Initial(); //初始化函数，初始化蛇的身体的初始长度，以及出生位置

	int Get_x();
	int Get_y();

	Snake *Get_next();

	bool Bite_self();//判断是否咬到自己
	void Can_not_crowall();//不能穿墙，所以碰到强会死
	void Move();//蛇的移动

private:
	int s_x;//蛇的x，y坐标
	int s_y;
	Snake *next;//使用链表完成，两个数据域，存放横x纵y坐标。一个指针域，存放链接后续身体节点的地址
};

struct Obstacle//障碍物结构体，内部有x和y两个量
{
	//障碍物的横纵坐标
	int x;
	int y;
};

