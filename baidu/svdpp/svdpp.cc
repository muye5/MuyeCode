// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)

#include "svdpp.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iomanip>

SVDPP::SVDPP(int dimension) : dim(dimension), numMovie(0), numCust(0), mean(0.0) {}

SVDPP::~SVDPP() {
    for(vector<Entry*>::iterator it = datas.begin(); it != datas.end(); ++it) delete *it;
    for(map<int, Customer*>::iterator it = customers.begin(); it != customers.end(); ++it) delete it->second;
    for(map<int, Movie*>::iterator it = movies.begin(); it != movies.end(); ++it) delete it->second;
    for(map<int, FeedBack*>::iterator it = fdbks.begin(); it != fdbks.end(); ++it) delete it->second;
}

void SVDPP::TrainDataLoad(const string& path) {
    ifstream ifs(path.data(), ifstream::in);
    Customer* pc = NULL;
    Movie* pm = NULL;
    int cid, mid;
    double drate;
    mean = 0.0;
    while(ifs >> cid >> mid >> drate) {
        Entry* entry = new Entry(cid, mid, drate);
        // user entry
        if(customers.find(cid) != customers.end()) {
            pc = customers[cid];
            pc->rateSum += drate;
            ++(pc->rateCnt);
            pc->rates.push_back(mid);
        } else {
            pc = new Customer();
            pc->rateSum = drate;
            pc->rateCnt = 1;
            pc->rates.push_back(mid);
            customers.insert(make_pair<int, Customer*>(cid, pc));
        }
        // movie entry
        if(movies.find(mid) != movies.end()) {
            pm = movies[mid];
            pm->rateSum += drate;
            ++(pm->rateCnt);
            pm->users.push_back(cid);
        } else {
            pm = new Movie();
            pm->rateSum = drate;
            pm->rateCnt = 1;
            pm->users.push_back(cid);
            movies.insert(make_pair<int, Movie*>(mid, pm));
        }
        // average rate
        mean += drate;
        datas.push_back(entry);
    }
    ifs.close();
    numCust = customers.size();
    numMovie = movies.size();
    mean /= datas.size();
}

void SVDPP::ProbeDataLoad(const string& path) {
    ifstream ifs(path.data(), ifstream::in);
    int cid, mid;
    double drate;
    while(ifs >> cid >> mid >> drate) {
        Entry* entry = new Entry(cid, mid, drate);
        probes.push_back(entry);
    }
    ifs.close();
}

void SVDPP::ImplicitDataLoad(const string& path) {
    ifstream ifs(path.data(), ifstream::in);
    int mid;
    FeedBack* fd = NULL;
    while(ifs >> mid) {
        fd = new FeedBack();
        fdbks.insert(make_pair<int, FeedBack*>(mid, fd));
    }
    ifs.close();
}

void SVDPP::Train(int maxloops, int dimension, double alpha1, double alpha2, double beta1, double beta2) {
    InitBais();
    InitPQ();
    double prmse, rmse;
    for(int loop = 0; loop < maxloops; ++loop) {

    }
}

void SVDPP::Predict(const string& path, const string& result) {
    ifstream ifs(path.data(), ifstream::in);
    ofstream ofs(result.data(), ofstream::out);
    int custId, movieId;
    double rate;
    map<int, Customer*>::iterator itc;
    map<int, Movie*>::iterator itm;
    while(ifs >> custId >> movieId) {
        ofs << custId << '\t' << movieId << '\t';
        itc = customers.find(custId);
        itm = movies.find(movieId);
        rate = mean;
        if(itc != customers.end()) rate += itc->second->bu;
        if(itm != movies.end()) rate += itm->second->bi;
        if(rate < 1.0) rate = 1.0;
        if(rate > 5.0) rate = 5.0;
        ofs << setprecision(2) << rate << endl;
    }
    ifs.close();
    ofs.close();
}

void SVDPP::Save(const string& path, const string& result) const {
    ofstream ofs(path.data(), ofstream::out);
    ofs << mean << endl;
    ofs << customers.size() << endl;
    for(map<int, Customer*>::const_iterator it = customers.begin(); it != customers.end(); ++it) {
        ofs << it->first << '\t'
            << it->second->rateCnt << '\t'
            << it->second->rateSum << '\t'
            << it->second->bu << endl;
    }
    ofs << movies.size() << endl;
    for(map<int, Movie*>::const_iterator it = movies.begin(); it != movies.end(); ++it) {
        ofs << it->first << '\t'
            << it->second->rateCnt << '\t'
            << it->second->rateSum << '\t'
            << it->second->bi << endl;
    }
    ofs.close();

    ofstream rt(result.data(), ofstream::out);
    for(vector<Entry*>::const_iterator it = datas.begin(); it != datas.end(); ++it) {
        rt << (*it)->custId << '\t'
           << (*it)->rate << '\t'
           << customers.find((*it)->custId)->second->bu << '\t'
           << movies.find((*it)->movieId)->second->bi << endl;
    }
    rt.close();
}

void SVDPP::InitBais() {
    for(map<int, Customer*>::iterator it = customers.begin(); it != customers.end(); ++it) {
        it->second->bu = it->second->rateSum / it->second->rateCnt - mean;
    }
    for(map<int, Movie*>::iterator it = movies.begin(); it != movies.end(); ++it) {
        it->second->bi = it->second->rateSum / it->second->rateCnt - mean;
    }
}

void SVDPP::InitPQ() {
    srand((unsigned)time(NULL));

    map<int, Customer*>::iterator itu = customers.begin();
    for(; itu != customers.end(); ++itu) SetRand(itu->second->pu);

    map<int, Movie*>::iterator itm = movies.begin();
    for(; itm != movies.end(); ++itm) SetRand(itm->second->qi);
}

void SVDPP::SetRand(vector<double>& v) {
    v.clear();
    v.resize(dim);
    double d = sqrt(dim);
    for(int i = 0; i < dim; ++i) v[i] = 0.1 * (rand() / (double)RAND_MAX) / d;
}

double SVDPP::CalError() {
}

