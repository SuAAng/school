#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void filter(Mat img, Mat& dst, Mat mask) {
	dst = Mat(img.size(), CV_32F, Scalar(0));
	Point h_m = mask.size() / 2;

	for (int i = h_m.y; i < img.rows - h_m.y; i++) {//맞는지 확인
		for (int j = h_m.x; j < img.cols - h_m.x; j++) {
			float sum = 0;
			for (int u = 0; u < mask.rows; u++) {
				for (int v = 0; v < mask.cols; v++) {
					int y = i + u - h_m.y;
					int x = j + v - h_m.x;
					sum += mask.at<float>(u, v) * img.at<uchar>(y, x);
					
				}
			}

			dst.at<float>(i, j) = sum;
		}
	}
}

int main() {
	Mat image = imread("../image/filter_sharpen.jpg");//다시..
	Mat bgr[3];
	split(image, bgr);
	CV_Assert(image.data);

	float data1[] = {
		0, -1, 0,
		-1, 5, -1,
		0, -1, 0,
	};

	float data2[] = {
		-1, -1, -1,
		-1, 9, -1,
		-1, -1, -1,
	};

	Mat mask1(3, 3, CV_32F, data1);
	Mat mask2(3, 3, CV_32F, data2);
	Mat B, G, R,B2,G2,R2, sharpen, sharpen2;

	filter(bgr[0], B, mask1);
	filter(bgr[1], G, mask1);
	filter(bgr[2], R, mask1);
	B.convertTo(B, CV_8U);
	G.convertTo(G, CV_8U);
	R.convertTo(R, CV_8U);
	Mat result1[] = { B, G, R };

	filter(bgr[0], B2, mask2);
	filter(bgr[1], G2, mask2);
	filter(bgr[2], R2, mask2);
	B2.convertTo(B2, CV_8U);
	G2.convertTo(G2, CV_8U);
	R2.convertTo(R2, CV_8U);
	Mat result2[] = { B2, G2, R2 };
	
	merge(result1, 3, sharpen);
	merge(result2, 3, sharpen2);

	imshow("image", image);
	imshow("sharpen", sharpen);
	imshow("sharpen2", sharpen2);

	waitKey();
	return 0;


}