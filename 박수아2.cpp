//10.1.6������ sort_lines() �Լ��� �ߺ��� ���ŵ� ���� ���� ��Ŀ��� �Ӱ谪���� ū ���������� ������ �Ŀ� �� ������ ������������ �����Ѵ�.
//�� �Լ��� cv::sortIdx()�Լ��� ������� �ʰ� ���� ���� �˰������� �����Ͻÿ�(2���� �̻��� ���� �˰����� �����Ͻÿ�)

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

//����
void sort_lines(Mat lines, vector<Vec2f>& s_lines) {
	Mat acc = lines.col(2), idx;
	sortIdx(acc, idx, SORT_EVERY_COLUMN + SORT_DESCENDING);

	cout << "sortIdx ���" << endl << idx << endl<<endl;

	for (int i = 0; i < idx.rows; i++) {
		int id = idx.at<int>(i);
		float rho = lines.at<float>(id, 0);
		float radian = lines.at<float>(id, 1);
		s_lines.push_back(Vec2f(rho, radian));

	}
}

//��������
Mat insertion_sort(Mat acc) {
	Mat acc_copy = acc.clone();
	Mat idx(acc.size(), acc.type());
	for (int i = 0; i < idx.rows; i++) {//index ����
		for (int j = 0; j < idx.cols; j++) {
			idx.at<int>(i, j) = i;
		}
	}
	//acc���� ��� ������ 1������ ����� ���� ������� ����� ���� �ݺ��� 2�� ���
	for (int i = 0; i < acc_copy.cols; i++) {//acc�� ���� ������ŭ �ݺ��� ����
		for (int j = 1; j < acc_copy.rows; j++) {//acc�� ���� ������ŭ �ݺ��� ����
			for (int a = j - 1; a >= 0; a--) {//a�� ���� ���� ���� ��
				if (acc_copy.at<int>(a, i) >= acc_copy.at<int>(j, i)) {//���� ���� ���ϴ� ������ �۰ų� ���� ��  ���ϴ� ���� ���簪 ������ ������ ��ġ�� �ٲ�
					if (a + 1 == j) {
						break;
					}
					else {
						int change = acc_copy.at<int>(j, i);//��
						int change_idx = idx.at<int>(j, i);//�ε��� ��
						for (int b = j - 1; b > a; b--) {//���� ū �� ������ ������ �и�.
							acc_copy.at<int>(b + 1, i) = acc_copy.at<int>(b, i);
							idx.at<int>(b + 1, i) = idx.at<int>(b, i);//index ����.
						}
						acc_copy.at<int>(a + 1, i) = change;
						idx.at<int>(a + 1, i) = change_idx;
						break;
					}
				}
				else if (a == 0 && acc_copy.at<int>(a, i) < acc_copy.at<int>(j, i)) {//�ڽ��� ��ġ���� ó�� ��ġ���� �������� �� �ڽ��� ������ ū ���� ���� ��
					int change = acc_copy.at<int>(j, i);//��
					int change_idx = idx.at<int>(j, i);//�ε��� ��
					for (int b = j - 1; b >= a; b--) {//ù ������ ���� ��ġ���� �з��� ����� 
						acc_copy.at<int>(b + 1, i) = acc_copy.at<int>(b, i);
						idx.at<int>(b + 1, i) = idx.at<int>(b, i);//index ����.
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
//��������
Mat selection_sort(Mat acc) {
	Mat acc_copy = acc.clone();
	Mat idx(acc.size(), acc.type());

	for (int i = 0; i < idx.rows; i++) {//index ����
		for (int j = 0; j < idx.cols; j++) {
			idx.at<int>(i, j) = i;
		}
	}

	//acc���� ��� ������ 1������ ����� ���� ������� ����� ���� �ݺ��� 2�� ���
	for (int i = 0; i < acc_copy.cols; i++) {//acc�� ���� ������ŭ �ݺ��� ����
		for (int j = 0; j < acc_copy.rows; j++) {//acc�� ���� ������ŭ �ݺ��� ����
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
//��������
void insertion_sort_lines(Mat lines, vector<Vec2f>& s_lines) {
	Mat acc = lines.col(2), idx;

	idx = insertion_sort(acc);

	cout << "�������� ���" << endl << idx << endl<<endl;
	for (int i = 0; i < idx.rows; i++) {
		int id = idx.at<int>(i);
		float rho = lines.at<float>(id, 0);
		float radian = lines.at<float>(id, 1);
		s_lines.push_back(Vec2f(rho, radian));

	}
}
//��������
void selection_sort_lines(Mat lines, vector<Vec2f>& s_lines) {
	Mat acc = lines.col(2), idx;

	idx = selection_sort(acc);

	cout << "�������� ���" <<endl<< idx << endl<<endl;
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

	cout << "lines= " << endl<< lines << endl<<endl; //lines�� �� ������

	sort_lines(lines, s_lines);//sortIdx �Լ� ���
	insertion_sort_lines(lines, s_lines); //��������
	selection_sort_lines(lines, s_lines); //��������


}