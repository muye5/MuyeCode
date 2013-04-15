// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)

#include "svdpp.h"
#include <cmath>
#include <iomanip>

SVDPP::SVDPP() : numMovie(0), numCust(0), aveRate(0.0) {
    datas.reserve(ENTRIES);
}

SVDPP::~SVDPP() {
    for(vector<Entry*>::iterator it = datas.begin(); it != datas.end(); ++it) {
        delete *it;
    }
    for(map<int, Customer*>::iterator it = customers.begin(); it != customers.end(); ++it) {
        delete it->second;
    }
    for(map<int, Movie*>::iterator it = movies.begin(); it != movies.end(); ++it) {
        delete it->second;
    }
}

void SVDPP::LoadData(const string& path) {
    ifstream ifs(path.data(), ifstream::in);
    Customer* pc = NULL;
    Movie* pm = NULL;
    int cid, mid;
    double drate;
    aveRate = 0.0;
    while(ifs >> cid >> mid >> drate) {
        Entry* entry = new Entry(cid, mid, drate);
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
        datas.push_back(entry);
    }
    ifs.close();
    numCust = customers.size();
    numMovie = movies.size();
    aveRate /= datas.size();
    InitValue();
    cout << "average rate is " << aveRate << endl;
}

void SVDPP::Train() {
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
        rate = aveRate;
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
    ofs << aveRate << endl;
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

void SVDPP::InitValue() {
    for(map<int, Customer*>::iterator it = customers.begin(); it != customers.end(); ++it) {
        it->second->bu = it->second->rateSum / it->second->rateCnt - aveRate;
    }
    for(map<int, Movie*>::iterator it = movies.begin(); it != movies.end(); ++it) {
        it->second->bi = it->second->rateSum / it->second->rateCnt - aveRate;
    }
}

double SVDPP::CalcError() {
    double errbusq = 0.0, errbisq=0.0, err = 0.0;
    for(map<int, Customer*>::const_iterator it = customers.begin(); it != customers.end(); ++it) {
        errbusq += pow(it->second->bu, 2);
    }
    for(map<int, Movie*>::const_iterator it = movies.begin(); it != movies.end(); ++it) {
        errbisq += pow(it->second->bi, 2);
    }
    for(vector<Entry*>::const_iterator it = datas.begin(); it != datas.end(); ++it) {
        double tmp = (*it)->rate - aveRate - customers.find((*it)->custId)->second->bu - movies.find((*it)->movieId)->second->bi;
        err += pow(tmp, 2);
    }
    return err + W * (errbusq + errbisq);
}

