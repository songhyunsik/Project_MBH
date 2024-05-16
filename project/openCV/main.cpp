#include "opencv2/opencv.hpp"
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 이미지를 불러옵니다.
    Mat image = imread("/home/matt/바탕화면/Project_MBH/project/data/seoul.jpg");
    if (image.empty()) {
        cerr << "이미지를 불러올 수 없습니다." << endl;
        return -1;
    }

    // 이미지를 그레이스케일로 변환합니다.
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);

    // 이미지를 이진화합니다.
    Mat binary;
    threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

    // 윤곽선을 검출합니다.
    vector<vector<Point>> contours;
    findContours(binary, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 가장 큰 윤곽선을 찾습니다. (텍스트 영역이라고 가정)
    int largest_contour_index = -1;
    double largest_area = 0;
    for (size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        if (area > largest_area) {
            largest_area = area;
            largest_contour_index = i;
        }
    }

    // 가장 큰 윤곽선을 사각형으로 둘러쌉니다.
    if (largest_contour_index != -1) {
        Rect bounding_rect = boundingRect(contours[largest_contour_index]);
        Mat text_region = gray(bounding_rect);

        // Tesseract OCR 객체를 초기화합니다.
        tesseract::TessBaseAPI ocr;
        ocr.Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);
        ocr.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
        
        // 이미지를 Tesseract OCR에 입력합니다.
        ocr.SetImage(text_region.data, text_region.cols, text_region.rows, 1, text_region.step);
        
        // 텍스트를 추출합니다.
        string text = string(ocr.GetUTF8Text());
        cout << "추출된 텍스트: " << text << endl;
        
        // 추출된 텍스트 영역을 시각화합니다.
        rectangle(image, bounding_rect, Scalar(0, 255, 0), 2);
        imshow("Detected Text Region", image);
        waitKey(0);
    } else {
        cerr << "텍스트 영역을 찾을 수 없습니다." << endl;
    }

    return 0;
}
