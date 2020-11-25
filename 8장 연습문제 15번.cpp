//13�� ����. 600*400 ũ���� �����쿡�� ���콺 �巡�׸� ���ؼ� �� ���� ��ǥ�� ��� ������ �߰�, 
//			 �� ������ ���̿� ����(3�� ���⿡�� �Ʒ� ������ ����)�� ����ϴ� ���α׷��� �ۼ��Ͻÿ�.
//15�� ����. 13�� �������� ���� ������ ����� ������ ���⸦ �����ϴ� ���α׷��� �ۼ��Ͻÿ�.

//�ϴ�, 13�� ������ �ذ��ϱ� ���� 600*400 ũ���� �̹����� �غ��Ѵ�. 
//���콺 �巡�׸� ���� �� ���� ��ǥ�� ��� ���̱� ������  EVENT_LBUTTONDOWN,�� EVENT_LBUTTONUP�� ����Ѵ�.
//EVENT_LBUTTONDOWN�� ��, �� ��ǥ�� �����ϰ� ������ ǥ���Ѵ�. ���������� EVENT_LBUTTONUP�� ��, �� ��ǥ�� �����ϰ� ������ ǥ���� �� ������ �ߴ´�.
//�׸��� calc_angle_lengt(Point pt)�� ����Ͽ� ������ ���̿� ������ ����� ���Ȱ��� ���Ѵ�.
//���� ���� ���� rotation(Mat img, Mat& dst, double radian, Point pt)�Լ��� �̿��Ͽ� �׸��� ȸ����Ų��.
//rotation�Լ����� pt�� �̹����� �߽����� �̿��Ͽ���. (�߽����� �߽����� ȸ���� �Ѵٴ� ��)
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat img;

//���� ȭ�� �缱�� ����
uchar bilinear_value(Mat img, int x, int y) {
	if (x >= img.cols - 1) x--;
	if (y >= img.rows - 1) y--;

	//4�� ȭ�� ������
	Point pt((int)x, (int)y);
	int A = img.at<uchar>(pt);//���� ��� ȭ��
	int B = img.at<uchar>(pt + Point(0, 1));//���� �ϴ� ȭ��
	int C = img.at<uchar>(pt + Point(1, 0));//������ ��� ȭ��
	int D = img.at<uchar>(pt + Point(1, 1));//������ �ϴ� ȭ��
	
	//�Ÿ� ����
	double alpha = y - pt.y;
	double beta = x - pt.x;

	//1�� ����
	int M1 = A + (int)cvRound(alpha * (B - A));
	int M2 = C + (int)cvRound(alpha * (D - C));

	//2�� ����
	int P = M1 + (int)cvRound(beta * (M2 - M1));

	return saturate_cast<uchar>(P);
}

//pt ��ǥ ���� ȸ�� ��ȯ
void rotation(Mat img, Mat& dst, double radian, Point pt) {
	double sin_value = sin(radian);
	double cos_value = cos(radian);

	Rect rect(Point(0, 0), img.size());
	dst = Mat(img.size(), img.type(), Scalar(0));

	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++)
		{
			// pt ��ǥ��ŭ  �����̵�
			int jj = j - pt.x;
			int ii = i - pt.y;
			double x = jj * cos_value + ii * sin_value + pt.x;
			double y = -jj * sin_value + ii * cos_value + pt.y;

			if (rect.contains(Point2d(x, y)))
				dst.at<uchar>(i, j) = bilinear_value(img, x, y);
		}
	}
}

double calc_angle_length(Point pt[2])
{
	int x = pt[1].x - pt[0].x;//x��ǥ ����
	int y = pt[1].y - pt[0].y;//y��ǥ ����
	float length = sqrt(x * x + y * y);//�� ����
	float tan = (float)y / (float)x;//����
	double radian = atan2f(y,x);//���� ��

	cout << "������ ����" << length << endl;
	cout << "������ ����" << tan << endl << endl;

	return radian;
}

void onMouse(int event, int x, int y, int flags, void*) {
	Point curr_pt(x, y);
	static Point pt[2] = {};//���콺 �̺�Ʈ�� �Ͼ ��
	static Mat tmp;
	double radian;
	Point center = img.size() / 2;
	if (event == EVENT_LBUTTONDOWN) {//���콺 ���� ��
		tmp = img.clone();
		pt[0] = curr_pt;//���� ���� ��ǥ ����
		circle(tmp, pt[0], 2, Scalar(0), 2);//���� ���� ��ġ�� �� �׸���
		imshow("image", tmp);
	}
	else if (event == EVENT_LBUTTONUP && pt[0].x > 0) {//���콺 ��� ��
		pt[1] = curr_pt;//��� ���� ��ǥ ����
		circle(tmp, pt[1], 2, Scalar(0), 2);//��� ���� ��ġ�� �� �׸���
		line(tmp, pt[0], pt[1], Scalar(0));//�� ��ǥ�� �մ� �� �׸���
		
		if (pt[1].x > 0) {
			radian = calc_angle_length(pt);//���̿� ����� ���� ���� ����ϰ�, ���� ���� ��ȯ
			pt[0] = pt[1] = Point(0, 0);//pt���� 0���� �ʱ�ȭ
		}
		rotation(tmp, tmp, radian, center);//�߽����� �������� ���� ����ŭ �׸��� ȸ����Ų��.
		imshow("image", tmp);
	}


}

int main()
{
	img = imread("../image/mouse_img.jpg", 0);//�̹��� �ҷ�����
	CV_Assert(!img.empty());//����ó��

	imshow("image", img);
	setMouseCallback("image", onMouse, 0);
	waitKey();
	return 0;
}