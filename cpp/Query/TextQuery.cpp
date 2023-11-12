#include <sstream>
#include <string>

#include "TextQuery.h"

TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>) {
    std::string text;
    while (getline(is, text)) {			// 对文件中的每一行
        file->push_back(text);			// 保留此行文本
        int n = file->size() - 1;		// 当前行号
        std::istringstream line(text);		// 将行文本分解为单词
        std::string word;
        while (line >> word) {			// 对行中每个单词
            // 如果单词不在wm中，以之为下标在wm中添加一项
            auto &lines = wm[word];		// lines是一个shared_ptr
            if (!lines)					// 在我们第一次遇到这个单词时，此指针为空
                lines.reset(new std::set<line_no>);		// 分配一个新的set
            lines->insert(n);			// 将此行号插入set中
        }
    }
}