//������ �׸��� ���� ĳ�Ͽ��� �˰��򿡼� ���� �Ӱ谪�� Ʈ���ٷ� ���� �� ���� �Ӱ谪�� �����Ͽ� ������ �����ϵ��� ���α׷��� �ۼ��Ͻÿ�.

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