// Copyright (c) 2014
// Author: Yanshi.WYS ()

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) {
        vector<int> range;
        range.push_back(binary_search_first_meet_or_negative_one(A, n, target));
        range.push_back(binary_search_last_meet_or_negative_one(A, n, target));
        return range;
    }

    int binary_search_first_meet_or_negative_one(int A[], int n, int target) {
        int i = 0, j = n;
        while(i < j) {
            int m = (i + j) / 2;
            (target <= A[m]) ? j = m : i = m + 1;
        }
        return j == n || A[j] != target ? -1 : j;
    }

    int binary_search_last_meet_or_negative_one(int A[], int n, int target) {
        int i = 0, j = n;
        while(i < j) {
            int m = (i + j) / 2;
            (target < A[m]) ? j = m : i = m + 1;
        }
        return i - 1 == -1 || A[i-1] != target ? -1 : i - 1;
    }
};

