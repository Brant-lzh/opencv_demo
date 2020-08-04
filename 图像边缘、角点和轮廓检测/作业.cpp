
#include <opencv2/opencv.hpp>  
using namespace cv;
using namespace std;
int main()
{ 
	Mat srcImage = imread("Fruits.jpg");  //����ͼ�� 
	imshow("srcImage", srcImage);

	//Canny��Ե���
	Mat canyImage;
	Canny(srcImage, canyImage, 3, 9, 3);
	imshow(" Canny ���� ", canyImage);

	//Sobel��Ե���
	Mat sobel_x;
	Mat sobel_y;
	Mat sobelImage;
	Sobel(srcImage, sobel_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(sobel_x, sobel_x);
	Sobel(srcImage, sobel_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(sobel_y, sobel_y);
	addWeighted(sobel_x, 0.5, sobel_y, 0.5, 0, sobelImage);
	//imshow("sobel_x", sobel_x);
	//imshow("sobel_y", sobel_y);
	imshow("Sobel ���� ", sobelImage);

	//Laplacian��Ե���
	Mat laplacianImage;
	Laplacian(srcImage, laplacianImage, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(laplacianImage, laplacianImage);
	imshow(" Laplacian ���� ", laplacianImage);

	//Scharr�˲�
	Mat scharr_x;
	Mat scharr_y;
	Mat scharrImage;
	Scharr(srcImage, scharr_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(scharr_x, scharr_x);
	Scharr(srcImage, scharr_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(scharr_y, scharr_y);
	addWeighted(scharr_x, 0.5, scharr_y, 0.5, 0, scharrImage);
	//imshow("scharr_x", scharr_x);
	//imshow("scharr_y", scharr_y);
	imshow(" Scharr �˲��� ", scharrImage);

	//Harris �ǵ���
	int thresh = 30; //��ֵ  
	Mat dstImage;//Ŀ��ͼ  
	Mat normImage;//��һ�����ͼ  
	Mat scaledImage;//���Ա任��İ�λ�޷������͵�ͼ 
	Mat g_srcImage, g_grayImage;
	g_srcImage = srcImage.clone();//����ԭʼͼ�����п�¡����
	cvtColor(g_srcImage, g_grayImage, CV_BGR2GRAY);//����һ�ŻҶ�ͼ  
	cornerHarris(g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT);
	cornerHarris(g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT);
	normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(normImage, scaledImage);//����һ�����ͼ���Ա任��8λ�޷�������   
	// ����⵽�ģ��ҷ�����ֵ�����Ľǵ���Ƴ���  
	for (int j = 0; j < normImage.rows; j++)
	{
		for (int i = 0; i < normImage.cols; i++)
		{
			if ((int)normImage.at<float>(j, i) > thresh + 80)
			{
				circle(g_srcImage, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);
				circle(scaledImage, Point(i, j), 5, Scalar(0, 10, 255), 2, 8, 0);
			}
		}
	}
	//imshow(" Harris �ǵ��� ", scaledImage);
	imshow(" Harris �ǵ��� ", g_srcImage);

	//ShiTomasi �ǵ���
		vector<Point2f> corners;
		int maxCorners = 30;
		double qualityLevel = 0.01;  
		double minDistance = 10;  
		int blockSize = 3;  
		bool useHarrisDetector = false;  
		double k = 0.04;  
		goodFeaturesToTrack( g_grayImage,   
               corners,  
               maxCorners,  
               qualityLevel,  
               minDistance,  
               Mat(),  
               blockSize,  
               useHarrisDetector,  
               k ); 
		  for( int i = 0; i < corners.size(); i++ ){   
      //circle( dst_norm_scaled,  corners[i], 5,  Scalar(255), 2, 8, 0 );   
      circle( srcImage, corners[i], 5, Scalar(0, 10, 255), 2, 8, 0 );   
  }  
	imshow(" ShiTomasi �ǵ��� ", g_srcImage);
	waitKey(0);
	return 0;
}
