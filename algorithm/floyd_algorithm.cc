// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)

#include <iostream>
#include <climits>
using namespace std;

int main(int argc, char **argv) {
    const int inf = INT_MAX, N = 101;
    int matrix[N][N];
    int n, m;
    for(int i = 1; i < N; ++i) {
        matrix[i][i] = 0;
    }
    while(cin >> n >> m, m && n) {
        for(int i = 1; i <= n; ++i) {
            for(int j = i; j <= n; ++j) {
                matrix[i][j] = matrix[j][i] = inf;
            }
        }
        int u, v, d;
        for(int i = 0; i < m; ++i) {
            cin >> u >> v >> d;
            matrix[u][v] = matrix[v][u] = d;
        }
        for(int k = 1; k <= n; ++k) {
            for(int i = 1; i <= n; ++i) {
                for(int j = 1; j <= n; ++j) {
                    if(matrix[i][k] != inf && matrix[k][j] != inf && matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                    }
                }
            }
        }
        cout << matrix[1][n] << endl;
    }
    return 0;
}


