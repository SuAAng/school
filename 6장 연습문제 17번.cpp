//8주차 문제인 16번 문제를 바탕으로 Hue채널 히스토그램 그래프를 출력하는 코드를 추가하였다.
//16번 문제부터 말하자면 마우스 이벤트를 사용하여 왼쪽 버튼을 눌렀을 때와 떼었을 때의 위치를 이용하여
//사각형 영역을 저장한다. mask_reverse에 원본 이미지의 사각형 영역을 공유시킨다.
//mask_reverse영역을 반전시킨 뒤 출력하고 출력이 끝난 뒤에 반전시킨 곳을 다시 한 번 반전시켜 되돌린다.
//이 바탕에서 히스토그램 계산 함수와, hue 채널에 대한 색상 팔레트 행렬을 생성하고,
//색상 히스토그램을 그리는 함수를 추가한다. 드래그한 영역에 대해 mask에 복사해두고
//복사한 mask에 대한 히스토그램을 출력한다.


#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
Mat img;

void calc_Histo(const Mat& image, Mat& hist, int bins, int range_max = 256)//히스토그램 계산
{
	int histSize[] = { bins };//히스토그램 계급 개수
	float range[] = { 0, (float)range_max };//0번 채널 화소값 범위
	int channels[] = { 0 };//채널 목록 - 단일 채널
	const float* ranges[] = { range };//모든 채널 화소범위

	calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
}

Mat make_palatte(int rows)//hue 채널에 대한 색상 팔레트 행렬 생성
{
	Mat hsv(rows, 1, CV_8UC3);
	for (int i = 0; i < rows; i++) {//행수만큼 반복
		uchar hue = saturate_cast<uchar>((float)i / rows * 180);//색상 계산
		hsv.at<Vec3b>(i) = Vec3b(hue, 255, 255);//HSV 컬러 지정

	}
	cvtColor(hsv, hsv, COLOR_HSV2BGR);//HSV 컬러 -> BGR 컬러
	
	return hsv;
}

void draw_histo_hue(Mat hist, Mat& hist_img, Size size = Size(256, 200))//색상으로 히스토그램 그리기
{
	Mat hsv_palatte = make_palatte(hist.rows);//색상팔레트 생성

	hist_img = Mat(size, CV_8UC3, Scalar(255, 255, 255));
	float bin = (float)hist_img.cols / hist.rows;//계급 개수
	normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);//정규화

	for (int i = 0; i < hist.rows; i++)
	{
		float start_x = (i * bin);
		float end_x = (i + 1) * bin;
		Point2f pt1(start_x, 0);
		Point2f pt2(end_x, hist.at <float>(i));

		Scalar color = hsv_palatte.at<Vec3b>(i);//색상팔레트 색지정
		if (pt2.y > 0) rectangle(hist_img, pt1, pt2, color, -1);//팔레트 색으로 그리기
	}
	flip(hist_img, hist_img, 0);//상하 뒤집기
}

void onMouse(int event, int x, int y, int flags, void* param) {
	static Point pt1(-1, -1), pt2(-1, -1);
	Scalar white(255, 255, 255);
	if (event == EVENT_LBUTTONDOWN) {//마우스 왼쪽 버튼 누르기
		pt1 = Point(x, y);//버튼 누른 위치 저장
	}

	if (event == EVENT_LBUTTONUP) {//마우스 왼쪽 버튼 떼기
		pt2 = Point(x, y);//버튼 뗀 위치 저장
		Mat mask;
		img(Rect(pt1, pt2)).copyTo(mask);//드래그 시킨 영역을 복사
		Mat mask_reverse = img(Rect(pt1, pt2));//반전시킬 곳 공유
		mask_reverse = white - mask_reverse;//드래그한 영역 반전시킴
		imshow("선택영역", mask);//공유한 영역 새창에 출력

		Mat HSV_img, HSV_arr[3];
		cvtColor(mask, HSV_img, COLOR_BGR2HSV);//BGR 컬러 -> HSV 컬러
		split(HSV_img, HSV_arr);//채널 분리

		Mat hue_hist, hue_hist_img;
		calc_Histo(HSV_arr[0], hue_hist, 18, 180);//Hue 채널 히스토그램 계산
		draw_histo_hue(hue_hist, hue_hist_img, Size(360, 200));//히스토그램 그래프

		imshow("연습문제 17", img);//반전시킨 이미지 출력
		imshow("Histogram", hue_hist_img);//히스토그램 출력

		mask_reverse = white - mask_reverse;//반전시킨 영역 다시 돌려놓음
	}

}

int main() {
	img = imread("../image/mouse_img.jpg", 1);//이미지 불러오기
	CV_Assert(!img.empty());//예외처리


	imshow("연습문제 17", img);//이미지 띄우기
	setMouseCallback("연습문제 17", onMouse, 0);//콜백함수 등록

	waitKey();//이미지 출력 유지시키기
	return 0;
}