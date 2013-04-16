// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)

#include "svdpp.h"
#include <cmath>
#include <ctime>
#include <cstdlib>

SVDPP::SVDPP(int dimension, int nu, int nm, int nf) : dim(dimension), mean(0.0) {
    customers.resize(nu+1);
    movies.resize(nm+1);
    fdbks.resize(nf+1);
}

SVDPP::~SVDPP() {}

void SVDPP::TrainDataLoad(const string& path) {
    int cid, mid, num = 0;
    double rate;
    mean = 0.0;
    ifstream ifs(path.data(), ifstream::in);
    while(ifs >> cid >> mid >> rate) {
        ++num;
        mean += rate;
        ++movies[mid].n;
        customers[cid].rated.push_back(Entry(mid, rate));
    }
    ifs.close();
    mean /= num;
}

void SVDPP::ProbeDataLoad(const string& path) {
    ifstream ifs(path.data(), ifstream::in);
    int cid, mid;
    double rate;
    while(ifs >> cid >> mid >> rate) {
        probes.push_back(ProbeEntry(cid, mid, rate));
    }
    ifs.close();
}

void SVDPP::ImplicitDataLoad(const string& path) {
    int cid, mid;
    ifstream ifs(path.data(), ifstream::in);
    while(ifs >> cid >> mid) {
        customers[cid].imfdbk.push_back(mid);
    }
    ifs.close();
}

void SVDPP::Train(int maxloops, double alpha1, double alpha2, double beta1, double beta2) {
    cout << "initialize bais" << endl;
    InitBais();
    cout << "initialize P and Q" << endl;
    InitPQ();
    double prmse = 100000000.0, rmse = 0.0;
    for(int loop = 0; loop < maxloops; ++loop) {
        rmse = 0.0;
        for(vector<Customer>::iterator it = ++customers.begin(); it != customers.end(); ++it) {
            const vector<double>& pu = it->pu;
            const vector<int>& fd = it->imfdbk;
            vector<double> tmp(dim, 0.0);
            double rate = mean + pu[uid].bu + movies[iid].bi;
            double ru = sqrt((double)fd.size());
            for(vector<int>::iterator itf = fd.begin(); itf != fd.end(); ++itf) {
                const vector<double>& yj = fdbks[*itf].yj;
                for(int i = 0; i < dim; ++i) tmp[i] += yj[i];
            }
            for(int i = 0; i < dim; ++i) {
                tmp[i] /= ru;
                tmp[i] += pu[i];
                rate += tmp[i] * qi[i];
            }
            vector<double> tmp(dim, 0.0);
            double eui = it->rate - predict(it->custId, it->movieId);
            rmse += pow(eui, 2);
            Customer* pc = customers[(*it)->custId];
            Movie* pm = movies[(*it)->movieId];
            pc->bu = pc->bu + alpha1 * (eui - beta1 * pc->bu);
            pm->bi = pm->bi + alpha1 * (eui - beta1 * pm->bi);
            vector<int>& fd = pc->imfdbk;
            double r = sqrt((double)fd.size());
            for(vector<int>::iterator ifd = fd.begin(); ifd != fd.end(); ++ifd) {
                vector<double>& yj = fdbks[*ifd]->yj;
                for(int i = 0; i < dim; ++i) {
                    tmp[i] += yj[i];
                    yj[i] += alpha2 * (eui * pm->qi[i] / r - beta2 * yj[i]);
                }
            }
            for(int i = 0; i < dim; ++i) {
                tmp[i] /= r;
                tmp[i] += eui * pc->pu[i];
                tmp[i] -= beta2 * pm->qi[i];
                tmp[i] = pm->qi[i] + alpha2 * tmp[i];
            }
            for(int i = 0; i < dim; ++i) pc->pu[i] += alpha2 * (eui * pm->qi[i] - beta2 * pc->pu[i]);
            for(int i = 0; i < dim; ++i) pm->qi[i] = tmp[i];
            if((it - datas.begin() + 1) % 10000 == 0) {
                cout << "loop[" << loop << "] : " << it - datas.begin() + 1 << " entries done" << endl;
            }
        }
        rmse = sqrt(rmse / datas.size());
        if(loop > 3 && rmse > prmse) {
            cout << "Over! rmse = " << prmse << "\tcalerror : " << CalError() << endl;
            break;
        }
        cout << "loop[" << loop << "]\trmse = " << rmse << "\tcalerror : " << CalError() << endl;
        prmse = rmse;
    }
}

void SVDPP::Predict(const string& path, const string& result) {
    ifstream ifs(path.data(), ifstream::in);
    ofstream ofs(result.data(), ofstream::out);
    int custId, movieId;
    double rate;
    while(ifs >> custId >> movieId) {
        ofs << custId << '\t' << movieId << '\t';
        rate = predict(custId, movieId);
        if(rate < 1.0) rate = 1.0;
        if(rate > 5.0) rate = 5.0;
        ofs << rate << endl;
    }
    ifs.close();
    ofs.close();
}

void SVDPP::InitBais() {
    for(vector<Customer>::iterator it = ++customers.begin(); it != customers.end(); ++it) {
        for(vector<Entry>::iterator ie = it->rated.begin(); ie != it->rated.end(); ++ie) {
            it->bu += ie->rate - mean;
            movies[ie->mid].bi += ie->rate - mean;
        }
        it->bu /= it->rated.size();
    }
    for(vector<Movie>::iterator it = ++movies.begin(); it != movies.end(); ++it) it->bi /= it->n;
}

void SVDPP::InitPQ() {
    srand((unsigned)time(NULL));

    for(vector<Customer>::iterator itu = ++customers.begin(); itu != customers.end(); ++itu) SetRand(itu->pu);
    for(vector<Movie>::iterator itm = ++movies.begin(); ; itm != movies.end(); ++itm) SetRand(itm->qi);
    for(vector<FeedBack>::iterator itf = ++fdbks.begin(); itf != fdbks.end(); ++itf) SetRand(itf->yj);
}

void SVDPP::SetRand(vector<double>& v) {
    v.clear();
    v.resize(dim, 0.0);
    double d = sqrt(dim);
    for(int i = 0; i < dim; ++i) v[i] = 0.1 * (rand() / (double)RAND_MAX) / d;
}

double SVDPP::CalError() {
    double rmse = 0.0, rate = 0.0;
    vector<ProbeEntry>::iterator it = probes.begin();
    for(; it != probes.end(); ++it) {
        rate = predict(it->cid, it->mid);
        rmse += pow(it->rate - rate, 2);
    }
    return sqrt(rmse/probes.size());
}

double SVDPP::predict(const int& uid, const int& iid) {
    const vector<double>& pu = customers[uid].pu;
    const vector<double>& qi = movies[iid].qi;
    const vector<int>& fd = customers[uid].imfdbk;
    vector<double> tmp(dim, 0.0);
    double rate = mean + pu[uid].bu + movies[iid].bi;
    double ru = sqrt((double)fd.size());
    for(vector<int>::iterator it = fd.begin(); it != fd.end(); ++it) {
        const vector<double>& yj = fdbks[*it].yj;
        for(int i = 0; i < dim; ++i) tmp[i] += yj[i];
    }
    for(int i = 0; i < dim; ++i) {
        tmp[i] /= ru;
        tmp[i] += pu[i];
        rate += tmp[i] * qi[i];
    }
    return rate;
}
