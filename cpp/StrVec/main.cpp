#include <iostream>
#include "StrVec.h"

using namespace std;

// 静态变量
allocator<string> StrVec::alloc;

int main() {
    StrVec sv;
    sv.push_back("Hello");
    sv.push_back("World");
    cout << sv << endl;

    return 0;
}
