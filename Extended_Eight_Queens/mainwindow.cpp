#include "mainwindow.h"
#include"ui_mainwindow.h"

#include<QPainter>
#include<QBrush>

//#include<iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化棋盘，为八皇后
    this->N_queen=8;
    this->sum=0;


    //设置显示窗口
    this->setFixedSize(this->width(),this->height());//固定窗口大小
    setMinimumSize(1000,850);//固定大小为1000*850
    setWindowTitle("N-皇后问题");//设置窗口标题


    //显示输入提示框
    input=new QLabel(this);
    input->setGeometry(750,200,200,40);//前两个参数为起始顶点坐标，后两个参数为方框长度和宽度
    input->setText("请输入皇后个数N(3<N<10):");


    //皇后个数输入框
    edit=new QLineEdit(this);
    edit->setGeometry(750,250,200,40);//前两个参数为起始顶点坐标，后两个参数为方框长度和宽度


    //确定按钮
    btnOK=new QPushButton(this);
    connect(btnOK,SIGNAL(clicked()),this,SLOT(display()));//链接到总方案数，方案号最大值
    btnOK->setGeometry(800,300,100,40);//前两个参数为起始顶点坐标，后两个参数为方框长度和高度
    btnOK->setText("确定");


    //显示总解决方案数目
    output=new QLabel(this);
    output->setGeometry(750,400,100,50);
    output->setText("解的个数:");


    //方案号标签
    solu=new QLabel(this);
    solu->setGeometry(750,500,100,50);//位置
    solu->setText("方案号：");


    //方案号选择框
    spin=new QSpinBox(this);
    spin->setGeometry(820,500,100,40);
    connect(spin,SIGNAL(valueChanged(int)),this,SLOT(Show_Solution()));

}

//析构函数
MainWindow::~MainWindow()
{
    delete ui;
}


//设置棋盘大小
void MainWindow::Set_Queen(int N)
{
    this->N_queen=N;
}


//调用绘图函数
void MainWindow::paintEvent(QPaintEvent *)
{
    this->Show();//调用棋盘绘制函数
    this->Chess_Show();//绘制解决方案
}


//绘制各个解决方案
void MainWindow::Chess_Show()
{
    Queen.Once_Solution(spin->text().toInt(),0);

    int rect=640/this->N_queen;//依据皇后数目将区域等分
    QPainter painter(this);
    QBrush brush(QColor(Qt::blue));//定义为蓝色画刷
    painter.setBrush(brush);//选择画刷brush
    for(int i=0;i<N_queen;i++)
        for(int j=0;j<N_queen;j++)
            if(Queen.Show[i][j]==true)
                painter.drawEllipse(50+j*rect,70+i*rect,rect,rect);//圆表示棋子

}

//绘制网格世界
void MainWindow::Show()
{
    int rect=640/this->N_queen;//依据皇后数目将区域等分
    QPainter painter(this);
    //设置画笔颜色、宽度
    painter.setPen(QPen(QColor(0, 0, 0), 2));
    //绘制背景网格
    for(int i=0;i<= N_queen;i++)
    {
        for(int j=0;j<= N_queen;j++)
        {
            painter.drawLine(50,70+i*rect,50+N_queen*rect,70+i*rect);//绘制横线
            painter.drawLine(50+i*rect,70,50+rect*i,70+ N_queen*rect);//绘制竖线
        }
    }
    //设置背景画刷颜色
    QBrush brush1(QColor(Qt::black));//定义为黑色画刷
    painter.setBrush(brush1);//选择画刷brush1
    //填充背景网格颜色
    for(int i=0;i< N_queen;i++)
    {
        for(int j=0;j< N_queen;j++)
        {
            if(i%2==0)//偶数行
            {
                if(j%2==0)//偶数列
                    painter.drawRect(50+i*rect,70+j*rect,rect,rect);
            }
            else//奇数行
            {
                if(j%2!=0)//奇数列
                    painter.drawRect(50+i*rect,70+j*rect,rect,rect);
            }
        }
    }
}


//输出方案总数
void MainWindow::display()
{
    if(edit->text().toInt()<=9 && edit->text().toInt()>=4)
    {
        Set_Queen(edit->text().toInt());
        Queen.reset(N_queen);
        spin->setValue(0);

        Queen.Put_Chess(0);//寻找解决方案总数
        sum=Queen.GetCounts();
        output->setText("解的个数: "+QString::number(sum));
        spin->setMaximum(sum);//限制方案号选择框最大值

        this->update();//更新
    }
    else
    {
        edit->setText("为非法输入，请重新输入");
    }

}

//选择方案号
void MainWindow::Show_Solution()
{
    Queen.Once_Solution(spin->text().toInt(),0);
    Queen.reset(N_queen);

    update();//更新
}
























