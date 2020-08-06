#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;
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
	src = imread("1.jpg");
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src); 
	setMouseCallback("input", onMouse);		
	Mat result = Mat::zeros(src.size(), CV_8UC1);
	Mat bgModel, fgModel;
	char c = waitKey(0);
	if (c == 'g') {
		Mat image = imread("1.jpg", 1);
		Mat bg; Mat fg;
		Mat mask, res;
		mask.create(image.size(), CV_8UC1);
		grabCut(image, mask, rect, bg, fg,2, 0);
		Mat binMask;
		getBinMask(mask, binMask);
		image.copyTo(res, binMask);
		Mat res_clone = res.clone();
		imshow("1",res_clone);
		imshow("2",mask);
		imshow("3",binMask);


		Mat img = imread("2.jpg");

	imshow("display", img);
	

	CascadeClassifier cascade;

	const string path = "haarcascade_frontalface_alt.xml";
	if ( ! cascade.load(path))
	{
		cout << "cascade load failed!\n";
	}
	

	vector<Rect> faces(0);
	cascade.detectMultiScale(img, faces, 1.1, 2, 0 ,Size(30,30));
 
	cout << "detect face number is :" << faces.size() << endl;

	
	if (faces.size() > 0)
	{
		for (size_t i = 0;i < faces.size();i++)
		{
			rectangle(img, faces[i], Scalar(150, 0, 0), 3, 8, 0);

			//cv::Mat logo = cv::imread("1.jpg");

			//cv::Mat mask = cv::imread("1.jpg",0);

			cv::Mat imageROI;
			//mask.create(res_clone.size(), CV_8UC1);
			imageROI = img(cv::Rect(faces[i].x-100,faces[i].y-100,res_clone.cols,res_clone.rows));

			res_clone.copyTo(imageROI,binMask);

			cv::namedWindow("result");

			cv::imshow("result",img);
 
		}
	}
	else{
		cout << "未检测到人脸" << endl;
	}
 

 

	imshow("face_detect", img);
	}
	waitKey(0); 
	return 0;
}
void showImg() {
	src.copyTo(roiImg);
	rectangle(roiImg, rect, Scalar(0, 0, 255), 2);
	imshow("input", roiImg);
}
//鼠标选择矩形框
void onMouse(int event, int x, int y, int flags, void* userdata){
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN://鼠标左键按下事件
		rect.x = x;
		rect.y = y;
		rect.width = 1;
		rect.height = 1;
		break;
	case CV_EVENT_MOUSEMOVE://鼠标移动事件
		if (flags && CV_EVENT_FLAG_LBUTTON) {
			rect = Rect(Point(rect.x, rect.y), Point(x, y));
			showImg();
		}
		break;
	case EVENT_LBUTTONUP://鼠标弹起事件
		if (rect.width > 1 && rect.height > 1) {
			showImg();
		}
		break;
	default:
		break;
	}
}
/*
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;
void onMouse(int event, int x, int y, int flags, void* userdata);
Rect rect;
Mat src, roiImg, result;
void showImg();

void getBinMask(const Mat& comMask, Mat& binMask)
{
	binMask.create(comMask.size(), CV_8UC1);
	binMask = comMask & 1;
}
int main(int arc, char** argv) {
	
	src = imread("1.jpg");
	
	//namedWindow("图片1", CV_WINDOW_AUTOSIZE);
	//imshow("图片1", src);
	//setMouseCallback("图片1", onMouse);
	
	Mat result = Mat::zeros(src.size(), CV_8UC1);
	Mat bgModel, fgModel;
	//char c = waitKey(0);
	//if (c == 'g') {
		Mat img1 = imread("1.jpg", 1);
		Mat bg; Mat fg;
		Mat mask, cutImg1;
		mask.create(img1.size(), CV_8UC1);
		rect = Rect(0, 0, img1.rows, img1.cols);
		grabCut(img1, mask, rect, bg, fg, 2, 0);
		Mat binMask;
		getBinMask(mask, binMask);
		img1.copyTo(cutImg1, binMask);
		Mat cutImg1_clone = cutImg1.clone();
		imshow("抠完后的图片1", cutImg1_clone);

		//人脸识别程序
		Mat img2 = imread("2.jpg");
		imshow("图片2", img2);
		Mat img2_clone = img2.clone();
		CascadeClassifier cascade;
		const string path = "haarcascade_frontalface_alt.xml";
		cascade.load(path);
		vector<Rect> faces(0);
		cascade.detectMultiScale(img2, faces, 1.1, 2, 0, Size(30, 30));

		if (faces.size() > 0)
		{
			for (size_t i = 0; i < faces.size(); i++)
			{
				rectangle(img2, faces[i], Scalar(150, 0, 0), 3, 8, 0);
				imshow("人脸识别后图片2", img2);
				Mat imageROI;
				imageROI = img2_clone(Rect(faces[i].x - 190, faces[i].y - 125, cutImg1_clone.cols, cutImg1_clone.rows));
				cutImg1_clone.copyTo(imageROI, binMask);
			}
		}
		imshow("最终结果", img2_clone);
	//}
	waitKey(0);
	return 0;
}
void showImg() {
	src.copyTo(roiImg);
	rectangle(roiImg, rect, Scalar(0, 0, 255), 2);
	imshow("图片1", roiImg);
}
//鼠标选择矩形框
void onMouse(int event, int x, int y, int flags, void* userdata){
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN://鼠标左键按下事件
		rect.x = x;
		rect.y = y;
		rect.width = 1;
		rect.height = 1;
		break;
	case CV_EVENT_MOUSEMOVE://鼠标移动事件
		if (flags && CV_EVENT_FLAG_LBUTTON) {
			rect = Rect(Point(rect.x, rect.y), Point(x, y));
			showImg();
		}
		break;
	case EVENT_LBUTTONUP://鼠标弹起事件
		if (rect.width > 1 && rect.height > 1) {
			showImg();
		}
		break;
	default:
		break;
	}
}
*/