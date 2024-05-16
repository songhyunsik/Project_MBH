#include <iostream>
#include <string>

using namespace std;

string intToString(int number) {
    return to_string(number);
}

int main() {
    int num = 123;
    string str = intToString(num);
    cout << "정수를 문자열로 변환한 결과: " << str << endl;
    return 0;
}