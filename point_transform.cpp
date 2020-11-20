#include <opencv2/opencv.hpp>
// 클릭한 위치에 사각형이 그려지게 만들었고, 회전각 마이너스도 있게 만들었습니다.
using namespace cv;
using namespace std;

Mat image;
string title = "image";

void onMouse(int event, int x, int y, int flags, void* param) {
	vector<Point> rect_pt1, rect_pt2;
	static Point pt(-1, -1);
	static Point pt1(0, 0);
	if (event == EVENT_LBUTTONDOWN) {
		if (pt.x < 0) {
			pt = Point(x, y);
			pt1 = Point(x, y);
			rect_pt1.push_back(Point(pt1.x, pt1.y));
			rect_pt1.push_back(Point(pt1.x + 200, pt1.y));
			rect_pt1.push_back(Point(pt1.x + 200, pt1.y + 200));
			rect_pt1.push_back(Point(pt1.x, pt1.y + 200));

			for (int i = 0; i < 4; i++)
			{
				line(image, rect_pt1[i], rect_pt1[(i + 1) % 4], Scalar(0, 0, 0), 1);
				cout << "rect_pt1[" + to_string(i) + "] = " << rect_pt1[i] << "\t" << endl;
			}
			imshow(title, image);
		
		}
		else {
			Point pt2 = Point(x, y);

			rect_pt1.push_back(Point(pt1.x, pt1.y));
			rect_pt1.push_back(Point(pt1.x + 200, pt1.y));
			rect_pt1.push_back(Point(pt1.x + 200, pt1.y + 200));
			rect_pt1.push_back(Point(pt1.x, pt1.y + 200));

			float degree = atan2f(pt2.y, pt2.x) - atan2f(pt1.y, pt1.x);

			Matx22f m(cos(degree), -sin(degree), sin(degree), cos(degree));
			transform(rect_pt1, rect_pt2, m);

			for (int i = 0; i < 4; i++)
			{
				line(image, rect_pt2[i], rect_pt2[(i + 1) % 4], Scalar(255, 0, 0), 2);
				cout << "rect_pt2[" + to_string(i) + "] = " << rect_pt2[i] << endl;
			}
			cout << endl << "라디안 = " << degree << endl;
			cout << "각도 = " << degree * 180 / CV_PI << endl;

			imshow(title, image);
			pt = Point(-1, -1);
		}
	}

}
int main()
{	
	image = Mat (400, 500, CV_8UC3, Scalar(255, 255, 255));
	imshow(title, image);
	setMouseCallback(title, onMouse, 0);

	waitKey(0);
	return 0;
}