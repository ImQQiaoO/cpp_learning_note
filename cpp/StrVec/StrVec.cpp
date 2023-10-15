#include <memory>
#include <iostream>
#include <string>

#include "StrVec.h"

void StrVec::push_back(const std::string& s) {
    chk_n_alloc();  // 确保有空间容纳新元素
    // 在first_free指向的元素中构造s的副本
    //alloc.construct(first_free++, s);		// 注意：C++20中此函数已被移除！！
    std::allocator_traits<decltype(alloc)>::construct(alloc, first_free++, s);
}

void StrVec::push_back(std::string &&s) {
    chk_n_alloc();  // 确保有空间容纳新元素
    // 在first_free指向的元素中构造s的副本
    //alloc.construct(first_free++, std::move(s));		// 注意：C++20中此函数已被移除！！
    std::allocator_traits<decltype(alloc)>::construct(alloc, first_free++, std::move(s));
}

std::pair<std::string*, std::string*> StrVec::alloc_n_copy(const std::string* b,
    const std::string* e) {

    // 分配空间保存给定范围中的元素
    auto data = alloc.allocate(e - b);
    // 初始化并返回一个pair，该pair由data和uninitialized_copy的返回值构成
    return { data, std::uninitialized_copy(b, e, data) };
}

void StrVec::free() {
    // 不能传递给deallocate一个空指针，如果elements为0，函数什么也不做
    if (elements) {
        // 逆序销毁旧元素
        for (auto p = first_free; p != elements; /* 空 */) {
            // destroy的参数必须是指向构造出的元素
            std::allocator_traits<decltype(alloc)>::destroy(alloc, --p);
        }
        alloc.deallocate(elements, cap - elements);
    }
}

StrVec::StrVec(const StrVec& s) {
    // 调用alloc_n_copy分配空间以容纳与s中一样多的元素
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVec() {
    free();
}

StrVec& StrVec::operator=(const StrVec& rhs) {
    if (this == &rhs) {
        return *this;
    }
    // 调用alloc_n_copy分配内存，大小与rhs中元素占用空间一样多
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    this->free();     // 销毁对象在this指向的元素
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::reallocate() {
    // 我们分配当前大小两倍的内存空间
    auto newcapacity = size() ? 2 * size() : 1;
    // 分配新内存
    auto newdata = alloc.allocate(newcapacity);
    // 将数据从旧内存移动到新内存
    auto dest = newdata;    // 指向新数组中下一个空闲位置
    auto elem = elements;   // 指向旧数组中下一个元素
    for (size_t i = 0; i != size(); ++i) {
        // 使用移动构造函数，将元素从旧位置移动到新位置
        // alloc.construct(dest++, std::move(*elem++));		// 注意：C++20中此函数已被移除！！
        std::allocator_traits<decltype(alloc)>::construct(alloc, dest++, std::move(*elem++));
    }
    free();     // 一旦我们移动完元素就释放旧内存空间
    // 更新我们的数据结构，执行新元素
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

// 为什么MSVC编译器（C++20）重载运算符<<时，不能直接使用字符串的字面值？
// 但是GCC编译器（C++20）可以直接使用字符串的字面值。MSVC（C++17）也可以直接使用字符串的字面值。
// 例如：os << "{Hello, World}"，会报错：error C2679: 二进制“<<”: 没有找到接受“const char [14]”类型的左操作数的运算符(或没有可接受的转换)
// 原因： MSVC编译器不支持C++20中的std::string_view类型，而C++20中的std::string_view类型可以直接使用字符串的字面值。
//os << std::string("{");
std::ostream& operator<<(std::ostream& os, const StrVec& sv) {
    os << "{";
    for (auto p = sv.begin(); p != sv.end(); ++p) {
        os << *p;
        if (p != sv.end() - 1) {
            os << ", ";
        }
    }
    os << "}";
    return os;
}

StrVec::StrVec(StrVec&& s)      // 移动操作不应抛出任何异常
// 成员初始化器接管s中的资源
    : elements(s.elements), first_free(s.first_free), cap(s.cap) {
    // 令s进入这样的状态：对其运行析构函数是安全的
    s.elements = s.first_free = s.cap = nullptr;
}

StrVec& StrVec::operator=(StrVec&& rhs) noexcept {
    if (this == &rhs) {
        return *this;
    }
    this->free();     // 释放已有元素
    elements = rhs.elements;    // 从rhs中接管资源
    first_free = rhs.first_free;
    cap = rhs.cap;
    // 将rhs置于可析构状态
    rhs.elements = rhs.first_free = rhs.cap = nullptr;
    return *this;
}

