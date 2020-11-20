#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void MaxFilter(Mat img, Mat& dst, int size) {
	dst = Mat(img.size(), CV_8U, Scalar(0));
	Size msize(size, size);
	Point h_m = msize / 2;

	for (int i = h_m.y; i < img.rows - h_m.y; i++) {
		for (int j = h_m.x; j < img.cols - h_m.x; j++) {
			Point start = Point(j, i) - h_m;
			Rect roi(start, msize);
			Mat mask = img(roi);

			double minVal, maxVal;
			minMaxLoc(mask, &minVal, &maxVal);
			dst.at<uchar>(i, j) = 1 ? maxVal : minVal;
		}
	}
}

int main() {
	Mat image = imread("../image/max.jpg", 0);
	CV_Assert(image.data);

	Mat max_img;
	MaxFilter(image, max_img, 5);
	copyMakeBorder(max_img, max_img, 10, 10, 10, 10, BORDER_REFLECT);
	imshow("image", image);
	imshow("maxFilter_img", max_img);

	waitKey();
	return 0;
}