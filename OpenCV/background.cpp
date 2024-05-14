
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/hrd/Desktop/Project_MBH/data/";

int main() {
	Mat src = imread(folder + "background.jpg", IMREAD_COLOR);
    Mat background = src.clone();
    putText(background, "TIME", Point(700,150),FONT_HERSHEY_PLAIN,8,Scalar(255,255,255),15);
	putText(background, "tmeperature: ", Point(100,300),FONT_HERSHEY_PLAIN,10,Scalar(255,255,255),15);
	putText(background, "HM: ", Point(100,400),FONT_HERSHEY_PLAIN,10,Scalar(255,255,255),15);
	putText(background, "RN: ", Point(100,500),FONT_HERSHEY_PLAIN,10,Scalar(255,255,255),15);
	
	imshow("background", background);
	waitKey();
	destroyAllWindows();
	return 0;
}