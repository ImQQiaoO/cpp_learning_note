#ifndef BASKET_H
#define BASKET_H

#include <memory>
#include <set>


#include "Quote.h"

double print_total(std::ostream &os, const Quote &item, size_t n);

class Basket {
public:
    // Basket使用合成的默认构造函数和拷贝控制成员
    void add_item(const std::shared_ptr<Quote> &sale) { items.insert(sale); }
    // 打印每本书的总价和购物篮中所有书的总价
    double total_receipt(std::ostream &) const;
    // 该函数用于比较shared_ptr,multiset成员会用到它
private:
    static bool compare(const std::shared_ptr<Quote> &lhs,
                        const std::shared_ptr<Quote> &rhs) {
        return lhs->isbn() < rhs->isbn();
    }
    // multiset保存多个报价，按照compare成员排序
    std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items{ compare };
    //std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items1(compare);
    // 编译器会将上面的写法解析成函数声明，所以要是有{ }
};

#endif // BASKET_H
