#ifndef WORDQUERY_H
#define WORDQUERY_H

#include "Query_base.h"
#include "QueryResult.h"

class WordQuery : public Query_base {
    friend class Query;     // Query 使用 WordQuery 的构造函数
    WordQuery(const std::string &s) : query_word(s) {}
    // 具体的类：WordQuery 将定义所有继承而来的纯虚函数
    QueryResult eval(const TextQuery &t) const override { return t.query(query_word); }
    std::string rep() const override { return query_word; }
    std::string query_word; // 要查找的单词
};


#endif // WORDQUERY_H
