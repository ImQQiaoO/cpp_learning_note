#ifndef NOTQUERY_H
#define NOTQUERY_H

#include "QueryResult.h"
#include "Query.h"

class NotQuery : public Query_base {
	friend Query operator~(const Query &);
	NotQuery(const Query &q) : query(q) {}
	// 具体的类：NotQuery 将定义所有继承而来的纯虚函数
	std::string rep() const override { return "~(" + query.rep() + ")"; }
	QueryResult eval(const TextQuery &) const override;
	Query query;
};

inline Query operator~(const Query &operand) {
	return std::shared_ptr<Query_base>(new NotQuery(operand));
}


#endif // NOTQUERY_H
