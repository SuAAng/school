//check_match�Լ��� ���������� ����ִµ�, erosion�� mode�� 0, dilation�� mode�� 1�̴�.
//�ڵ尡 ���� �κ��� �����ϰ� mode�� 0���� 1������ ���� if�� ����Ͽ� �ڵ带 ���� ��Ÿ������.
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

//����ũ ���ҿ� ����ũ ���� �Է�ȭ�� ���� ��ġ ���� üũ
bool check_match(Mat img, Point start, Mat mask, int mode) 
{
	for (int u = 0; u < mask.rows; u++) {
		for (int v = 0; v < mask.cols; v++) {
			Point pt(v, u);// ��ȸ ��ǥ
			int m = mask.at<uchar>(pt);//����ũ ���
			int p = img.at<uchar>(start + pt);//�ش� ��ġ �Է� ȭ��

			bool ch = (p == 255);//����� ȭ�Ұ� ��ġ ��
			if (m == 1 && ch == mode)	return false;//mode 0�̸� ħ��, 1�̸� ��â

		}
	}
	return true;
}

void morphology(Mat img, Mat& dst, Mat mask, int mode)//mode�� 0�̸� erosion, 1�̸� dilation
{
	dst = Mat(img.size(), CV_8U, Scalar(0));

	if (mask.empty() && mode == 0)	 mask = Mat(3, 3, CV_8UC1, Scalar(1));
	else if (mask.empty() && mode == 1) mask = Mat(3, 3, CV_8UC1, Scalar(0));

	Point h_m = mask.size() / 2;//����ũ ���� ũ��
	for (int i = h_m.y; i < img.rows - h_m.y; i++) {
		for (int j = h_m.x; j < img.cols - h_m.x; j++) {
			Point start = Point(j, i) - h_m;
			bool check = check_match(img, start, mask, mode);//mode�� 0�� ��, ���� ��ġ ���� ��
															 //mode�� 1�� ��, ���� ����ġ ���� ��
			if (mode == 0) {
				dst.at <uchar>(i, j) = (check) ? 255 : 0;//erosion�� ���ȭ�� ����
			}
			else if (mode == 1) {
				dst.at <uchar>(i, j) = (check) ? 0 : 255;//dilation�� ���ȭ�� ����
			}
		}
	}
}

int main() 
{
	Mat image = imread("../image/morph_test1.jpg", 0);
	CV_Assert(image.data);//����ó��
	Mat th_img, erosion, dilation;
	threshold(image, th_img, 128, 255, THRESH_BINARY);//����ȭ

	//erosion data
	uchar data[] =  { 0,0,0,
					  1,1,1,
					  0,1,0 };
	//dilation data
	uchar data2[] = { 0,1,0,
					  1,1,1,
					  0,1,0 };


	Mat mask(3, 3, CV_8UC1, data);//erosion mask
	Mat mask2(3, 3, CV_8UC1, data2);//dilation data
	morphology(th_img, erosion, (Mat)mask, 0);//erosion ����
	morphology(th_img, dilation, (Mat)mask2, 1);//dilation ����

	imshow("image", image);//����
	imshow("User_erosion", erosion);//erosion ���
	imshow("User_dilation", dilation);//dilation ���
	waitKey();
	return 0;

}