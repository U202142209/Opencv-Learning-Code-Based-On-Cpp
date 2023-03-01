#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include<iostream>
#include <string>
#include<vector>
#include <stdlib.h>

// 导入自定义头文件
#include"ErodeDilateExercise.h"
#include"MorphologyLearning.h"
#include"形态学滤波综合案例.h"
#include"图像修补案例.h"
#define WINDOW_WIDTG 600

using namespace cv;
using namespace std;

// 第一个案例，显示图像
void showImage() {
	Mat srcimage = imread("D:\\test.jpg");
	imshow("【原图像】", srcimage);
	waitKey(0);
}
// 第二个案例，图像腐蚀
void imagefushi() {
	Mat srcimage = imread("D:\\test.jpg");
	imshow("【腐蚀前的图像】", srcimage);
	// 进行腐蚀操作
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat dstimg;
	erode(srcimage, dstimg, element);
	imshow("【腐蚀后的图像】", dstimg);
	waitKey(0);
}
// 第三个案例，图像滤波，模糊处理
void lvbo() {
	Mat srcimage = imread("D:\\test.jpg");
	imshow("原图像", srcimage);
	Mat dstimg;
	blur(srcimage, dstimg, Size(7, 7));
	imshow("处理后的图像", dstimg);
	waitKey(0);
}
// 第四个案例，canny边缘检测
void cannytest() {
	Mat srcimage = imread("D:\\test.jpg");
	imshow("原图像", srcimage);
	Mat dstimg, edge, grayimage;
	dstimg.create(srcimage.size(), srcimage.type());
	cvtColor(srcimage, grayimage, COLOR_BGR2GRAY);
	blur(grayimage, edge, Size(3, 3));
	Canny(edge, edge, 3, 9, 3);
	imshow("处理后的图像", edge);
	waitKey(0);
}
// 读取摄像头的图像
void shexiangtou() {
	VideoCapture capture(0);
	while (1) {
		Mat frame;
		capture >> frame;
		imshow("读取到的图像；", frame);
		waitKey(30);
	}
}
// 读取摄像头的图像，并使用canny边缘检测，滤波进行处理
void sxtbc() {
	VideoCapture capture(0);
	Mat edges;
	while (1) {
		Mat frame;
		capture >> frame;
		cvtColor(frame, edges, COLOR_BGR2GRAY);
		blur(edges, edges, Size(7, 7));
		Canny(edges, edges, 0, 30, 3);
		imshow("处理后的视频；", edges);
		waitKey(30);
	}
}
// 创建含有Alpha通道的mat图像
void createAlphaMat(Mat& mat) {
	for (int i = 0; i < mat.rows; i++) {
		for (int j = 0; j < mat.cols; j++) {
			Vec4b& rgba = mat.at<Vec4b>(i, j);
			rgba[0] = UCHAR_MAX;
			rgba[1] = saturate_cast<uchar>((float(mat.cols - j)) / ((float)mat.cols) * UCHAR_MAX);
			rgba[2] = saturate_cast<uchar>((float(mat.rows - i)) / ((float)mat.rows) * UCHAR_MAX);
			rgba[3] = saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
		}
	}
}
// 第三章imwrite函数的学习
void imwriteLearning() {
	Mat mat(480, 640, CV_8UC4);
	createAlphaMat(mat);
	vector<int>compression_params;
	compression_params.push_back(IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);
	try {
		imwrite("透明Alpha值图.png", mat, compression_params);
		imshow("生产的Alpha图", mat);
		waitKey(0);
	}
	catch (runtime_error& ex) {
		cout << "\n\n\n发生了错误\n\n\n" << endl;
	}
}
void cvtcolorlearning() {
	Mat srcimage = imread("D:\\test.jpg"), dstimg;
	imshow("【原图像】", srcimage);
	cvtColor(srcimage, dstimg, COLOR_BGR2GRAY);
	imshow("【效果图】", dstimg);
	waitKey(0);
}
// 输出图像的基本信息
void showdetails(Mat img, string name) {
	cout << "\n图像的基本信息如下：" << endl <<
		"图像名称:" << name << endl <<
		"图像的cols:" << img.cols << endl <<
		"图像的rows:" << img.rows << endl <<
		"图像的channels:" << img.channels() << endl;

}
// 产生随机图像
void createMat() {
	int a = 0, b = 255;
	while (1) {
		int bb = (rand() % (b - a + 1)) + a;
		int gg = (rand() % (b - a + 1)) + a;
		int rr = (rand() % (b - a + 1)) + a;
		Mat rawImg(800, 1600, CV_8UC3, Scalar(bb, gg, rr));
		imshow("随机图像", rawImg);
		waitKey(0);
	}
}
void Addmask(Mat& srcimg, Mat mask, int x, int y) {
	if (srcimg.cols < x + mask.cols) {
		cout << "图像水平方向溢出" << endl;
		return;
	}
	if (srcimg.rows < y + mask.rows) {
		cout << "图像垂直方向溢出" << endl;
		return;
	}
	if (srcimg.channels() != mask.channels()) {
		cout << "图像通道数不同" << endl;
		return;
	}
	// 输出图像的而基本信息
	showdetails(srcimg, "srcimg");
	showdetails(mask, "mask");
	for (int i = 0; i < mask.rows; i++) {
		for (int j = 0; j < mask.cols; j++) {
			srcimg.at<Vec3b>(x + i, y + j)[0] = mask.at<Vec3b>(i, j)[0];
			srcimg.at<Vec3b>(x + i, y + j)[1] = mask.at<Vec3b>(i, j)[0];
			srcimg.at<Vec3b>(x + i, y + j)[2] = mask.at<Vec3b>(i, j)[0];
		}
	}
}
void TsetAddMask() {
	Mat srcimg = imread("D:\\test.jpg");
	Mat mask = imread("D:\\mask.jpg");
	imshow("原图像", srcimg);
	Addmask(srcimg, mask, 100, 50);
	imshow("处理后的图像", srcimg);
	waitKey(0);
}
void blurlearning() {
	Mat srcimage = imread("D:\\test.jpg");
	imshow("【原图像】", srcimage);
	Mat out;
	// 方框滤波
	boxFilter(srcimage, out, -1, Size(7, 7));
	// 均值滤波
	blur(srcimage, out, Size(7, 7));
	// 高斯滤波
	GaussianBlur(srcimage, out, Size(5, 5), 0, 0);
	// 中值滤波
	medianBlur(srcimage, out, 7);
	// 双边滤波
	bilateralFilter(srcimage, out, 25, 25 * 2, 25 / 2);
	imshow("滤波后的图像效果", out);
	waitKey(0);
}
// 膨胀操作学习，对白色的区域进行膨胀
void dilatelearning() {
	// 载入原图像
	Mat srcimage = imread("D:\\test.jpg");
	// 获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat out;
	dilate(srcimage, out, element);
	imshow("【原图像】", srcimage);
	imshow("【膨胀的效果如】", out);
	waitKey(0);
}

// 腐蚀学习，对白色的区域进行腐蚀
void erodelearning() {
	// 载入原图像
	Mat srcimage = imread("D:\\test.jpg");
	// 获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat out;
	erode(srcimage, out, element);
	imshow("【原图像】", srcimage);
	imshow("【腐蚀的效果如】", out);
	waitKey(0);
}
// 图像金子谈函数相关api
void pyrUplearning() {
	// 载入原图像
	Mat srcimage = imread("D:\\test.jpg");
	// 临时变量
	Mat tempimage, dstimage;
	tempimage = srcimage;
	imshow("【原图像】", srcimage);
	// 进行向上取样操作
	// 将图像的尺寸放大两倍
	// pyrUp(tempimage, dstimage, Size(tempimage.cols * 2, tempimage.rows * 2));
	pyrDown(tempimage, dstimage, Size(tempimage.cols / 2, tempimage.rows / 2));
	imshow("效果图", dstimage);
	waitKey(0);

}

// 数值分析作业编程
void numerical_analysis_compute() {

}
// 测试
void test0001() {
	Mat srcimage = imread("D:\\test.jpg");
	imshow("【原图像】", srcimage);
	cvtColor(srcimage, srcimage, COLOR_RGB2GRAY);
	imshow("【效果图】", srcimage);
	waitKey(0);
}
// 寻找轮廓
void findContourslearning() {
	Mat srcimage = imread("D:\\test.jpg");
	imshow("【原图像】", srcimage);
	Mat dstimage = Mat::zeros(srcimage.rows, srcimage.cols, CV_8UC3);
	// srcimage = srcimage > 119;

	// 定义轮廓和结构层次
	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;
	// 查找轮廓


	imshow("【效果图】", srcimage);
	waitKey(0);
}

// 船舰包围轮廓的矩形边界
// 使用矩形包围随机点
void boundarylearning() {
	//初始化变量和随机值
	Mat image(600, 600, CV_8UC3);
	RNG rng = theRNG();
	// 循环
	while (1) {
		// 参数初始化
		int count = rng.uniform(13, 103);	//随机生成点的数量
		vector<Point>points;
		// 随机生成点的坐标
		for (int i = 0; i < count; i++) {
			Point point;
			point.x = rng.uniform(image.cols / 5, image.cols * 4 / 5);
			point.y = rng.uniform(image.rows / 5, image.rows * 4 / 5);
			points.push_back(point);
		}
		// 对于给定的2d点集，寻找最小面积包围图形
		RotatedRect box = minAreaRect(Mat(points));
		Point2f vertex[4];
		box.points(vertex);

		// 绘制出随机颜色的点
		image = Scalar::all(0);
		for (int i = 0; i < count; i++) {
			circle(image, points[i], 5,Scalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255)),FILLED,LINE_AA);
		}

		// 绘制出最小面积的包围图像
		for (int i = 0; i < 4; i++) {
			line(image, vertex[i], vertex[(i + 1) % 4], Scalar(100, 200, 211), 2, LINE_AA);
		}

		// 显示窗口
		imshow("矩形包围示例", image);

		char key = (char)waitKey();
		if (key == 'q' || key == 'Q')
			break;
	}
}

// 使用原型包围随机点
void UseCircleBoundRandDots() {
	//初始化变量和随机值
	Mat image(600, 600, CV_8UC3);
	RNG rng = theRNG();
	// 循环
	while (1) {
		// 参数初始化
		int count = rng.uniform(53, 153);	//随机生成点的数量
		vector<Point>points;
		// 随机生成点的坐标
		for (int i = 0; i < count; i++) {
			Point point;
			point.x = rng.uniform(image.cols / 5, image.cols * 4 / 5);
			point.y = rng.uniform(image.rows / 5, image.rows * 4 / 5);
			points.push_back(point);
		}

		// 对于给定的2d点集，寻找最小面积包围图形
		Point2f center;
		float radius = 0;
		minEnclosingCircle(Mat(points), center, radius);

		// 绘制出随机颜色的点
		image = Scalar::all(0);
		for (int i = 0; i < count; i++) {
			circle(image, points[i], 5, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);
		}

		// 绘制出最小面积的包围图像
		circle(image, center, cvRound(radius), Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2, LINE_AA);

		// 对于给定的2d点集，寻找最小面积包围图形
		RotatedRect box = minAreaRect(Mat(points));
		Point2f vertex[4];
		box.points(vertex);

		// 绘制出最小面积的包围图像
		for (int i = 0; i < 4; i++) {
			line(image, vertex[i], vertex[(i + 1) % 4], Scalar(100, 200, 211), 2, LINE_AA);
		}



		// 显示窗口
		imshow("矩形包围示例", image);

		char key = (char)waitKey();
		if (key == 'q' || key == 'Q')
			break;
	}
}

// 数据结构作业
void homework() {
	int n = 100, p = 100,m=100;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			++p;
		}
	}
	int i = 1;
	while (1 <= n) {
		i *= 3;
	}
}

// 分水岭算法学习
void watershedlearning() {

}

// 主函数
int main() {
	/*showImage();*/
	/*imagefushi();*/
	/*lvbo();*/
	/*cannytest();*/
	/*shexiangtou();*/
	// sxtbc();					// 读取摄像头的图像，并使用canny边缘检测，滤波进行处理
	// imwriteLearning();
	// Point2f p(6, 2);
	// cvtcolorlearning();
	// createMat();
	// TsetAddMask();
	// blurlearning();
	// dilatelearning();
	// erodelearning();
	// exercisemain();
	// morphologyLearning();
	// xingtaixueblur();				// 形态学滤波综合案例
	// pyrUplearning();
	// test0001();
	// findContourslearning();
	// boundarylearning();
	// UseCircleBoundRandDots();		// 使用原型包围随机点
	inpaintlearning();
	cout << "\n\n\n当前opencv的版本；" << CV_VERSION << "n\n\n" << endl;
	return 0;
}

