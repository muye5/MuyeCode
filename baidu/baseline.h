// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)


#ifndef BASELINE_H_
#define BASELINE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define ENTRIES 1300000
#define CUSTOMERS 10000
#define MOVIES 8000

#define X 25
#define Y 10
#define Z 1
#define DIFF 5

#define R 0.005
#define P 0.02

struct Entry {
    int custId;
    int movieId;
    double rate;
};

struct Customer {
    int rateCnt;
    int rateSum;
    double bu;
    vector<int> items;
};

struct Movie {
    int rateCnt;
    int rateSum;
    double bi;
    vector<int> users;
};

class BaseLine {
public:
    BaseLine();
    ~BaseLine();
    void LoadData(const string& path);
    void Train();
    void Predict(const string& path, const string& result);
    void Save(const string& path) const;
private:
    void InitValue();
    void next();
    void next1(int x, int y);
    double CalcError();
private:
    int numMovie;
    int numCust;
    double aveRate;
    vector<Entry*> dataset;
    map<int, Customer*> customers;
    map<int, Movie*> movies;
};
#endif  // BASELINE_H_

