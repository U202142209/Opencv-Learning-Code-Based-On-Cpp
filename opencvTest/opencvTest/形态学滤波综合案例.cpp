#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

// 定义全局变量部分
Mat g_srcimage, g_dstimage;				// 原始图和效果如
int g_nElementShape = MORPH_RECT;		// 结构元素的形状

// 变量接收的Trackbar位置参数
int g_nMaxIterationNum = 10;
int g_nOpenCloseNum = 9;
int g_nErodeDilateNum = 9;
int g_nTopBlackNum = 2;

// 全局函数生命部分
static void on_OpenClose(int, void*);		// 回调函数
static void on_ErodeDilate(int, void*);		// 回调函数
static void on_TopBlackHat(int, void*);		// 回调函数
// static void ShowHelpText(int, void*);		// 帮助文本显示

int xingtaixueblur() {
	// 载入原图像
	g_srcimage = imread("D:\\test.jpg");
	namedWindow("【原始图】");
	imshow("【原始图】", g_srcimage);
	
	// 创建三个窗口
	namedWindow("【开运算/闭运算】",1);
	namedWindow("【腐蚀/膨胀】",1);
	namedWindow("【顶帽/黑帽】",1);

	// 分别为三个窗口创建滚动条
	createTrackbar("选代值", "【开运算/闭运算】", &g_nOpenCloseNum, g_nMaxIterationNum * 2 + 1, on_OpenClose);
	createTrackbar("选代值", "【腐蚀/膨胀】", &g_nErodeDilateNum, g_nMaxIterationNum * 2 + 1, on_ErodeDilate);
	createTrackbar("选代值", "【顶帽/黑帽】", &g_nTopBlackNum, g_nMaxIterationNum * 2 + 1, on_TopBlackHat);

	// 轮询获取键盘信息
	while (1) {
		int c;
		// 执行回调函数
		on_OpenClose(g_nOpenCloseNum, 0);
		on_ErodeDilate(g_nErodeDilateNum, 0);
		on_TopBlackHat(g_nTopBlackNum, 0);

		// 获取案件
		c = waitKey(0);
		if ((char)c == 'q' || (char)c == 27)
			break;
		// 按下键盘1，使用椭圆结构元素
		if ((char)c == 49)
			g_nElementShape = MORPH_ELLIPSE;
		// 按下键盘2，使用矩形结构元素
		if ((char)c == 50)
			g_nElementShape = MORPH_RECT;
		// 按下键盘3，使用十字形结构元素
		else if ((char)c == 51)
			g_nElementShape = MORPH_CROSS;
		// 当按下键盘空格键，在矩形，椭圆，十字中循环
		else if ((char)c == ' ')
			g_nElementShape = (g_nElementShape + 1) % 3;
	}
	return 0;
}

static void on_OpenClose(int, void*) {
	// 偏移量的控制
	int offset = g_nOpenCloseNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;	// 偏移量的绝对值
	// 自定义核
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1), Point(Absolute_offset, Absolute_offset));
		// 进行操作
		if (offset < 0) {
			morphologyEx(g_srcimage, g_dstimage, MORPH_OPEN, element);
		}
		else {
			morphologyEx(g_srcimage, g_dstimage, MORPH_CLOSE, element);
		}
	// 显示图像
	imshow("【开运算/闭运算】", g_dstimage);
}

static void on_ErodeDilate(int, void*) {
	// 偏移量的控制
	int offset = g_nErodeDilateNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;	// 偏移量的绝对值
	// 自定义核
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1), Point(Absolute_offset, Absolute_offset));
		// 进行操作
		if (offset < 0) {
			morphologyEx(g_srcimage, g_dstimage, MORPH_ERODE, element);
		}
		else {
			morphologyEx(g_srcimage, g_dstimage, MORPH_DILATE, element);
		}
	// 显示图像
	imshow("【腐蚀/膨胀】", g_dstimage);
}

static void on_TopBlackHat(int, void*) {
	// 偏移量的控制
	int offset = g_nTopBlackNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;	// 偏移量的绝对值
	// 自定义核
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1), Point(Absolute_offset, Absolute_offset));
		// 进行操作
		if (offset < 0) {
			morphologyEx(g_srcimage, g_dstimage, MORPH_TOPHAT, element);
		}
		else {
			morphologyEx(g_srcimage, g_dstimage, MORPH_BLACKHAT, element);
		}
	// 显示图像
	imshow("【顶帽/黑帽】", g_dstimage);
}