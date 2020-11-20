//calcHisto()를 이용하여 히스토그램을 계산할 때는 1차원이 아닌 2차원으로 계산하도록 채널 목록이나 범위를 지정한다.
//색상 채널의 화소 범위는 0~180이고, 채도 채널 범위는 0~256이다. 계급 개수는 색상은 30개, 채도는 42개로 지정한다.
//계산된 히스토그램은 draw_histo()를 이용하여 행렬로 나타낸다. 그릴 때는 행렬의 각각 위치에 해당하는 채도값, 색상값, 빈도값을 통해 색을 표현한다.
//문제에 나온 그림의 예시와 같게 출력하기 위해서 행렬의 데이터 타입과 크기를 조정해준다.

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


void calc_Histo(const Mat& image, Mat& hist, Vec3i bins, Vec3f range) {
	int dims = 2; //히스토그램 차원수 (2차원)
	int channels[] = { 0, 1 };//채널 목록 (이중 채널)
	int histSize[] = { bins[0], bins[1]};//히스토그램 계급 개수 (색상 30개, 채도 42개)

	float range1[] = { 0, range[0] };//색상 채널 화소 범위
	float range2[] = { 0, range[1] };//채도 채널 화소 범위
	
	const float* ranges[] = { range1, range2};//색상, 채도 채널 화소범위

	calcHist(&image, 1, channels, Mat(), hist, dims, histSize, ranges);
	
}

void draw_histo(Mat hist, Mat &hist_img) 
{
	normalize(hist, hist, 0, 1, NORM_MINMAX);//최솟값이 0이고 최댓값이 1이 되도록 빈도깂 조정 (정규화)
	float ratio_value = 512.f; //휘도 범위 스케일 비율
	float ratio_hue = 180.f / hist.rows; // 색상 범위 스케일 비율
	float ratio_sat = 256.f / hist.cols; // 채도 범위 스케일 비율

	hist_img = Mat(hist.size(), CV_32FC3);//2차원 히스토그램 띄울 행렬

	for (int i = 0; i < hist.rows; i++) {
		for (int j = 0; j < hist.cols; j++) {
			float value = hist.at<float>(i, j) * ratio_value; //빈도값
			float hue = i * ratio_hue; //색상값
			float sat = j * ratio_sat; //채도값
			hist_img.at<Vec3f>(i, j) = Vec3f(hue, sat, value);

		}
	}

	hist_img.convertTo(hist_img, CV_8U);//데이터 타입 변경
	cvtColor(hist_img, hist_img, COLOR_HSV2BGR); //HSV -> BGR 컬러변환
	resize(hist_img, hist_img, Size(0, 0), 10, 10, INTER_NEAREST); //그래프 크기 변경

}

int main()
{
	Mat image = imread("../image/hue.jpg", IMREAD_COLOR);
	CV_Assert(image.data);

	Mat hsv, hist, hist_img;
	Vec3i bins(30, 42);//히스토그램 계급 개수
	Vec3f ranges(180, 256);//채널의 화소 범위

	cvtColor(image, hsv, COLOR_BGR2HSV);//BGR -> HSV
	calc_Histo(hsv, hist, bins, ranges);//히스토그램 계산
	draw_histo(hist, hist_img);//그래프 그리기
	
	imshow("image", image);
	imshow("hist_img", hist_img);
	waitKey();
	return 0;


}