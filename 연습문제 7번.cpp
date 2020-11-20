#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image = imread("../image/logo.jpg", 1);
	Mat bgr[3], blue_img, red_img, green_img, zero(image.size(), CV_8U, Scalar(0));
	split(image, bgr);

	Mat B[] = { bgr[0], zero, zero };
	Mat G[] = { zero, bgr[1], zero };
	Mat R[] = { zero, zero, bgr[2] };
	merge(B, 3, blue_img);
	merge(G, 3, green_img);
	merge(R, 3, red_img);


	imshow("image", image);
	imshow("blue_img", blue_img);
	imshow("greem_img", green_img);
	imshow("red_img", red_img);
	waitKey();
}