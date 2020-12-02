//예제_10.4.1은 가로 방향으로 드래그한 비율만큼 영상을 왜곡시킨다. 
//여기에 세로 방향으로 드래그할 때에도 왜곡을 하도록 morphing()함수의 소스를 수정하시오.

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Point2f pt1, pt2;
Mat image;

void morphing()
{
	Mat dst(image.size(), image.type(), Scalar(0));
	int width = image.cols;
	int length = image.rows;
	for (float y = 0; y < image.rows; y+=0.1f) {
		for (float x = 0; x < image.cols; x += 0.1f) {
			float ratio_x, ratio_y;

			if (x < pt1.x) ratio_x = x / pt1.x;
			else ratio_x = (width - x) / (width - pt1.x);

			if (y < pt1.y)ratio_y = y / pt1.y;
			else ratio_y = (length - y) / (length - pt1.y);

			float dx = ratio_x * (pt2.x - pt1.x);
			float dy = ratio_y * (pt2.y - pt1.y);

			dst.at<uchar>(y + dy, x + dx) = image.at <uchar>(y, x);
		}
	}
	dst.copyTo(image);
	imshow("image", image);
}

void onMouse(int event, int x, int y, int flags, void* param) {
	if (event == EVENT_LBUTTONDOWN) {
		pt1 = Point2f(x, y);

	}
	else if (event == EVENT_LBUTTONUP) {
		pt2 = Point2f(x, y);
		morphing();
	}
}

int main()
{
	image = imread("../image/warp_test.jpg", 0);
	CV_Assert(image.data);

	imshow("image",image);
	setMouseCallback("image", onMouse);
	waitKey();
	return 0;
}