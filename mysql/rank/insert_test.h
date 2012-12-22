// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)


#ifndef RANK_INSERT_TEST_H_
#define RANK_INSERT_TEST_H_

#include <gtest/gtest.h>
#include <vector>
#include <cstdlib>
#include <ctime>

class InsertTest : public ::testing::Test {
public:
    std::vector<int> cases;
    std::vector<int> offsets;
public:
    InsertTest() {
#define CNT 100000
        srand((unsigned)time(NULL));
        for(int i = 0; i < 10; ++i) {
            cases.push_back(rand() % CNT + 1);
            offsets.push_back(rand() % 1000 - 500);
        }
    }
};
#endif  // RANK_INSERT_TEST_H_

