//����������������������ͷ�ļ�  
#include <opencv2/opencv.hpp>  
  
//�����ռ��������� 
using namespace cv;  
using namespace std;

int main()
{
	Mat src0,src1,src2,dst0,dst1,dst2,dst3,tempframe;
	src0=imread("00.bmp");
	src1=imread("01.bmp");//����ͼ��
	src2=imread("02.bmp");

	cvtColor(src0,dst0,CV_BGR2GRAY);
	cvtColor(src1,dst1,CV_BGR2GRAY);//ת��Ϊ�Ҷ�ͼ
	cvtColor(src2,dst2,CV_BGR2GRAY);

	absdiff(dst0,dst1,dst1);//��֡��
	absdiff(dst1,dst2,dst2);//��֡��
	bitwise_and(dst1, dst2, dst3);

	threshold( dst3, tempframe, 20, 255, CV_THRESH_BINARY );//��ֵ��������Ϊ��ֵͼ
	dilate(tempframe, tempframe, Mat());//����  
	erode(tempframe, tempframe, Mat());//��ʴ

	//imshow("�Ҷ�ͼ", dst1);
	imshow("������ͼ", tempframe);


	waitKey(0);   
    return 0;  
}
