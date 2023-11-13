#include "Query.h"
#include "WordQuery.hpp"

Query::Query(const std::string &s) : q(new WordQuery(s)) {}

