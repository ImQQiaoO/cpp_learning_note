#ifndef QUERY_BASE_H
#define QUERY_BASE_H

#include <string>

#include "TextQuery.h"

// 这是一个抽象基类，具体的查询类型从中派生，所有成员都是private 的
class Query_base {
    friend class Query;
protected:
    using line_no = TextQuery::line_no; // 用于eval函数
    virtual ~Query_base() = default;
private:
    // eval返回与当前Query匹配的QueryResult
    virtual QueryResult eval(const TextQuery &) const = 0;
    // rep是表示查询的一个string
    virtual std::string rep() const = 0;
};


#endif // QUERY_BASE_H
