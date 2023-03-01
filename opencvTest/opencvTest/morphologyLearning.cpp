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

	namedWindow("【原始图】");
	namedWindow("【效果图】");
	imshow("【原始图】", srcimage);
	// 定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	// 进行形态学操作

	// 腐蚀
	// morphologyEx(srcimage, srcimage, MORPH_ERODE, element);
	// 膨胀
	// morphologyEx(srcimage, srcimage, MORPH_DILATE, element);
	// 形态学梯度
	// morphologyEx(srcimage, srcimage, MORPH_GRADIENT, element);
	// 开运算
	// morphologyEx(srcimage, srcimage, MORPH_OPEN, element);
	// 闭运算
	// morphologyEx(srcimage, srcimage, MORPH_CLOSE, element);
	// 顶帽
	// morphologyEx(srcimage, srcimage, MORPH_TOPHAT, element);
	// 黑帽
	morphologyEx(srcimage, srcimage, MORPH_BLACKHAT, element);
	imshow("【效果图】", srcimage);

	waitKey(0); 
	return 0;
}