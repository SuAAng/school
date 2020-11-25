//13. 주파수 영역 필터링에서 중간 주파수 대역만을 통과시키도록 필터를 생성해서 필터링을 수행하는 프로그램을 작성하시오.
//14. 13번 문제를 두 개의 트랙바를 이용해서 중간 주파수 대역을 변경할 수 있도록 프로그램을 작성하시오.
//13번 문제를 해결하기 위해서 중간 주파수 대역만을 통과시키는 필터를 생성해야한다. 
//get_middlepassFilter함수를 작성하였는데, 필터 처음의 값은 0으로 지정하고, 
//고주파 영역을 통과시키지 못하도록 필터에 값이 1인 원을 삽입하고, 저주파를 영역또한 통과시키지 못하도록 값이 0인 원을 필터에 삽입하였다.

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
Mat image = imread("../image/filter_test.jpg", 0);
int radius[2] = { 20,50 };

//셔플링
void shuffling(Mat mag_img, Mat& dst) {
	int cx = mag_img.cols / 2;
	int cy = mag_img.rows / 2;
	Rect q1(cx, 0, cx, cy);//1사분면 사각형
	Rect q2(0, 0, cx, cy);//2사분면 사각형
	Rect q3(0, cy, cx, cy);//3사분면 사각형
	Rect q4(cx, cy, cx, cy);//4사분면 사각형

	dst = Mat(mag_img.size(), mag_img.type());

	//각각의 사분면 복사
	mag_img(q1).copyTo(dst(q3));
	mag_img(q3).copyTo(dst(q1));
	mag_img(q2).copyTo(dst(q4));
	mag_img(q4).copyTo(dst(q2));
}
//채널 분리 및 크기 계산
void log_mag(Mat complex_mat, Mat& dst) {
	Mat planes[2];
	split(complex_mat, planes); //2채널 복소 행렬 분리
	magnitude(planes[0], planes[1], dst);//크기 계산
	log(dst + 1, dst);
	normalize(dst, dst, 0, 255, NORM_MINMAX);//정규화 수행
	dst.convertTo(dst, CV_8U);
}
//영삽입
Mat zeropadding(Mat img) {
	int m = 1 << (int)ceil(log2(img.rows));//2의 자승 계산
	int n = 1 << (int)ceil(log2(img.cols));
	Mat dst(m, n, img.type(), Scalar(0));

	Rect rect(Point(0, 0), img.size());//원본 영상크기 관심영역
	img.copyTo(dst(rect));//원본영상을 고
	dst.convertTo(dst, CV_32F);

	return dst;
}
//중간주파 통과 필터 생성 함수
Mat get_middlepassFilter(Size size, int min_radius, int max_radius) {
	Point center = size / 2;
	Mat filter(size, CV_32FC2, Vec2f(0, 0));//필터 베이스 0값
	circle(filter, center, max_radius, Vec2f(1, 1), -1);//고주파 영역 통과 못하는 원 - 1값 필터에 삽입
	circle(filter, center, min_radius, Vec2f(0, 0), -1);//저주파 영역 통과 못하는 원 - 0값 필터에 삽입

	return filter;
}
//FFT 전체 과정 수행 함수
void FFT(Mat image, Mat& dft_coef, Mat& dft_img) {
	Mat complex_img;
	Mat pad_img = zeropadding(image);//영삽입
	Mat tmp[] = { pad_img, Mat::zeros(pad_img.size(), pad_img.type()) };
	merge(tmp, 2, complex_img);//복소 행렬 구성
	dft(complex_img, dft_coef, 0);//FFT함수
	shuffling(dft_coef, dft_coef);//셔플링
	log_mag(dft_coef, dft_img);//주파수 스펙트럼 영상
}
//IFFT 전체 과정 수행 함수
Mat IFFT(Mat dft_coef, Size size) {
	Mat idft_coef, idft_img[2];
	shuffling(dft_coef, dft_coef);//역 셔플링 수행
	dft(dft_coef, idft_coef, DFT_INVERSE + DFT_SCALE);
	split(idft_coef, idft_img);//복소 행렬 분리

	Rect img_rect(Point(0, 0), size);//입력영상 크기 사각형
	idft_img[0](img_rect).convertTo(idft_img[0], CV_8U);//영삽입 부분 제거
	return idft_img[0];
}

void onChange(int value, void* userdata) {
	Mat dft_coef, dft_img, middle_dft, filtered_mat;
	FFT(image, dft_coef, dft_img);//FFT 수행 및 셔플링
	Mat middle_filter = get_middlepassFilter(dft_coef.size(), radius[0], radius[1]); //min_radius와 max_radius로 중간주파 영역을 정함
	multiply(dft_coef, middle_filter, filtered_mat);//필터링 - 원소 간 곱셈
	log_mag(filtered_mat, middle_dft);//주파수 스펙트럼 생성
	imshow("middle_dft", middle_dft);
	imshow("middlepassed_img", IFFT(filtered_mat, image.size()));
}

int main() {
	
	CV_Assert(image.data);

	namedWindow("middlepassed_img", WINDOW_AUTOSIZE);
	createTrackbar("반지름1", "middlepassed_img", &radius[0], min(image.rows, image.cols)/2, onChange);//저주파를 통과시키지 못하는 원의 반지름의 값을 지정하는 트랙바
	createTrackbar("반지름2", "middlepassed_img", &radius[1], min(image.rows, image.cols)/2, onChange);//고주파를 통과시키지 못하는 원의 반지름의 값을 지정하는 트랙바
	onChange(0, 0);

	imshow("image", image);
	waitKey();
	return 0;
}