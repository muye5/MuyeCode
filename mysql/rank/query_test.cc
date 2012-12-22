// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)

#include "rank/querybysql.h"
#include "rank/querybygroup.h"
#include "rank/treequery.h"
#include "rank/arrayquery.h"
#include "rank/query_test.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <gtest/gtest.h>

using namespace std;
using namespace Query;

vector<int> GetParameter() {
    vector<int> values;
    srand((unsigned)time(NULL));
    for(int i = 0; i < 10; ++i) {
        values.push_back(rand() % 100000 + 1);
    }
    return values;
}

TEST_P(QueryTest, Sql) {
    QueryBySQL sql;
    QueryByGroup grp;
    QueryTree qtr;
    QueryArray qar;
    int uid = GetParam();

    EXPECT_EQ(sql.query(uid), grp.query(uid));
    EXPECT_EQ(sql.query(uid), qtr.query(uid));
    EXPECT_EQ(sql.query(uid), qar.query(uid));
}

INSTANTIATE_TEST_CASE_P(QueryTest, QueryTest, ValuesIn(GetParameter()));

TEST_F(QueryTest, GroupQuery) {
    QueryByGroup grp;
    QueryBySQL sql;

    for(vector<int>::iterator it = uids.begin(); it != uids.end(); ++it) {
        EXPECT_EQ(sql.query(*it), grp.query(*it));
    }
}

TEST_F(QueryTest, ArrayQuery) {
    QueryArray qar;
    QueryBySQL sql;

    for(vector<int>::iterator it = uids.begin(); it != uids.end(); ++it) {
        EXPECT_EQ(sql.query(*it), qar.query(*it));
    }
}

TEST_F(QueryTest, TreeQuery) {
    QueryTree qtr;
    QueryBySQL sql;

    for(vector<int>::iterator it = uids.begin(); it != uids.end(); ++it) {
        EXPECT_EQ(sql.query(*it), qtr.query(*it));
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
