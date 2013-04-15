// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)

#include "baseline.h"

int main(int argc, char **argv) {
    BaseLine base;
    cout << "LoadData..." << endl;
    base.LoadData("./data/training_set.txt");
    cout << "Train..." << endl;
    base.GradientDesc();
    cout << "Predict..." << endl;
    base.Predict("./data/predict.txt", "./out/result.txt");
    cout << "Save..." << endl;
    base.Save("./out/argu.txt", "./out/check.txt");
    cout << "Over" << endl;
    return 0;
}

