#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<photo/photo.hpp>
#include<iostream>
#include"ͼ���޲�����.h"
using  namespace cv;
using namespace std;
// ����һЩ������
#define WINDOW_NAME1 "��ԭͼ��"
#define WINDOW_NAME2 "���޲����Ч��ͼ��"
// ����ȫ�ֱ���
Mat srcimage11, inpaintmask;
Point previousPoint(-1, -1);	// ԭ���������
// ��Ӧ�����Ϣ�Ļص�����
static void on_mouse(int event, int x, int y, int flags, void*) {
	// ������������Ϣ
	if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
		previousPoint = Point(-1, -1);
	// ������������Ϣ
	else if (event == EVENT_LBUTTONDOWN)
		previousPoint = Point(x, y);
	// ��갴�²����ƶ������л���
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (previousPoint.x < 0)
			previousPoint = pt;
		// ��֪��ɫ����
		line(inpaintmask, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		line(srcimage11, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		previousPoint = pt;
		imshow(WINDOW_NAME1, srcimage11);
	}
}

// �ư��޸���������ں���
void inpaintlearning() {
	// ����ԭͼ��
	Mat srcimage = imread("D:\\test.jpg");
	srcimage11 = srcimage.clone();
	inpaintmask = Mat::zeros(srcimage11.size(), CV_8U);
	imshow(WINDOW_NAME1, srcimage);
	// �������ص���Ϣ
	setMouseCallback(WINDOW_NAME1, on_mouse, 0);
	// ��ѯ����
	while (1) {
		char c = (char)waitKey();
		if (c == 27)
			break;
		// ��2���ָ�ԭͼ��
		if (c == '2')
		{
			inpaintmask = Scalar::all(0);
			srcimage.copyTo(srcimage11);
			imshow(WINDOW_NAME1, srcimage);
		}
		// ������Ϊ�ո����1������ͼ���޸�
		if (c == '1' || c == ' ')
		{
			Mat inpaintedimage;
			inpaint(srcimage11, inpaintmask, inpaintedimage, 3, INPAINT_TELEA);
			imshow(WINDOW_NAME2, inpaintedimage);
		}
	}
}
