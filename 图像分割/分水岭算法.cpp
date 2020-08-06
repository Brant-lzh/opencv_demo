#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Vec3b RandomColor(int value);  //生成随机颜色函数

int main( int argc, char* argv[] )
{
	Mat image=imread("lena.jpg");    //载入RGB彩色图像
	imshow("Source Image",image);

	//灰度化，滤波，Canny边缘检测
	Mat imageGray;
	cvtColor(image,imageGray,CV_RGB2GRAY);//灰度转换
	GaussianBlur(imageGray,imageGray,Size(5,5),2);   //高斯滤波
	imshow("Gray Image",imageGray); 
	Canny(imageGray,imageGray,80,150);  
	imshow("Canny Image",imageGray);

	//查找轮廓
	vector<vector<Point>> contours;  
	vector<Vec4i> hierarchy;  
	findContours(imageGray,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point());  
	Mat imageContours=Mat::zeros(image.size(),CV_8UC1);  //轮廓	
	Mat marks(image.size(),CV_32S);   //Opencv分水岭第二个矩阵参数
	marks=Scalar::all(0);
	int index = 0;
	int compCount = 0;
	for( ; index >= 0; index = hierarchy[index][0], compCount++ ) 
	{
		//对marks进行标记，对不同区域的轮廓进行编号，相当于设置注水点，有多少轮廓，就有多少注水点
		drawContours(marks, contours, index, Scalar::all(compCount+1), 1, 8, hierarchy);
		drawContours(imageContours,contours,index,Scalar(255),1,8,hierarchy);  
	}

	//我们来看一下传入的矩阵marks里是什么东西
	Mat marksShows;
	convertScaleAbs(marks,marksShows);
	imshow("marksShow",marksShows);
	imshow("轮廓",imageContours);
	watershed(image,marks);

	//我们再来看一下分水岭算法之后的矩阵marks里是什么东西
	Mat afterWatershed;
	convertScaleAbs(marks,afterWatershed);
	imshow("After Watershed",afterWatershed);

	//对每一个区域进行颜色填充
	Mat PerspectiveImage=Mat::zeros(image.size(),CV_8UC3);
	for(int i=0;i<marks.rows;i++)
	{
		for(int j=0;j<marks.cols;j++)
		{
			int index=marks.at<int>(i,j);
			if(marks.at<int>(i,j)==-1)
			{
				PerspectiveImage.at<Vec3b>(i,j)=Vec3b(255,255,255);
			}			 
			else
			{
				PerspectiveImage.at<Vec3b>(i,j) =RandomColor(index);
			}
		}
	}
	imshow("After ColorFill",PerspectiveImage);

	//分割并填充颜色的结果跟原始图像融合
	Mat wshed;
	addWeighted(image,0.4,PerspectiveImage,0.6,0,wshed);
	imshow("AddWeighted Image",wshed);

	waitKey();
}


Vec3b RandomColor(int value) //生成随机颜色函数
{
	value=value%255;  //生成0~255的随机数
	RNG rng;
	int aa=rng.uniform(0,value);
	int bb=rng.uniform(0,value);
	int cc=rng.uniform(0,value);
	return Vec3b(aa,bb,cc);
}