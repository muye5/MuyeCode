#!/usr/bin/env python
from numpy import *

def loadDataSet(filename):
    dataArr = []; labelArr = []
    fr = open(filename)
    for line in fr.readlines():
        Arr = line.strip().split('\t')
        dataArr.append([1.0] + [float(x) for x in Arr[:-1]])
        labelArr.append(int(Arr[-1]))
    return array(dataArr), array(labelArr)

def LogisticRegression(step, rate, dataArr, labelArr):
    n, d = shape(dataArr)
    W = zeros(d)
    for t in range(step):
        de = zeros(d)
        for i in range(n):
            de -= labelArr[i] * dataArr[i] / (1 + exp(labelArr[i] * sum(W * dataArr[i])))
        de /= n
        W -= rate * de
    return W

def SGDLR(step, rate, dataArr, labelArr):
    n, d = shape(dataArr)
    W = zeros(d)
    for t in range(step):
        i = t % n
        de = labelArr[i] * dataArr[i] / (1 + exp(labelArr[i] * sum(W * dataArr[i])))
        W += rate * de
    return W

def test(W, dataArr, labelArr):
    n = shape(dataArr)[0]
    error = 0.0
    for i in range(n):
        if sign(sum(W * dataArr[i])) != labelArr[i]:
            error += 1
    return error / n

if __name__ == "__main__":
    dataArr, labelArr = loadDataSet("/home/muye/code/python/data/coursera/lr_train.txt")
    #W = LogisticRegression(2000, 0.01, dataArr, labelArr)
    W = SGDLR(2000, 0.001, dataArr, labelArr)
    testData, testLabel = loadDataSet("/home/muye/code/python/data/coursera/lr_test.txt")
    error = test(W, testData, testLabel)
    print error

