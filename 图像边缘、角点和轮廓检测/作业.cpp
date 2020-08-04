
#include <opencv2/opencv.hpp>  
using namespace cv;
using namespace std;
int main()
{ 
	Mat srcImage = imread("Fruits.jpg");  //载入图像 
	imshow("srcImage", srcImage);

	//Canny边缘检测
	Mat canyImage;
	Canny(srcImage, canyImage, 3, 9, 3);
	imshow(" Canny 算子 ", canyImage);

	//Sobel边缘检测
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
	imshow("Sobel 算子 ", sobelImage);

	//Laplacian边缘检测
	Mat laplacianImage;
	Laplacian(srcImage, laplacianImage, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(laplacianImage, laplacianImage);
	imshow(" Laplacian 算子 ", laplacianImage);

	//Scharr滤波
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
	imshow(" Scharr 滤波器 ", scharrImage);

	//Harris 角点检测
	int thresh = 30; //阈值  
	Mat dstImage;//目标图  
	Mat normImage;//归一化后的图  
	Mat scaledImage;//线性变换后的八位无符号整型的图 
	Mat g_srcImage, g_grayImage;
	g_srcImage = srcImage.clone();//载入原始图并进行克隆保存
	cvtColor(g_srcImage, g_grayImage, CV_BGR2GRAY);//存留一张灰度图  
	cornerHarris(g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT);
	cornerHarris(g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT);
	normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(normImage, scaledImage);//将归一化后的图线性变换成8位无符号整型   
	// 将检测到的，且符合阈值条件的角点绘制出来  
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
	//imshow(" Harris 角点检测 ", scaledImage);
	imshow(" Harris 角点检测 ", g_srcImage);

	//ShiTomasi 角点检测
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
	imshow(" ShiTomasi 角点检测 ", g_srcImage);
	waitKey(0);
	return 0;
}
