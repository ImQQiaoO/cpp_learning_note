#include <iostream>
#include "String.h"

using namespace std;

int main() {
    String s1("Hello");
    String s2("World");
    s1 = s2;
    cout << s1 << endl;
    cout << s2 << endl;
    return 0;
}
