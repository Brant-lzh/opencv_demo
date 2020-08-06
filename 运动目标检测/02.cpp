#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	//string videoFile = "Laboratory_raw.avi";
	string videoFile = "Test.mp4";
	VideoCapture capture;
	capture.open(videoFile);

	if (!capture.isOpened())
	{
		cout << "read video failure" << endl;
		return -1;
	}

	//BackgroundSubtractorMOG2 mog;
	Ptr<BackgroundSubtractorMOG2> mog = createBackgroundSubtractorMOG2();
	Mat foreground;
	Mat background;
	Mat frame;
	long frameNo = 0;
	while (capture.read(frame))
	{
		++frameNo;
		cout << frameNo << endl;
		// �˶�ǰ����⣬�����±���
		mog->apply(frame, foreground, 0.01);
		// ��ʴ
		erode(foreground, foreground, Mat());
		// ����
		dilate(foreground, foreground, Mat());
		mog->getBackgroundImage(background);  // ���ص�ǰ����ͼ��
		imshow("video", foreground);
		imshow("background", background);
		if (waitKey(25) > 0)
		{
			break;
		}
	}
	return 0;
}
