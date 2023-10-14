#include <iostream>

#include "Message.h"
#include "Folder.h"

using namespace std;

int main() {
    auto m1 = new Message("m1");
    auto m2 = new Message("m2");
    auto f1 = new Folder();     // 两个不同的Message被存放到同一个Folder中
    m1->save(*f1);
    m2->save(*f1);

    m1->print_debug();      // m1
    m2->print_debug();      // m2

    swap(*m1, *m2);

    m1->print_debug();      // m2
    m2->print_debug();      // m1

    delete m1;
    delete m2;
    delete f1;
    return 0;
}
