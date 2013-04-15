// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)


#ifndef SVDPLUSPLUS_H_
#define SVDPLUSPLUS_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Entry {
public:
    Entry(int c, int m, double r = 0.0) : custId(c), movieId(m), rate(r) {}
public:
    int custId;
    int movieId;
    double rate;
};

class Customer {
public:
    Customer(int dimension) : rateCnt(0), rateSum(0), bu(0.0) {
        pu.resize(dimension)
    }
public:
    vector<double> pu;
    vector<int> items;
    int rateCnt;
    int rateSum;
    double bu;
};

class Movie {
public:
    Movie(int dimension) : rateCnt(0), rateSum(0), bi(0.0), sumbu(0.0) {
        yi.resize(dimension);
        qi.resize(dimension);
    }
public:
    vector<double> yi;
    vector<double> qi;
    vector<int> users;
    int rateCnt;
    int rateSum;
    double bi;
};

class SVDPP {
public:
    SVDPP();
    ~SVDPP();
    void TrainDataLoad(const string& path);
    void ProbeDataLoad(const string& path);
    void Train(int maxloops, int dimension, double alpha1, double alpha2, double beta1, double beta2);
    void Predict(const string& path, const string& result);
    void Save(const string& path, const string& result) const;
private:
    void InitValue();
    void InitBais(); // initialize bu bi
    void InitPQ(); // initialize pu qi yj
    double CalcError();
    double predict(int dimension, int uid, int iid);
private:
    int numMovie;
    int numCust;
    double mean;
    vector<Entry*> datas;
    map<int, Customer*> customers;
    map<int, Movie*> movies;
};
#endif  // SVDPLUSPLUS_H_

