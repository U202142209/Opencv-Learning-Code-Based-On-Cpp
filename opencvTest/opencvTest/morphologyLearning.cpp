// "this is the morphologyEX comprenhensive exercise "

#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
using namespace std;
using namespace cv;


#include"MorphologyLearning.h"
int morphologyLearning() {
	cout << "this is the morphologyEX comprenhensive exercise " << endl;
	Mat srcimage = imread("D:\\test.jpg");

	namedWindow("��ԭʼͼ��");
	namedWindow("��Ч��ͼ��");
	imshow("��ԭʼͼ��", srcimage);
	// �����
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	// ������̬ѧ����

	// ��ʴ
	// morphologyEx(srcimage, srcimage, MORPH_ERODE, element);
	// ����
	// morphologyEx(srcimage, srcimage, MORPH_DILATE, element);
	// ��̬ѧ�ݶ�
	// morphologyEx(srcimage, srcimage, MORPH_GRADIENT, element);
	// ������
	// morphologyEx(srcimage, srcimage, MORPH_OPEN, element);
	// ������
	// morphologyEx(srcimage, srcimage, MORPH_CLOSE, element);
	// ��ñ
	// morphologyEx(srcimage, srcimage, MORPH_TOPHAT, element);
	// ��ñ
	morphologyEx(srcimage, srcimage, MORPH_BLACKHAT, element);
	imshow("��Ч��ͼ��", srcimage);

	waitKey(0); 
	return 0;
}