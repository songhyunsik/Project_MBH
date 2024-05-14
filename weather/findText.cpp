#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// 5번째 줄 12번, 14번, 16번에 있는 단어 추출
int main() {
    std::ifstream inputFile("/home/hrd/Desktop/Project_MBH/weather/build/output1.txt"); // 파일 경로를 수정하세요
    std::string line;
    std::string temperature; // 추출한 단어를 저장할 변수
    std::string humidity; // 추출한 단어를 저장할 변수
    std::string precipitation; // 추출한 단어를 저장할 변수

    // 파일이 열렸는지 확인
    if (!inputFile.is_open()) {
        std::cerr << "파일을 열 수 없습니다." << std::endl;
        return 1;
    }

    // 파일을 한 줄씩 읽어서 특정 줄과 특정 단어를 추출
    int currentLine = 0;
    while (std::getline(inputFile, line)) {
        currentLine++;

        // 5번째 줄인 경우
        if (currentLine == 12) {
            std::istringstream iss(line);
            std::string word;
            int wordCount = 0;

            // 공백을 구분자로 하여 단어 추출
            while (iss >> word) {
                wordCount++;
                // 12번째 단어
                // if (wordCount == 12) {
                //     temperature = word;
                //     continue;
                // }
                // // 14번째 단어
                // if (wordCount == 14) {
                //     humidity = word;
                //     continue;
                // }
                // 16번째 단어
                if (wordCount == 5) {
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
    std::cout << precipitation <<  std::endl;
    
    inputFile.close();

    return 0;
}
