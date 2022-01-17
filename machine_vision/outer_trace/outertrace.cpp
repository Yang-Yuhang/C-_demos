#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

void traceBoundary(Mat src,Mat& dst,Mat& out)//dstΪ�ڱ߽�,outΪ��߽�;8-�ڽ�
{
	Point ptStart;  //��ʼ�߽��
	Point ptCur;    //��ǰ�߽��
	//������������{�ң����ϣ��ϣ����ϣ������£��£�����},��Ŵ�0~7
	int Direction[8][2] = { { 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 },{ -1,0 },{ -1, 1 },{ 0,1 },{ 1,1 } };
	int nCurDirect;//��ǰ̽�鷽��
	int dir=7;//��ʼ��
	bool bAtStartPt;//������ʼ

	int x, y;//x��Ӧ��,y��Ӧ�У�ԭ�������Ͻ�
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			if (src.at<uchar>(i, j)>0)//Ѱ�ҵ�һ�����ص�
			{
				//��ʼ���ص�����
				ptStart.x = j;
				ptStart.y = i;

				ptCur = ptStart;//��ʼ����ǰ����
				bAtStartPt = true;//������ʼ��ע�����ֿ�ʼ�ͽ���

				while ((ptCur.x != ptStart.x) || (ptCur.y != ptStart.y) || bAtStartPt==true)
				{
					bAtStartPt = false;

					//������ʼ̽��λ��
					if (dir % 2 == 1)//����
					{
						nCurDirect = (dir + 6) % 8;
					}
					else
					{
						nCurDirect = (dir + 7) % 8;
					}
					//��һ��̽�������
					//int nSearchTimes = 0;//��������
					x = ptCur.x + Direction[nCurDirect][0];
					y = ptCur.y + Direction[nCurDirect][1];
					//nSearchTimes = 1;
					for (int nSearchTimes = 1; nSearchTimes <= 8; nSearchTimes++)//תһȦ�ҳ����з����ص�
					{
						if (src.at<uchar>(y, x) == 0)
							//����߽�ͼ���ϱ����߽�
							out.at<uchar>(ptCur.y, ptCur.x) = 255;//ͼ��Ϊ��
						nCurDirect++;//��ʱ����ת45��
						if (nCurDirect >= 8)
							nCurDirect = nCurDirect - 8;
						x = ptCur.x + Direction[nCurDirect][0];
						y = ptCur.y + Direction[nCurDirect][1];
					}

					int Searchtime = 1;
					while (src.at<uchar>(y, x) == 0)//�����ص�
					{
						nCurDirect++;//��ʱ����ת45��
						if (nCurDirect >= 8)
							nCurDirect -= 8;
						x = ptCur.x + Direction[nCurDirect][0];
						y = ptCur.y + Direction[nCurDirect][1];
						//8�����ж�û�б߽�㣬˵���ǹ�����
						if (++Searchtime >= 8)
						{
							x = ptCur.x;
							y = ptCur.y;
							break;
						}
					}
					//�ҵ���һ���ڱ߽��
					ptCur.x = x;
					ptCur.y = y;
					//���ڱ߽�ͼ���ϱ�Ǳ߽�
					dst.at<uchar>(ptCur.y, ptCur.x) = 255;//ͼ��Ϊ��

					dir = nCurDirect;//����dir
				}
				return;
			}
		}
	}
}

int main()
{
	Mat src = imread("C:/Users/dell/Desktop/plane.jpg");//��ȡ�Ҷ�ͼ
	imshow("����ͼ��", src);

	Mat a;//�Ҷ�ͼ
	cvtColor(src, a, CV_BGR2GRAY);
	imshow("ת��Ϊ�Ҷ�ͼ", a);

	Mat src_binary;//��ֵͼ
				   
	threshold(src, src_binary, 220, 255, THRESH_BINARY);//��ֵ��
	imshow("��ֵͼ��", src_binary);

	Mat InnerBoundaryImg = Mat::zeros(src_binary.size(), src_binary.type());//�ڱ߽�ͼ��
	Mat OuterBoundaryImg = Mat::zeros(src_binary.size(), src_binary.type());//��߽�ͼ��
	traceBoundary(src_binary,InnerBoundaryImg,OuterBoundaryImg);

	imshow("�ڱ߽�ͼ��", InnerBoundaryImg);
	imshow("��߽�ͼ��", OuterBoundaryImg);

	waitKey(0);
	return 0;

}
