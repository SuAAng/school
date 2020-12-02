//예제_10.3.3을 화살표키로 연속적으로 실험데이터를 입력받을 수 있도록 소스코드를 수정하시오.

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
	cout << "오른쪽, 왼쪽 화살표로 영상 이동 가능" << endl;
	while (1) {
		cout << "영상 번호: " << no << endl;
		string demo_file = format("../image/num%02d.png", no);
		Mat test_img = imread(demo_file, 0);
		CV_Assert(test_img.data);

		threshold(test_img, test_img, 128, 255, THRESH_BINARY);
		Mat num = find_number(test_img);
		Mat data = place_middle(num, size);

		Mat result;
		knn->findNearest(data, K, result);
		cout << "분류결과 : " << result.at<float>(0, 0) << endl;
		imshow("test_img", test_img);
		waitKey();

		int key = waitKeyEx(0);
		if (key == 27) break;

		switch (key)
		{
		case 0x270000://오른쪽 화살표키 누르기
			if (no%10 != 5) {//그림의 번호가 05, 15, 25, 35, 45,...,95가 아니면
				no++;
			}
			else if(no != 95){//그림이 각각의 5번째 영상이고 95번 영상이 아니면
				no += 5;
			}
			else {//95번 영상이면 00번으로
				no = 0;
			}
		case 0x250000://왼쪽 화살표키 누르기
			if (no%10 != 0) {//그림의 번호가 00,10,20,30,...,90가 아니면
				no--;
			}
			else if(no != 0){//그림이 각각의 0번째 영상이고 00번 영상이 아니면
				no -= 5;
			}
			else {//00번 영상이면 95번 영상으로
				no = 95;
			}

		}

	}
	return 0;
}
