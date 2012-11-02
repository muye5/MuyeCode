// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
//
// ��Ϧ����,������������С���������һ�������ħʯ.
// ���ħʯƽ���ǰ����޹��,��ֻҪ�����ħʯ����ħ��,ħʯ�ͻ���ڲ�������ͬ��ɫ��Ѥ������,�ǳ��ÿ�.
// �����Ĺ����ɫ,����ħʯ�ϲ�������ħ�۵ı�ŵ����(Xor)ֵ��������ֵΪ0,Ҳ��һ����ɫ,���ֵ��ͬ��ʾ��ɫ��ͬ��.
// ������������һ����6��ħ��,�����6 7 17 46 47 56,�����ǳ���֪�����ħʯ�����ܷ�����������ɫ�Ĺ�.
// �������ʵ��̫��,�������ܹ���������������,�����㲻������ʧ����
// ���ħ����20�֣����256���ڣ�,�ָ���μ���?
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

