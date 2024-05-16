#include <iostream>
#include <ctime>

int main (void) {
    // 현재 시간을 가져옴
    std::time_t now = std::time(nullptr);
    
    // 시간 구조체로 변환
    std::tm* current_time = std::localtime(&now);
    
    // 시간 출력
    std::cout << "현재 시간: ";
    std::cout << current_time->tm_year + 1900 << '-' // 연도
              << current_time->tm_mon + 1 << '-'    // 월
              << current_time->tm_mday << ' '       // 일
              << current_time->tm_hour << ':'       // 시
              << current_time->tm_min << ':'        // 분
              << current_time->tm_sec << '\n';      // 초
    

    return 0;
}