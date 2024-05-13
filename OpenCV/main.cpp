#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;
String folder = "/home/hrd/Desktop/Project_MBH/data/";


int main() {
    // file data 추출(기온, 습도, 강수량)
    ifstream inputFile("/home/hrd/Desktop/Project_MBH/weather/build/output.txt"); // 파일 경로를 수정하세요
    string line;
    string temperature;        // 기온
    string humidity;           // 습도
    string precipitation;      // 강수량

    // 파일이 열렸는지 확인
    if (!inputFile.is_open()) {
        cerr << "파일을 열 수 없습니다." << endl;
        return 1;
    }

    // 파일을 한 줄씩 읽어서 특정 줄과 특정 단어를 추출
    int currentLine = 0;
    while (getline(inputFile, line)) {
        currentLine++;

        // 5번째 줄인 경우
        if (currentLine == 5) {
            istringstream iss(line);
            string word;
            int wordCount = 0;

            // 공백을 구분자로 하여 단어 추출
            while (iss >> word) {
                wordCount++;
                // 12번째 단어
                if (wordCount == 12) {
                    temperature = word;
                    continue;
                }
                // 14번째 단어
                if (wordCount == 14) {
                    humidity = word;
                    continue;
                }
                // 16번째 단어
                if (wordCount == 16) {
                    precipitation = word;
                    break;
                }
            }

            break;
        }
    }

    // 단어를 출력
    // std::cout << "현재 세종시 기온은 " <<temperature << "도입니다." << std::endl;
    // std::cout << "현재 세종시 습도은 " <<humidity << "도입니다." << std::endl;
    // std::cout << "현재 세종시 강수량은 " <<precipitation << "mm입니다." << std::endl;
    
    inputFile.close();
    
    //TIME
    time_t now = std::time(nullptr);            // 현재시간
    tm* current_time = std::localtime(&now);    // 구조체 
    

    // OpenCV
    Mat src = imread(folder + "background.jpg", IMREAD_COLOR);
    Mat background = src.clone();
    putText(background, temperature, Point(100,200),FONT_HERSHEY_PLAIN,10,Scalar(255,255,255),15);
	
	imshow("background", background);
	waitKey();
	destroyAllWindows();
	return 0;

}
