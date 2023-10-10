#ifndef STRVEC_H
#define STRVEC_H

#include <string>
#include <memory>

// 类vector类分配内存策略的简化实现：
class StrVec {
    // 重载的输出运算符作为友元函数
    friend std::ostream &operator<<(std::ostream &, const StrVec &);
public:
    // allocator成员进行默认初始化
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec &);                  // 拷贝构造函数
    StrVec &operator=(const StrVec &);       // 拷贝赋值运算符
    ~StrVec();                              // 析构函数
    void push_back(const std::string &);     // 拷贝元素
    size_t size() const { return first_free - elements; }  // 返回元素个数
    size_t capacity() const { return cap - elements; }     // 返回容量
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }
    // ...

private:
    static std::allocator<std::string> alloc;  // 分配元素的工具
    // 被添加元素的函数所使用
    void chk_n_alloc() { if (size() == capacity()) reallocate(); }
    // 工具函数，被拷贝构造函数、赋值运算符和析构函数所使用
    std::pair<std::string *, std::string *> alloc_n_copy(const std::string *, const std::string *);
    void free();            // 销毁元素并释放内存
    void reallocate();      // 获得更多内存并拷贝已有元素
    // 指向数组首元素的指针
    std::string *elements;
    // 指向数组第一个空闲元素的指针
    std::string *first_free;
    // 指向数组尾后位置的指针
    std::string *cap;
};


#endif // STRVEC_H
