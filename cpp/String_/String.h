#ifndef STRING_H
#define STRING_H

#include <memory>
#include <utility>

class String {
    friend std::ostream& operator<<(std::ostream&, const String&); // 输出运算符
    friend String operator+(const String&, const String&);
public:
    String() : String("") {}          // 默认构造函数
    String(const char* s);              // 构造函数
    String(const String&);              // 拷贝构造函数
    String& operator=(const String&);   // 拷贝赋值运算符
    ~String();                          // 析构函数
    // 移动构造函数
    String(String&& s) noexcept : elements(s.elements), end(s.end) {
        s.elements = s.end = nullptr;
    }
    // 移动赋值运算符
    String& operator=(String&& rhs) noexcept {
        if (this != &rhs) {
            free();
            elements = rhs.elements;
            end = rhs.end;
            rhs.elements = rhs.end = nullptr;
        }
        return *this;
    }
    size_t size() const { return end - elements; } // 返回数组大小
    String& operator+=(const String&);  // 重载+=运算符

private:
    std::allocator<char> alloc;  // 分配内存

    char* elements; // 指向数组首元素的指针
    char* end;  // 指向数组尾元素的下一个位置的指针

    void init(const char*); // 工具函数
    void free();    // 工具函数

    std::pair<char*, char*> equal_range(const char* b, const char* e); // 工具函数
    void range_pointer(const char* first, const char* last); // 工具函数

};

std::ostream& operator<<(std::ostream&, const String&); // 输出运算符
String operator+(const String&, const String&); // 重载+运算符

#endif // STRING_H
