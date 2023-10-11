#include <memory>
#include <algorithm>
#include <iostream>

#include "String.h"

// 构造首尾指针范围内的元素
std::pair<char*, char*> String::equal_range(const char* b, const char* e) {
    auto data = String::alloc.allocate(e - b);
    return { data, std::uninitialized_copy(b, e, data) };
}

// 记录首尾指针
void String::range_pointer(const char* first, const char* last) {
    const auto res = equal_range(first, last);
    this->elements = res.first;
    this->end = res.second;
}

void String::init(const char* s) {
    auto p = s;
    while (*p) {
        ++p;
    }
    range_pointer(s, p);
}

String::String(const char* s) {
    init(s);
    // 此处需要construct吗？
    // 不需要。因为init函数中已经调用了uninitialized_copy函数，该函数会调用construct函数。
}

String::String(const String& rhs) {
    std::cout << "Copy Constructor, curr element is : " << rhs << std::endl;
    range_pointer(rhs.elements, rhs.end);
}

void String::free() {
    // 确认对象不为空
    if (elements) {
        std::for_each(elements, end, [this](char& c) {
            std::allocator_traits<decltype(alloc)>::destroy(alloc, &c);
            });
        alloc.deallocate(elements, end - elements);
    }
}

String::~String() {
    free();
}

String& String::operator=(const String& rhs) {
    std::cout << "Copy Assignment Operator" << std::endl;
    if (this == &rhs) {
        //std::cout << "Self Assignment" << std::endl;
        return *this;
    }
    this->free();
    range_pointer(rhs.elements, rhs.end);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const String& s) {
    for (auto p = s.elements; p != s.end; ++p) {
        os << *p;
    }
    return os;
}

String& String::operator+=(const String& rhs) {
    const auto new_size = size() + rhs.size();
    auto new_data = alloc.allocate(new_size);
    auto dest = std::uninitialized_copy(elements, end, new_data);
    dest = std::uninitialized_copy(rhs.elements, rhs.end, dest);
    this->free();
    this->elements = new_data;
    this->end = dest;
    return *this;
}

String operator+(const String& rhs, const String& lhs) {
    String ret = rhs;
    ret += lhs;
    return ret;     // 返回一个rvalue
}
