#ifndef DISC_QUOTE_H
#define DISC_QUOTE_H

#include "Quote.h"

class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string &book, double price, std::size_t qty, double disc) :
        Quote(book, price), quantity(qty), discount(disc) {}
    ~Disc_quote() override = default;
    double net_price(std::size_t) const override = 0; // 纯虚函数
    std::pair<size_t, double> discount_policy() const {
        return { quantity, discount };
    }
protected:
    std::size_t quantity = 0;   // 折扣适用的购买量
    double discount = 0.0;      // 表示折扣的小数值
};


#endif // DISC_QUOTE_H
