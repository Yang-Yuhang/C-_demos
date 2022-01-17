#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

void traceBoundary(Mat src,Mat& dst,Mat& out)//dst为内边界,out为外边界;8-邻接
{
	Point ptStart;  //起始边界点
	Point ptCur;    //当前边界点
	//搜索方向数组{右，右上，上，左上，左，左下，下，右下},编号从0~7
	int Direction[8][2] = { { 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 },{ -1,0 },{ -1, 1 },{ 0,1 },{ 1,1 } };
	int nCurDirect;//当前探查方向
	int dir=7;//初始化
	bool bAtStartPt;//搜索开始

	int x, y;//x对应列,y对应行，原点在左上角
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			if (src.at<uchar>(i, j)>0)//寻找第一个像素点
			{
				//起始像素点坐标
				ptStart.x = j;
				ptStart.y = i;

				ptCur = ptStart;//初始化当前像素
				bAtStartPt = true;//搜索开始，注意区分开始和结束

				while ((ptCur.x != ptStart.x) || (ptCur.y != ptStart.y) || bAtStartPt==true)
				{
					bAtStartPt = false;

					//计算起始探查位置
					if (dir % 2 == 1)//奇数
					{
						nCurDirect = (dir + 6) % 8;
					}
					else
					{
						nCurDirect = (dir + 7) % 8;
					}
					//下一个探查点坐标
					//int nSearchTimes = 0;//搜索次数
					x = ptCur.x + Direction[nCurDirect][0];
					y = ptCur.y + Direction[nCurDirect][1];
					//nSearchTimes = 1;
					for (int nSearchTimes = 1; nSearchTimes <= 8; nSearchTimes++)//转一圈找出所有非像素点
					{
						if (src.at<uchar>(y, x) == 0)
							//在外边界图像上标记外边界
							out.at<uchar>(ptCur.y, ptCur.x) = 255;//图像为白
						nCurDirect++;//逆时针旋转45度
						if (nCurDirect >= 8)
							nCurDirect = nCurDirect - 8;
						x = ptCur.x + Direction[nCurDirect][0];
						y = ptCur.y + Direction[nCurDirect][1];
					}

					int Searchtime = 1;
					while (src.at<uchar>(y, x) == 0)//非像素点
					{
						nCurDirect++;//逆时针旋转45度
						if (nCurDirect >= 8)
							nCurDirect -= 8;
						x = ptCur.x + Direction[nCurDirect][0];
						y = ptCur.y + Direction[nCurDirect][1];
						//8领域中都没有边界点，说明是孤立点
						if (++Searchtime >= 8)
						{
							x = ptCur.x;
							y = ptCur.y;
							break;
						}
					}
					//找到下一个内边界点
					ptCur.x = x;
					ptCur.y = y;
					//在内边界图像上标记边界
					dst.at<uchar>(ptCur.y, ptCur.x) = 255;//图像为白

					dir = nCurDirect;//更新dir
				}
				return;
			}
		}
	}
}

int main()
{
	Mat src = imread("C:/Users/dell/Desktop/plane.jpg");//读取灰度图
	imshow("输入图像", src);

	Mat a;//灰度图
	cvtColor(src, a, CV_BGR2GRAY);
	imshow("转化为灰度图", a);

	Mat src_binary;//二值图
				   
	threshold(src, src_binary, 220, 255, THRESH_BINARY);//二值化
	imshow("二值图像", src_binary);

	Mat InnerBoundaryImg = Mat::zeros(src_binary.size(), src_binary.type());//内边界图像
	Mat OuterBoundaryImg = Mat::zeros(src_binary.size(), src_binary.type());//外边界图像
	traceBoundary(src_binary,InnerBoundaryImg,OuterBoundaryImg);

	imshow("内边界图像", InnerBoundaryImg);
	imshow("外边界图像", OuterBoundaryImg);

	waitKey(0);
	return 0;

}
