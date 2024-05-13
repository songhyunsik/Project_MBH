#include <curl/curl.h>
#include <stdio.h>

int main() {
    CURL* curl = curl_easy_init();
    if (curl) {
        FILE* fp = fopen("output.txt", "wb"); // 파일 열기
        const char* url = "https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=202305120900&stn=1&help=0&authKey=93hdUM5UQ6O4XVDOVOOjwA"; // URL 문자열 변수 설정
        curl_easy_setopt(curl, CURLOPT_URL, url); // URL 설정
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // 데이터 쓰기 설정
        CURLcode res = curl_easy_perform(curl); // 데이터 다운로드 수행
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res)); // 오류 처리
        }
        printf("res: %d\n", res);
        curl_easy_cleanup(curl); // CURL 정리
        fclose(fp); // 파일 닫기
    }
    
    return 0;
}