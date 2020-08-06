#include<opencv2/opencv.hpp>  
#include<iostream>  
#include<vector>  
using namespace cv;  
using namespace std;  

int main()  
{  
    Mat srcImage = imread("1.jpg");  
    Mat compareImage = imread("2.jpg");  
    imshow("��ԭͼ��", srcImage);  
    imshow("����Ҫ�Ƚϵ�ͼ��", compareImage);  
  
    //�ڱȽ�ֱ��ͼʱ����Ѳ�������HSV�ռ��в�����������Ҫ��BGR�ռ�ת��ΪHSV�ռ�  
    Mat srcHsvImage;  
    Mat compareHsvImage;  
    cvtColor(srcImage, srcHsvImage, CV_BGR2HSV);  
    cvtColor(compareImage, compareHsvImage, CV_BGR2HSV);  
  
    //����H-Sֱ��ͼ���д���  
    //���ȵ�����ֱ��ͼ�Ĳ���  
    MatND srcHist, compHist;  
    //H��Sͨ��  
    int channels[] = { 0, 1 };  
    int histSize[] = { 30, 32 };  
    float HRanges[] = { 0, 180 };  
    float SRanges[] = { 0, 256 };  
    const float *ranges[] = { HRanges, SRanges };  
  
    //����ԭͼֱ��ͼ�ļ���  
    calcHist(&srcHsvImage, 1, channels, Mat(), srcHist, 2, histSize, ranges, true, false);  
    //����Ҫ�Ƚϵ�ͼ����ֱ��ͼ�ļ���  
    calcHist(&compareHsvImage, 1, channels, Mat(), compHist, 2, histSize, ranges, true, false);  
  
    //ע�⣺������Ҫ������ֱ��ͼ���й�һ������  
    normalize(srcHist, srcHist, 0, 1, NORM_MINMAX);  
    normalize(compHist, compHist, 0, 1, NORM_MINMAX);  
  
    //�Եõ���ֱ��ͼ�Ա�  
    double g_dCompareRecult = compareHist(srcHist, compHist, 0);  
    cout << "����һ������ͼ��ȽϵĽ��Ϊ��" << g_dCompareRecult << endl;  
    g_dCompareRecult = compareHist(srcHist, compHist, 1);  
    cout << "������������ͼ��ȽϵĽ��Ϊ��" << g_dCompareRecult << endl;  
    g_dCompareRecult = compareHist(srcHist, compHist, 2);  
    cout << "������������ͼ��ȽϵĽ��Ϊ��" << g_dCompareRecult << endl;  
    g_dCompareRecult = compareHist(srcHist, compHist, 3);  
    cout << "�����ģ�����ͼ��ȽϵĽ��Ϊ��" << g_dCompareRecult << endl;  
  
    waitKey(0);  
    return 0;  
}
