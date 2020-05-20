#pragma once

using namespace cv;
void markup(Mat image, int elem, Point pt1, Point pt2) {
	int pl = image.cols / 5;
	int pw = image.rows;
	//отступ немного больше для изображений, у которых есть меню телефона под приложением инстаграм
	Point pt3((elem - 1) * pl + 1, pw - 145);
	Point pt4((elem - 1) * pl + 1, pw);
	Point pt5((elem - 1) * pl + 1, pw - 145);
	Point pt6(elem * pl + 1, pw - 145);
	Point pt7(elem * pl + 1, pw - 145);
	Point pt8(elem * pl + 1, pw);
	line(image, pt3, pt4, (0, 0, 255), 2);
	line(image, pt5, pt6, (0, 0, 255), 2);
	line(image, pt7, pt8, (0, 0, 255), 2);
	if (pt1.x > pt3.x && pt1.x < pt7.x && pt1.y > pt5.y && pt1.y<1300 && abs(pt1.x - pt2.x)>pl / 4 && abs(pt1.y - pt2.y) > pl / 4) {
		std::cout << "pattern found";
	}
	else {
		std::cout << "pattern not found" << std::endl;
	}
}
