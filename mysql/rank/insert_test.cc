// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)

#include "rank/querybygroup.h"
#include "rank/arrayquery.h"
#include "rank/treequery.h"
#include "rank/insert_test.h"
#include <gtest/gtest.h>

using namespace std;
using namespace Query;

TEST_F(InsertTest, GroupUpdate) {
    QueryByGroup grp;

    for(vector<int>::iterator it1 = cases.begin(), it2 = offsets.begin(); it1 != cases.end(); ++it1, ++it2) {
        ASSERT_TRUE(grp.update(*it1, *it2)) << "[uid:offset] = [" << *it1 << ":" << *it2 << "]";
    }
}

TEST_F(InsertTest, ArrayAndTree) {
    QueryArray qar;
    QueryTree qtr;

    for(vector<int>::iterator it1 = cases.begin(), it2 = offsets.begin(); it1 != cases.end(); ++it1, ++it2) {
        ASSERT_TRUE(qar.update(*it1, *it2)) << "[uid:offset] = [" << *it1 << ":" << *it2 << "]";
        ASSERT_TRUE(qtr.update(*it1, *it2)) << "[uid:offset] = [" << *it1 << ":" << *it2 << "]";
    }
    for(vector<int>::iterator it = cases.begin(); it != cases.end(); ++it) {
        EXPECT_EQ(qar.query(*it), qtr.query(*it));
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
