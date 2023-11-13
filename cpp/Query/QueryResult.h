#ifndef QUERYRESULT_H
#define QUERYRESULT_H
#include <set>
#include <vector>

#include "TextQuery.h"

std::string make_plural(size_t count, const std::string &word, const std::string &ending);

class QueryResult {
    friend std::ostream &print(std::ostream &, const QueryResult &);
public:
    QueryResult(std::string s,
                std::shared_ptr<std::set<TextQuery::line_no>> p,
                std::shared_ptr<std::vector<std::string>> f) :
        sought(s), lines(p), file(f) {}
    std::set<TextQuery::line_no>::iterator begin() { return lines->begin(); }
    std::set<TextQuery::line_no>::iterator end() { return lines->end(); }
    std::shared_ptr<std::vector<std::string>> get_file() { return file; }
private:
    std::string sought;        // 查询单词
    std::shared_ptr<std::set<TextQuery::line_no>> lines;        // 出现的行号
    std::shared_ptr<std::vector<std::string>> file;        // 输入文件
};

std::ostream &print(std::ostream &os, const QueryResult &qr);

#endif // QUERYRESULT_H
