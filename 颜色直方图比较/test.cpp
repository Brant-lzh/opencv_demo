#include<opencv2/opencv.hpp>  
#include<iostream>  
#include<vector>  
using namespace cv;  
using namespace std;  

int main()  
{  
    Mat srcImage = imread("1.jpg");  
    Mat compareImage = imread("2.jpg");  
    imshow("【原图】", srcImage);  
    imshow("【需要比较的图像】", compareImage);  
  
    //在比较直方图时，最佳操作是在HSV空间中操作，所以需要将BGR空间转换为HSV空间  
    Mat srcHsvImage;  
    Mat compareHsvImage;  
    cvtColor(srcImage, srcHsvImage, CV_BGR2HSV);  
    cvtColor(compareImage, compareHsvImage, CV_BGR2HSV);  
  
    //采用H-S直方图进行处理  
    //首先得配置直方图的参数  
    MatND srcHist, compHist;  
    //H、S通道  
    int channels[] = { 0, 1 };  
    int histSize[] = { 30, 32 };  
    float HRanges[] = { 0, 180 };  
    float SRanges[] = { 0, 256 };  
    const float *ranges[] = { HRanges, SRanges };  
  
    //进行原图直方图的计算  
    calcHist(&srcHsvImage, 1, channels, Mat(), srcHist, 2, histSize, ranges, true, false);  
    //对需要比较的图进行直方图的计算  
    calcHist(&compareHsvImage, 1, channels, Mat(), compHist, 2, histSize, ranges, true, false);  
  
    //注意：这里需要对两个直方图进行归一化操作  
    normalize(srcHist, srcHist, 0, 1, NORM_MINMAX);  
    normalize(compHist, compHist, 0, 1, NORM_MINMAX);  
  
    //对得到的直方图对比  
    double g_dCompareRecult = compareHist(srcHist, compHist, 0);  
    cout << "方法一：两幅图像比较的结果为：" << g_dCompareRecult << endl;  
    g_dCompareRecult = compareHist(srcHist, compHist, 1);  
    cout << "方法二：两幅图像比较的结果为：" << g_dCompareRecult << endl;  
    g_dCompareRecult = compareHist(srcHist, compHist, 2);  
    cout << "方法三：两幅图像比较的结果为：" << g_dCompareRecult << endl;  
    g_dCompareRecult = compareHist(srcHist, compHist, 3);  
    cout << "方法四：两幅图像比较的结果为：" << g_dCompareRecult << endl;  
  
    waitKey(0);  
    return 0;  
}
