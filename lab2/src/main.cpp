#include <opencv2\highgui.hpp>
#include <iostream>
#include <opencv2\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

Mat difference(Mat img, Mat first_img) {
	Mat main_img = Mat::zeros(img.rows * 2, img.cols * 2, CV_8UC3);
	Mat empty_image = Mat::zeros(img.rows, img.cols, CV_8UC1);
	int from_to1[] = { 0,0, 1,1, 2,2 };
	Mat gray;
	Mat gray_first;
	vector<Mat> spl;
	split(img, spl);
	vector<Mat> spl_first;
	split(first_img, spl_first);

	Mat result_blue(img.rows, img.cols, CV_8UC3);
	Mat result_green(img.rows, img.cols, CV_8UC3);
	Mat result_red(img.rows, img.cols, CV_8UC3);

	Mat result_blue_first(img.rows, img.cols, CV_8UC3);
	Mat result_green_first(img.rows, img.cols, CV_8UC3);
	Mat result_red_first(img.rows, img.cols, CV_8UC3);

	Mat in3[] = { empty_image, empty_image, spl[2] };
	Mat in3_first[] = { empty_image, empty_image, spl_first[2] };
	mixChannels(in3, 3, &result_red, 1, from_to1, 3);
	mixChannels(in3_first, 3, &result_red_first, 1, from_to1, 3);
	Mat red_res = (result_red_first - result_red) * 30;
	red_res.copyTo(main_img(Rect(0, 0, img.cols, img.rows)));

	Mat in2[] = { empty_image, spl[1], empty_image };
	Mat in2_first[] = { empty_image, spl_first[1], empty_image };
	mixChannels(in2, 3, &result_green, 1, from_to1, 3);
	mixChannels(in2_first, 3, &result_green_first, 1, from_to1, 3);
	Mat green_res = (result_green_first - result_green) * 30;
	green_res.copyTo(main_img(Rect(img.cols, 0, img.cols, img.rows)));

	Mat in1[] = { spl[0], empty_image, empty_image };
	Mat in1_first[] = { spl_first[0], empty_image, empty_image };
	mixChannels(in1, 3, &result_blue, 1, from_to1, 3);
	mixChannels(in1_first, 3, &result_blue_first, 1, from_to1, 3);
	Mat blue_res = (result_blue_first - result_blue) * 30;
	blue_res.copyTo(main_img(Rect(0, img.rows, img.cols, img.rows)));

	cvtColor(img, gray, COLOR_BGR2GRAY);
	cvtColor(gray, gray, COLOR_GRAY2BGR);
	cvtColor(first_img, gray_first, COLOR_BGR2GRAY);
	cvtColor(gray_first, gray_first, COLOR_GRAY2BGR);
	Mat gray_res = (gray_first - gray) * 30;
	gray_res.copyTo(main_img(Rect(img.cols, img.rows, img.cols, img.rows)));

	return main_img;
}

int main() {
	Mat img = imread("cup.png");

	vector<int> params65;
	params65.push_back(IMWRITE_JPEG_QUALITY);
	params65.push_back(65);
	vector<int> params95;
	params95.push_back(IMWRITE_JPEG_QUALITY);
	params95.push_back(95);

	imwrite("cup65.jpg", img, params65);
	imwrite("cup95.jpg", img, params95);

	Mat img65 = imread("cup65.jpg");
	Mat img95 = imread("cup95.jpg");

	Mat newimg65 = difference(img65, img);
	Mat newimg95 = difference(img95, img);

	imshow("Difference 65", newimg65);
	imwrite("img_res_65.jpg", newimg65);

	imshow("Difference 95", newimg95);
	imwrite("img_res_95.jpg", newimg95);

	waitKey(0);
	return 0;
}
