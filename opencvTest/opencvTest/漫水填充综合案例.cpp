#include"漫水填充综合案例.h"
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace cv;
using namespace std;

// 定义全局变量
Mat srcimage, dstimage, grayimage, maskimage;
int FillMode = 1;						// 漫水填充的模式
int LowDifference = 20, UpDifference = 20;	// 负差最大值，正差最大值
int Connectivity = 4;		// 表示floodFill函数标识符低八位的通道数
int TsColor = true;			// 是否为彩色图的标识符
int UseMask = false;		// 是否使用掩膜窗口
int NewMaskVal = 255;		// 重新绘制的像素值

// 鼠标消息的回调函数
static void onMouse(int event,int x,int y,int,void*) {
	if (event != EVENT_LBUTTONDOWN)
		return;
	// 调用函数前的参数准备
	Point seed = Point(x, y);
	int LOWDIFFERENCE = FillMode == 0 ? 0 : LowDifference;
	int UPDIFFERENCE = FillMode == 0 ? 0 : UpDifference;
	int flag = Connectivity + (NewMaskVal << 8) + (FillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);

	// 随机生成bgr值
	int b = (unsigned)theRNG & 255;		// 产生随机数
	int g=  (unsigned)theRNG & 255;
	int r=  (unsigned)theRNG & 255;
	Rect comp;
	Scalar newVal = 0;

}


