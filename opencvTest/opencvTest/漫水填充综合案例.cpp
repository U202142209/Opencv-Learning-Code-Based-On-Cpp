#include"��ˮ����ۺϰ���.h"
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace cv;
using namespace std;

// ����ȫ�ֱ���
Mat srcimage, dstimage, grayimage, maskimage;
int FillMode = 1;						// ��ˮ����ģʽ
int LowDifference = 20, UpDifference = 20;	// �������ֵ���������ֵ
int Connectivity = 4;		// ��ʾfloodFill������ʶ���Ͱ�λ��ͨ����
int TsColor = true;			// �Ƿ�Ϊ��ɫͼ�ı�ʶ��
int UseMask = false;		// �Ƿ�ʹ����Ĥ����
int NewMaskVal = 255;		// ���»��Ƶ�����ֵ

// �����Ϣ�Ļص�����
static void onMouse(int event,int x,int y,int,void*) {
	if (event != EVENT_LBUTTONDOWN)
		return;
	// ���ú���ǰ�Ĳ���׼��
	Point seed = Point(x, y);
	int LOWDIFFERENCE = FillMode == 0 ? 0 : LowDifference;
	int UPDIFFERENCE = FillMode == 0 ? 0 : UpDifference;
	int flag = Connectivity + (NewMaskVal << 8) + (FillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);

	// �������bgrֵ
	int b = (unsigned)theRNG & 255;		// ���������
	int g=  (unsigned)theRNG & 255;
	int r=  (unsigned)theRNG & 255;
	Rect comp;
	Scalar newVal = 0;

}


