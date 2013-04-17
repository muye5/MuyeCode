// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)

#include "svdpp.h"

int main(int argc, char **argv) {
    int dimension = 10;
    int maxloops = 60;
    double alpha1 = 0.005;
    double alpha2 = 0.005;
    double beta1 = 0.005;
    double beta2 = 0.005;

    SVDPP svdpp(dimension, 100, 100, 100);

    cout << "Load Train Data..." << endl;
    svdpp.TrainDataLoad("./data/train.txt");

    cout << "Load Probe Data..." << endl;
    svdpp.ProbeDataLoad("./data/probe.txt");

    cout << "Load Implicit Data..." << endl;
    svdpp.ImplicitDataLoad("./data/history.txt");

    cout << "Begin Train..." << endl;
    svdpp.Train(maxloops, alpha1, alpha2, beta1, beta2);

    cout << "Begin Predict..." << endl;
    svdpp.Predict("./data/predict.txt", "./out/result.txt");
    return 0;
}

