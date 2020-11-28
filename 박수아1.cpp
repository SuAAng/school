//다음과 같이 컬러 입력 영상에 허프 변환 함수를 구현해서 직선을 검출하고, 하여 그리시오.
//거리간격 1픽셀, 각도간격 2도 지정
//직선 임계값 100화소 지정
//최대 10개 녹색 직선 표시, 직선 두께 2 지정

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void hough_coord(Mat image, Mat& acc_mat, double rho, double theta) {
	int acc_h = (image.rows + image.cols) * 2 / rho;
	int acc_w = CV_PI / theta;
	acc_mat = Mat(acc_h, acc_w, CV_32S, Scalar(0));

	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			Point pt(x, y);
			if (image.at<uchar>(pt) > 0) {
				for (int t = 0; t < acc_w; t++) {
					double radian = t * theta;
					float r = pt.x * cos(radian) + pt.y * sin(radian);
					r = cvRound(r / rho + acc_mat.rows / 2);
					acc_mat.at<int>(r, t)++;
				}
			}
		}
	}
}

void acc_mask(Mat acc_mat, Mat& acc_dst, Size size, int thresh) {
	acc_dst = Mat(acc_mat.size(), CV_32S, Scalar(0));
	Point h_m = size / 2;

	for (int r = h_m.y; r < acc_mat.rows - h_m.y; r++) {
		for (int t = h_m.x; t < acc_mat.cols - h_m.x; t++) {
			Point center = Point(t, r) - h_m;
			int c_value = acc_mat.at<int>(center);
			if (c_value >= thresh) {
				double maxVal = 0;
				for (int u = 0; u < size.height; u++) {
					for (int v = 0; v < size.width; v++) {
						Point start = center + Point(v, u);
						if (start != center && acc_mat.at<int>(start) > maxVal)
							maxVal = acc_mat.at<int>(start);
					}
				}
				Rect rect(center, size);
				if (c_value >= maxVal) {
					acc_dst.at<int>(center) = c_value;
					acc_mat(rect).setTo(0);
				}

			}

		}
	}
}
void sort_lines(Mat lines, vector<Vec2f>& s_lines) {
	Mat acc = lines.col(2), idx;
	sortIdx(acc, idx, SORT_EVERY_COLUMN + SORT_DESCENDING);

	for (int i = 0; i < idx.rows; i++) {
		int id = idx.at<int>(i);
		float rho = lines.at<float>(id, 0);
		float radian = lines.at<float>(id, 1);
		s_lines.push_back(Vec2f(rho, radian));

	}
}

void thres_lines(Mat acc_dst, Mat& lines, double _rho, double theta, int thresh) {
	for (int r = 0; r < acc_dst.rows; r++) {
		for (int t = 0; t < acc_dst.cols; t++) {
			float value = (float)acc_dst.at<int>(r, t);
			if (value >= thresh) {
				float rho = (float)((r - acc_dst.rows / 2) * _rho);
				float radian = (float)(t * theta);

				Matx13f line(rho, radian, value);
				lines.push_back((Mat)line);

			}
		}
	}
}
void houghLines(Mat src, vector<Vec2f>& s_lines, double rho, double theta, int thresh) {
	Mat acc_mat, acc_dst, lines;
	hough_coord(src, acc_mat, rho, theta);
	acc_mask(acc_mat, acc_dst, Size(3, 7), thresh);

	thres_lines(acc_dst, lines, rho, theta, thresh);
	sort_lines(lines, s_lines);
}
void draw_houghLines(Mat src, Mat image, vector<Vec2f> lines, int nline) {

	for (size_t i = 0; i < min((int)lines.size(), nline); i++) {
		float rho = lines[i][0], theta = lines[i][1];
		double a = cos(theta), b = sin(theta);
		Point2d pt(a * rho, b * rho);
		Point2d delta(1000 * -b, 1000 * a);
		line(image, pt + delta, pt - delta, Scalar(0, 255, 0), 2, LINE_AA);//녹색직선, 두께 2
	}
}

int main() {
	Mat image = imread("../image/hough_test.jpg",1);
	Mat gray_image;
	cvtColor(image, gray_image, COLOR_BGR2GRAY);

	CV_Assert(image.data);
	Mat canny;

	double rho = 1, theta = 2 * CV_PI / 180;//거리간격 1픽셀 각도간격 2도 지정
	GaussianBlur(gray_image, canny, Size(5, 5), 2, 2);
	Canny(canny, canny, 100, 150, 3);
	vector<Vec2f> lines;

	houghLines(canny, lines, rho, theta, 100);//직선 임계값 100화소
	draw_houghLines(canny, image, lines, 10);//직선개수 최대 10개


	imshow("컬러 입력 영상 - 허프 변환 함수", image);
	waitKey();

}