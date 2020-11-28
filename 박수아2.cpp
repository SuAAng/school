//10.1.6절에서 sort_lines() 함수는 중복이 제거된 허프 누적 행렬에서 임계값보다 큰 누적값들을 선별한 후에 이 값들을 내림차순으로 정렬한다.
//이 함수를 cv::sortIdx()함수를 사용하지 않고 직접 정렬 알고리즘으로 구현하시오(2가지 이상의 정렬 알고리즘을 구현하시오)

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

//원본
void sort_lines(Mat lines, vector<Vec2f>& s_lines) {
	Mat acc = lines.col(2), idx;
	sortIdx(acc, idx, SORT_EVERY_COLUMN + SORT_DESCENDING);

	cout << "sortIdx 사용" << endl << idx << endl<<endl;

	for (int i = 0; i < idx.rows; i++) {
		int id = idx.at<int>(i);
		float rho = lines.at<float>(id, 0);
		float radian = lines.at<float>(id, 1);
		s_lines.push_back(Vec2f(rho, radian));

	}
}

//삽입정렬
Mat insertion_sort(Mat acc) {
	Mat acc_copy = acc.clone();
	Mat idx(acc.size(), acc.type());
	for (int i = 0; i < idx.rows; i++) {//index 지정
		for (int j = 0; j < idx.cols; j++) {
			idx.at<int>(i, j) = i;
		}
	}
	//acc같은 경우 열수가 1개지만 행렬의 개수 상관없이 만들기 위해 반복문 2개 사용
	for (int i = 0; i < acc_copy.cols; i++) {//acc의 열의 개수만큼 반복문 돌림
		for (int j = 1; j < acc_copy.rows; j++) {//acc의 행의 개수만큼 반복문 돌림
			for (int a = j - 1; a >= 0; a--) {//a는 현재 값과 비교할 행
				if (acc_copy.at<int>(a, i) >= acc_copy.at<int>(j, i)) {//현재 값이 비교하는 값보다 작거나 같을 때  비교하는 값과 현재값 사이의 값들의 위치를 바꿈
					if (a + 1 == j) {
						break;
					}
					else {
						int change = acc_copy.at<int>(j, i);//값
						int change_idx = idx.at<int>(j, i);//인덱스 값
						for (int b = j - 1; b > a; b--) {//값이 큰 값 다음의 값부터 밀림.
							acc_copy.at<int>(b + 1, i) = acc_copy.at<int>(b, i);
							idx.at<int>(b + 1, i) = idx.at<int>(b, i);//index 변경.
						}
						acc_copy.at<int>(a + 1, i) = change;
						idx.at<int>(a + 1, i) = change_idx;
						break;
					}
				}
				else if (a == 0 && acc_copy.at<int>(a, i) < acc_copy.at<int>(j, i)) {//자신의 위치부터 처음 위치까지 돌려봤을 때 자신의 값보다 큰 값이 없을 때
					int change = acc_copy.at<int>(j, i);//값
					int change_idx = idx.at<int>(j, i);//인덱스 값
					for (int b = j - 1; b >= a; b--) {//첫 값부터 현재 위치까지 밀려서 저장됨 
						acc_copy.at<int>(b + 1, i) = acc_copy.at<int>(b, i);
						idx.at<int>(b + 1, i) = idx.at<int>(b, i);//index 변경.
					}
					acc_copy.at<int>(a, i) = change;
					idx.at<int>(a, i) = change_idx;
					break;
				}
			}
		}
	}
	return idx;
}
//선택정렬
Mat selection_sort(Mat acc) {
	Mat acc_copy = acc.clone();
	Mat idx(acc.size(), acc.type());

	for (int i = 0; i < idx.rows; i++) {//index 지정
		for (int j = 0; j < idx.cols; j++) {
			idx.at<int>(i, j) = i;
		}
	}

	//acc같은 경우 열수가 1개지만 행렬의 개수 상관없이 만들기 위해 반복문 2개 사용
	for (int i = 0; i < acc_copy.cols; i++) {//acc의 열의 개수만큼 반복문 돌림
		for (int j = 0; j < acc_copy.rows; j++) {//acc의 행의 개수만큼 반복문 돌림
			int choice = acc_copy.at<int>(j, i);
			int choice_idx = idx.at<int>(j, i);
			int index = j;
			for (int now = j; now < acc_copy.rows; now++) {
				if (choice < acc_copy.at<int>(now, i)) {
					choice = acc_copy.at<int>(now, i);
					choice_idx = idx.at<int>(now, i);
					index = now;
				}
			}
			acc_copy.at<int>(index, i) = acc_copy.at<int>(j, i);
			acc_copy.at<int>(j, i) = choice;
			idx.at<int>(index, i) = idx.at<int>(j, i);
			idx.at<int>(j, i) = choice_idx;
		}

	}





	return idx;
}
//삽입정렬
void insertion_sort_lines(Mat lines, vector<Vec2f>& s_lines) {
	Mat acc = lines.col(2), idx;

	idx = insertion_sort(acc);

	cout << "삽입정렬 사용" << endl << idx << endl<<endl;
	for (int i = 0; i < idx.rows; i++) {
		int id = idx.at<int>(i);
		float rho = lines.at<float>(id, 0);
		float radian = lines.at<float>(id, 1);
		s_lines.push_back(Vec2f(rho, radian));

	}
}
//선택정렬
void selection_sort_lines(Mat lines, vector<Vec2f>& s_lines) {
	Mat acc = lines.col(2), idx;

	idx = selection_sort(acc);

	cout << "선택정렬 사용" <<endl<< idx << endl<<endl;
	for (int i = 0; i < idx.rows; i++) {
		int id = idx.at<int>(i);
		float rho = lines.at<float>(id, 0);
		float radian = lines.at<float>(id, 1);
		s_lines.push_back(Vec2f(rho, radian));

	}
}

int main() {
	int data[] = {
		13,26,35,12,32,
		27,24,33,22,13,
		24,53,25,17,455,
		452,2,6,72,35,
		19,20,42,51,15
	};

	Mat lines(5,5, CV_32S, data);
	vector<Vec2f> s_lines;

	cout << "lines= " << endl<< lines << endl<<endl; //lines에 들어간 데이터

	sort_lines(lines, s_lines);//sortIdx 함수 사용
	insertion_sort_lines(lines, s_lines); //삽입정렬
	selection_sort_lines(lines, s_lines); //선택정렬


}