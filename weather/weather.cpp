#include <curl/curl.h>
#include <stdio.h>
#include <string>


//세종 : 239


int main() {
    CURL* curl = curl_easy_init();
    if (curl) {
        FILE* fp = fopen("output1.txt", "wb");
        //세종특별자치시 code : 239
        const char* url = "https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=0&stn=239&help=1&authKey=bkPKWXM3RQmDyllzN-UJmA" ; // URL 문자열 변수 설정
        curl_easy_setopt(curl, CURLOPT_URL, url); // URL 설정
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // 데이터 쓰기 설정
        CURLcode res = curl_easy_perform(curl); // 데이터 다운로드 수행
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res)); // 오류 처리
        }
        curl_easy_cleanup(curl); // CURL 정리
        fclose(fp); // 파일 닫기
    }
    
    return 0;
}

