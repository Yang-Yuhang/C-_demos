//通过帧差法确定动态目标并标定
#include<opencv\cv.hpp>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<time.h>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	clock_t start_time = clock();

	VideoCapture video("D:/课件/机器视觉基础/课件/作业2019/作业2019/老鼠视频.mp4");
	if (!video.isOpened())
		return -1;//视频打开失败

	int totalFrameNumber = video.get(CV_CAP_PROP_FRAME_COUNT);//获取视频的总帧数
	double rate = video.get(CV_CAP_PROP_FPS);//获取视频帧率
	Size size = Size(video.get(CV_CAP_PROP_FRAME_WIDTH), video.get(CV_CAP_PROP_FRAME_HEIGHT));//每帧大小
	

	VideoWriter out;
	out.open("D:/课件/机器视觉基础/课件/作业2019/作业2019/结果.avi", CV_FOURCC('M', 'J', 'P', 'G'), rate, size, true);
	if (!out.isOpened()) 
	{
		return -1;//视频写失败
	}

	Mat Frame;
	Mat GrayFrame;//灰度图
	Mat FirstGrayFrame;//前二帧灰度图
	Mat SecondGrayFrame;//第一帧灰度图
	
	Mat AbsFrame;//帧差法获得的差异图像
	Mat PreviousBinaryFrame;//前两帧差异的二值图
	Mat CurrentBinaryFrame;//当前帧和第一帧差异的二值图
	Mat Segmentation;//分割结果

	//用于形态变化的结构元素，参数分别为：矩形，内核尺寸，描点位于中心点
	Mat Kernel = getStructuringElement(MORPH_RECT, Size(43, 45), Point(-1, -1));
	
	//双阈值增强图像对比度
	int low = 129;//低阈值
	int high = 159;//高阈值
	double k = 255 / (high - low);//中间对比度
	
	//创建可调节大小的视频播放窗口
	namedWindow("video", 0);
	namedWindow("segmentation", 0);

	for (int i = 0; i < totalFrameNumber;i++)
	{
		video >> Frame;//读入视频帧
		if (!Frame.data)
			break;

		cvtColor(Frame, GrayFrame, COLOR_BGR2GRAY);//转化为灰度图
		GaussianBlur(GrayFrame, GrayFrame, Size(3, 3), 0, 0);//高斯滤波
		//用双阈值增强图像对比度
		for (int y = 0; y <GrayFrame.rows; y++)
		{
			for (int x = 0; x <GrayFrame.cols; x++)
			{
				if (GrayFrame.at<uchar>(y, x) < low)
					GrayFrame.at<uchar>(y, x) = 0;
				else if (GrayFrame.at<uchar>(y, x) > high)
					GrayFrame.at<uchar>(y, x) = 255;
				else
					GrayFrame.at<uchar>(y, x) = k * (GrayFrame.at<uchar>(y, x));
			}
		}

		if (i == 0)//为第一帧图片
		{
			FirstGrayFrame = GrayFrame;
			imshow("video", Frame);
			continue;
		}
		else if (i == 1)//为第二帧图片
		{
			SecondGrayFrame = GrayFrame;

			//帧差法，获取帧差异,参数为:输入第二帧图像,输入第一帧图像,输出差异图像
			absdiff(SecondGrayFrame, FirstGrayFrame, AbsFrame);

			//阈值化，参数分别为:输入输出图像,OTSU阈值,阈值最大值,二值化
			threshold(AbsFrame, PreviousBinaryFrame, 10, 255, THRESH_BINARY | THRESH_OTSU);
			
			imshow("video", Frame);
			continue;
		}
		else//为其他帧图片
		{
			absdiff(GrayFrame, FirstGrayFrame, AbsFrame);//当前帧和第一帧图像的差异
			threshold(AbsFrame, CurrentBinaryFrame, 30, 255, THRESH_BINARY | THRESH_OTSU);//二值化
			bitwise_and(PreviousBinaryFrame, CurrentBinaryFrame, Segmentation);//像素加和,获取分割结果

			medianBlur(Segmentation, Segmentation, 3);//中值滤波
			dilate(Segmentation, Segmentation, Kernel);//膨胀

			//获取边界
			vector<vector<Point>>contours;//边界
			vector<Vec4i>hierarchy;//层次

			//轮廓提取,参数分别为：输入图像,输出边界,层次,最外围轮廓,轮廓拐点信息,偏移量
			findContours(Segmentation, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

			//计算轮廓距
			vector<Moments> mu(contours.size());
			for (int i = 0; i < contours.size(); i++)
			{
				mu[i] = moments(contours[i], false);
			}

			//计算轮廓的质心     
			vector<Point2f> mc(contours.size());
			for (int i = 0; i < contours.size(); i++)
			{
				mc[i] = Point2d(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
			}

			//绘制质心和矩形框
			for (int i = 0; i< contours.size(); i++)
			{
				//绘制质心,参数为:要绘制图像,质心位置,圆半径,颜色为蓝色,填充,线型,圆心坐标和半径小数点位数
				circle(Frame, mc[i], 5, Scalar(255, 0, 0), -1, 8, 0);
				//绘制矩形,参数为:要绘制图像,绘制位置(外部矩形边界),颜色为绿色
				rectangle(Frame, boundingRect(contours.at(i)), cvScalar(0, 0, 255));
			}

			out.write(Frame);//写入每一帧

			imshow("video", Frame);
			imshow("segmentation", Segmentation);
			FirstGrayFrame = GrayFrame.clone();
			PreviousBinaryFrame = CurrentBinaryFrame.clone();
		}
		if ((char)waitKey(30) == 27)
			break;
	}
	video.release();

	clock_t end_time = clock();
	long times = (end_time - start_time) / CLOCKS_PER_SEC;
	cout << "程序段运行时间：" << times << "  秒" << endl;
	cout << "视频帧数为：" << totalFrameNumber << "  帧" << endl;
	cout << "处理速度为" << (double)(totalFrameNumber / times) << " 帧/秒" << endl;
	return 0;
}

