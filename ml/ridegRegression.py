#!/usr/bin/env python
from numpy import *

def loadDataSet(filename):
    dataArr = []; labelArr = []
    with open(filename) as f:
        for line in f.readlines():
            terms = line.strip().split('\t')
            dataArr.append([1.0, float(terms[0]), float(terms[1])])
            labelArr.append(int(terms[2]))
    return dataArr, labelArr

def ridgeRegression(alpha, dataArr, labelArr):
    dataMat = mat(dataArr)
    labelMat = mat(labelArr).T
    return asarray((dataMat.T * dataMat + mat(alpha * eye(shape(dataMat)[1]))).I * dataMat.T * labelMat).T[0]

def test(W, testDataArr, testLabelArr):
    error = 0.0
    for x, y in zip(testDataArr, testLabelArr):
        if sign(sum(W * x)) != y:
            error += 1
    return error / len(testLabelArr)

if __name__ == "__main__":
    filename = '/home/muye/code/python/data/coursera/ridge_regression_train.dat'
    dataArr, labelArr = loadDataSet(filename)

    filename = '/home/muye/code/python/data/coursera/ridge_regression_test.dat'
    testDataArr, testLabelArr = loadDataSet(filename)
    for i in range(2, -11, -1):
        alpha = 10 ** i
        Ecv = 0.0
        for j in range(5):
            W = ridgeRegression(alpha, dataArr[:j * 40] + dataArr[(j+1) * 40:], labelArr[:j * 40] + labelArr[(j+1) * 40:])
            Err = test(W, dataArr[j * 40:(j+1) * 40], labelArr[j * 40:(j+1) * 40])
            Ecv += Err
        print "log(alpha):", i, "\tEcv:", Ecv / 5

    W = ridgeRegression(10 ** -8, dataArr, labelArr)
    Ein = test(W, dataArr, labelArr)
    Eout = test(W, testDataArr, testLabelArr)
    print "Ein:", Ein, "\tEout:", Eout
