#include <iostream>
#include <fstream>

#include "Query.h"
#include "AndQuery.h"
#include "OrQuery.h"
#include "TextQuery.h"
#include "QueryResult.h"

using namespace std;

int main() {
    // test Query
    Query q = Query("fiery") & Query("bird") | Query("wind");
    cout << q << endl;
    ifstream ifs("text.txt");
    if (!ifs) {
        cerr << "No data!" << endl;
        return -1;
    }
    TextQuery tq(ifs);
    QueryResult qr = q.eval(tq);
    print(cout, qr);

    return 0;
}