//영상 파일을 읽어 윈도우에 표시하고, 마우스 이벤트를 통해서 드래그할 때 선택된 영역이 반전되어 표시되도록 프로그램을 작성하시오.

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat img;

void onMouse(int event, int x, int y, int flags, void *param) {
	static Point pt1(-1,-1), pt2(-1,-1);
	Scalar white(255, 255, 255);

	if (event == EVENT_LBUTTONDOWN) {//마우스 왼쪽 버튼 누르기
		pt1 = Point(x, y);
	}

	if (event == EVENT_LBUTTONUP){//마우스 왼쪽 버튼 떼기
		pt2 = Point(x, y);
		Mat mask_reverse = img(Rect(pt1, pt2));//반전시킬 곳 공유
		mask_reverse = white - mask_reverse;

		imshow("image", img);
		mask_reverse = white - mask_reverse;
	}
}

int main() {
	img = imread("../image/mouse_img.jpg",1);
	CV_Assert(!img.empty());
	

	imshow("image", img);
	setMouseCallback("image", onMouse, 0);
	
	waitKey();
	return 0;
}