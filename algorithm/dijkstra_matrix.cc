// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// http://acm.hdu.edu.cn/showproblem.php?pid=2544

#include <iostream>
#include <climits>
#include <vector>
using namespace std;

#define INF (INT_MAX >> 1)

int main(int argc, char **argv) {
    const int max_n = 101;
    int adjacent_matrix[max_n][max_n], distance[max_n];
    vector<int> values;
    int n, m;
    while(cin >> n >> m, n && m) {
        for(int k = 1; k <= n; ++k) {
            for(int g = 1; g <= n; ++g) {
                adjacent_matrix[k][g] = INF;
            }
        }
        for(int k = 1; k <= n; ++k) {
            adjacent_matrix[k][k] = 0;
            distance[k] = INF;
        }
        int i, j;
        for(int k = 0; k < m; ++k) {
            cin >> i >> j;
            cin >> adjacent_matrix[i][j];
            adjacent_matrix[j][i] = adjacent_matrix[i][j];
        }
        distance[1] = 0;
        vector<int> nodes;
        for(int k = 1; k <= n; ++k) {
            nodes.push_back(k);
        }
        while(!nodes.empty()) {
            int node = 0, index = 0, dis = INF;
            for(size_t k = 0; k < nodes.size(); ++k) {
                if(distance[nodes[k]] < dis) {
                    dis = distance[nodes[k]];
                    index = k;
                }
            }
            node = nodes[index];
            nodes.erase(nodes.begin() + index);
            for(size_t k = 0; k < nodes.size(); ++k) {
                if(distance[nodes[k]] > adjacent_matrix[node][nodes[k]] + distance[node]) {
                    distance[nodes[k]] = adjacent_matrix[node][nodes[k]] + distance[node];
                }
            }
        }
        cout << distance[n] << endl;
    }
    return 0;
}

