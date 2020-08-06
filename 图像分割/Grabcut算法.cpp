#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void MyShowImage(Mat Image, const string winName)
{
	imshow(winName, Image);
}
void getBinMask(const Mat& comMask, Mat& binMask)
{
	binMask.create(comMask.size(), CV_8UC1);
	binMask = comMask & 1;
}

int main(int argc, char** argv)
{
	Mat image = imread("lena.jpg", 1);
	const string winName = "image";
	MyShowImage(image, winName);

	Mat bg; Mat fg;
	Rect rect = Rect(47, 48, 408, 464);
	Mat mask, res;
	mask.create(image.size(), CV_8UC1);
	grabCut(image, mask, rect, bg, fg, 1, 0);

	Mat binMask;
	getBinMask(mask, binMask);
	image.copyTo(res, binMask);
	MyShowImage(res, winName);
	waitKey(0);
	return 0;
}
