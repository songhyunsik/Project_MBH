
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/hrd/Desktop/Project_MBH/data/";

int main() {
	Mat src = imread(folder + "background.jpg", IMREAD_COLOR);
    Mat background = src.clone();
    putText(background, "hello", Point(100,200),FONT_HERSHEY_PLAIN,10,Scalar(255,255,255),15);
	
	imshow("background", background);
	waitKey();
	destroyAllWindows();
	return 0;
}