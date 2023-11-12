#ifndef QUERY_H
#define QUERY_H

#include <string>

#include "Query_base.h"
#include "TextQuery.h"
#include "QueryResult.h"

// 这是一个管理Query_base继承体系的接口类
class Query {
    friend Query operator~(const Query &);
    friend Query operator|(const Query &, const Query &);
    friend Query operator&(const Query &, const Query &);
    friend std::ostream &operator<<(std::ostream &, const Query &);
public:
    Query(const std::string &); // 构建一个新的WordQuery
    // 接口函数：调用对应的Query_base操作
    QueryResult eval(const TextQuery &t) const { return q->eval(t); }
    std::string rep() const { return q->rep(); }

private:
    Query(std::shared_ptr<Query_base> query) : q(query) {}
    std::shared_ptr<Query_base> q;
};

inline std::ostream &operator<<(std::ostream &os, const Query &query) {
    // Query::rep通过它的Query_base指针对rep()进行了虚调用
    return os << query.rep();
}

#endif // QUERY_H
