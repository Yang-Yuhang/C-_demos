//ͨ��֡�ȷ����̬Ŀ�겢�궨
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

	VideoCapture video("D:/�μ�/�����Ӿ�����/�μ�/��ҵ2019/��ҵ2019/������Ƶ.mp4");
	if (!video.isOpened())
		return -1;//��Ƶ��ʧ��

	int totalFrameNumber = video.get(CV_CAP_PROP_FRAME_COUNT);//��ȡ��Ƶ����֡��
	double rate = video.get(CV_CAP_PROP_FPS);//��ȡ��Ƶ֡��
	Size size = Size(video.get(CV_CAP_PROP_FRAME_WIDTH), video.get(CV_CAP_PROP_FRAME_HEIGHT));//ÿ֡��С
	

	VideoWriter out;
	out.open("D:/�μ�/�����Ӿ�����/�μ�/��ҵ2019/��ҵ2019/���.avi", CV_FOURCC('M', 'J', 'P', 'G'), rate, size, true);
	if (!out.isOpened()) 
	{
		return -1;//��Ƶдʧ��
	}

	Mat Frame;
	Mat GrayFrame;//�Ҷ�ͼ
	Mat FirstGrayFrame;//ǰ��֡�Ҷ�ͼ
	Mat SecondGrayFrame;//��һ֡�Ҷ�ͼ
	
	Mat AbsFrame;//֡���õĲ���ͼ��
	Mat PreviousBinaryFrame;//ǰ��֡����Ķ�ֵͼ
	Mat CurrentBinaryFrame;//��ǰ֡�͵�һ֡����Ķ�ֵͼ
	Mat Segmentation;//�ָ���

	//������̬�仯�ĽṹԪ�أ������ֱ�Ϊ�����Σ��ں˳ߴ磬���λ�����ĵ�
	Mat Kernel = getStructuringElement(MORPH_RECT, Size(43, 45), Point(-1, -1));
	
	//˫��ֵ��ǿͼ��Աȶ�
	int low = 129;//����ֵ
	int high = 159;//����ֵ
	double k = 255 / (high - low);//�м�Աȶ�
	
	//�����ɵ��ڴ�С����Ƶ���Ŵ���
	namedWindow("video", 0);
	namedWindow("segmentation", 0);

	for (int i = 0; i < totalFrameNumber;i++)
	{
		video >> Frame;//������Ƶ֡
		if (!Frame.data)
			break;

		cvtColor(Frame, GrayFrame, COLOR_BGR2GRAY);//ת��Ϊ�Ҷ�ͼ
		GaussianBlur(GrayFrame, GrayFrame, Size(3, 3), 0, 0);//��˹�˲�
		//��˫��ֵ��ǿͼ��Աȶ�
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

		if (i == 0)//Ϊ��һ֡ͼƬ
		{
			FirstGrayFrame = GrayFrame;
			imshow("video", Frame);
			continue;
		}
		else if (i == 1)//Ϊ�ڶ�֡ͼƬ
		{
			SecondGrayFrame = GrayFrame;

			//֡�����ȡ֡����,����Ϊ:����ڶ�֡ͼ��,�����һ֡ͼ��,�������ͼ��
			absdiff(SecondGrayFrame, FirstGrayFrame, AbsFrame);

			//��ֵ���������ֱ�Ϊ:�������ͼ��,OTSU��ֵ,��ֵ���ֵ,��ֵ��
			threshold(AbsFrame, PreviousBinaryFrame, 10, 255, THRESH_BINARY | THRESH_OTSU);
			
			imshow("video", Frame);
			continue;
		}
		else//Ϊ����֡ͼƬ
		{
			absdiff(GrayFrame, FirstGrayFrame, AbsFrame);//��ǰ֡�͵�һ֡ͼ��Ĳ���
			threshold(AbsFrame, CurrentBinaryFrame, 30, 255, THRESH_BINARY | THRESH_OTSU);//��ֵ��
			bitwise_and(PreviousBinaryFrame, CurrentBinaryFrame, Segmentation);//���ؼӺ�,��ȡ�ָ���

			medianBlur(Segmentation, Segmentation, 3);//��ֵ�˲�
			dilate(Segmentation, Segmentation, Kernel);//����

			//��ȡ�߽�
			vector<vector<Point>>contours;//�߽�
			vector<Vec4i>hierarchy;//���

			//������ȡ,�����ֱ�Ϊ������ͼ��,����߽�,���,����Χ����,�����յ���Ϣ,ƫ����
			findContours(Segmentation, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

			//����������
			vector<Moments> mu(contours.size());
			for (int i = 0; i < contours.size(); i++)
			{
				mu[i] = moments(contours[i], false);
			}

			//��������������     
			vector<Point2f> mc(contours.size());
			for (int i = 0; i < contours.size(); i++)
			{
				mc[i] = Point2d(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
			}

			//�������ĺ;��ο�
			for (int i = 0; i< contours.size(); i++)
			{
				//��������,����Ϊ:Ҫ����ͼ��,����λ��,Բ�뾶,��ɫΪ��ɫ,���,����,Բ������Ͱ뾶С����λ��
				circle(Frame, mc[i], 5, Scalar(255, 0, 0), -1, 8, 0);
				//���ƾ���,����Ϊ:Ҫ����ͼ��,����λ��(�ⲿ���α߽�),��ɫΪ��ɫ
				rectangle(Frame, boundingRect(contours.at(i)), cvScalar(0, 0, 255));
			}

			out.write(Frame);//д��ÿһ֡

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
	cout << "���������ʱ�䣺" << times << "  ��" << endl;
	cout << "��Ƶ֡��Ϊ��" << totalFrameNumber << "  ֡" << endl;
	cout << "�����ٶ�Ϊ" << (double)(totalFrameNumber / times) << " ֡/��" << endl;
	return 0;
}

