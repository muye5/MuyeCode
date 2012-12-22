// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)

#ifndef RANK_QUERYBYSQL_H_
#define RANK_QUERYBYSQL_H_

#include "mysql/connect/connect.h"
#include "rank/property.h"

namespace Query {
    using namespace std;
    using namespace RankProperty;

    class QueryBySQL {
    private:
        stringstream sql;
        MuyeMySQL::MuyeConnection con;
        tr1::shared_ptr<sql::Statement> stmt;
    public:
        QueryBySQL();
    public:
        int query(int uid);
    };
} // namespace Query
#endif  // RANK_QUERYBYSQL_H_

