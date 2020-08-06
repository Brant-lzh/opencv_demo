#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	//������Ƶ  
	VideoCapture capture("Laboratory_raw.avi");  
	//VideoCapture capture(0);
 
	Mat tempframe, currentframe, previousframe,difframe;
	Mat s3,difframe2,difframe3,tempframe2;
	Mat frame;
	int framenum = 0;
	//��ȡһ֡����  
	while (true)
	{
		if (!capture.isOpened())
		{
			cout << "read video failure" << endl;
			return -1;
		}
		//tempframe = capture.read(frame);  
		capture >> frame;
		imshow("ԭ��Ƶ", frame);
		previousframe = frame.clone();

		capture >> frame;
		currentframe = frame.clone();

		cvtColor(previousframe, previousframe, CV_BGR2GRAY);
		cvtColor(currentframe, currentframe, CV_BGR2GRAY);
		absdiff(currentframe, previousframe, difframe);//���������ֵ    
		threshold(difframe, tempframe, 20, 255.0, CV_THRESH_BINARY);
		dilate(tempframe, tempframe, Mat());//����  
		erode(tempframe, tempframe, Mat());//��ʴ

		capture >> frame;
		s3 = frame.clone();//����֡
		cvtColor(s3, s3, CV_BGR2GRAY);
		absdiff(previousframe, s3, difframe2);//���������ֵ
		bitwise_and(difframe, difframe2, difframe3);
		threshold(difframe3, tempframe2, 20, 255.0, CV_THRESH_BINARY);
		dilate(tempframe2, tempframe2, Mat());//����  
		erode(tempframe2, tempframe2, Mat());//��ʴ

		imshow("�˶�Ŀ�� ��֡֡�", tempframe);

		imshow("�˶�Ŀ�� ��֡֡�", tempframe2);
 
		waitKey(50);
	}//end while    
}
