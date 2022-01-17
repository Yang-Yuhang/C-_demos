/*
贪吃蛇功能函数实现
*/

#pragma once
#include"Function.h"

int Snake::Get_x()
{
	return s_x;
}

int Snake::Get_y()
{
	return s_y;
}

Snake *Snake::Get_next()
{
	return next;
}

//是否咬到自己
bool Snake::Bite_self()
{
	Snake *self;//遍历整个蛇检查是否咬到自己的指针

	self = head->Get_next();//从蛇头的下一个节点出发
	
	while (self != NULL)//遍历所有结点
	{
		if (self->Get_x() == head->Get_x() && self->Get_y() == head->Get_y())//如果self所指向的x，y的坐标与蛇头的x，y相等，说明咬到自己了
			return 1;//咬到自己
		self = self->Get_next();//结点后移
	}
	return 0;//没咬到
}

//撞墙函数
void Snake::Can_not_crowall()
{
	//撞到障碍物
	for (int i = 0; i < 30; i++)
	{
		if (head->s_x == o[i].x && head->s_y == o[i].y)
		{
			end_condition = 4;//撞到障碍物死亡
			Die();
		}
	}
	//撞墙，注意墙上有四个通口
	if ((head->s_x == 0 && head->s_y != 20) ||
		(head->s_x == 58 && head->s_y != 6) ||
		(head->s_x != 10 && head->s_y == 0) ||
		(head->s_x != 50 && head->s_y == 29))
	{
		end_condition = 1;//撞墙死亡
		Die();           //输出相对应情况的结束画面
	}
}

//蛇移动的函数
void Snake::Move()
{
	head->Can_not_crowall();//先判断原来的头部是否撞墙
	Snake *next_head = new Snake;//新的头部,完成蛇的移动
	//确定蛇的移动情况
    //向上
	if (condition == UP)
	{
		next_head->s_x = head->s_x;//新头的x坐标
		next_head->s_y = head->s_y - 1;//新头的y坐标
		next_head->next = head;//新头与现有的头节点链接
		head = next_head;//head指针前移
		q = head;//q指针指向head
		//到此为止,蛇比正常情况多出一个结点,现在分情况讨论是否删除多余结点
		//新头部有食物
		if (next_head->s_x == food->s_x && next_head->s_y == food->s_y)
		{
			Set_location(food->s_x, food->s_y);
			cout << "  ";
			delete food;
			while (q != NULL)
			{
				if (q == head)
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
			score += add;//吃到食物，加分
			creat_food();
		}
		//下一个位置没有食物
		else
		{
			while (q->next->next != NULL)//寻找到实际最后一个结点
			{
				if (q->s_y < 0)//y方向穿墙实现:从(10,0)穿到(50,29)
				{
					q->s_x += 40;
					q->s_y += 30;//坐标从(10,-1)到(50,29)
				}
				if (q == head)
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
			Set_location(q->next->s_x, q->next->s_y);//定位到多余结点
			cout << "  ";
			delete q->next;//删除多余结点
			q->next = NULL;
			Set_location(q->s_x, q->s_y);//此时q为蛇最后一个节点
			Green_color();
			cout << "■";
		}
	}

	//向下
	if (condition == DOWN)//下 情况
	{
		next_head->s_x = head->s_x;//新头的x坐标
		next_head->s_y = head->s_y + 1;//新头的y坐标
		next_head->next = head;//新头与现有的头节点链接
		head = next_head;//head指针前移
		q = head;//q指针指向head
		 //到此为止,蛇比正常情况多出一个结点,现在分情况讨论是否删除多余结点
		 //新头部有食物
		if (next_head->s_x == food->s_x && next_head->s_y == food->s_y)
		{
			Set_location(food->s_x, food->s_y);
			cout << "  ";
			delete food;
			while (q != NULL)
			{
				if (q == head)
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
			score += add;//吃到食物，加分
			creat_food();
		}
		//下一个位置没有食物
		else
		{
			while (q->next->next != NULL)
			{
				if (q->s_y > 29)//y方向穿墙实现:从(50,29)穿到(10,0)
				{
					q->s_x -= 40;
					q->s_y -= 30;////坐标从(50,30)到(10,0)
				}
				if (q == head)
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
			Set_location(q->next->s_x, q->next->s_y);//定位到多余结点
			cout << "  ";
			delete q->next;//删除多余结点
			q->next = NULL;
			Set_location(q->s_x, q->s_y);//此时q为蛇最后一个节点
			Green_color();
			cout << "■";
		}
	}

	//向左
	if (condition == LEFT)
	{
		next_head->s_x = head->s_x - 2;//新头的x坐标
		next_head->s_y = head->s_y;//新头的y坐标
		next_head->next = head;//新头与现有的头节点链接
		head = next_head;//head指针前移
		q = head;//q指针指向head
				 //到此为止,蛇比正常情况多出一个结点,现在分情况讨论是否删除多余结点
				 //新头部有食物
		if (next_head->s_x == food->s_x && next_head->s_y == food->s_y)
		{
			Set_location(food->s_x, food->s_y);
			cout << "  ";
			delete food;
			while (q != NULL)
			{
				if (q == head)
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
			score += add;//吃到食物，加分
			creat_food();
		}
		//下一个位置没有食物
		else
		{
			while (q->next->next != NULL)
			{
				if (q->s_x < 0)//x方向穿墙实现:从(0,20)穿到(58,6)
				{
					q->s_x += 60;
					q->s_y -= 14;//坐标从(-2,20)到(58,6)
				}
				if (q == head)
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
			Set_location(q->next->s_x, q->next->s_y);//定位到多余结点
			cout << "  ";
			delete q->next;//删除多余结点
			q->next = NULL;
			Set_location(q->s_x, q->s_y);//此时q为蛇最后一个节点
			Green_color();
			cout << "■";
		}
		q = head;
	}

	//向右
	if (condition == RIGHT)
	{
		next_head->s_x = head->s_x + 2;//新头的x坐标
		next_head->s_y = head->s_y;//新头的y坐标
		next_head->next = head;//新头与现有的头节点链接
		head = next_head;//head指针前移
		q = head;//q指针指向head
				 //到此为止,蛇比正常情况多出一个结点,现在分情况讨论是否删除多余结点
				 //新头部有食物
		if (next_head->s_x == food->s_x && next_head->s_y == food->s_y)
		{
			Set_location(food->s_x, food->s_y);
			cout << "  ";
			delete food;
			while (q != NULL)
			{
				if (q == head)
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
			score += add;//吃到食物，加分
			creat_food();
		}
		//下一个位置没有食物
		else
		{
			while (q->next->next != NULL)
			{
				if (q->s_x > 58)//x方向穿墙实现:从(58,6)穿到(0,20)
				{
					q->s_x -= 60;
					q->s_y += 14;//坐标从(60,6)到(0,20)
				}
				if (q == head)
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
			Set_location(q->next->s_x, q->next->s_y);//定位到多余结点
			cout << "  ";
			delete q->next;//删除多余结点
			q->next = NULL;
			Set_location(q->s_x, q->s_y);//此时q为蛇最后一个节点
			Green_color();
			cout << "■";
		}
	}

	//每次移动后检查是否咬到自己
	if (Bite_self())
	{
		end_condition = 2;//如果要到自己就要给end_condition赋上相应死亡情况的值
		Die();//咬到自己调用die函数
	}

}

