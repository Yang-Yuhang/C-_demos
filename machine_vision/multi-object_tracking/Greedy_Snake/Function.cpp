/*
贪吃蛇功能函数实现
*/

#pragma once
#include"Function.h"

Snake *head=NULL, *food=NULL;//全局指针，head是永远指向第一个节点的指针，food是指向食物的指针
Snake *q=NULL;//遍历整个蛇所用到的指针
int condition;//代表按键情况，上述把按键四种情况分别赋了整数值，所以这里的情况也是int 类型
int end_condition = 0;//表示结束的情况，=1，撞墙；=2，咬到自己；=3，自己结束;4 撞到障碍物而死
int score = 0;//得分
int add = 1;//每个食物的分数
Obstacle o[30];//定义一个存放障碍物的结构体数组用来存放每一块障碍物的x，y坐标


//设置为绿色(蛇）
inline void Green_color()//这里用到一个SetConsoleTextAttribute，是API设置控制台窗口颜色属性的函数，这里和句柄搭配
{                               
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,
		FOREGROUND_GREEN |
		FOREGROUND_INTENSITY);
}

//设置颜色为红色（食物)
inline void Red_color()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,
		FOREGROUND_RED |
		FOREGROUND_INTENSITY);
}

//设置颜色为黄色(说明文字和蛇头)
inline void Yellow_color()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,
		FOREGROUND_RED |
		FOREGROUND_GREEN |
		FOREGROUND_INTENSITY);
}

//设置颜色为白色(墙和障碍)
inline void White_color()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,
		FOREGROUND_RED |
		FOREGROUND_GREEN |
		FOREGROUND_BLUE |
		FOREGROUND_INTENSITY);
}

//定位函数，作用是移动光标到给出的坐标，用于打印
void Set_location(int x, int y)
{
	COORD cd;
	HANDLE hOut;
	cd.X = x;
	cd.Y = y;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, cd);//定位坐标
}

//设置地图内部障碍物,一共四块障碍物
//打印"■"：横坐标占2，纵坐标占1
void Creat_obs(Obstacle o[], int n)
{
	//第一块障碍,形状为横排+竖排
	int a = 14;//横排起点横坐标
	int b = 9;//竖排起点纵坐标
	for (int i = 0; i < 15; i++)
	{
		if (i < 6)
		{
			o[i].x = a;
			o[i].y = 8;
			a += 2;
		}
		else
		{
			o[i].x = 24;
			o[i].y = b;
			b++;
		}
	}

	//第二块障碍:斜排
	a = 8;
	b = 16;
	for (int i = 15; i < 24; i++)
	{
		o[i].x = a;
		a += 2;
		o[i].y = b;
		b++;
	}
	
	//第三块障碍：竖排
	a = 40;
	b = 6;
	for (int i = 20; i < 26; i++)
	{
		o[i].x = a;
		o[i].y = b;
		b++;
	}
	
	//第四块障碍:横排
	a = 44;
	b = 20;
	for (int i = 26; i < 30; i++)
	{
		o[i].x = a;
		a -= 2;
		o[i].y = b;
	}

	//把上述设置的障碍物打印到地图上
	for (int i = 0; i < 30; i++)
	{
		Set_location(o[i].x, o[i].y);
		cout << "■";//横坐标占2，纵坐标占1
	}
}

//初始化蛇，蛇一开始有五节
void Initial()
{
	Snake *tail = new Snake;//蛇头
	tail->s_x = 22;//初始化蛇头位置x坐标
	tail->s_y = 5;//初始化蛇头y坐标
	tail->next = NULL;
	head = tail;

	for (int i = 0; i < 4; i++)//初始化蛇身的长度为4
	{
		Snake *newnode = new Snake;
		newnode->s_x = tail->s_x + 2;
		newnode->s_y = tail->s_y;
		newnode->next = NULL;

		tail->next = newnode;
		tail = newnode;
	}
	tail = NULL;

	q = head;
	while (q != NULL)
	{
		if (q == head)//将蛇头标注为黄色
		{
			Set_location(q->s_x, q->s_y);
			Yellow_color();
			cout << "■";
			q = q->next;
		}
		else
		{
			Set_location(q->s_x, q->s_y);
			Green_color();
			cout << "■";
			q = q->next;
		}
	}
}

//创建地图:30*30
void creatMap()
{
	//打印上下边框
	for (int i = 0; i<60; i += 2)
	{
		Set_location(i, 0);
		cout << "■";
		Set_location(i, 29);
		cout << "■";
	}
	Set_location(10, 0);//穿越口
	cout << "  ";
	Set_location(50, 29);//穿越口
	cout << "  ";

	//打印左右边框
	for (int i = 1; i<29; i++)
	{
		Set_location(0, i);
		cout << "■";
		Set_location(58, i);
		cout << "■";
	}
	Set_location(0, 20);//穿越口
	cout << "  ";
	Set_location(58, 6);//穿越口
	cout << "  ";

	//建立障碍
	Creat_obs(o, 30);
}

//随机生成食物的函数
void creat_food()
{
	srand((unsigned)time(NULL));//给定一个随机数种子
	Snake *food_1;//创造出来的食物是先由food_1指向的，等创建好食物之后，再赋值给全局food指针
	food_1 = new Snake;
  
	//随机生成食物
	while (true)//保障生成的随机数在可运行空间内部
	{
		food_1->s_y = (rand() % 28) + 1;//食物x坐标
		food_1->s_x = (rand() % 55) + 2;//食物y坐标
		if ((food_1->s_x % 2) == 0 )
			break;
	}
	
	//使用递归思想判断是否符合要求
	//判断食物是否在蛇身上
	q = head;//q是定义的一个全局指针，用来遍历整个蛇身
	while (q != NULL)
	{
		if (q->s_x == food_1->s_x && q->s_y == food_1->s_y) 
		{
			delete food_1;//重合,重新生成
			creat_food();
			food_1 = NULL;
			break;
		}
		else
			q = q->next;
	}
	//判断食物是否在障碍物上
	for (int i = 0; i < 30; i++)
	{
		if (o[i].x == food_1->s_x && o[i].y == food_1->s_y)
		{
			delete food_1;//重合,重新生成
			creat_food();
			food_1 = NULL;
			break;
		}
	}
	//生成食物成功,打印
	if (food_1 != NULL)
	{
		Set_location(food_1->s_x, food_1->s_y);
		food = food_1;
		Red_color();//让食物变成红色
		cout << "★";//输出食物
	}
}

//暂停函数：按下空格
void pause()
{
	while (1)
	{
		Sleep(300);//延时函数，1000表示延时1s，这里是延时0.3s
		if (GetAsyncKeyState(VK_SPACE))//VK表示键盘按键行为，“_”表示是哪一个按键，这里判断是空格按键
			break; //这里判断如果按键是SPACE 就要暂停游戏
	}
}

//开始游戏
void Start()
{
	system("mode con cols=100 lines=30");//设置运行框的大小

	for (int i = 33; i<60; i += 2)//打印上下边框
	{
		Set_location(i, 10);
		cout << "■";
		Set_location(i, 14);
		cout << "■";
	}
	for (int i = 10; i<15; i++)//打印左右边框
	{
		Set_location(33, i);
		cout << "■";
		Set_location(61, i);
		cout << "■";
	}
	Set_location(42, 12);
	cout << "贪吃蛇小游戏" << endl;
	Set_location(38, 16);
	cout << "制作人:杨宇航" << endl;
	system("pause");

	system("cls");//清屏

	Set_location(44, 10);
	cout << "玩法介绍" << endl;
	Set_location(30, 12);
	cout << "1.用↑.↓.←.→分别控制蛇的移动！" << endl;
	Set_location(30, 14);
	cout << "2.地图边框设有隧道，贪吃蛇可从中穿越！" << endl;
	Set_location(30, 16);
	cout << "3.蛇碰到墙壁、障碍物，或咬到自己，则游戏结束！" << endl;
	Set_location(30, 18);
	cout << "4.随着分数增加，蛇移动速度会加快！" << endl;
	Set_location(30, 18);
	cout << "5.游戏途中，按Space键暂停，按Esc键退出！" << endl;
	system("pause");

	system("cls");//清屏

	creatMap();
	Initial();
	creat_food();
}

//进行游戏中
void Playing()
{
	Set_location(64, 8);
	Yellow_color();
	cout << "每个食物: " << add << " 分";
	Set_location(64, 14);
	Yellow_color();
	cout << "1.用↑.↓.←.→分别控制蛇的移动！" << endl;
	Set_location(64, 16);
	Yellow_color();
	cout << "2.不能碰到墙壁、障碍,不能咬到自己！" << endl;
	Set_location(64, 18);
	Yellow_color();
	cout << "3.贪吃蛇可以穿越墙壁上的隧道！" << endl;
	Set_location(64, 20);
	Yellow_color();
	cout << "4.ESC :退出游戏. space:暂停游戏" << endl;

	while (true)
	{
		//判断按键状态函数
		if (GetAsyncKeyState(VK_UP) && condition != DOWN)
			condition = UP;
		else if (GetAsyncKeyState(VK_DOWN) && condition != UP)
			condition = DOWN;
		else if (GetAsyncKeyState(VK_LEFT) && condition != RIGHT)
			condition = LEFT;
		else if (GetAsyncKeyState(VK_RIGHT) && condition != LEFT)
			condition = RIGHT;
		else if (GetAsyncKeyState(VK_SPACE))
			pause();
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			end_condition = 3;
			Die();
		}
		//根据已经获得的分数调整屏幕刷新时间
		if (score <= 3)
			Sleep(250);
		if (score > 3 && score <= 9)
			Sleep(150);
		if(score > 9)
			Sleep(50);

		//移动蛇
		head->Move();

		//显示分数
		Set_location(64, 10);
		Yellow_color();
		cout << "Your Score : " << score << " 分";

	}
}

//游戏结束
void Die()
{
	system("cls");
	Set_location(40, 10);
	if (end_condition == 1)
	{
		Yellow_color();
		cout << "撞墙而死！！！！";
	}
	else if (end_condition == 2)
	{
		Yellow_color();
		cout << "咬到自己！！！！";
	}

	else if (end_condition == 3)
	{
		Yellow_color();
		cout << "你自己结束了游戏。。。";
	}
	else if (end_condition == 4)
	{
		Yellow_color();
		cout << "撞到障碍物！！！！";
	}
	Set_location(40, 14);
	Yellow_color();
	cout << "总得分: " << score << endl;
	system("pause");
	exit(0);
}