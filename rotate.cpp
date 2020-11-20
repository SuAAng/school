#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

uchar bilinear_value(Mat img, int x, int y) {
	if (x >= img.cols - 1) x--;
	if (y >= img.rows - 1) y--;

	//4개 화소 가져옴
	Point pt((int)x, (int)y);
	int A = img.at<uchar>(pt);
	int B = img.at<uchar>(pt + Point(0, 1));
	int C = img.at<uchar>(pt + Point(1, 0));
	int D = img.at<uchar>(pt + Point(1, 1));

	double alpha = y - pt.y;
	double beta = x - pt.x;
	int M1 = A + (int)cvRound(alpha * (B - A));
	int M2 = A + (int)cvRound(alpha * (D - C));
	int P = M1 + (int)cvRound(beta * (M2 - M1));

	return saturate_cast<uchar>(P);
}

void rotation(Mat img, Mat& dst, double dgree) {
	double radian = dgree / 180 * CV_PI;
	double sin_value = sin(radian);
	double cos_value = cos(radian);

	Rect rect(Point(0, 0), img.size());
	dst = Mat(img.size(), img.type(), Scalar(0));

	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			double x = j * cos_value + i * sin_value;
			double y = -j * sin_value + i * cos_value;

			if (rect.contains(Point2d(x, y)))
				dst.at<uchar>(i, j) = bilinear_value(img, x, y);
		}
	}
}

void rotation(Mat img, Mat& dst, double dgree, Point pt) {
	double radian = dgree / 180 * CV_PI;
	double sin_value = sin(radian);
	double cos_value = cos(radian);

	Rect rect(Point(0, 0), img.size());
	dst = Mat(img.size(), img.type(), Scalar(0));

	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			int jj = j - pt.x;
			int ii = i - pt.y;
			double x = jj * cos_value + ii * sin_value + pt.x;
			double y = -jj * sin_value + ii * cos_value + pt.y;

			if (rect.contains(Point2d(x, y)))
				dst.at<uchar>(i, j) = bilinear_value(img, x, y);
		}
	}
}

int main()
{
	Mat image = imread("../image/rotate_test.jpg", 1);
	CV_Assert(image.data);
	Mat bgr[3];
	split(image, bgr);
	
	Mat dst_ori[3], result_ori, dst_center[3], result_center;
	Point center = image.size() / 2;
	rotation(bgr[0], dst_ori[0], 20);
	rotation(bgr[1], dst_ori[1], 20);
	rotation(bgr[2], dst_ori[2], 20);
	merge(dst_ori, 3, result_ori);

	rotation(bgr[0], dst_center[0], 20, center);
	rotation(bgr[1], dst_center[1], 20, center);
	rotation(bgr[2], dst_center[2], 20, center);
	merge(dst_center, 3, result_center);

	imshow("image", image);
	imshow("dst1-20도 회전(원점)", result_ori);
	imshow("dst2-20도 회전(중심점)", result_center);
	waitKey();
	return 0;
}