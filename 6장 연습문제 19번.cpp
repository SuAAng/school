//calcHisto()�� �̿��Ͽ� ������׷��� ����� ���� 1������ �ƴ� 2�������� ����ϵ��� ä�� ����̳� ������ �����Ѵ�.
//���� ä���� ȭ�� ������ 0~180�̰�, ä�� ä�� ������ 0~256�̴�. ��� ������ ������ 30��, ä���� 42���� �����Ѵ�.
//���� ������׷��� draw_histo()�� �̿��Ͽ� ��ķ� ��Ÿ����. �׸� ���� ����� ���� ��ġ�� �ش��ϴ� ä����, ����, �󵵰��� ���� ���� ǥ���Ѵ�.
//������ ���� �׸��� ���ÿ� ���� ����ϱ� ���ؼ� ����� ������ Ÿ�԰� ũ�⸦ �������ش�.

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


void calc_Histo(const Mat& image, Mat& hist, Vec3i bins, Vec3f range) {
	int dims = 2; //������׷� ������ (2����)
	int channels[] = { 0, 1 };//ä�� ��� (���� ä��)
	int histSize[] = { bins[0], bins[1]};//������׷� ��� ���� (���� 30��, ä�� 42��)

	float range1[] = { 0, range[0] };//���� ä�� ȭ�� ����
	float range2[] = { 0, range[1] };//ä�� ä�� ȭ�� ����
	
	const float* ranges[] = { range1, range2};//����, ä�� ä�� ȭ�ҹ���

	calcHist(&image, 1, channels, Mat(), hist, dims, histSize, ranges);
	
}

void draw_histo(Mat hist, Mat &hist_img) 
{
	normalize(hist, hist, 0, 1, NORM_MINMAX);//�ּڰ��� 0�̰� �ִ��� 1�� �ǵ��� �󵵃� ���� (����ȭ)
	float ratio_value = 512.f; //�ֵ� ���� ������ ����
	float ratio_hue = 180.f / hist.rows; // ���� ���� ������ ����
	float ratio_sat = 256.f / hist.cols; // ä�� ���� ������ ����

	hist_img = Mat(hist.size(), CV_32FC3);//2���� ������׷� ��� ���

	for (int i = 0; i < hist.rows; i++) {
		for (int j = 0; j < hist.cols; j++) {
			float value = hist.at<float>(i, j) * ratio_value; //�󵵰�
			float hue = i * ratio_hue; //����
			float sat = j * ratio_sat; //ä����
			hist_img.at<Vec3f>(i, j) = Vec3f(hue, sat, value);

		}
	}

	hist_img.convertTo(hist_img, CV_8U);//������ Ÿ�� ����
	cvtColor(hist_img, hist_img, COLOR_HSV2BGR); //HSV -> BGR �÷���ȯ
	resize(hist_img, hist_img, Size(0, 0), 10, 10, INTER_NEAREST); //�׷��� ũ�� ����

}

int main()
{
	Mat image = imread("../image/hue.jpg", IMREAD_COLOR);
	CV_Assert(image.data);

	Mat hsv, hist, hist_img;
	Vec3i bins(30, 42);//������׷� ��� ����
	Vec3f ranges(180, 256);//ä���� ȭ�� ����

	cvtColor(image, hsv, COLOR_BGR2HSV);//BGR -> HSV
	calc_Histo(hsv, hist, bins, ranges);//������׷� ���
	draw_histo(hist, hist_img);//�׷��� �׸���
	
	imshow("image", image);
	imshow("hist_img", hist_img);
	waitKey();
	return 0;


}