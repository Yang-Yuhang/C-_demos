#include"double_queen.h"
#include<iostream>

const int n_max=9;//最大皇后数目
const int n_min=4;//最小皇后数目

//默认构造函数，默认八皇后
queen::queen()
{
    Queen_Number=8;//默认皇后数目
    //分配内存
    board=new bool*[Queen_Number];
    for(int i=0;i<Queen_Number;i++)
    {
        board[i]=new bool[Queen_Number];
    }
    //初始化棋盘
    for(int i=0;i<Queen_Number;i++)
    {
        for(int j=0;j<Queen_Number;j++)
        {
            board[i][j]=false;
        }
    }
    Counts=0;

    count=0;
    Is_Recursion=true;

    //打印棋盘
    //分配内存
    Show=new bool*[Queen_Number];
    for(int i=0;i<Queen_Number;i++)
    {
         Show[i]=new bool[Queen_Number];
    }
    //初始化棋盘
    for(int i=0;i<Queen_Number;i++)
    {
        for(int j=0;j<Queen_Number;j++)
        {
             Show[i][j]=false;
        }
    }
}

/*
//有参构造,设置皇后数目
queen::queen(int N)
{
    //判断输入皇后数目是否在给定范围内
    if(N<n_min || N>n_max)//输入不合法
    {
        Queen_Number=8;
    }
    else//输入合法
    {
        Queen_Number=N;
    }
    //分配动态内存
    board=new bool*[Queen_Number];
    for(int i=0;i<Queen_Number;i++)
    {
        board[i]=new bool[Queen_Number];
    }
    //初始化棋盘
    for(int i=0;i<Queen_Number;i++)
    {
        for(int j=0;j<Queen_Number;j++)
        {
            board[i][j]=false;
        }
    }
    Counts=0;

    count=0;
    Is_Recursion=true;

    //打印棋盘
    //分配内存
    Show=new bool*[Queen_Number];
    for(int i=0;i<Queen_Number;i++)
    {
         Show[i]=new bool[Queen_Number];
    }
    //初始化棋盘
    for(int i=0;i<Queen_Number;i++)
    {
        for(int j=0;j<Queen_Number;j++)
        {
             Show[i][j]=false;
        }
    }
}
*/


//析构函数
queen::~queen()
{
    for(int i=0;i<Queen_Number;i++)
    {
        delete[] board[i];
    }
    delete[] board;

    //打印棋盘
    for(int i=0;i<Queen_Number;i++)
    {
        delete[] Show[i];
    }
    delete[] Show;
}





//默认重置棋盘
void queen::reset()
{
    Queen_Number=8;//默认皇后数目
    //分配棋盘内存
    board=new bool*[Queen_Number];
    for(int i=0;i<Queen_Number;i++)
    {
        board[i]=new bool[Queen_Number];
    }
    //初始化棋盘
    for(int i=0;i<Queen_Number;i++)
    {
        for(int j=0;j<Queen_Number;j++)
        {
            board[i][j]=false;
        }
    }
    Counts=0;

    count=0;
    Is_Recursion=true;

    //打印棋盘
    //分配内存
    Show=new bool*[Queen_Number];
    for(int i=0;i<Queen_Number;i++)
    {
         Show[i]=new bool[Queen_Number];
    }
    //初始化棋盘
    for(int i=0;i<Queen_Number;i++)
    {
        for(int j=0;j<Queen_Number;j++)
        {
             Show[i][j]=false;
        }
    }
}

//自定义重置棋盘
void queen::reset(int N)
{
    if(N<n_min || N>n_max)//输入不合法
    {
        Queen_Number=8;
    }
    else//输入合法
    {
        Queen_Number=N;
    }
    //分配动态内存
    board=new bool*[Queen_Number];
    for(int i=0;i<Queen_Number;i++)
    {
        board[i]=new bool[Queen_Number];
    }
    //初始化棋盘
    for(int i=0;i<Queen_Number;i++)
    {
        for(int j=0;j<Queen_Number;j++)
        {
           board[i][j]=false;
        }
    }
    Counts=0;

    count=0;
    Is_Recursion=true;

    //打印棋盘
    //分配内存
    Show=new bool*[Queen_Number];
    for(int i=0;i<Queen_Number;i++)
    {
         Show[i]=new bool[Queen_Number];
    }
    //初始化棋盘
    for(int i=0;i<Queen_Number;i++)
    {
        for(int j=0;j<Queen_Number;j++)
        {
             Show[i][j]=false;
        }
    }
}

//打印解决方案
void queen::chess_show()
{
    for(int i=0;i<Queen_Number;i++)
    {
        for(int j=0;j<Queen_Number;j++)
        {
            Show[i][j]=this->board[i][j];
        }
    }
}

/*
//结果输出
void queen::show(bool **Q)
{
    int m=Queen_Number;
    //分配动态内存
    Q=new bool*[m];
    for(int i=0;i<m;i++)
    {
        Q[i]=new bool[m];
    }
    //复制数据
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<m;j++)
        {
            Q[i][j]=this->board[i][j];
        }
    }

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<m;j++)
        {
            std::cout<<Q[i][j]<<"  ";
        }
        std::cout<<"\n";
    }
     std::cout<<"\n";
}
*/


//判断函数
bool queen::Check(int row, int col)
{
    //判断行是否满足条件
    for(int j=0;j<col;j++)
    {
        if(board[row][j]==true)
            return false;
    }
    //判断列是否满足条件
    for(int i=0;i<row;i++)
    {
        if(board[i][col]==true)
            return false;
    }
    //判断右斜线
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<Queen_Number;j++)
        {
            if(board[i][j]==true && ((i+j)==(row+col)))
                return false;
        }
    }
    //判断左斜线
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(board[i][j]==true && ((i-j)==(row-col)))
                return false;
        }
    }
    return true;
}



//寻找解决方案总数
void queen::Put_Chess(int m)//从第m行开始放置
{
    for(int j=0;j<Queen_Number;j++)
    {
        if(Check(m,j)==true)
        {
            this->board[m][j]=true;//在该位置放置棋子
            if(m==(Queen_Number-1))//棋子放置完毕
            {
                Counts++;
                for(int k=0;k<Queen_Number;k++)//归零
                    this->board[m][k]=false;
                return;
            }
            Put_Chess(m+1);//递归下一行
            for(int k=0;k<Queen_Number;k++)
                board[m][k]=false;
        }
    }
}


//寻找当单个解决方案（打印最后一种解决方案）
void queen::Once_Solution(int solu,int cur)//,bool **Q)
{
   // bool **Q;
    if(Is_Recursion==false)//递归结束
        return;
    if(cur==Queen_Number)//递归至最后一行
    {
        count++;
        if(count==solu)
        {
        //    show(Q);//打印最后一种解决方案
            chess_show();
            Is_Recursion=false;//递归结束
            return;
        }
        return;
    }
    else
    {
        for(int j=0;j<Queen_Number;j++)
        {
            if(Check(cur,j))//检查当前行和列
            {
                board[cur][j]=true;//放置棋子
                Once_Solution(solu,cur+1);//递归下一行

                for(int k=0;k<Queen_Number;k++)
                    board[cur][k]=false;
            }
        }
    }
}


//获取解决方案总数
int queen::GetCounts()
{
    return Counts;
}

//获取皇后数目
int queen::GetQueenNumber()
{
    return Queen_Number;
}


