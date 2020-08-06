#include <opencv2/highgui/highgui.hpp>      
#include <opencv2/imgproc/imgproc.hpp>  
using namespace cv;  

int main(int argc, char *argv[])  
{  
    Mat image = imread("Test.jpg");  
    Mat imageLog(image.size(), CV_32FC3);  
    for (int i = 0; i < image.rows; i++)  
    {  
        for (int j = 0; j < image.cols; j++)  
        {  
            imageLog.at<Vec3f>(i, j)[0] = log(float(1 + image.at<Vec3b>(i, j)[0]));  
            imageLog.at<Vec3f>(i, j)[1] = log(float(1 + image.at<Vec3b>(i, j)[1]));  
            imageLog.at<Vec3f>(i, j)[2] = log(float(1 + image.at<Vec3b>(i, j)[2]));  
        }  
    }  
    //��һ����0~255    
    normalize(imageLog, imageLog, 0, 255, CV_MINMAX);  
    //ת����8bitͼ����ʾ    
    convertScaleAbs(imageLog, imageLog);  
    imshow("Soure", image);  
    imshow("����LOG�任", imageLog);  
    waitKey();    
    return 0;  
}