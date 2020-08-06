#include <opencv2/highgui/highgui.hpp>      
#include <opencv2/imgproc/imgproc.hpp>  
#include <iostream>  
using namespace cv; 

int main(int argc, char *argv[])  
{  
    Mat image = imread("Test.jpg", 1);  
    if (image.empty())  
    {  
        std::cout << "��ͼƬʧ��,����" << std::endl;  
        return -1;  
    }  
    imshow("ԭͼ��", image);  
    Mat imageRGB[3];  
    split(image, imageRGB);  
    for (int i = 0; i < 3; i++)  
    {  
        equalizeHist(imageRGB[i], imageRGB[i]);  
    }
    merge(imageRGB, 3, image);  
    imshow("ֱ��ͼ���⻯ͼ����ǿЧ��", image);  
    waitKey(0);  
    return 0;  
} 