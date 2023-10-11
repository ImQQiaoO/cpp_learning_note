#include <iostream>
#include <vector>

#include "String.h"

using namespace std;

void test_func() {
    // test default constructor and operator<<
    String s1("Hello");
    String s2("World");
    cout << "s2 size is: " << s2.size() << endl;

    // test copy constructor
    s1 = s2;
    cout << s1 << endl;
    cout << s2 << endl;

    // test operator+=
    String s3("Hellohaha");
    String s4("World");

    s3 += s4;

    cout << s3 << endl;
    cout << s4 << endl;


    // test operator+
    String s5("Hello");
    String s6("World");
    String s7;
    s7 = s5 + s6;
    cout << "s7 is:";
    cout << s7 << endl;
    cout << "s7 size is : ";
    cout << s7.size() << endl;
}

int main() {
    //test_func();
    vector<String> vec;
    vec.reserve(5); // 申请5个空间，避免多次扩容
    vec.push_back("Hello0");
    vec.push_back("Hello1");
    vec.push_back("Hello2");
    vec.push_back("Hello3");
    vec.push_back("Hello4");

    return 0;
}
