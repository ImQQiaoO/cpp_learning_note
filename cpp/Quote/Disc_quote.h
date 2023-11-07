#ifndef DISC_QUOTE_H
#define DISC_QUOTE_H

#include "Quote.h"

class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string &book, double price, std::size_t qty, double disc) :
        Quote(book, price), quantity(qty), discount(disc) {}
    ~Disc_quote() override = default;
    // 拷贝构造函数
    Disc_quote(const Disc_quote &dq) : Quote(dq), quantity(dq.quantity), discount(dq.discount) {}
    // 拷贝赋值运算符
    Disc_quote &operator=(const Disc_quote &rhs) {
        if (this != &rhs) {
            Quote::operator=(rhs);
            quantity = rhs.quantity;
            discount = rhs.discount;
        }
        return *this;
    }
    // 移动构造函数
    Disc_quote(Disc_quote &&dq) noexcept : Quote(std::move(dq)), quantity(dq.quantity),
        discount(dq.discount) {}
    // 移动赋值运算符
    Disc_quote &operator=(Disc_quote &&rhs) noexcept {
        if (this != &rhs) {
            Quote::operator=(std::move(rhs));
            quantity = std::move(rhs.quantity);
            discount = std::move(rhs.discount);
        }
        return *this;
    }
    double net_price(std::size_t) const override = 0; // 纯虚函数
    std::pair<size_t, double> discount_policy() const {
        return { quantity, discount };
    }
protected:
    std::size_t quantity = 0;   // 折扣适用的购买量
    double discount = 0.0;      // 表示折扣的小数值
};


#endif // DISC_QUOTE_H
