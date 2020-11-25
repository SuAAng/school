//상하뒤집기같은 경우에는 [1, 0;  를 이용하여 상하로 뒤집어주고, 이미지의 y축이 음수가 되므로 이미지의 행수만큼 y좌표를 평행이동 시켜주었다.
//						   0, -1]
//좌우뒤집기같은 경우에는 [-1, 0; 를 이용하여 좌우로 뒤집어주고, 이미지의 x축이 음수가 되므로 이미지의 열수만큼 x좌표를 평행이동 시켜주었다.
//						   0, 1]
//상하좌우뒤집기 같은 경우에는 [-1, 0; 를 이용하여 상하좌우로 뒤집어주고, 이미지의 x축, y축이 음수가 되므로 이미지의 행수와 열수 만큼 y좌표와 x좌표를 평행이동 시켜주었다.
//								0, -1]

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("../image/affine_test5.jpg", 0);
	CV_Assert(image.data);

	//warpAffine()를 이용하여 뒤집기를 수행하여라
	
	Matx23d flip_map1(1, 0, 0, 0, -1, image.rows);//상하뒤집기, 상하로 뒤집을 수 있는 행렬을 이용하고, image.rows만큼 평행이동 시켜줌
	Matx23d flip_map2(-1, 0, image.cols, 0, 1, 0);//좌우뒤집기, 좌우로 뒤집을 수 있는 행렬을 이용하고, image.cols만큼 평행이동 시켜줌
	Matx23d flip_map3(-1, 0, image.cols, 0, -1, image.rows);//상하좌우뒤집기, 상하좌우로 뒤집을 수 있는 행렬을 이용하고, (image.cols, image.rows)만큼 평행이동 시켜줌


	Mat dst1, dst2, dst3;
	warpAffine(image, dst1, flip_map1, image.size());//상하뒤집기
	warpAffine(image, dst2, flip_map2, image.size());//좌우뒤집기
	warpAffine(image, dst3, flip_map3, image.size());//상하좌우뒤집기

	imshow("image", image);
	imshow("dst1 - 상하뒤집기", dst1);
	imshow("dst2 - 좌우뒤집기", dst2);
	imshow("dst3 - 상하좌우뒤집기", dst3);
	waitKey();
	return 0;
}