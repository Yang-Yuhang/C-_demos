#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>

#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QString>
#include<QSpinBox>
#include<QPainter>

#include"double_queen.h"



namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    queen Queen;//调用皇后对象
    int N_queen;//皇后数目
    int sum;//解决方案总数目

private:
    QLabel *input;//输入框
    QLabel *output;//输出框
    QLineEdit *edit;//编辑框
    QPushButton *btnOK;//确定按钮
    QLabel *solu;//显示方案号
    QSpinBox *spin;//方案号选择

    void Set_Queen(int N);//设置棋盘大小

    void Show();//绘制棋盘
    void Chess_Show();//绘制棋子
    void paintEvent(QPaintEvent *);//默认绘图函数


private slots:
    void display();//槽函数,显示总解决方案数目
    void Show_Solution();//槽函数,显示各个解决方案

};

#endif // MAINWINDOW_H
