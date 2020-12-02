//����_10.3.3�� ȭ��ǥŰ�� ���������� ���赥���͸� �Է¹��� �� �ֵ��� �ҽ��ڵ带 �����Ͻÿ�.

#include "kNN.hpp"

int main() {
	Size size(40, 40);
	int K = 15;
	int Nclass = 10;
	int Nsample = 20;

	string image_file = "../image/train_numbers.png";
	Mat train_image = imread(image_file, 0);
	CV_Assert(train_image.data);

	threshold(train_image, train_image, 32, 255, THRESH_BINARY);
	cout << train_image.size() << endl;
	Mat trainData, classLable;
	for (int i = 0, k = 0; i < Nclass; i++) {
		for (int j = 0; j < Nsample; j++, k++) {
			Point start(j * size.width, i * size.height);
			Rect roi(start, size);
			Mat part = train_image(roi);
			Mat num = find_number(part);
		
			Mat data = place_middle(num, size);
			trainData.push_back(data);
			classLable.push_back(i);
		}
	}
	Ptr<ml::KNearest> knn = ml::KNearest::create();
	knn->train(trainData, ml::ROW_SAMPLE, classLable);

	int no = 0;
	cout << "������, ���� ȭ��ǥ�� ���� �̵� ����" << endl;
	while (1) {
		cout << "���� ��ȣ: " << no << endl;
		string demo_file = format("../image/num%02d.png", no);
		Mat test_img = imread(demo_file, 0);
		CV_Assert(test_img.data);

		threshold(test_img, test_img, 128, 255, THRESH_BINARY);
		Mat num = find_number(test_img);
		Mat data = place_middle(num, size);

		Mat result;
		knn->findNearest(data, K, result);
		cout << "�з���� : " << result.at<float>(0, 0) << endl;
		imshow("test_img", test_img);
		waitKey();

		int key = waitKeyEx(0);
		if (key == 27) break;

		switch (key)
		{
		case 0x270000://������ ȭ��ǥŰ ������
			if (no%10 != 5) {//�׸��� ��ȣ�� 05, 15, 25, 35, 45,...,95�� �ƴϸ�
				no++;
			}
			else if(no != 95){//�׸��� ������ 5��° �����̰� 95�� ������ �ƴϸ�
				no += 5;
			}
			else {//95�� �����̸� 00������
				no = 0;
			}
		case 0x250000://���� ȭ��ǥŰ ������
			if (no%10 != 0) {//�׸��� ��ȣ�� 00,10,20,30,...,90�� �ƴϸ�
				no--;
			}
			else if(no != 0){//�׸��� ������ 0��° �����̰� 00�� ������ �ƴϸ�
				no -= 5;
			}
			else {//00�� �����̸� 95�� ��������
				no = 95;
			}

		}

	}
	return 0;
}
