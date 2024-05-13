// libcurl을 사용하여 API를 호출하고, 결과를 읽고 출력합니다.
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <cstring>

int main(int argc, char* argv[]) {
  // libcurl 객체를 초기화합니다.
  CURL* curl;
  CURLcode res;
  std::string readBuffer;

  curl = curl_easy_init();
  if (curl) {
    // 요청 URL을 설정합니다.
    curl_easy_setopt(curl, CURLOPT_URL, "https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=202405130900&stn=0&help=0&authKey=93hdUM5UQ6O4XVDOVOOjwA");
    // 리다이렉션을 따르도록 설정합니다.
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    // 응답을 어떻게 처리할지 설정하는 콜백 함수를 등록합니다.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](char* ptr, size_t size, size_t nmemb, std::string* data) -> size_t {
        // 응답의 각 조각(chunk)을 읽어들여 버퍼에 추가합니다.
        data->append(ptr, size * nmemb);
        // std::cout << data << std::endl;
        return size * nmemb;
    });
    // WRITEFUNCTION 콜백 함수에서 사용할 데이터를 설정합니다. 여기서는 readBuffer를 사용합니다.
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    // 요청을 실행하고 결과를 저장합니다.
    // res = curl_easy_perform(curl);
    // std::cout << res << std::endl;
    
    // libcurl 객체를 정리합니다.
    curl_easy_cleanup(curl);

    // 응답을 출력합니다.
    // std::cout << readBuffer << std::endl;
  }
  return 0;
}