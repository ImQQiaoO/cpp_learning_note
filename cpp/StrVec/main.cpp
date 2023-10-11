#include <iostream>
#include "StrVec.h"

using namespace std;

int main() {
    StrVec sv;
    sv.push_back("Hello");
    sv.push_back("World");
    cout << sv << endl;

    return 0;
}
