#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main() {
	Matx<ushort, 5, 4> pts;
	Mat_<int> sizes, sort_idx;
	vector<Rect> rects;
	randn(pts, Scalar(200), Scalar(100));

	for (int i = 0; i < pts.rows; i++) {//임의 사각형 생성
		Point pt1(pts(i, 0), pts(i, 1));
		Point pt2(pts(i, 2), pts(i, 3));
		rects.push_back(Rect(pt1, pt2));
		sizes.push_back(rects[i].area());
	}

	sortIdx(sizes, sort_idx, SORT_EVERY_COLUMN);

	cout << endl << "\t사각형 정보 \t\t 크기(오름차순)" << endl << endl;
	for (int i = 0; i < rects.size(); i++) {
		int idx = sort_idx(i);
		cout << rects[idx] << "\t" << sizes(idx) << endl;
	}

	return 0;
}