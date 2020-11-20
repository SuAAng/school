//check_match함수는 공통적으로 들어있는데, erosion은 mode가 0, dilation은 mode가 1이다.
//코드가 같은 부분은 생략하고 mode가 0인지 1인지에 따라서 if를 사용하여 코드를 나눠 나타내었다.
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

//마스크 원소와 마스크 범위 입력화소 간의 일치 여부 체크
bool check_match(Mat img, Point start, Mat mask, int mode) 
{
	for (int u = 0; u < mask.rows; u++) {
		for (int v = 0; v < mask.cols; v++) {
			Point pt(v, u);// 순회 좌표
			int m = mask.at<uchar>(pt);//마스크 계수
			int p = img.at<uchar>(start + pt);//해당 위치 입력 화소

			bool ch = (p == 255);//계수와 화소값 일치 비교
			if (m == 1 && ch == mode)	return false;//mode 0이면 침식, 1이면 팽창

		}
	}
	return true;
}

void morphology(Mat img, Mat& dst, Mat mask, int mode)//mode가 0이면 erosion, 1이면 dilation
{
	dst = Mat(img.size(), CV_8U, Scalar(0));

	if (mask.empty() && mode == 0)	 mask = Mat(3, 3, CV_8UC1, Scalar(1));
	else if (mask.empty() && mode == 1) mask = Mat(3, 3, CV_8UC1, Scalar(0));

	Point h_m = mask.size() / 2;//마스크 절반 크기
	for (int i = h_m.y; i < img.rows - h_m.y; i++) {
		for (int j = h_m.x; j < img.cols - h_m.x; j++) {
			Point start = Point(j, i) - h_m;
			bool check = check_match(img, start, mask, mode);//mode가 0일 때, 원소 일치 여부 비교
															 //mode가 1일 때, 원소 불일치 여부 비교
			if (mode == 0) {
				dst.at <uchar>(i, j) = (check) ? 255 : 0;//erosion의 출력화소 저장
			}
			else if (mode == 1) {
				dst.at <uchar>(i, j) = (check) ? 0 : 255;//dilation의 출력화소 저장
			}
		}
	}
}

int main() 
{
	Mat image = imread("../image/morph_test1.jpg", 0);
	CV_Assert(image.data);//예외처리
	Mat th_img, erosion, dilation;
	threshold(image, th_img, 128, 255, THRESH_BINARY);//이진화

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
	morphology(th_img, erosion, (Mat)mask, 0);//erosion 실행
	morphology(th_img, dilation, (Mat)mask2, 1);//dilation 실행

	imshow("image", image);//원본
	imshow("User_erosion", erosion);//erosion 출력
	imshow("User_dilation", dilation);//dilation 출력
	waitKey();
	return 0;

}