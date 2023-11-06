#ifndef QUOTE_H
#define QUOTE_H

#include <string>

class Quote {
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) {}
    std::string isbn() const { return bookNo; }
    // 返回给定数量的书籍的销售总额
    // 派生类负责改写并使用不同的折扣计算算法
    virtual double net_price(std::size_t n) const { return n * price; }
    // 拷贝构造函数
    Quote(const Quote &q) : bookNo(q.bookNo), price(q.price) {}
    // 拷贝赋值运算符
    Quote &operator=(const Quote &rhs) {
        if (this != &rhs) {
            bookNo = rhs.bookNo;
            price = rhs.price;
        }
        return *this;
    }
    // 移动构造函数
    Quote(Quote &&q) noexcept : bookNo(std::move(q.bookNo)), price(q.price) {}
    // 移动赋值运算符
    Quote &operator=(Quote &&rhs) noexcept {
        if (this != &rhs) {
            bookNo = std::move(rhs.bookNo);
            price = rhs.price;
        }
        return *this;
    }
    virtual ~Quote() = default; // 对析构函数进行动态绑定
private:
    std::string bookNo; // 书籍的ISBN编号
protected:
    double price = 0.0; // 代表普通状态下不打折的价格
};


#endif // QUOTE_H
