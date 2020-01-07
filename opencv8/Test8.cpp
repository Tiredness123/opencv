#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<opencv2/imgproc/imgproc.hpp>  
#include<vector>
#include<iostream>  
#include<string>
#include<math.h>

using namespace std;
using namespace cv;

//bgrͼ��  
Mat bgr;

//HSVͼ��  
Mat hsv;

//ɫ��  
int hmin = 0;//h����ȡ����
int hmax = 180;//h����ȡ����
int h_Max = 180; //h������ȡ�����ֵ

//���Ͷ�  
int smin = 0;//s����ȡ����
int smax = 255;//s����ȡ����
int s_Max = 255;//s������ȡ�����ֵ

//����  
int vmin = 0;//v����ȡ����
int vmax = 255;//v����ȡ����
int v_Max = 255;//v������ȡ�����ֵ

string windowName = "src";

string dstName = "dst";

//���ͼ��  
Mat dst;

//�ص�����  
void callBack(int, void*)
{
	//���ͼ������ڴ�  
	dst = Mat::zeros(bgr.size(), bgr.type());
	 
	Mat mask;
	inRange(hsv, Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax), mask);
	 
	for (int r = 0; r < bgr.rows; r++)
	{
		for (int c = 0; c < bgr.cols; c++)
		{
			if (mask.at<uchar>(r, c) == 255)
			{
				dst.at<Vec3b>(r, c)[0] = bgr.at<Vec3b>(r, c)[0];
				dst.at<Vec3b>(r, c)[1] = bgr.at<Vec3b>(r, c)[1];
				dst.at<Vec3b>(r, c)[2] = bgr.at<Vec3b>(r, c)[2];
			}
		}
	}
	imshow("mask", mask);

	//���ͼƬ
	imshow("dst", dst);
}
int main()
{
	//����ͼƬ 
	Mat srcImage = imread("C:\\Users\\Administrator\\Desktop\\002.jpg");
	if (!srcImage.data){
		cout << "ͼƬ��ȡʧ��" << endl;
		system("pause");
		return -1;
	}
	imshow(windowName, srcImage);
	bgr = srcImage;

	//��ɫ�ռ�ת��  
	cvtColor(bgr, hsv, COLOR_BGR2HSV);

	//�������ͼ�����ʾ����  
	namedWindow(dstName, WINDOW_AUTOSIZE);

	//����ɫ�� H  
	createTrackbar("hmin", dstName, &hmin, h_Max, callBack);
	createTrackbar("hmax", dstName, &hmax, h_Max, callBack);

	//���ڱ��Ͷ� S  
	createTrackbar("smin", dstName, &smin, s_Max, callBack);
	createTrackbar("smax", dstName, &smax, s_Max, callBack);

	//�������� V  
	createTrackbar("vmin", dstName, &vmin, v_Max, callBack);
	createTrackbar("vmax", dstName, &vmax, v_Max, callBack);
	callBack(0, 0);
	waitKey(0);
	return 0;
}
