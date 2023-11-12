#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <memory>
#include <set>


class QueryResult;		// 为了定义函数query的返回类型，这个定义是必需的
class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream &);
	QueryResult query(const std::string &) const;
private:
	std::shared_ptr<std::vector<std::string>> file;		// 输入文件
	// 每个单词到它所在行号的集合的映射
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};


#endif // TEXTQUERY_H
