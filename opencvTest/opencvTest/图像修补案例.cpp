#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<photo/photo.hpp>
#include<iostream>
#include"图像修补案例.h"
using  namespace cv;
using namespace std;
// 定义一些辅助宏
#define WINDOW_NAME1 "【原图像】"
#define WINDOW_NAME2 "【修补后的效果图】"
// 定义全局变量
Mat srcimage11, inpaintmask;
Point previousPoint(-1, -1);	// 原来的坐标点
// 相应鼠标消息的回调函数
static void on_mouse(int event, int x, int y, int flags, void*) {
	// 鼠标左键弹起消息
	if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
		previousPoint = Point(-1, -1);
	// 鼠标左键按下消息
	else if (event == EVENT_LBUTTONDOWN)
		previousPoint = Point(x, y);
	// 鼠标按下并且移动，进行绘制
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (previousPoint.x < 0)
			previousPoint = pt;
		// 获知白色线条
		line(inpaintmask, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		line(srcimage11, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		previousPoint = pt;
		imshow(WINDOW_NAME1, srcimage11);
	}
}

// 推昂修复案例的入口函数
void inpaintlearning() {
	// 载入原图像
	Mat srcimage = imread("D:\\test.jpg");
	srcimage11 = srcimage.clone();
	inpaintmask = Mat::zeros(srcimage11.size(), CV_8U);
	imshow(WINDOW_NAME1, srcimage);
	// 设置鼠标回调消息
	setMouseCallback(WINDOW_NAME1, on_mouse, 0);
	// 轮询案件
	while (1) {
		char c = (char)waitKey();
		if (c == 27)
			break;
		// 当2，恢复原图像
		if (c == '2')
		{
			inpaintmask = Scalar::all(0);
			srcimage.copyTo(srcimage11);
			imshow(WINDOW_NAME1, srcimage);
		}
		// 当案件为空格或者1，进行图像修复
		if (c == '1' || c == ' ')
		{
			Mat inpaintedimage;
			inpaint(srcimage11, inpaintmask, inpaintedimage, 3, INPAINT_TELEA);
			imshow(WINDOW_NAME2, inpaintedimage);
		}
	}
}
