#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

string title = "���� �ռ�", bar_name = "�ռ���";
Mat image1;

void onChange(int value, void* userdata) {
	double alpha = (double)value/100, beta = 1 - alpha;
	Mat image2 = imread("../image/add2.jpg", IMREAD_GRAYSCALE);


	cout << "�ռ��� " << value << endl;
	
	Mat add_img = image1*beta + image2*alpha;
	addWeighted(image1, beta, image2, alpha, 0, add_img);

	Mat tmp = add_img;
	imshow(title, tmp);
}

int main()
{
	int value = 0;
	image1 = imread("../image/add1.jpg", IMREAD_GRAYSCALE);

	namedWindow(title, WINDOW_AUTOSIZE);
	createTrackbar(bar_name, title, &value, 100, onChange);//Ʈ���� �ִ밪 100

	imshow(title, image1);
	waitKey(0);
	return 0;
}