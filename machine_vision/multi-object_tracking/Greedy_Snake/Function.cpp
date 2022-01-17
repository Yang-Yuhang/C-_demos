/*
̰���߹��ܺ���ʵ��
*/

#pragma once
#include"Function.h"

Snake *head=NULL, *food=NULL;//ȫ��ָ�룬head����Զָ���һ���ڵ��ָ�룬food��ָ��ʳ���ָ��
Snake *q=NULL;//�������������õ���ָ��
int condition;//����������������Ѱ�����������ֱ�������ֵ��������������Ҳ��int ����
int end_condition = 0;//��ʾ�����������=1��ײǽ��=2��ҧ���Լ���=3���Լ�����;4 ײ���ϰ������
int score = 0;//�÷�
int add = 1;//ÿ��ʳ��ķ���
Obstacle o[30];//����һ������ϰ���Ľṹ�������������ÿһ���ϰ����x��y����


//����Ϊ��ɫ(�ߣ�
inline void Green_color()//�����õ�һ��SetConsoleTextAttribute����API���ÿ���̨������ɫ���Եĺ���������;������
{                               
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,
		FOREGROUND_GREEN |
		FOREGROUND_INTENSITY);
}

//������ɫΪ��ɫ��ʳ��)
inline void Red_color()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,
		FOREGROUND_RED |
		FOREGROUND_INTENSITY);
}

//������ɫΪ��ɫ(˵�����ֺ���ͷ)
inline void Yellow_color()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,
		FOREGROUND_RED |
		FOREGROUND_GREEN |
		FOREGROUND_INTENSITY);
}

//������ɫΪ��ɫ(ǽ���ϰ�)
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

//��λ�������������ƶ���굽���������꣬���ڴ�ӡ
void Set_location(int x, int y)
{
	COORD cd;
	HANDLE hOut;
	cd.X = x;
	cd.Y = y;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, cd);//��λ����
}

//���õ�ͼ�ڲ��ϰ���,һ���Ŀ��ϰ���
//��ӡ"��"��������ռ2��������ռ1
void Creat_obs(Obstacle o[], int n)
{
	//��һ���ϰ�,��״Ϊ����+����
	int a = 14;//������������
	int b = 9;//�������������
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

	//�ڶ����ϰ�:б��
	a = 8;
	b = 16;
	for (int i = 15; i < 24; i++)
	{
		o[i].x = a;
		a += 2;
		o[i].y = b;
		b++;
	}
	
	//�������ϰ�������
	a = 40;
	b = 6;
	for (int i = 20; i < 26; i++)
	{
		o[i].x = a;
		o[i].y = b;
		b++;
	}
	
	//���Ŀ��ϰ�:����
	a = 44;
	b = 20;
	for (int i = 26; i < 30; i++)
	{
		o[i].x = a;
		a -= 2;
		o[i].y = b;
	}

	//���������õ��ϰ����ӡ����ͼ��
	for (int i = 0; i < 30; i++)
	{
		Set_location(o[i].x, o[i].y);
		cout << "��";//������ռ2��������ռ1
	}
}

//��ʼ���ߣ���һ��ʼ�����
void Initial()
{
	Snake *tail = new Snake;//��ͷ
	tail->s_x = 22;//��ʼ����ͷλ��x����
	tail->s_y = 5;//��ʼ����ͷy����
	tail->next = NULL;
	head = tail;

	for (int i = 0; i < 4; i++)//��ʼ������ĳ���Ϊ4
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
		if (q == head)//����ͷ��עΪ��ɫ
		{
			Set_location(q->s_x, q->s_y);
			Yellow_color();
			cout << "��";
			q = q->next;
		}
		else
		{
			Set_location(q->s_x, q->s_y);
			Green_color();
			cout << "��";
			q = q->next;
		}
	}
}

//������ͼ:30*30
void creatMap()
{
	//��ӡ���±߿�
	for (int i = 0; i<60; i += 2)
	{
		Set_location(i, 0);
		cout << "��";
		Set_location(i, 29);
		cout << "��";
	}
	Set_location(10, 0);//��Խ��
	cout << "  ";
	Set_location(50, 29);//��Խ��
	cout << "  ";

	//��ӡ���ұ߿�
	for (int i = 1; i<29; i++)
	{
		Set_location(0, i);
		cout << "��";
		Set_location(58, i);
		cout << "��";
	}
	Set_location(0, 20);//��Խ��
	cout << "  ";
	Set_location(58, 6);//��Խ��
	cout << "  ";

	//�����ϰ�
	Creat_obs(o, 30);
}

//�������ʳ��ĺ���
void creat_food()
{
	srand((unsigned)time(NULL));//����һ�����������
	Snake *food_1;//���������ʳ��������food_1ָ��ģ��ȴ�����ʳ��֮���ٸ�ֵ��ȫ��foodָ��
	food_1 = new Snake;
  
	//�������ʳ��
	while (true)//�������ɵ�������ڿ����пռ��ڲ�
	{
		food_1->s_y = (rand() % 28) + 1;//ʳ��x����
		food_1->s_x = (rand() % 55) + 2;//ʳ��y����
		if ((food_1->s_x % 2) == 0 )
			break;
	}
	
	//ʹ�õݹ�˼���ж��Ƿ����Ҫ��
	//�ж�ʳ���Ƿ���������
	q = head;//q�Ƕ����һ��ȫ��ָ�룬����������������
	while (q != NULL)
	{
		if (q->s_x == food_1->s_x && q->s_y == food_1->s_y) 
		{
			delete food_1;//�غ�,��������
			creat_food();
			food_1 = NULL;
			break;
		}
		else
			q = q->next;
	}
	//�ж�ʳ���Ƿ����ϰ�����
	for (int i = 0; i < 30; i++)
	{
		if (o[i].x == food_1->s_x && o[i].y == food_1->s_y)
		{
			delete food_1;//�غ�,��������
			creat_food();
			food_1 = NULL;
			break;
		}
	}
	//����ʳ��ɹ�,��ӡ
	if (food_1 != NULL)
	{
		Set_location(food_1->s_x, food_1->s_y);
		food = food_1;
		Red_color();//��ʳ���ɺ�ɫ
		cout << "��";//���ʳ��
	}
}

//��ͣ���������¿ո�
void pause()
{
	while (1)
	{
		Sleep(300);//��ʱ������1000��ʾ��ʱ1s����������ʱ0.3s
		if (GetAsyncKeyState(VK_SPACE))//VK��ʾ���̰�����Ϊ����_����ʾ����һ�������������ж��ǿո񰴼�
			break; //�����ж����������SPACE ��Ҫ��ͣ��Ϸ
	}
}

//��ʼ��Ϸ
void Start()
{
	system("mode con cols=100 lines=30");//�������п�Ĵ�С

	for (int i = 33; i<60; i += 2)//��ӡ���±߿�
	{
		Set_location(i, 10);
		cout << "��";
		Set_location(i, 14);
		cout << "��";
	}
	for (int i = 10; i<15; i++)//��ӡ���ұ߿�
	{
		Set_location(33, i);
		cout << "��";
		Set_location(61, i);
		cout << "��";
	}
	Set_location(42, 12);
	cout << "̰����С��Ϸ" << endl;
	Set_location(38, 16);
	cout << "������:���" << endl;
	system("pause");

	system("cls");//����

	Set_location(44, 10);
	cout << "�淨����" << endl;
	Set_location(30, 12);
	cout << "1.�á�.��.��.���ֱ�����ߵ��ƶ���" << endl;
	Set_location(30, 14);
	cout << "2.��ͼ�߿����������̰���߿ɴ��д�Խ��" << endl;
	Set_location(30, 16);
	cout << "3.������ǽ�ڡ��ϰ����ҧ���Լ�������Ϸ������" << endl;
	Set_location(30, 18);
	cout << "4.���ŷ������ӣ����ƶ��ٶȻ�ӿ죡" << endl;
	Set_location(30, 18);
	cout << "5.��Ϸ;�У���Space����ͣ����Esc���˳���" << endl;
	system("pause");

	system("cls");//����

	creatMap();
	Initial();
	creat_food();
}

//������Ϸ��
void Playing()
{
	Set_location(64, 8);
	Yellow_color();
	cout << "ÿ��ʳ��: " << add << " ��";
	Set_location(64, 14);
	Yellow_color();
	cout << "1.�á�.��.��.���ֱ�����ߵ��ƶ���" << endl;
	Set_location(64, 16);
	Yellow_color();
	cout << "2.��������ǽ�ڡ��ϰ�,����ҧ���Լ���" << endl;
	Set_location(64, 18);
	Yellow_color();
	cout << "3.̰���߿��Դ�Խǽ���ϵ������" << endl;
	Set_location(64, 20);
	Yellow_color();
	cout << "4.ESC :�˳���Ϸ. space:��ͣ��Ϸ" << endl;

	while (true)
	{
		//�жϰ���״̬����
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
		//�����Ѿ���õķ���������Ļˢ��ʱ��
		if (score <= 3)
			Sleep(250);
		if (score > 3 && score <= 9)
			Sleep(150);
		if(score > 9)
			Sleep(50);

		//�ƶ���
		head->Move();

		//��ʾ����
		Set_location(64, 10);
		Yellow_color();
		cout << "Your Score : " << score << " ��";

	}
}

//��Ϸ����
void Die()
{
	system("cls");
	Set_location(40, 10);
	if (end_condition == 1)
	{
		Yellow_color();
		cout << "ײǽ������������";
	}
	else if (end_condition == 2)
	{
		Yellow_color();
		cout << "ҧ���Լ���������";
	}

	else if (end_condition == 3)
	{
		Yellow_color();
		cout << "���Լ���������Ϸ������";
	}
	else if (end_condition == 4)
	{
		Yellow_color();
		cout << "ײ���ϰ��������";
	}
	Set_location(40, 14);
	Yellow_color();
	cout << "�ܵ÷�: " << score << endl;
	system("pause");
	exit(0);
}