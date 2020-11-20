//심화예제_7.4.4는 키보드로부터 영상파일의 번호를 입력받아서 열림 연산을 수행한다. 
//이 예제를 윗쪽과 아래쪽 화살표 키를 이용해서 다음 영상을 로드하는 하여 수행하며, ESC 키를 누르면 종료하도록 수정하시오.

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


int main()
{
	while (1)
	{
		int no;
		cout << "차량 영상 번호( 0:종료 ) : ";
		cin >> no;
		if (no == 0)	break;

		string fname = format("../test_car/%02d.jpg", no);
		Mat image = imread(fname, 1);

		if (image.empty()) {
			cout << to_string(no) + "번 영상 파일이 없습니다. " << endl;
			continue;
		}

		Mat gray, sobel, th_img, morph;
		Mat kernel(5, 25, CV_8UC1, Scalar(1));
		cvtColor(image, gray, COLOR_BGR2GRAY);
		blur(gray, gray, Size(5, 5));
		Sobel(gray, gray, CV_8U, 1, 0, 3);

		threshold(gray, th_img, 120, 255, THRESH_BINARY);
		morphologyEx(th_img, morph, MORPH_CLOSE, kernel);

		imshow("image", image);//기본 이미지 띄우기
		cout << to_string(no) + "번 영상 파일을 열었습니다." << endl;
		
		int num = 1;

		while (1) {
			int key = waitKeyEx(0);
			if (key == 27) { cout << to_string(no) + "번 영상 파일 열람을 종료됩니다." << endl;	break; }

			switch (key)
			{
			case 0x260000:// 윗방향 키 누르기
				if (num == 1) {
					imshow("image", morph);
					num = 3;
					cout << "열림 연산" << endl;
				}
				else if (num == 2) {
					imshow("image", image);
					num = 1;
					cout << "기본 이미지" << endl;

				}
				else if (num == 3) {
					imshow("image", th_img);
					num = 2;
					cout << "이진 연산" << endl;
				}
				break;
			
			case 0x280000://아랫방향 키 누르기
				if (num == 1) {
					imshow("image", th_img);
					num = 2;
					cout << "이진 연산" << endl;

				}
				else if (num == 2) {
					imshow("image", morph);
					num = 3;
					cout << "열림 연산" << endl;

				}
				else if (num == 3) {
					imshow("image", image);
					num = 1;
					cout << "기본 이미지" << endl;
				}
				break;
		
			}
		}	
	}
	return 0;
}