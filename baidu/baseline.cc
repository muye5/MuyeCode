// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)

#include "baseline.h"
#include <cmath>
#include <climits>

BaseLine::BaseLine() : numMovie(0), numCust(0), aveRate(0.0) {
    dataset.reserve(ENTRIES);
}

BaseLine::~BaseLine() {
    for(vector<Entry*>::iterator it = dataset.begin(); it != dataset.end(); ++it) {
        delete *it;
    }
    for(map<int, Customer*>::iterator it = customers.begin(); it != customers.end(); ++it) {
        delete it->second;
    }
    for(map<int, Movie*>::iterator it = movies.begin(); it != movies.end(); ++it) {
        delete it->second;
    }
}

void BaseLine::LoadData(const string& path) {
    Customer* pc = NULL;
    Movie* pm = NULL;
    ifstream ifs(path.data(), ifstream::in);
    aveRate = 0.0;
    while(ifs.good()) {
        Entry* entry = new Entry();
        ifs >> entry->custId >> entry->movieId >> entry->rate;
        // user entry
        if(customers.find(entry->custId) != customers.end()) {
            pc = customers[entry->custId];
            pc->rateSum += entry->rate;
            ++(pc->rateCnt);
            pc->items.push_back(entry->movieId);
        } else {
            pc = new Customer();
            pc->rateSum = entry->rate;
            pc->rateCnt = 1;
            pc->items.push_back(entry->movieId);
            customers.insert(make_pair<int, Customer*>(entry->custId, pc));
        }
        // movie entry
        if(movies.find(entry->movieId) != movies.end()) {
            pm = movies[entry->movieId];
            pm->rateSum += entry->rate;
            ++(pm->rateCnt);
            pm->users.push_back(entry->custId);

        } else {
            pm = new Movie();
            pm->rateSum = entry->rate;
            pm->rateCnt = 1;
            pm->users.push_back(entry->custId);
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
    cout << "average rate is " << aveRate << endl;
}

void BaseLine::Train() {
    double minerr = INT_MAX, err = 0.0;
    int x = 0, y = 0;
    for(int i = 5; i < 50; i += 5) {
        for(int j = 5; j < 50; j += 5) {
            next1(i, j);
            err = CalcError();
            if(fabs(err) < minerr) {
                minerr = fabs(err);
                x = i;
                y = j;
            }
            cout << "err = " << err << endl;
        }
    }
    next1(x, y);
    cout << "minerr = " << minerr << endl;
}

void BaseLine::Predict(const string& path, const string& result) {
    ifstream ifs(path.data(), ifstream::in);
    ofstream ofs(result.data(), ofstream::out);
    int custId, movieId, rate;
    map<int, Customer*>::iterator itc;
    map<int, Movie*>::iterator itm;
    while(ifs.good()) {
        ifs >> custId >> movieId;
        ofs << custId << '\t' << movieId << '\t';
        itc = customers.find(custId);
        itm = movies.find(movieId);
        rate = aveRate;
        if(itc != customers.end()) rate += itc->second->bu;
        if(itm != movies.end()) rate += itm->second->bi;
        ofs << (int)(rate + 0.5) << endl;
    }
    ifs.close();
    ofs.close();
}

void BaseLine::Save(const string& path) const {
    ofstream ofs(path.data(), ofstream::out);
    ofs << aveRate << endl;
    ofs << customers.size() << endl;
    for(map<int, Customer*>::const_iterator it = customers.begin(); it != customers.end(); ++it) {
        it->second->bu = it->second->rateSum / it->second->rateCnt - aveRate;
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
}

void BaseLine::InitValue() {
    for(map<int, Customer*>::iterator it = customers.begin(); it != customers.end(); ++it) {
        it->second->bu = it->second->rateSum / it->second->rateCnt - aveRate;
    }
    for(map<int, Movie*>::iterator it = movies.begin(); it != movies.end(); ++it) {
        it->second->bi = it->second->rateSum / it->second->rateCnt - aveRate;
    }
}

void BaseLine::next() {
    double eui, bu, bi;
    for(vector<Entry*>::iterator it = dataset.begin(); it != dataset.end(); ++it) {
        bu = customers[(*it)->custId]->bu;
        bi = movies[(*it)->movieId]->bi;
        eui = (*it)->rate - aveRate - bu - bi;
        customers[(*it)->custId]->bu = bu + R * (eui - P * bu);
        movies[(*it)->movieId]->bi = bi + R * (eui - P * bi);
    }
}

void BaseLine::next1(int x, int y) {
    Movie* pmovie = NULL;
    Customer* pcustomer = NULL;
    for(map<int, Movie*>::iterator it = movies.begin(); it != movies.end(); ++it) {
        pmovie = it->second;
        pmovie->bi = (pmovie->rateSum - pmovie->rateCnt * aveRate) / (x + pmovie->rateCnt);
    }
    for(map<int, Customer*>::iterator it = customers.begin(); it != customers.end(); ++it) {
        pcustomer = it->second;
        double sumbi = 0.0;
        for(vector<int>::iterator t = pcustomer->items.begin(); t != pcustomer->items.end(); ++t) {
            sumbi += movies.find(*t)->second->bi;
        }
        pcustomer->bu = (pcustomer->rateSum - pcustomer->rateCnt * aveRate - sumbi) / (y + pcustomer->rateCnt);
    }
}

double BaseLine::CalcError() {
    double errbusq = 0.0, errbisq=0.0, err = 0.0;
    for(map<int, Customer*>::const_iterator it = customers.begin(); it != customers.end(); ++it) {
        errbusq += pow(it->second->bu, 2);
    }
    for(map<int, Movie*>::const_iterator it = movies.begin(); it != movies.end(); ++it) {
        errbisq += pow(it->second->bi, 2);
    }
    for(vector<Entry*>::const_iterator it = dataset.begin(); it != dataset.end(); ++it) {
        double tmp = (*it)->rate - aveRate - customers[(*it)->custId]->bu - movies[(*it)->movieId]->bi;
        err += pow(tmp, 2);
    }
    return err + Z * (errbusq + errbisq);
}

