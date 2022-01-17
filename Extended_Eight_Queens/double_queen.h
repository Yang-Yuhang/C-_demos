#ifndef DOUBLE_QUEEN
#define DOUBLE_QUEEN

class queen
{
private:
    bool **board;//二维棋盘
    int Queen_Number;//皇后数目
    int Counts;//统计解决方案数目
    int count;//用于单个解决方案
    bool Is_Recursion;//判断是否递归,用于单个解决方案

public:
    bool **Show;//用于打印的棋盘

    queen();//无参构造函数,默认为八皇后
    //queen(int N);//有参构造函数，设置皇后数目
    ~queen();//析构函数

    void reset();//默认重置棋盘
    void reset(int N);//重置棋盘大小

    //void show(bool **Q);//结果输出
    void chess_show();//解决方案打印

    bool Check(int row,int col);//判断函数，判断(row,col)位置是否合法
    void Put_Chess(int m);//寻找所有解决方案，不输出
    void Once_Solution(int solu,int i);//寻找最后一种解决方案，并输出

    int GetCounts();//获取解决方案总数
    int GetQueenNumber();//获取皇后数目

};


#endif // DOUBLE_QUEEN

