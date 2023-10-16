#include <iostream>
#include "StrVec.h"

using namespace std;

int main() {
    StrVec sv;
    sv.push_back("Hello");
    sv.push_back("World");
    cout << sv << endl;

    /* An Example in Chap 13.6.2 */
    //StrVec v1, v2;
    //v1 = v2;    // v2是左值，调用拷贝赋值运算符
    //StrVec getVec(istream &);   // getVec的返回值是右值
    //v2 = getVec(cin);   // getVec(cin)的返回值是右值，调用移动赋值运算符

    return 0;
}
