#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	//������Ƶ  
	VideoCapture capture("Laboratory_raw.avi");  
	//VideoCapture capture(0);
 
	Mat tempframe, currentframe, previousframe,difframe;
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
		tempframe = frame;
		framenum++;
		if (framenum == 1)
		{
			cvtColor(tempframe, previousframe, CV_BGR2GRAY);
		}
		if (framenum >= 2)
		{
			//Mat currentframe1, currentframe2, currentframe3, currentframe4;
			cvtColor(tempframe, currentframe, CV_BGR2GRAY);//ת��Ϊ��ͨ���Ҷ�ͼ����ʱcurrentFrame�Ѿ�����tempFrame������   
			absdiff(currentframe, previousframe, currentframe);//���������ֵ    
			threshold(currentframe, currentframe, 20, 255.0, CV_THRESH_BINARY);
			dilate(currentframe, currentframe, Mat());//����  
			erode(currentframe, currentframe, Mat());//��ʴ  

			//��ʾͼ��    
			imshow("camera", tempframe);
			imshow("moving area", currentframe);

		}
		//�ѵ�ǰ֡������Ϊ��һ�δ����ǰһ֡    
		//cvtColor(tempframe, previousframe, CV_BGR2GRAY);  
		waitKey(33);
	}//end while    
}
