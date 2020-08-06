
#include<opencv2\opencv.hpp>
using namespace cv;
void onMouse(int event, int x, int y, int flags, void* userdata);
Rect rect;
Mat src,roiImg, result;
void showImg();

void getBinMask(const Mat& comMask, Mat& binMask)
{
	binMask.create(comMask.size(), CV_8UC1);
	binMask = comMask & 1;
}
int main(int arc, char** argv) { 
	src = imread("test2.jpg");
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src); 
	setMouseCallback("input", onMouse);		
	Mat result = Mat::zeros(src.size(), CV_8UC1);
	Mat bgModel, fgModel;
	char c = waitKey(0);
	if (c == 'g') {
		Mat image = imread("test2.jpg", 1);
		Mat bg; Mat fg;
		Mat mask, res;
		mask.create(image.size(), CV_8UC1);
		grabCut(image, mask, rect, bg, fg,2, 0);
		Mat binMask;
		getBinMask(mask, binMask);
		image.copyTo(res, binMask);
		Mat res_clone = res.clone();
		Mat background;
		absdiff(image,res_clone, background);
		imshow("dst", background);
		Mat imageGray;
		//ת��Ϊ�Ҷ�ͼ
		cvtColor(background, imageGray, CV_RGB2GRAY, 0);
		Mat imageMask = Mat(background.size(), CV_8UC1, Scalar::all(0));
		//ͨ����ֵ��������Mask
		threshold(imageGray, imageMask, 1, 255, THRESH_BINARY_INV);//240-1 CV_THRESH_BINARY-THRESH_BINARY_INV
		Mat Kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		//��Mask���ʹ�������Mask���
		dilate(imageMask, imageMask, Kernel);
		//ͼ���޸�
		inpaint(background, imageMask, background, 50, INPAINT_TELEA);//5-50
		imshow("Mask", imageMask);
		imshow("�޸���", background);
		Mat new_dst;
		bilateralFilter(background,new_dst,15,150,3);

		//namedWindow("bilateralFilter", WINDOW_AUTOSIZE);
		//imshow("bilateralFilter", dst);

		Mat  result;
		Mat kernal = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
		filter2D(new_dst, result, -1, kernal,Point(-1,-1),0);
		imshow("ͼ����ǿ��", result);
	}
	waitKey(0); 
	return 0;
}
void showImg() {
	src.copyTo(roiImg);
	rectangle(roiImg, rect, Scalar(0, 0, 255), 2);
	imshow("input", roiImg);
}
//���ѡ����ο�
void onMouse(int event, int x, int y, int flags, void* userdata){
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN://�����������¼�
		rect.x = x;
		rect.y = y;
		rect.width = 1;
		rect.height = 1;
		break;
	case CV_EVENT_MOUSEMOVE://����ƶ��¼�
		if (flags && CV_EVENT_FLAG_LBUTTON) {
			rect = Rect(Point(rect.x, rect.y), Point(x, y));
			showImg();
		}
		break;
	case EVENT_LBUTTONUP://��굯���¼�
		if (rect.width > 1 && rect.height > 1) {
			showImg();
		}
		break;
	default:
		break;
	}
}