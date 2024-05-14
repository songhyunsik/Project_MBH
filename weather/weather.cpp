#include <curl/curl.h>
#include <stdio.h>
#include <string>


//https://apihub.kma.go.kr/api/typ01/url/fct_shrt_reg.php?stn=239&tmfc=0&authKey=93hdUM5UQ6O4XVDOVOOjwA

// 단기 육상예보
// https://apihub.kma.go.kr/api/typ01/url/fct_afs_dl.php?reg=&tmfc1=2013121106&tmfc2=2013121118&disp=0&help=1&authKey=93hdUM5UQ6O4XVDOVOOjwA

int main() {
    CURL* curl = curl_easy_init();
    if (curl) {
        FILE* fp = fopen("output1.txt", "wb");
        //세종특별자치시 code : 239
        const char* url = "https://apihub.kma.go.kr/api/typ01/url/fct_afs_dl.php?reg=&tmfc=0&stn=239&disp=0&help=1&authKey=93hdUM5UQ6O4XVDOVOOjwA" ; // URL 문자열 변수 설정
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

