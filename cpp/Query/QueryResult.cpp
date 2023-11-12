#include <string>
#include <memory>
#include "QueryResult.h"

std::string make_plural(size_t count, const std::string &word, const std::string &ending) {
    return count > 1 ? word + ending : word;
}

QueryResult TextQuery::query(const std::string &sought) const {
    // 如果未找到sought，我们将返回一个指向此set的指针
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    // 使用find而不是下标运算符来查找单词，避免将单词添加到wm中
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file);    // 未找到
    else
        return QueryResult(sought, loc->second, file);
}

std::ostream &print(std::ostream &os, const QueryResult &qr) {
    // 如果找到了单词，打印出现次数和所有出现的位置
    os << qr.sought << " occurs " << qr.lines->size() << " "
        << make_plural(qr.lines->size(), "time", "s") << std::endl;
    // 打印单词出现的每一行
    for (auto num : *qr.lines)        // 对set中每个单词
        // 避免行号从0开始给用户带来的困惑
        os << "\t(line " << num + 1 << ") "
        << *(qr.file->begin() + num) << std::endl;
    return os;
}

