#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
using namespace std;
using namespace cv;

#include"ErodeDilateExercise.h"

// 腐蚀与膨胀综合案例

Mat g_srcinage, g_DSTIMAGE;			// 原图像和效果图
int g_ntrackbarnumber = 0;			// 0表示腐蚀erode,1表示膨胀dilate
int g_nStructelementSize = 3;		// 构造元素，内核矩阵的尺寸

// 定义全局函数
void Process();
void on_TrackBarNumberChange(int, void*);
void on_ElementSizeChange(int, void*);

int exercisemain() {
	system("color5E");					// 改变字体颜色
	// 载入原图像
	g_srcinage = imread("D:\\test.jpg");
	namedWindow("【原图像】");
	imshow("【原图像】", g_srcinage);
	// 进行初次腐蚀操作并显示效果图
	namedWindow("【效果图】");
	// 获取自定义核
	Mat element = getStructuringElement(
		MORPH_RECT,
		Size(2 * g_nStructelementSize + 1, 2 * g_nStructelementSize + 1),
		Point(g_nStructelementSize, g_nStructelementSize
		));
	erode(g_srcinage, g_DSTIMAGE, element);
	imshow("【效果图】", g_DSTIMAGE);

	// 创建轨迹条
	createTrackbar(
		"腐蚀/膨胀", "【效果图】", &g_ntrackbarnumber, 1, on_TrackBarNumberChange
	);
	createTrackbar(
		"内核尺寸", "【效果图】", &g_nStructelementSize, 21, on_ElementSizeChange
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
	imshow("【效果图】", g_DSTIMAGE);
}									// 膨胀和腐蚀的处理函数
void on_TrackBarNumberChange(int, void*) {
	Process();
}									// // 回调函数
void on_ElementSizeChange(int, void*) {
	Process();
}
// 主函数
