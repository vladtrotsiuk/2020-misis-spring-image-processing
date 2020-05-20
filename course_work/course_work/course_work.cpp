//импортируем необходимые библиотеки
#include <opencv2\highgui.hpp>
#include <iostream>
#include <opencv2\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <cmath>
#include "markup.cpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	String imname;
	cout << "Input image file name: ";
	cin >> imname;
	cout << "1 - home" << endl << "2 - search" << endl;
	cout << "3 - add photo" << endl << "4 - liked photos" << endl << "5 - My profile" << endl;
	cout << "Input pattern number(from 1 to 5): ";
	String tmpltname;
	cin >> tmpltname;
	//считываем изображения и шаблон, переводим их в серый цвет
	int flags = IMREAD_GRAYSCALE;
	Mat image = imread(imname);
	Mat gray;
	int elem;

	elem = stoi(tmpltname);
	while (elem < 1 || elem > 5) {
		cout << "Input number from 1 to 5: ";
		cin >> tmpltname;
		elem = stoi(tmpltname);
	}
	if (image.data == NULL)
	{
		printf("image cannot be loaded\n");
		return 1;
	}

	cvtColor(image, gray, cv::COLOR_BGR2GRAY);

	namedWindow("My");

	Mat result;
	//используем краевой детектор для выделения границ
	Canny(gray, gray, 50, 200);
	int h = gray.rows;
	int w = gray.cols;


	Mat tmplte = imread(tmpltname + ".png", flags);
	if (tmplte.data == NULL)
	{
		printf("pattern cannot be loaded\n");
		return 1;
	}
	int tw = tmplte.rows;
	int th = tmplte.cols;
	Canny(tmplte, tmplte, 50, 200);
	imshow("Template", tmplte);

	double found0 = 0;
	Point found1(0.0, 0.0);
	float found2 = 0.0;
	Mat resized;
	Mat edged;

	//запускаем цикл с различными размерами изображения
	for (long double i = 1; i > 0.1; i -= 0.2) {

		resize(image, resized, Size(w * i, h * i));
		float r = gray.cols / resized.cols;
		if ((resized.rows < th) || (resized.cols < tw)) {
			break;
		}
		Canny(resized, edged, 50, 200);
		matchTemplate(edged, tmplte, result, TM_CCOEFF_NORMED);

		double minVal;
		double maxVal;
		Point minIdx;
		Point maxIdx;
		//смотрим, нашли ли хороший шаблон, если да, то 
		minMaxLoc(result, &minVal, &maxVal, &minIdx, &maxIdx);
		if (found0 < maxVal) {
			found0 = maxVal;
			found1 = maxIdx;
			found2 = r;
		}

	}


	int startX = found1.x * found2;
	int startY = found1.y * found2;

	int endX = (found1.x + th) * found2;
	int endY = (found1.y + tw) * found2;
	Point pt1(startX, startY);
	Point pt2(endX, endY);
	//строим прямоугольник вокруг шаблона
	rectangle(image, pt1, pt2, (0, 0, 255), 4);
	//проверяем, находится ли прямоугольник в нужном участке разметки
	markup(image, elem, pt1, pt2);

	imshow("My", image);
	waitKey(0);

	return 0;
}