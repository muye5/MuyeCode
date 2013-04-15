// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)

#include "baseline.h"
#include <cmath>
#include <iomanip>

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
        dataset.push_back(entry);
    }
    ifs.close();
    numCust = customers.size();
    numMovie = movies.size();
    aveRate /= dataset.size();
    InitValue();
    cout << "average rate is " << aveRate << endl;
}

void BaseLine::Train() {
}

void BaseLine::GradientDesc() {
    double err1 = CalcError(), err2 = 0.0, step = 0.0;
    Movie* pmovie = NULL;
    Customer* pcustomer = NULL;
    while(fabs(err1 - err2) > DIFF) {
        err2 = err1;
        step = BestStep();
        // update bu && bi
        for(map<int, Movie*>::iterator it = movies.begin(); it != movies.end(); ++it) {
            pmovie = it->second;
            pmovie->bi += step * (pmovie->sumbu - W * pmovie->bi);
        }
        for(map<int, Customer*>::iterator it = customers.begin(); it != customers.end(); ++it) {
            pcustomer = it->second;
            pcustomer->bu += step * (pcustomer->sumbi - W * pcustomer->bu);
        }
        err1 = CalcError();
        cout << "err = " << err1 << "\t==\tdiff = " << err1 - err2 << endl;
    }
}

void BaseLine::Predict(const string& path, const string& result) {
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

void BaseLine::Save(const string& path, const string& result) const {
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
    for(vector<Entry*>::const_iterator it = dataset.begin(); it != dataset.end(); ++it) {
        rt << (*it)->custId << '\t'
           << (*it)->rate << '\t'
           << customers.find((*it)->custId)->second->bu << '\t'
           << movies.find((*it)->movieId)->second->bi << endl;
    }
    rt.close();
}

void BaseLine::InitValue() {
    for(map<int, Customer*>::iterator it = customers.begin(); it != customers.end(); ++it) {
        it->second->bu = it->second->rateSum / it->second->rateCnt - aveRate;
    }
    for(map<int, Movie*>::iterator it = movies.begin(); it != movies.end(); ++it) {
        it->second->bi = it->second->rateSum / it->second->rateCnt - aveRate;
    }
}

double BaseLine::BestStep() {
    double up = 0.0, up1 = 0.0, up2 = 0.0;
    double down = 0.0, down1 = 0.0, down2 = 0.0;
    double eui, sui;
    // sum(bi)
    Movie* pmovie = NULL;
    for(map<int, Movie*>::iterator it = movies.begin(); it != movies.end(); ++it) {
        pmovie = it->second;
        double tmp = 0.0;
        for(vector<int>::iterator p = pmovie->users.begin(); p != pmovie->users.end(); ++p) {
            tmp += customers.find(*p)->second->bu;
        }
        pmovie->sumbu = pmovie->rateSum - pmovie->rateCnt * aveRate - tmp - pmovie->rateCnt * pmovie->bi;
        eui = pmovie->sumbu - W * pmovie->bi;
        up2 += pmovie->bi * eui;
        down2 += pow(eui, 2);
    }
    // sum(bu)
    Customer* pcustomer = NULL;
    for(map<int, Customer*>::iterator it = customers.begin(); it != customers.end(); ++it) {
        pcustomer = it->second;
        double tmp = 0.0;
        for(vector<int>::iterator p = pcustomer->items.begin(); p != pcustomer->items.end(); ++p) {
            tmp += movies.find(*p)->second->bi;
        }
        pcustomer->sumbi = pcustomer->rateSum - pcustomer->rateCnt * aveRate - tmp - pcustomer->rateCnt * pcustomer->bu;
        sui = pcustomer->sumbi - W * pcustomer->bu;
        up2 += pcustomer->bu * sui;
        down2 += pow(sui, 2);
    }
    up2 *= W;
    down2 *= W;
    // best step
    for(vector<Entry*>::iterator it = dataset.begin(); it != dataset.end(); ++it) {
        pcustomer = customers[(*it)->custId];
        pmovie = movies[(*it)->movieId];
        eui = (*it)->rate - aveRate - pcustomer->bu - pmovie->bi;
        sui = pcustomer->sumbi + pmovie->sumbu - W * (pcustomer->bu + pmovie->bi);
        up1 += eui * sui;
        down1 += pow(sui, 2);
    }
    up = up1 - up2;
    down = down1 + down2;
    return up / down;
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
        double tmp = (*it)->rate - aveRate - customers.find((*it)->custId)->second->bu - movies.find((*it)->movieId)->second->bi;
        err += pow(tmp, 2);
    }
    return err + W * (errbusq + errbisq);
}

