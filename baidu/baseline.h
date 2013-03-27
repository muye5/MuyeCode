// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)


#ifndef BASELINE_H_
#define BASELINE_H_

#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define ENTRIES 1300000
#define CUSTOMERS 10000
#define MOVIES 8000

#define R 0.005
#define P 0.02
#define LIMIT 0.001

struct Entry {
    int custId;
    int movieId;
    double rate;
};

struct Customer {
    int rateCnt;
    int rateSum;
    double bu;
};

struct Movie {
    int rateCnt;
    int rateSum;
    double bi;
};

class BaseLine {
public:
    BaseLine();
    ~BaseLine();
    void LoadData(const string& path);
    double CalcError() const;
    void Train();
private:
    void InitValue();
    void next();
private:
    int numMovie;
    int numCust;
    double aveRate;
    vector<Entry*> dataset;
    map<int, Customer*> customers;
    map<int, Movie*> movies;
};
#endif  // BASELINE_H_

