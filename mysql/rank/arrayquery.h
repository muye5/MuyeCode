// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)

#ifndef RANK_ARRAYQUERY_H_
#define RANK_ARRAYQUERY_H_

#include "mysql/connect/connect.h"
#include "rank/property.h"

namespace Query {
    using namespace std;
    using namespace RankProperty;

    class QueryArray {
    private:
#define CNT 100000
#define MAX_SCORE (CNT/10 - 1)
        bool flag;
        stringstream sql;
        MuyeMySQL::MuyeConnection con;
        tr1::shared_ptr<sql::Statement> stmt;
        int* uids;
        int* ranks;
    public:
        QueryArray();
        ~QueryArray();
    public:
        int query(int uid);
        bool update(int uid, int offset);
    };
} // namespace Query
#endif  // RANK_ARRAYQUERY_H_

