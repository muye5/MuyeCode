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
    Customer() : rateCnt(0), rateSum(0), bu(0.0) {}
public:
    vector<double> pu;
    vector<int> imfdbk;
    int rateCnt;
    int rateSum;
    double bu;
};

class Movie {
public:
    Movie() : rateCnt(0), rateSum(0), bi(0.0) {}
public:
    vector<double> qi;
    int rateCnt;
    int rateSum;
    double bi;
};

class FeedBack {
public:
    vector<double> yj;
};

class SVDPP {
public:
    SVDPP(int dimension);
    ~SVDPP();
    void TrainDataLoad(const string& path);
    void ProbeDataLoad(const string& path);
    void ImplicitDataLoad(const string& path);
    void Train(int maxloops, int dimension, double alpha1, double alpha2, double beta1, double beta2);
    void Predict(const string& path, const string& result);
    void Save(const string& path, const string& result) const;
private:
    void InitBais(); // initialize bu bi
    void InitPQ(); // initialize pu qi yj
    void SetRand(vector<double>& v);
    double CalError();
    double predict(int uid, int iid);
private:
    int dim;
    int numMovie;
    int numCust;
    double mean;
    vector<Entry*> datas;
    vector<Entry*> probes;
    map<int, Customer*> customers;
    map<int, Movie*> movies;
    map<int, FeedBack*> fdbks;
};
#endif  // SVDPLUSPLUS_H_

