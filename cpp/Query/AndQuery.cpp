#include "AndQuery.h"
#include <algorithm>

// 返回运算对象的交集
QueryResult AndQuery::eval(const TextQuery &text) const {
    // 通过Query成员lhs和rhs进行的虚调用，以获得运算对象的查询结果set
    auto left = lhs.eval(text), right = rhs.eval(text);
    // 将左侧运算对象的行号拷贝到结果set中
    auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
    // 将两个范围的交集写入一个目的迭代器中
    std::set_intersection(left.begin(), left.end(),
                          right.begin(), right.end(),
                          std::inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}
