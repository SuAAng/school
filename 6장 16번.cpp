//���� ������ �о� �����쿡 ǥ���ϰ�, ���콺 �̺�Ʈ�� ���ؼ� �巡���� �� ���õ� ������ �����Ǿ� ǥ�õǵ��� ���α׷��� �ۼ��Ͻÿ�.

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat img;

void onMouse(int event, int x, int y, int flags, void *param) {
	static Point pt1(-1,-1), pt2(-1,-1);
	Scalar white(255, 255, 255);

	if (event == EVENT_LBUTTONDOWN) {//���콺 ���� ��ư ������
		pt1 = Point(x, y);
	}

	if (event == EVENT_LBUTTONUP){//���콺 ���� ��ư ����
		pt2 = Point(x, y);
		Mat mask_reverse = img(Rect(pt1, pt2));//������ų �� ����
		mask_reverse = white - mask_reverse;

		imshow("image", img);
		mask_reverse = white - mask_reverse;
	}
}

int main() {
	img = imread("../image/mouse_img.jpg",1);
	CV_Assert(!img.empty());
	

	imshow("image", img);
	setMouseCallback("image", onMouse, 0);
	
	waitKey();
	return 0;
}