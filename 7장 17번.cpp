//다음의 그림과 같이 캐니에지 알고리즘에서 이중 임계값을 트랙바로 만들어서 두 개의 임계값을 조절하여 에지를 검출하도록 프로그램을 작성하시오.

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat image, gray, edge;
string title = "canny edge";
int th1 = 20, th2 = 20;

void onTrackbar(int, void* ) 
{
	GaussianBlur(gray, edge, Size(3, 3), 0.7);
	Canny(edge, edge, th1, th2, 3);


	imshow(title, edge);
}
int main() {
	
	image = imread("../image/canny.jpg", 1);
	CV_Assert(image.data);
	cvtColor(image, gray, COLOR_BGR2GRAY);


	namedWindow(title, WINDOW_AUTOSIZE);
	createTrackbar("th1", title, &th1, 255, onTrackbar);
	createTrackbar("th2", title, &th2, 255, onTrackbar);
	onTrackbar(th1, 0);
	onTrackbar(th2, 0);

	waitKey();
	return 0;

}