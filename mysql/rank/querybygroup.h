// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)


#ifndef RANK_QUERYBYGROUP_H_
#define RANK_QUERYBYGROUP_H_

#include "mysql/connect/connect.h"
#include "rank/property.h"

namespace Query {
    using namespace std;
    using namespace RankProperty;

    class QueryByGroup {
#define CNT 100000
#define MAX_SCORE (CNT/10 - 1)
    private:
        stringstream sql;
        MuyeMySQL::MuyeConnection con;
        tr1::shared_ptr<sql::Connection> connect;
        tr1::shared_ptr<sql::Statement> stmt;
    public:
        QueryByGroup();
    public:
        int query(int uid);
        bool update(int uid, int offset);
    };
} // namespace Query

#endif  // RANK_QUERYBYGROUP_H_

