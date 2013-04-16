// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)


#ifndef SVDPLUSPLUS_H_
#define SVDPLUSPLUS_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

class ProbeEntry {
public:
    ProbeEntry(int c, int m, double r = 0.0) : cid(c), mid(m), rate(r) {}
public:
    int cid;
    int mid;
    double rate;
};

class Entry {
public:
    Entry(int m, double r = 0.0) : mid(m), rate(r) {}
public:
    int mid;
    double rate;
};

class Customer {
public:
    Customer() : bu(0.0) {}
public:
    double bu;
    vector<int> imfdbk;
    vector<double> pu;
    vector<Entry> rated;
};

class Movie {
public:
    Movie() : n(0), bi(0.0) {}
public:
    int n;
    double bi;
    vector<double> qi;
};

class FeedBack {
public:
    vector<double> yj;
};

class SVDPP {
public:
    SVDPP(int dimension, int nu, int nm, int nf);
    ~SVDPP();
    void TrainDataLoad(const string& path);
    void ProbeDataLoad(const string& path);
    void ImplicitDataLoad(const string& path);
    void Train(int maxloops, double alpha1, double alpha2, double beta1, double beta2);
    void Predict(const string& path, const string& result);
private:
    void InitBais(); // initialize bu bi
    void InitPQ(); // initialize pu qi yj
    void SetRand(vector<double>& v);
    double CalError();
    double predict(const int& uid, const int& iid);
private:
    int dim;
    double mean;
    vector<ProbeEntry> probes;
    vector<Customer> customers;
    vector<Movie> movies;
    vector<FeedBack> fdbks;
};
#endif  // SVDPLUSPLUS_H_

