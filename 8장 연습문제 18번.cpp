//���ϵ����ⰰ�� ��쿡�� [1, 0;  �� �̿��Ͽ� ���Ϸ� �������ְ�, �̹����� y���� ������ �ǹǷ� �̹����� �����ŭ y��ǥ�� �����̵� �����־���.
//						   0, -1]
//�¿�����ⰰ�� ��쿡�� [-1, 0; �� �̿��Ͽ� �¿�� �������ְ�, �̹����� x���� ������ �ǹǷ� �̹����� ������ŭ x��ǥ�� �����̵� �����־���.
//						   0, 1]
//�����¿������ ���� ��쿡�� [-1, 0; �� �̿��Ͽ� �����¿�� �������ְ�, �̹����� x��, y���� ������ �ǹǷ� �̹����� ����� ���� ��ŭ y��ǥ�� x��ǥ�� �����̵� �����־���.
//								0, -1]

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("../image/affine_test5.jpg", 0);
	CV_Assert(image.data);

	//warpAffine()�� �̿��Ͽ� �����⸦ �����Ͽ���
	
	Matx23d flip_map1(1, 0, 0, 0, -1, image.rows);//���ϵ�����, ���Ϸ� ������ �� �ִ� ����� �̿��ϰ�, image.rows��ŭ �����̵� ������
	Matx23d flip_map2(-1, 0, image.cols, 0, 1, 0);//�¿������, �¿�� ������ �� �ִ� ����� �̿��ϰ�, image.cols��ŭ �����̵� ������
	Matx23d flip_map3(-1, 0, image.cols, 0, -1, image.rows);//�����¿������, �����¿�� ������ �� �ִ� ����� �̿��ϰ�, (image.cols, image.rows)��ŭ �����̵� ������


	Mat dst1, dst2, dst3;
	warpAffine(image, dst1, flip_map1, image.size());//���ϵ�����
	warpAffine(image, dst2, flip_map2, image.size());//�¿������
	warpAffine(image, dst3, flip_map3, image.size());//�����¿������

	imshow("image", image);
	imshow("dst1 - ���ϵ�����", dst1);
	imshow("dst2 - �¿������", dst2);
	imshow("dst3 - �����¿������", dst3);
	waitKey();
	return 0;
}