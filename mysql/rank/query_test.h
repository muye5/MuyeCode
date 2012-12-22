// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)


#ifndef RANK_QUERY_TEST_H_
#define RANK_QUERY_TEST_H_

#include <gtest/gtest.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using ::testing::TestWithParam;
using ::testing::ValuesIn;

class QueryTest : public TestWithParam<int> {
public:
    std::vector<int> uids;
public:
    QueryTest() {
#define CNT 100000
        srand((unsigned)time(NULL));
        for(int i = 0; i < 100; ++i) {
            uids.push_back(rand() % CNT + 1);
        }
    }
};

#endif  // RANK_QUERY_TEST_H_

