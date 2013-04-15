// Copyright (c) 2013 default
// Author: Muye (muyepiaozhou@gmail.com)

#include "baseline.h"

int main(int argc, char **argv) {
    BaseLine base;
    cout << "LoadData..." << endl;
    base.LoadData("./training_set.txt");
    cout << "Train..." << endl;
    base.GradientDesc();
    cout << "Predict..." << endl;
    base.Predict("./predict.txt", "./result.txt");
    cout << "Save..." << endl;
    base.Save("./argu.txt", "./check.txt");
    cout << "Over" << endl;
    return 0;
}

