// Copyright (c) 2014
// Author: Yanshi.WYS ()

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
using namespace std;

void longest_sequence(int A[], int n, int& start, int& end) {
    map<int, int> table;
    start = end = 0;
    int head = 0, tail = 0;
    for(int i = 0; i < n; ++i) {
        if(table.find(A[i]) == table.end()) {
            table[A[i]] = A[i];
            head = tail = A[i];
            if(table.find(A[i]-1) != table.end()) head = table[A[i]-1];
            if(table.find(A[i]+1) != table.end()) tail = table[A[i]+1];
            if(tail - head > end - start) {
                start = head; end = tail;
            }
            table[head] = tail;
            table[tail] = head;
        }
    }
}

int main(int argc, char **argv) {
    int A[] = {1, 6, 10, 4, 7, 9, 5};
    int start = 0, end = 0;
    longest_sequence(A, 7, start, end);
    vector<int> range;
    while(start <= end) range.push_back(start++);
    copy(range.begin(), range.end(), ostream_iterator<int>(cout, ", "));
    cout << endl;
    return 0;
}
