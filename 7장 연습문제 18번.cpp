//cvtColor�Լ����� COLOR_BGR2GRAY�� ����Ͽ� �÷� ������ ��ϵ� �������� ��ȯ�Ѵ�. �� �� GaussianBlur�Լ��� ����Ͽ� ����þ� ������ �����ϰ�
//threshold�Լ��� THRESH_BINARY�� ����Ͽ� ����ȭ ��Ų��. ���������� mophologyEx ��������ν� �������� ���� ������ �����Ѵ�.
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("../image/coin.jpg", 1);
	CV_Assert(!img.empty());//����ó��
	Mat gray_img,gaussian_img, binary_img,morph_img;//���� �� �̹��� ����
	Mat kernel(7, 7, CV_8UC1, Scalar(1));//���� ���� ����ũ
	Size size(5, 5);//����þ� ������ ���
	double sigmaX = 0.3 * ((size.width - 1) * 0.5 - 1) + 0.8;//����þ� ������ ���(���ι��� ǥ������)
	double sigmaY = 0.3 * ((size.height - 1) * 0.5 - 1) + 0.8;//����þ� ������ ���(���ι��� ǥ������)

	cvtColor(img, gray_img, COLOR_BGR2GRAY);//BGR �÷� -> ��ϵ� ����
	GaussianBlur(gray_img, gaussian_img, size, sigmaX, sigmaY);//����þ� ����
	threshold(gaussian_img, binary_img, 95, 255, THRESH_BINARY);//����ȭ
	morphologyEx(binary_img, morph_img, MORPH_CLOSE, kernel);//�������� ���� ���� ����



	imshow("image", img);
	//imshow("gray", gray_img);
	//imshow("gaussian", gaussian_img);
	//imshow("binary", binary_img);
	imshow("�������� 18", morph_img);
	waitKey();

	return 0;

}