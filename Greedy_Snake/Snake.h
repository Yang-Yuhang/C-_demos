/*
̰���߹��ܺ���ʵ��
*/

#pragma once
class Snake//���࣬�������ߵĻ���Ԫ�غ��ߵ����л�����������������ɵ�
{
public:

	friend void creat_food();//����ʳ��ĺ���
	friend void Initial(); //��ʼ����������ʼ���ߵ�����ĳ�ʼ���ȣ��Լ�����λ��

	int Get_x();
	int Get_y();

	Snake *Get_next();

	bool Bite_self();//�ж��Ƿ�ҧ���Լ�
	void Can_not_crowall();//���ܴ�ǽ����������ǿ����
	void Move();//�ߵ��ƶ�

private:
	int s_x;//�ߵ�x��y����
	int s_y;
	Snake *next;//ʹ��������ɣ����������򣬴�ź�x��y���ꡣһ��ָ���򣬴�����Ӻ�������ڵ�ĵ�ַ
};

struct Obstacle//�ϰ���ṹ�壬�ڲ���x��y������
{
	//�ϰ���ĺ�������
	int x;
	int y;
};

