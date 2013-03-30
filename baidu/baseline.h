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
#define DIFF 50000.0
#define W 1.0

struct Entry {
    int custId;
    int movieId;
    double rate;
};

struct Customer {
    int rateCnt;
    int rateSum;
    double bu;
    double sumbi;
    vector<int> items;
    Customer() : rateCnt(0), rateSum(0), bu(0.0), sumbi(0.0) {}
};

struct Movie {
    int rateCnt;
    int rateSum;
    double bi;
    double sumbu;
    vector<int> users;
    Movie() : rateCnt(0), rateSum(0), bi(0.0), sumbu(0.0) {}
};

class BaseLine {
public:
    BaseLine();
    ~BaseLine();
    void LoadData(const string& path);
    void Train();
    void GradientDesc();
    void Predict(const string& path, const string& result);
    void Save(const string& path) const;
private:
    void InitValue();
    double BestStep();
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

