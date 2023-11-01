#ifndef BULK_QUOTE_H
#define BULK_QUOTE_H

#include <string>

#include "Disc_quote.h"

// 当同一书籍的销售量超过一个给定的值时，将享受折扣
// 折扣的值是一个小于1的正小数，表示折扣额
class Bulk_quote : public Disc_quote {	// Bulk_quote继承了抽象基类Disc_quote
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string &book, double price, std::size_t qty, double disc) :
        Disc_quote(book, price, qty, disc) {}
    // 覆盖基类的函数版本以实现基于大量购买的折扣政策
    double net_price(std::size_t) const override;

};


#endif // BULK_QUOTE_H
