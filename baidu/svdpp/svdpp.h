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
#define DIFF 0.5
#define W 10

struct Entry {
    int custId;
    int movieId;
    double rate;
    Entry(int c, int m, double r = 0.0) : custId(c), movieId(m), rate(r) {}
};

struct Customer {
    int rateCnt;
    int rateSum;
    double bu;
    vector<int> items;
    Customer() : rateCnt(0), rateSum(0), bu(0.0) {}
};

struct Movie {
    int rateCnt;
    int rateSum;
    double bi;
    vector<double> y;
    vector<int> users;
    Movie(int dimension) : rateCnt(0), rateSum(0), bi(0.0), sumbu(0.0) {
        y.resize(dimension);
    }
};

class SVDPP {
public:
    SVDPP();
    ~SVDPP();
    void LoadData(const string& path);
    void Train();
    void Predict(const string& path, const string& result);
    void Save(const string& path, const string& result) const;
private:
    void InitValue();
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

