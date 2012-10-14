// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>
#define PINF 100000
using namespace std;

const int m = 5, n = 6;

bool young_insert(int (* const &young)[n], const int& v, int& x, int& y);
bool young_delete(int (* const &young)[n], const int& x, const int& y);
bool young_find(const int (* const &young)[n], const int& v, int& x, int& y);
void young_print(const int (* const &young)[n]);

bool young_insert(int (* const &young)[n], const int& v, int& x, int& y) {
    int i = m - 1, j = n - 1;
    while(i >= 0) {
        if(young[i][n-1] == PINF) {
            --i;
        } else {
            break;
        }
    }
    if(i == m - 1) {
        cerr << "no room to insert" << endl;
        return false;
    } else {
        ++i;
        while(j >= 0) {
            if(young[i][j] == PINF) {
                --j;
            } else {
                break;
            }
        }
        young[i][++j] = v;
        int left, up;
        while(i > -1 && j > -1) {
            if(i - 1 == -1 || j - 1 == -1) {
                if(i - 1 == -1 && j - 1 == -1) {
                    up = -PINF;
                    left = -PINF;
                } else if(i - 1 == -1) {
                    up = -PINF;
                    left = young[i][j-1];
                } else {
                    left = -PINF;
                    up = young[i-1][j];
                }
            } else {
                left = young[i][j-1];
                up = young[i-1][j];
            }
            if(young[i][j] >= left && young[i][j] >= up) {
                break;
            } else if(left > young[i][j] && left > up) {
                young[i][j] = left;
                young[i][--j] = v;
            } else {
                young[i][j] = up;
                young[--i][j] = v;
            }
        }
        if(i < 0 || j < 0) {
            cerr << "wrong" << endl;
            exit(-1);
        }
        x = i; y = j;
        return true;
    }
}

bool young_delete(int (* const &young)[n], const int& x, const int& y) {
    if(young[x-1][y-1] == PINF) {
        cerr << "no element to delete" << endl;
        return false;
    }
    int value = PINF;
    for(int i = m - 1; i >= 0; --i) {
        if(young[i][n-1] < PINF) {
            value = young[i][n-1];
            young[i][n-1] = PINF;
            break;
        }
    }
    if(value == PINF) {
        for(int j = n-1; j >= 0; --j) {
            if(young[0][j] < PINF) {
                value = young[0][j];
                young[0][j] = PINF;
                if(x == 1 && y == j + 1) {
                    return true;
                }
                break;
            }
        }
    }
    young[x-1][y-1] = value;
    int i = x - 1, j = y - 1;
    int down = PINF, right = PINF;
    while(i < m && j < n) {
        if(i + 1 == m || j + 1 == n) {
            if(i + 1 == m && j + 1 == n) {
                down = PINF;
                right = PINF;
            } else if(i + 1 == m) {
                down = PINF;
                right = young[i][j+1];
            } else {
                down = young[i+1][j];
                right = PINF;
            }
        } else {
            down = young[i+1][j];
            right = young[i][j+1];
        }
        if(young[i][j] <= down && young[i][j] <= right) {
            break;
        } else if(down > right){
            young[i][j] = right;
            young[i][++j] = value;
        } else {
            young[i][j] = down;
            young[++i][j] = value;
        }
    }
    return true;
}

bool young_find(const int (* const &young)[n], const int& v, int& x, int& y) {
    for(x = m - 1, y = 0; x >= 0; --x) {
        if(young[x][0] < PINF) {
            break;
        }
    }
    while(x >= 0 && y < n) {
        if(young[x][y] == v) {
            return true;
        } else if(young[x][y] > v) {
            --x;
        } else {
            ++y;
        }
    }
    return false;
}

void young_print(const int (* const &young)[n]) {
    cout << "==================================================" << endl;
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            if(young[i][j] == PINF) {
                printf("%-8s", "PINF");
            } else {
                printf("%-8d", young[i][j]);
            }
        }
        cout << endl;
    }
    cout << "==================================================" << endl;
}

TEST(young_insert, insert) {
    vector<int> temp(m*n, PINF);
    int young[m][n];
    int x, y;
    copy(temp.begin(), temp.end(), young[0]);
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            EXPECT_TRUE(young_insert(young, i * m + j, x, y));
        }
    }
    EXPECT_TRUE(false == young_insert(young, 1, x, y));
}

TEST(young_find, find) {
    int young[m][n] = {{1, 3, 5, 7, 8, 11}, {4, 6, 9, 14, 15, 19},
        {10, 21, 23, 33, 56, 57}, {34, 35, 45, 55, PINF, PINF}, {PINF, PINF, PINF, PINF, PINF, PINF}};
    int x, y, v = 33;
    EXPECT_TRUE(young_find(young, v, x, y));
    cout << v << " = (" << x << ", " << y << ")" << endl;
    EXPECT_TRUE(false == young_find(young, 100, x, y));
}

TEST(young_delete, delete) {
    vector<int> temp(m*n, PINF);
    int young[m][n];
    int x, y;
    copy(temp.begin(), temp.end(), young[0]);
    EXPECT_FALSE(young_delete(young, 2, 3));
    young_insert(young, 3, x, y);
    young_insert(young, 6, x, y);
    EXPECT_TRUE(young_delete(young, 1, 2));
    EXPECT_FALSE(young_delete(young, 1, 2));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

