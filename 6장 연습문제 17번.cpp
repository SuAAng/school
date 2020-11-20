//8���� ������ 16�� ������ �������� Hueä�� ������׷� �׷����� ����ϴ� �ڵ带 �߰��Ͽ���.
//16�� �������� �����ڸ� ���콺 �̺�Ʈ�� ����Ͽ� ���� ��ư�� ������ ���� ������ ���� ��ġ�� �̿��Ͽ�
//�簢�� ������ �����Ѵ�. mask_reverse�� ���� �̹����� �簢�� ������ ������Ų��.
//mask_reverse������ ������Ų �� ����ϰ� ����� ���� �ڿ� ������Ų ���� �ٽ� �� �� �������� �ǵ�����.
//�� �������� ������׷� ��� �Լ���, hue ä�ο� ���� ���� �ȷ�Ʈ ����� �����ϰ�,
//���� ������׷��� �׸��� �Լ��� �߰��Ѵ�. �巡���� ������ ���� mask�� �����صΰ�
//������ mask�� ���� ������׷��� ����Ѵ�.


#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
Mat img;

void calc_Histo(const Mat& image, Mat& hist, int bins, int range_max = 256)//������׷� ���
{
	int histSize[] = { bins };//������׷� ��� ����
	float range[] = { 0, (float)range_max };//0�� ä�� ȭ�Ұ� ����
	int channels[] = { 0 };//ä�� ��� - ���� ä��
	const float* ranges[] = { range };//��� ä�� ȭ�ҹ���

	calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
}

Mat make_palatte(int rows)//hue ä�ο� ���� ���� �ȷ�Ʈ ��� ����
{
	Mat hsv(rows, 1, CV_8UC3);
	for (int i = 0; i < rows; i++) {//�����ŭ �ݺ�
		uchar hue = saturate_cast<uchar>((float)i / rows * 180);//���� ���
		hsv.at<Vec3b>(i) = Vec3b(hue, 255, 255);//HSV �÷� ����

	}
	cvtColor(hsv, hsv, COLOR_HSV2BGR);//HSV �÷� -> BGR �÷�
	
	return hsv;
}

void draw_histo_hue(Mat hist, Mat& hist_img, Size size = Size(256, 200))//�������� ������׷� �׸���
{
	Mat hsv_palatte = make_palatte(hist.rows);//�����ȷ�Ʈ ����

	hist_img = Mat(size, CV_8UC3, Scalar(255, 255, 255));
	float bin = (float)hist_img.cols / hist.rows;//��� ����
	normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);//����ȭ

	for (int i = 0; i < hist.rows; i++)
	{
		float start_x = (i * bin);
		float end_x = (i + 1) * bin;
		Point2f pt1(start_x, 0);
		Point2f pt2(end_x, hist.at <float>(i));

		Scalar color = hsv_palatte.at<Vec3b>(i);//�����ȷ�Ʈ ������
		if (pt2.y > 0) rectangle(hist_img, pt1, pt2, color, -1);//�ȷ�Ʈ ������ �׸���
	}
	flip(hist_img, hist_img, 0);//���� ������
}

void onMouse(int event, int x, int y, int flags, void* param) {
	static Point pt1(-1, -1), pt2(-1, -1);
	Scalar white(255, 255, 255);
	if (event == EVENT_LBUTTONDOWN) {//���콺 ���� ��ư ������
		pt1 = Point(x, y);//��ư ���� ��ġ ����
	}

	if (event == EVENT_LBUTTONUP) {//���콺 ���� ��ư ����
		pt2 = Point(x, y);//��ư �� ��ġ ����
		Mat mask;
		img(Rect(pt1, pt2)).copyTo(mask);//�巡�� ��Ų ������ ����
		Mat mask_reverse = img(Rect(pt1, pt2));//������ų �� ����
		mask_reverse = white - mask_reverse;//�巡���� ���� ������Ŵ
		imshow("���ÿ���", mask);//������ ���� ��â�� ���

		Mat HSV_img, HSV_arr[3];
		cvtColor(mask, HSV_img, COLOR_BGR2HSV);//BGR �÷� -> HSV �÷�
		split(HSV_img, HSV_arr);//ä�� �и�

		Mat hue_hist, hue_hist_img;
		calc_Histo(HSV_arr[0], hue_hist, 18, 180);//Hue ä�� ������׷� ���
		draw_histo_hue(hue_hist, hue_hist_img, Size(360, 200));//������׷� �׷���

		imshow("�������� 17", img);//������Ų �̹��� ���
		imshow("Histogram", hue_hist_img);//������׷� ���

		mask_reverse = white - mask_reverse;//������Ų ���� �ٽ� ��������
	}

}

int main() {
	img = imread("../image/mouse_img.jpg", 1);//�̹��� �ҷ�����
	CV_Assert(!img.empty());//����ó��


	imshow("�������� 17", img);//�̹��� ����
	setMouseCallback("�������� 17", onMouse, 0);//�ݹ��Լ� ���

	waitKey();//�̹��� ��� ������Ű��
	return 0;
}