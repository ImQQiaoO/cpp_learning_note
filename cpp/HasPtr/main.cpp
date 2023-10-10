// HasPtr.cpp: 定义应用程序的入口点。
//
#include <algorithm>
#include <vector>

#include "HasPtr.h"

using namespace std;

int main() {
    HasPtr hp1("hello");
    HasPtr hp2("Hiiii");
    HasPtr hp3("GenshenImpact!");

    vector<HasPtr> vec{ hp1, hp2, hp3 };
    sort(vec.begin(), vec.end());

    cout << endl;
    for (auto &i : vec) {
        cout << i.getStr() << endl;
    }

    return 0;
}
