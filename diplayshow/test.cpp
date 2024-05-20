#include <opencv2/opencv.hpp>

int main() {
    // 이미지를 로드합니다.
    cv::Mat image = cv::imread("path_to_your_image.jpg");

    // 이미지가 잘 로드되었는지 확인합니다.
    if (image.empty()) {
        std::cerr << "Could not open or find the image!" << std::endl;
        return -1;
    }

    // 윈도우 이름 설정
    std::string windowName = "Fullscreen Window";

    // 윈도우 생성 및 전체 화면 모드 설정
    cv::namedWindow(windowName, cv::WINDOW_FULLSCREEN);

    // 이미지 표시
    cv::imshow(windowName, image);

    // 키보드 입력 대기
    cv::waitKey(0);

    return 0;
}