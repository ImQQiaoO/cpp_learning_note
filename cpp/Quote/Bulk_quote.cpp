#include "Bulk_quote.h"

// 如果达到了购买的最低量，则使用折扣价格计算
double Bulk_quote::net_price(std::size_t cnt) const {
    return cnt >= quantity ? cnt * (1 - discount) * price : cnt * price;
}
