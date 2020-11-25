//13. ���ļ� ���� ���͸����� �߰� ���ļ� �뿪���� �����Ű���� ���͸� �����ؼ� ���͸��� �����ϴ� ���α׷��� �ۼ��Ͻÿ�.
//14. 13�� ������ �� ���� Ʈ���ٸ� �̿��ؼ� �߰� ���ļ� �뿪�� ������ �� �ֵ��� ���α׷��� �ۼ��Ͻÿ�.
//13�� ������ �ذ��ϱ� ���ؼ� �߰� ���ļ� �뿪���� �����Ű�� ���͸� �����ؾ��Ѵ�. 
//get_middlepassFilter�Լ��� �ۼ��Ͽ��µ�, ���� ó���� ���� 0���� �����ϰ�, 
//������ ������ �����Ű�� ���ϵ��� ���Ϳ� ���� 1�� ���� �����ϰ�, �����ĸ� �������� �����Ű�� ���ϵ��� ���� 0�� ���� ���Ϳ� �����Ͽ���.

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
Mat image = imread("../image/filter_test.jpg", 0);
int radius[2] = { 20,50 };

//���ø�
void shuffling(Mat mag_img, Mat& dst) {
	int cx = mag_img.cols / 2;
	int cy = mag_img.rows / 2;
	Rect q1(cx, 0, cx, cy);//1��и� �簢��
	Rect q2(0, 0, cx, cy);//2��и� �簢��
	Rect q3(0, cy, cx, cy);//3��и� �簢��
	Rect q4(cx, cy, cx, cy);//4��и� �簢��

	dst = Mat(mag_img.size(), mag_img.type());

	//������ ��и� ����
	mag_img(q1).copyTo(dst(q3));
	mag_img(q3).copyTo(dst(q1));
	mag_img(q2).copyTo(dst(q4));
	mag_img(q4).copyTo(dst(q2));
}
//ä�� �и� �� ũ�� ���
void log_mag(Mat complex_mat, Mat& dst) {
	Mat planes[2];
	split(complex_mat, planes); //2ä�� ���� ��� �и�
	magnitude(planes[0], planes[1], dst);//ũ�� ���
	log(dst + 1, dst);
	normalize(dst, dst, 0, 255, NORM_MINMAX);//����ȭ ����
	dst.convertTo(dst, CV_8U);
}
//������
Mat zeropadding(Mat img) {
	int m = 1 << (int)ceil(log2(img.rows));//2�� �ڽ� ���
	int n = 1 << (int)ceil(log2(img.cols));
	Mat dst(m, n, img.type(), Scalar(0));

	Rect rect(Point(0, 0), img.size());//���� ����ũ�� ���ɿ���
	img.copyTo(dst(rect));//���������� ��
	dst.convertTo(dst, CV_32F);

	return dst;
}
//�߰����� ��� ���� ���� �Լ�
Mat get_middlepassFilter(Size size, int min_radius, int max_radius) {
	Point center = size / 2;
	Mat filter(size, CV_32FC2, Vec2f(0, 0));//���� ���̽� 0��
	circle(filter, center, max_radius, Vec2f(1, 1), -1);//������ ���� ��� ���ϴ� �� - 1�� ���Ϳ� ����
	circle(filter, center, min_radius, Vec2f(0, 0), -1);//������ ���� ��� ���ϴ� �� - 0�� ���Ϳ� ����

	return filter;
}
//FFT ��ü ���� ���� �Լ�
void FFT(Mat image, Mat& dft_coef, Mat& dft_img) {
	Mat complex_img;
	Mat pad_img = zeropadding(image);//������
	Mat tmp[] = { pad_img, Mat::zeros(pad_img.size(), pad_img.type()) };
	merge(tmp, 2, complex_img);//���� ��� ����
	dft(complex_img, dft_coef, 0);//FFT�Լ�
	shuffling(dft_coef, dft_coef);//���ø�
	log_mag(dft_coef, dft_img);//���ļ� ����Ʈ�� ����
}
//IFFT ��ü ���� ���� �Լ�
Mat IFFT(Mat dft_coef, Size size) {
	Mat idft_coef, idft_img[2];
	shuffling(dft_coef, dft_coef);//�� ���ø� ����
	dft(dft_coef, idft_coef, DFT_INVERSE + DFT_SCALE);
	split(idft_coef, idft_img);//���� ��� �и�

	Rect img_rect(Point(0, 0), size);//�Է¿��� ũ�� �簢��
	idft_img[0](img_rect).convertTo(idft_img[0], CV_8U);//������ �κ� ����
	return idft_img[0];
}

void onChange(int value, void* userdata) {
	Mat dft_coef, dft_img, middle_dft, filtered_mat;
	FFT(image, dft_coef, dft_img);//FFT ���� �� ���ø�
	Mat middle_filter = get_middlepassFilter(dft_coef.size(), radius[0], radius[1]); //min_radius�� max_radius�� �߰����� ������ ����
	multiply(dft_coef, middle_filter, filtered_mat);//���͸� - ���� �� ����
	log_mag(filtered_mat, middle_dft);//���ļ� ����Ʈ�� ����
	imshow("middle_dft", middle_dft);
	imshow("middlepassed_img", IFFT(filtered_mat, image.size()));
}

int main() {
	
	CV_Assert(image.data);

	namedWindow("middlepassed_img", WINDOW_AUTOSIZE);
	createTrackbar("������1", "middlepassed_img", &radius[0], min(image.rows, image.cols)/2, onChange);//�����ĸ� �����Ű�� ���ϴ� ���� �������� ���� �����ϴ� Ʈ����
	createTrackbar("������2", "middlepassed_img", &radius[1], min(image.rows, image.cols)/2, onChange);//�����ĸ� �����Ű�� ���ϴ� ���� �������� ���� �����ϴ� Ʈ����
	onChange(0, 0);

	imshow("image", image);
	waitKey();
	return 0;
}