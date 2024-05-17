#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

string folderPath = "/home/matt/바탕화면/Project_MBH/project/data/";

int main(){

    Mat img = imread(folderPath + "daejun.png");
    if (img.empty()) {
        cerr << "배경 이미지 불러오기 실패!" << endl;
        return -1;
    }

    putText(img, "DAEJEON ", Point(50, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(220, 245, 245), 5);
    putText(img, "Today's Weather : ", Point(50, 60), FONT_HERSHEY_SIMPLEX, 1, Scalar(220, 245, 245), 3);
    putText(img, "Today's Temperature : ", Point(50, 90), FONT_HERSHEY_SIMPLEX, 1, Scalar(220, 245, 245), 3);
    putText(img, "Today's Rainfall : ", Point(50, 120), FONT_HERSHEY_SIMPLEX, 1, Scalar(220, 245, 245), 3);
    putText(img, "Today's Total Cloudiness : ", Point(50, 150), FONT_HERSHEY_SIMPLEX, 1, Scalar(220, 245, 245), 3);

    // 이모지 이미지 불러오기
    Mat emoji = imread(folderPath + "smile.png", IMREAD_UNCHANGED); // IMREAD_UNCHANGED로 알파 채널 포함
    if (emoji.empty()) {
        cerr << "이모지 이미지 불러오기 실패!" << endl;
        return -1;
    }

    // 이모지 이미지 크기 조정
    double scale = 0.04;
    Mat resizedEmoji;
    resize(emoji, resizedEmoji, Size(), scale, scale);

    // 이모지를 놓을 위치 정의
    int emojiX = 340;
    int emojiY = 30;

    // 이미지 범위를 벗어나는지 확인
    if (emojiX + resizedEmoji.cols > img.cols || emojiY + resizedEmoji.rows > img.rows) {
        cerr << "이모지가 이미지의 범위를 벗어납니다!" << endl;
        return -1;
    }

    // ROI 설정
    Rect roi(Point(emojiX, emojiY), resizedEmoji.size());

    // 알파 채널이 있는 경우 투명도를 유지하면서 복사
    if (resizedEmoji.channels() == 4) {
        for (int r = 0; r < resizedEmoji.rows; ++r) {
            for (int c = 0; c < resizedEmoji.cols; ++c) {
                Vec4b& rgba = resizedEmoji.at<Vec4b>(r, c);
                if (rgba[3] > 0) { // 알파 채널이 0이 아닌 경우
                    img.at<Vec3b>(emojiY + r, emojiX + c)[0] = rgba[0];
                    img.at<Vec3b>(emojiY + r, emojiX + c)[1] = rgba[1];
                    img.at<Vec3b>(emojiY + r, emojiX + c)[2] = rgba[2];
                }
            }
        }
    } else {
        resizedEmoji.copyTo(img(roi));
    }

    imshow("img", img);
    waitKey(0);

    return 0;
}
