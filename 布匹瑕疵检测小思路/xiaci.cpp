#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;
Mat src, gray_src, drawImg;
int threshold_v = 231;
int threshold_max = 255;
const char* output_win = "rectangle-demo";
const char* binary_win = "binary image";
RNG rng(12345);
void Contours_Callback(int, void*);
void cvtColor_src(Mat &src, Mat &dst);

int main(int argc, char** argv) {
	src = imread("test_img.jpg");


	cvtColor(src, gray_src, CV_BGR2GRAY);
	//cvtColor_src(src,gray_src);
	blur(gray_src, gray_src, Size(3, 3), Point(-1, -1));

	const char* source_win = "input image";
	namedWindow(source_win, 0);
	namedWindow(output_win, 0);
	imshow(source_win, src);

	createTrackbar("Threshold Value:", output_win, &threshold_v, threshold_max, Contours_Callback);
	Contours_Callback(0, 0);

	waitKey(0);
	return 0;
}

void cvtColor_src(Mat &src, Mat &src_gray)
{
	//  转换单通道
	if (src.channels() == 4) {
		cv::cvtColor(src, src_gray, CV_BGRA2GRAY);
	}
	else if (src.channels() == 3) {
		cv::cvtColor(src, src_gray, CV_BGR2GRAY);
	}
	else if (src.channels() == 2) {
		cv::cvtColor(src, src_gray, CV_BGR5652GRAY);
	}
	else if (src.channels() == 1) {// 单通道的图片直接就不需要处理
		src_gray = src;
	}
	else { // 负数,说明图有问题 直接返回	
		src_gray = src;
	}

}


void Contours_Callback(int, void*) {
	Mat binary_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	threshold(gray_src, binary_output, threshold_v, threshold_max, THRESH_BINARY);
	//膨胀再腐蚀
	Mat element = getStructuringElement(MORPH_RECT, Size(30, 30), Point(-1, -1)); //定义结构元素
	dilate(binary_output, binary_output, element);
	namedWindow("dilate", 0);
	imshow("dilate", binary_output);
	erode(binary_output, binary_output, element);
	namedWindow("erode", 0);
	imshow("erode", binary_output);

	namedWindow(binary_win, 0);
	imshow("binary image", binary_output);
	findContours(binary_output, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(-1, -1));

	vector<vector<Point>> contours_ploy(contours.size());
	vector<Rect> ploy_rects(contours.size());
	vector<Point2f> ccs(contours.size());
	vector<float> radius(contours.size());

	vector<RotatedRect> minRects(contours.size());
	vector<RotatedRect> myellipse(contours.size());

	for (size_t i = 0; i < contours.size(); i++) {
		try{
				approxPolyDP(Mat(contours[i]), contours_ploy[i], 10, true);
			}catch(cv::Exception& e) {
				printf("exception: %s\n",e.what());
			}

		ploy_rects[i] = boundingRect(contours_ploy[i]);
		//minEnclosingCircle(contours_ploy[i], ccs[i], radius[i]);
		//if (contours_ploy[i].size() > 5) {
		//	myellipse[i] = fitEllipse(contours_ploy[i]);
		//	minRects[i] = minAreaRect(contours_ploy[i]);
		//}
	}

	// draw it
	src.copyTo(drawImg);
	Point2f pts[4];
	for (size_t t = 0; t < contours.size(); t++) {
		//Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		rectangle(drawImg, ploy_rects[t], (0,255,255), 10, 8);
		//circle(drawImg, ccs[t], radius[t], color, 2, 8);
		//if (contours_ploy[t].size() > 5) {
		//	ellipse(drawImg, myellipse[t], color, 1, 8);
		//	minRects[t].points(pts);
		//	for (int r = 0; r < 4; r++) {
		//		line(drawImg, pts[r], pts[(r + 1) % 4], color, 1, 8);
		//	}
		//}
	}

	imshow(output_win, drawImg);
	return;
}