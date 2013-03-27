// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)

#include "baseline.h"
#include <cmath>

BaseLine::BaseLine() : numMovie(0), numCust(0), aveRate(0.0) {
    dataset.reserve(ENTRIES);
    customers.reserve(CUSTOMERS);
    movies.reserve(MOVIES);
}

BaseLine::~BaseLine() {
    for(vector<Entry*>::iterator it = dataset.begin(); it != dataset.end(); ++it) {
        delete *it;
    }
    for(map<int, Customer*>::iterator it = customers.begin(); it != customers.end(); ++it) {
        delete *it;
    }
    for(map<int, Movie*>::iterator it = movies.begin(); it != movies.end(); ++it) {
        delete *it;
    }
}

void BaseLine::LoadData(const string& path) {
    ifstream ifs(path.data(), ifstream::in);
    aveRate = 0.0;
    while(ifs.good()) {
        Entry* entry = new Entry();
        ifs >> entry->custId >> entry->movieId >> entry->rate;
        // user entry
        if(customers.find(entry->custId) != customers.end()) {
            Customer* pc = customers[entry->custId];
            pc->rateSum += entry->rate;
            ++(pc->rateCnt);

        } else {
            Customer* pc = new Customer();
            pc->rateSum = entry->rate;
            pc->rateCnt = 1;
            customers.insert(make_pair<int, Customer*>(entry->custId, pc));
        }
        // movie entry
        if(movies.find(entry->movieId) != movies.end()) {
            Movie* pm = movies[entry->movieId];
            pm->rateSum += entry->rate;
            ++(pm->rateCnt);

        } else {
            Movie* pm = new Movie();
            pm->rateSum = entry->rate;
            pm->rateCnt = 1;
            movies.insert(make_pair<int, Movie*>(entry->movieId, pm));
        }
        // average rate
        aveRate += entry->rate;
        dataset.push_back(entry);
    }
    ifs.close();
    numCust = customers.size();
    numMovie = movies.size();
    aveRate /= dataset.size();
    InitValue();
}

double BaseLine::CalcError() const {
    double errbusq = 0.0, errbisq=0.0, err = 0.0;
    for(map<int, double>::const_iterator it = customers.begin(); it != customers.end(); ++it) {
        errbusq += pow(it->second->bu, 2);
    }
    for(map<int, double>::const_iterator it = movies.begin(); it != movies.end(); ++it) {
        errbisq += pow(it->second->bi, 2);
    }
    for(vector<Entry*>::const_iterator it = dataset.begin(); it != dataset.end(); ++it) {
        err += pow(it->rate - aveRate - bu[it->custId] - bi[it->movieId], 2);
    }
    return err + P * (errbusq + errbisq);
}

void BaseLine::Train() {
    double err1 = CalcError(), err2 = 0.0;
    while(fabs(err1 - err2) > LIMIT) {
        err1 = err2;
        next();
        err2 = CalcError();
        cout << "err1 : err2 = " << err1 << " : " << err2 << endl;
    }
}

void BaseLine::InitValue() {
    for(map<int, double>::const_iterator it = customers.begin(); it != customers.end(); ++it) {
        it->second->bu = it->second->rateSum / it->second->rateCnt - aveRate;
    }
    for(map<int, double>::const_iterator it = movies.begin(); it != movies.end(); ++it) {
        it->second->bi = it->second->rateSum / it->second->rateCnt - aveRate;
    }
}

void BaseLine::next() {
    double eui;
    for(map<int, double>::const_iterator it = customers.begin(); it != customers.end(); ++it) {

        it->second->bu = it->second->rateSum / it->second->rateCnt - aveRate;
    }
    for(map<int, double>::const_iterator it = movies.begin(); it != movies.end(); ++it) {
        it->second->bi = it->second->rateSum / it->second->rateCnt - aveRate;
    }
}
