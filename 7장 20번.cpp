//��ȭ����_7.4.4�� Ű����κ��� ���������� ��ȣ�� �Է¹޾Ƽ� ���� ������ �����Ѵ�. 
//�� ������ ���ʰ� �Ʒ��� ȭ��ǥ Ű�� �̿��ؼ� ���� ������ �ε��ϴ� �Ͽ� �����ϸ�, ESC Ű�� ������ �����ϵ��� �����Ͻÿ�.

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


int main()
{
	while (1)
	{
		int no;
		cout << "���� ���� ��ȣ( 0:���� ) : ";
		cin >> no;
		if (no == 0)	break;

		string fname = format("../test_car/%02d.jpg", no);
		Mat image = imread(fname, 1);

		if (image.empty()) {
			cout << to_string(no) + "�� ���� ������ �����ϴ�. " << endl;
			continue;
		}

		Mat gray, sobel, th_img, morph;
		Mat kernel(5, 25, CV_8UC1, Scalar(1));
		cvtColor(image, gray, COLOR_BGR2GRAY);
		blur(gray, gray, Size(5, 5));
		Sobel(gray, gray, CV_8U, 1, 0, 3);

		threshold(gray, th_img, 120, 255, THRESH_BINARY);
		morphologyEx(th_img, morph, MORPH_CLOSE, kernel);

		imshow("image", image);//�⺻ �̹��� ����
		cout << to_string(no) + "�� ���� ������ �������ϴ�." << endl;
		
		int num = 1;

		while (1) {
			int key = waitKeyEx(0);
			if (key == 27) { cout << to_string(no) + "�� ���� ���� ������ ����˴ϴ�." << endl;	break; }

			switch (key)
			{
			case 0x260000:// ������ Ű ������
				if (num == 1) {
					imshow("image", morph);
					num = 3;
					cout << "���� ����" << endl;
				}
				else if (num == 2) {
					imshow("image", image);
					num = 1;
					cout << "�⺻ �̹���" << endl;

				}
				else if (num == 3) {
					imshow("image", th_img);
					num = 2;
					cout << "���� ����" << endl;
				}
				break;
			
			case 0x280000://�Ʒ����� Ű ������
				if (num == 1) {
					imshow("image", th_img);
					num = 2;
					cout << "���� ����" << endl;

				}
				else if (num == 2) {
					imshow("image", morph);
					num = 3;
					cout << "���� ����" << endl;

				}
				else if (num == 3) {
					imshow("image", image);
					num = 1;
					cout << "�⺻ �̹���" << endl;
				}
				break;
		
			}
		}	
	}
	return 0;
}