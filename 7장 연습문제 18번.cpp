//cvtColor함수에서 COLOR_BGR2GRAY를 사용하여 컬러 영상을 명암도 영상으로 변환한다. 그 후 GaussianBlur함수를 사용하여 가우시안 블러링을 실행하고
//threshold함수의 THRESH_BINARY를 사용하여 이진화 시킨다. 마지막으로 mophologyEx 사용함으로써 모폴로지 열림 연산을 수행한다.
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("../image/coin.jpg", 1);
	CV_Assert(!img.empty());//예외처리
	Mat gray_img,gaussian_img, binary_img,morph_img;//연산 별 이미지 파일
	Mat kernel(7, 7, CV_8UC1, Scalar(1));//열림 연산 마스크
	Size size(5, 5);//가우시안 블러링에 사용
	double sigmaX = 0.3 * ((size.width - 1) * 0.5 - 1) + 0.8;//가우시안 블러링에 사용(가로방향 표준편차)
	double sigmaY = 0.3 * ((size.height - 1) * 0.5 - 1) + 0.8;//가우시안 블러링에 사용(세로방향 표준편차)

	cvtColor(img, gray_img, COLOR_BGR2GRAY);//BGR 컬러 -> 명암도 영상
	GaussianBlur(gray_img, gaussian_img, size, sigmaX, sigmaY);//가우시안 블러링
	threshold(gaussian_img, binary_img, 95, 255, THRESH_BINARY);//이진화
	morphologyEx(binary_img, morph_img, MORPH_CLOSE, kernel);//모폴로지 열림 연산 수행



	imshow("image", img);
	//imshow("gray", gray_img);
	//imshow("gaussian", gaussian_img);
	//imshow("binary", binary_img);
	imshow("연습문제 18", morph_img);
	waitKey();

	return 0;

}