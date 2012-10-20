// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
//
// 七夕那天,雯雯的男朋友小俞给她买了一颗神奇的魔石.
// 这颗魔石平常是暗淡无光的,但只要给这颗魔石擦上魔粉,魔石就会从内部发出不同颜色的绚丽光泽,非常好看.
// 发出的光的颜色,是在魔石上擦的所有魔粉的编号的异或(Xor)值（如果异或值为0,也是一种颜色,异或值相同表示颜色相同）.
// 雯雯手上现在一共有6种魔粉,编号是6 7 17 46 47 56,雯雯非常想知道这颗魔石究竟能发出多少种颜色的光.
// 由于组合实在太多,雯雯便跑过来求助聪明的你,相信你不会让她失望。
// 如果魔粉有20种（编号256以内）,又该如何计算?
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <gtest/gtest.h>
using namespace std;

const int n = sizeof(char) * 8;

void vector_minus(float* a, float* b);
void vector_multiply(float* a, float t);
void vector_swap_row(float* a, float* b);
void vector_swap_column(float matrix[][n], const int& a, const int& b);
int find_most_color(const unsigned char array[], const int& m);

void vector_minus(float* a, float* b) {
    for(int i = 0; i < n; ++i) {
        a[i] -= b[i];
    }
}

void vector_multiply(float* a, float t) {
    for(int i = 0; i < n; ++i) {
        a[i] *= t;
    }
}

void vector_swap_row(float* a, float* b) {
    for(int i = 0; i < n; ++i) {
        float temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

void vector_swap_column(float matrix[][n], const int& m, const int& i, const int& j) {
    for(int k = 0; k < m; ++k) {
        float temp = matrix[k][i];
        matrix[k][i] = matrix[k][j];
        matrix[k][j] = temp;
    }
}

int find_most_color(const unsigned char array[], const int& m) {
    int r = (m > n) ? n : m, rank = 0;
    float matrix[m][n];

    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            if((array[i] >> j) % 2) {
                matrix[i][j] = 1.0f;
            } else {
                matrix[i][j] = 0.0f;
            }
        }
    }

    for(int i, j, k = 0; k < r; ++k) {
        for(i = k; i < m; ++i) {
            for(j = k; j < n; ++j) {
                if(fabs(matrix[i][j]) > 1e-6 && i > k && j > k) {
                    vector_swap_row(matrix[i], matrix[k]);
                    vector_swap_column(matrix, m, k, j);
                    break;
                }
            }
            if(j < n) break;
        }
        if(i == m) break;
        for(i = 0; i < m; ++i) {
            if(i == k || fabs(matrix[i][k]) < 1e-6) continue;
            float diff = matrix[k][k] / matrix[i][k];
            vector_multiply(matrix[i], diff);
            vector_minus(matrix[i], matrix[k]);
        }
    }

    for(int i = 0; i < m; ++i) {
        if(fabs(matrix[i][i]) > 1e-6) {
            ++rank;
        }
    }

    cout << "==============================================" << endl;
    cout << "Rank = " << rank << " and most colors is " << (2 << (rank - 1)) << endl;
    /*
    cout << "==============================================" << endl;
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            printf("%-4.0f", matrix[i][j]);
        }
        cout << endl;
    }
    cout << "==============================================" << endl;
    */
    return 2 << (rank - 1);
}

TEST(find_most_color, test) {
    const int len = 6;
    unsigned char value[] = {1, 2, 4, 8, 16, 32};
    EXPECT_TRUE(64 == find_most_color(value, len));
    value[0] = 3;
    EXPECT_TRUE(64 == find_most_color(value, len));
    value[0] = 6;
    EXPECT_TRUE(32 == find_most_color(value, len));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

