#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

// ����ȫ�ֱ�������
Mat g_srcimage, g_dstimage;				// ԭʼͼ��Ч����
int g_nElementShape = MORPH_RECT;		// �ṹԪ�ص���״

// �������յ�Trackbarλ�ò���
int g_nMaxIterationNum = 10;
int g_nOpenCloseNum = 9;
int g_nErodeDilateNum = 9;
int g_nTopBlackNum = 2;

// ȫ�ֺ�����������
static void on_OpenClose(int, void*);		// �ص�����
static void on_ErodeDilate(int, void*);		// �ص�����
static void on_TopBlackHat(int, void*);		// �ص�����
// static void ShowHelpText(int, void*);		// �����ı���ʾ

int xingtaixueblur() {
	// ����ԭͼ��
	g_srcimage = imread("D:\\test.jpg");
	namedWindow("��ԭʼͼ��");
	imshow("��ԭʼͼ��", g_srcimage);
	
	// ������������
	namedWindow("��������/�����㡿",1);
	namedWindow("����ʴ/���͡�",1);
	namedWindow("����ñ/��ñ��",1);

	// �ֱ�Ϊ�������ڴ���������
	createTrackbar("ѡ��ֵ", "��������/�����㡿", &g_nOpenCloseNum, g_nMaxIterationNum * 2 + 1, on_OpenClose);
	createTrackbar("ѡ��ֵ", "����ʴ/���͡�", &g_nErodeDilateNum, g_nMaxIterationNum * 2 + 1, on_ErodeDilate);
	createTrackbar("ѡ��ֵ", "����ñ/��ñ��", &g_nTopBlackNum, g_nMaxIterationNum * 2 + 1, on_TopBlackHat);

	// ��ѯ��ȡ������Ϣ
	while (1) {
		int c;
		// ִ�лص�����
		on_OpenClose(g_nOpenCloseNum, 0);
		on_ErodeDilate(g_nErodeDilateNum, 0);
		on_TopBlackHat(g_nTopBlackNum, 0);

		// ��ȡ����
		c = waitKey(0);
		if ((char)c == 'q' || (char)c == 27)
			break;
		// ���¼���1��ʹ����Բ�ṹԪ��
		if ((char)c == 49)
			g_nElementShape = MORPH_ELLIPSE;
		// ���¼���2��ʹ�þ��νṹԪ��
		if ((char)c == 50)
			g_nElementShape = MORPH_RECT;
		// ���¼���3��ʹ��ʮ���νṹԪ��
		else if ((char)c == 51)
			g_nElementShape = MORPH_CROSS;
		// �����¼��̿ո�����ھ��Σ���Բ��ʮ����ѭ��
		else if ((char)c == ' ')
			g_nElementShape = (g_nElementShape + 1) % 3;
	}
	return 0;
}

static void on_OpenClose(int, void*) {
	// ƫ�����Ŀ���
	int offset = g_nOpenCloseNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;	// ƫ�����ľ���ֵ
	// �Զ����
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1), Point(Absolute_offset, Absolute_offset));
		// ���в���
		if (offset < 0) {
			morphologyEx(g_srcimage, g_dstimage, MORPH_OPEN, element);
		}
		else {
			morphologyEx(g_srcimage, g_dstimage, MORPH_CLOSE, element);
		}
	// ��ʾͼ��
	imshow("��������/�����㡿", g_dstimage);
}

static void on_ErodeDilate(int, void*) {
	// ƫ�����Ŀ���
	int offset = g_nErodeDilateNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;	// ƫ�����ľ���ֵ
	// �Զ����
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1), Point(Absolute_offset, Absolute_offset));
		// ���в���
		if (offset < 0) {
			morphologyEx(g_srcimage, g_dstimage, MORPH_ERODE, element);
		}
		else {
			morphologyEx(g_srcimage, g_dstimage, MORPH_DILATE, element);
		}
	// ��ʾͼ��
	imshow("����ʴ/���͡�", g_dstimage);
}

static void on_TopBlackHat(int, void*) {
	// ƫ�����Ŀ���
	int offset = g_nTopBlackNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;	// ƫ�����ľ���ֵ
	// �Զ����
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1), Point(Absolute_offset, Absolute_offset));
		// ���в���
		if (offset < 0) {
			morphologyEx(g_srcimage, g_dstimage, MORPH_TOPHAT, element);
		}
		else {
			morphologyEx(g_srcimage, g_dstimage, MORPH_BLACKHAT, element);
		}
	// ��ʾͼ��
	imshow("����ñ/��ñ��", g_dstimage);
}