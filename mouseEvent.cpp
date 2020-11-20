//600*400 크기의 윈도우에서 마우스 드래그를 통해서 두 개의 좌표를 얻어 직선을 긋고, 
//이 직선의 길이와 기울기(3시 방향에서 아래 방향의 기울기)를 계산하는 프로그램을 작성하시오.
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat image(400,600, CV_8U,Scalar(255));

void calc_angle_length(Point pt[2])
{
	int x = pt[1].x - pt[0].x;
	int y = pt[1]. y - pt[0].y;
	float length = sqrt(x * x + y * y);
	float tan = (float)y / (float)x;
	cout << "직선의 길이" << length <<endl;
	cout << "직선의 기울기" << tan << endl <<endl;
}

void onMouse(int event, int x, int y, int flags, void*) {
	Point curr_pt(x, y);
	static Point pt[2] = {};
	static Mat tmp;
	
	if (event == EVENT_LBUTTONDOWN) {
		tmp = image.clone();
		pt[0] = curr_pt;
		circle(tmp, pt[0], 2, Scalar(0), 2);
		imshow("image", tmp);
	}
	else if (event == EVENT_LBUTTONUP && pt[0].x > 0) {
		pt[1] = curr_pt;
		circle(tmp, pt[1], 2, Scalar(0), 2);
		line(tmp, pt[0], pt[1], Scalar(0));
		imshow("image", tmp);
	}
	
	if (pt[1].x > 0) {
		calc_angle_length(pt);
		pt[0] = pt[1] = Point(0, 0);
	}
}

int main()
{
	imshow("image", image);
	setMouseCallback("image", onMouse, 0);
	waitKey();
	return 0;
}