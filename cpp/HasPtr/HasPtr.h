// HasPtr.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#ifndef HASPTR_H
#define HASPTR_H

#include <iostream>
#include <string>

/**
 * 像值一样使用的类
 */
class HasPtr {

    friend void swap(HasPtr &, HasPtr &);

private:
    std::string *ps;
    int i;

public:
    HasPtr(const std::string &s = std::string()) :
        ps(new std::string(s)), i(0) {
    }

    // 编写一个拷贝构造函数，拷贝所有成员，动态分配一个新的string，
    // 并将对象拷贝到ps指向的位置，而不是拷贝ps本身
    HasPtr(const HasPtr &p) :
        ps(new std::string(*p.ps)), i(p.i) {
    }

    // 析构函数
    ~HasPtr() {
        delete ps;
    }

    // 为HasPtr定义一个赋值运算符，类似于拷贝构造函数，赋值运算符
    // 应该将对象拷贝到ps指向的位置，而不是拷贝ps本身
    HasPtr &operator=(const HasPtr &p) {
        // 避免自我赋值，比的是地址
        if (this == &p) {
            return *this;
        }
        std::cout << "我被执行了！" << std::endl;
        auto newp = new std::string(*p.ps);
        delete ps;
        ps = newp;
        i = p.i;

        return *this;
    }

    // 定义一个比较运算符<
    bool operator<(const HasPtr &p) const {
        return *ps < *p.ps;
    }

    // 定义一个函数
    std::string &getStr() const {
        return *ps;
    }

};

inline void swap(HasPtr &lhs, HasPtr &rhs) {
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
    std::cout << "swap被执行了！" << std::endl;
}


#endif // HASPTR_H
