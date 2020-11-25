//13번 문제. 600*400 크기의 윈도우에서 마우스 드래그를 통해서 두 개의 좌표를 얻어 직선을 긋고, 
//			 이 직선의 길이와 기울기(3시 방향에서 아래 방향의 기울기)를 계산하는 프로그램을 작성하시오.
//15번 문제. 13번 문제에서 그은 직선의 기울기로 영상의 기울기를 보정하는 프로그램을 작성하시오.

//일단, 13번 문제를 해결하기 위해 600*400 크기의 이미지를 준비한다. 
//마우스 드래그를 통해 두 개의 좌표를 얻는 것이기 때문에  EVENT_LBUTTONDOWN,과 EVENT_LBUTTONUP을 사용한다.
//EVENT_LBUTTONDOWN일 때, 그 좌표를 저장하고 점으로 표시한다. 마찬가지로 EVENT_LBUTTONUP일 때, 그 좌표를 저장하고 점으로 표시한 후 직선을 긋는다.
//그리고 calc_angle_lengt(Point pt)를 사용하여 직선의 길이와 직선의 기울기와 라디안값을 구한다.
//구한 라디안 값을 rotation(Mat img, Mat& dst, double radian, Point pt)함수를 이용하여 그림을 회전시킨다.
//rotation함수에서 pt는 이미지의 중심점을 이용하였다. (중심점을 중심으로 회전을 한다는 뜻)
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat img;

//단일 화소 양선형 보간
uchar bilinear_value(Mat img, int x, int y) {
	if (x >= img.cols - 1) x--;
	if (y >= img.rows - 1) y--;

	//4개 화소 가져옴
	Point pt((int)x, (int)y);
	int A = img.at<uchar>(pt);//왼쪽 상단 화소
	int B = img.at<uchar>(pt + Point(0, 1));//왼쪽 하단 화소
	int C = img.at<uchar>(pt + Point(1, 0));//오른쪽 상단 화소
	int D = img.at<uchar>(pt + Point(1, 1));//오른쪽 하단 화소
	
	//거리 비율
	double alpha = y - pt.y;
	double beta = x - pt.x;

	//1차 보간
	int M1 = A + (int)cvRound(alpha * (B - A));
	int M2 = C + (int)cvRound(alpha * (D - C));

	//2차 보간
	int P = M1 + (int)cvRound(beta * (M2 - M1));

	return saturate_cast<uchar>(P);
}

//pt 좌표 기준 회전 변환
void rotation(Mat img, Mat& dst, double radian, Point pt) {
	double sin_value = sin(radian);
	double cos_value = cos(radian);

	Rect rect(Point(0, 0), img.size());
	dst = Mat(img.size(), img.type(), Scalar(0));

	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++)
		{
			// pt 좌표만큼  평행이동
			int jj = j - pt.x;
			int ii = i - pt.y;
			double x = jj * cos_value + ii * sin_value + pt.x;
			double y = -jj * sin_value + ii * cos_value + pt.y;

			if (rect.contains(Point2d(x, y)))
				dst.at<uchar>(i, j) = bilinear_value(img, x, y);
		}
	}
}

double calc_angle_length(Point pt[2])
{
	int x = pt[1].x - pt[0].x;//x좌표 차이
	int y = pt[1].y - pt[0].y;//y좌표 차이
	float length = sqrt(x * x + y * y);//선 길이
	float tan = (float)y / (float)x;//기울기
	double radian = atan2f(y,x);//라디안 값

	cout << "직선의 길이" << length << endl;
	cout << "직선의 기울기" << tan << endl << endl;

	return radian;
}

void onMouse(int event, int x, int y, int flags, void*) {
	Point curr_pt(x, y);
	static Point pt[2] = {};//마우스 이벤트가 일어난 곳
	static Mat tmp;
	double radian;
	Point center = img.size() / 2;
	if (event == EVENT_LBUTTONDOWN) {//마우스 누를 때
		tmp = img.clone();
		pt[0] = curr_pt;//누른 곳의 좌표 저장
		circle(tmp, pt[0], 2, Scalar(0), 2);//누른 곳의 위치에 점 그리기
		imshow("image", tmp);
	}
	else if (event == EVENT_LBUTTONUP && pt[0].x > 0) {//마우스 떼어낼 때
		pt[1] = curr_pt;//떼어낸 곳의 좌표 저장
		circle(tmp, pt[1], 2, Scalar(0), 2);//떼어낸 곳의 위치에 점 그리기
		line(tmp, pt[0], pt[1], Scalar(0));//두 좌표를 잇는 선 그리기
		
		if (pt[1].x > 0) {
			radian = calc_angle_length(pt);//길이와 기울기와 라디안 값을 계산하고, 라디안 값을 반환
			pt[0] = pt[1] = Point(0, 0);//pt값을 0으로 초기화
		}
		rotation(tmp, tmp, radian, center);//중심점을 기준으로 라디안 값만큼 그림을 회전시킨다.
		imshow("image", tmp);
	}


}

int main()
{
	img = imread("../image/mouse_img.jpg", 0);//이미지 불러오기
	CV_Assert(!img.empty());//예외처리

	imshow("image", img);
	setMouseCallback("image", onMouse, 0);
	waitKey();
	return 0;
}