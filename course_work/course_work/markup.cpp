#include <opencv2\highgui.hpp>
#include <iostream>
#include <opencv2\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <cmath>
#include <fstream>

using namespace cv;
using namespace std;

void markup(Mat image, int elem, Point pt1, Point pt2) {
	int pl = image.cols / 5;
	int pw = image.rows;
	Point pt3((elem - 1) * pl + 1, pw - 145);
	Point pt4((elem - 1) * pl + 1, pw);
	Point pt5((elem - 1) * pl + 1, pw - 145);
	Point pt6(elem * pl + 1, pw - 145);
	Point pt7(elem * pl + 1, pw - 145);
	Point pt8(elem * pl + 1, pw);
	//line(image, pt3, pt4, (0, 0, 255), 2);
	//line(image, pt5, pt6, (0, 0, 255), 2);
	//line(image, pt7, pt8, (0, 0, 255), 2);
	if (pt1.x > pt3.x && pt1.x < pt7.x && pt1.y > pt5.y && pt1.y<1300 && abs(pt1.x - pt2.x)>pl / 4 && abs(pt1.y - pt2.y) > pl / 4) {
		cout << "pattern found correctly";
	}
	else {
		cout << "wrong pattern found" << std::endl;
	}
}

int main(int argc, char* argv[])
{
	string imname;
	char buff[50];
	cout << "Input image file name: ";
	cin >> imname;
	Mat image = imread(imname);
	//setlocale(LC_ALL, "rus"); 

	ifstream fin(imname.substr(0, imname.length() - 4) + "_info.txt");

	fin.getline(buff, 50);
	int elem = stoi(buff);
	fin.getline(buff, 50);
	int x1 = stoi(buff);
	fin.getline(buff, 50);
	int y1 = stoi(buff);
	Point pt1(x1, y1);
	fin.getline(buff, 50);
	int x2 = stoi(buff);
	fin.getline(buff, 50);
	int y2 = stoi(buff);
	Point pt2(x2, y2);

	markup(image, elem, pt1, pt2);

	fin.close();

	waitKey(0);

	return 0;

}
