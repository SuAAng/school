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
void affine_transform(Mat img, Mat& dst, Mat map, Size size) {//어파인 변환 함수
	dst = Mat(img.size(), img.type(), Scalar(0));
	Rect rect(Point(0, 0), img.size());

	Mat inv_map;
	invertAffineTransform(map, inv_map);

	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++)
		{
			Point3d ji(j, i, 1);
			Mat xy = inv_map * (Mat)ji;
			Point2d pt = (Point2d)xy;

			if (rect.contains(pt))
				dst.at<uchar>(i, j) = bilinear_value(img, pt.x, pt.y);

		}
	}
}
int main()
{
	Mat image = imread("../image/rotate_test.jpg", 0);
	CV_Assert(image.data);

	Mat rotate_img, aff_img;
	Point point(300, 100);//기준 좌표
	rotation(image, rotate_img, 30, point);//rotation() 함수 이용
	aff_img = getRotationMatrix2D(point, -30, 1);//회전변환 어파인 행렬
	affine_transform(image, aff_img, aff_img, image.size());//회전변환 수행
	imshow("image", image);
	imshow("30도 회전영상 - (300,100) 기준", rotate_img);
	imshow("30도 어파인 회전 - (300, 100) 기준", aff_img);
	waitKey();
	return 0;
}