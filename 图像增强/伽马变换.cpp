#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>  
using namespace cv;  

int main(int argc, char *argv[])  
{  
    Mat image = imread("Test.jpg");  
    Mat imageGamma(image.size(), CV_32FC3);  
    for (int i = 0; i < image.rows; i++)  
    {  
        for (int j = 0; j < image.cols; j++)  
        {  
            imageGamma.at<Vec3f>(i, j)[0] = (image.at<Vec3b>(i, j)[0])*(image.at<Vec3b>(i, j)[0])*(image.at<Vec3b>(i, j)[0]);  
            imageGamma.at<Vec3f>(i, j)[1] = (image.at<Vec3b>(i, j)[1])*(image.at<Vec3b>(i, j)[1])*(image.at<Vec3b>(i, j)[1]);  
            imageGamma.at<Vec3f>(i, j)[2] = (image.at<Vec3b>(i, j)[2])*(image.at<Vec3b>(i, j)[2])*(image.at<Vec3b>(i, j)[2]);  
        }  
    }  
    //归一化到0~255    
    normalize(imageGamma, imageGamma, 0, 255, CV_MINMAX);  
    //转换成8bit图像显示    
    convertScaleAbs(imageGamma, imageGamma);  
    imshow("原图", image);  
    imshow("伽马变换图像增强效果", imageGamma);  
    waitKey();  
    return 0;  
}