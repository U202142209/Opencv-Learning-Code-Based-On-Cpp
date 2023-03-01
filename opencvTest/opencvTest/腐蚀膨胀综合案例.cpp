#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
using namespace std;
using namespace cv;

#include"ErodeDilateExercise.h"

// ��ʴ�������ۺϰ���

Mat g_srcinage, g_DSTIMAGE;			// ԭͼ���Ч��ͼ
int g_ntrackbarnumber = 0;			// 0��ʾ��ʴerode,1��ʾ����dilate
int g_nStructelementSize = 3;		// ����Ԫ�أ��ں˾���ĳߴ�

// ����ȫ�ֺ���
void Process();
void on_TrackBarNumberChange(int, void*);
void on_ElementSizeChange(int, void*);

int exercisemain() {
	system("color5E");					// �ı�������ɫ
	// ����ԭͼ��
	g_srcinage = imread("D:\\test.jpg");
	namedWindow("��ԭͼ��");
	imshow("��ԭͼ��", g_srcinage);
	// ���г��θ�ʴ��������ʾЧ��ͼ
	namedWindow("��Ч��ͼ��");
	// ��ȡ�Զ����
	Mat element = getStructuringElement(
		MORPH_RECT,
		Size(2 * g_nStructelementSize + 1, 2 * g_nStructelementSize + 1),
		Point(g_nStructelementSize, g_nStructelementSize
		));
	erode(g_srcinage, g_DSTIMAGE, element);
	imshow("��Ч��ͼ��", g_DSTIMAGE);

	// �����켣��
	createTrackbar(
		"��ʴ/����", "��Ч��ͼ��", &g_ntrackbarnumber, 1, on_TrackBarNumberChange
	);
	createTrackbar(
		"�ں˳ߴ�", "��Ч��ͼ��", &g_nStructelementSize, 21, on_ElementSizeChange
	);
	while (char(waitKey(1)) != 'q') {}
	waitKey(0);
	return 0;
}


void Process() {
	Mat element = getStructuringElement(
		MORPH_RECT,
		Size(2 * g_nStructelementSize + 1, 2 * g_nStructelementSize + 1),
		Point(g_nStructelementSize, g_nStructelementSize)
	);
	if (g_ntrackbarnumber == 0) {
		erode(g_srcinage, g_DSTIMAGE, element);
	}
	else {
		dilate(g_srcinage, g_DSTIMAGE, element);
	}
	imshow("��Ч��ͼ��", g_DSTIMAGE);
}									// ���ͺ͸�ʴ�Ĵ�����
void on_TrackBarNumberChange(int, void*) {
	Process();
}									// // �ص�����
void on_ElementSizeChange(int, void*) {
	Process();
}
// ������
