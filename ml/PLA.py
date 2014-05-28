#!/usr/bin/env python
from numpy import *
import random

def loadDataSet(filename):
    dataArr = []; labelArr = []
    fr = open(filename)
    for line in fr.readlines():
        lineArr = line.strip().split('\t')
        dataArr.append([1.0] + [float(x) for x in lineArr[:-1]])
        labelArr.append(int(lineArr[4]))
    return dataArr, labelArr

def PLA(dataArrIn, classLabels):
    dataArr = array(dataArrIn); labelArr = array(classLabels)
    m, n = shape(dataArr)
    W = zeros(n)
    iter = 0
    while True:
        changedFlag = False
        for i in range(m):
            if sign(dot(W, dataArr[i])) != labelArr[i]:
                W = W + labelArr[i] * dataArr[i]
                changedFlag = True
                iter += 1
        if not changedFlag: break
    print W
    print "Iteration :", iter

def PLA2(dataArrIn, classLabels):
    dataArr = array(dataArrIn); labelArr = array(classLabels)
    m, n = shape(dataArr)
    iter = 0
    for j in range(2000):
        random.seed()
        index = range(m)
        random.shuffle(index)
        W = zeros(n)
        while True:
            changedFlag = False
            for j in index:
                if sign(dot(W, dataArr[j])) != labelArr[j]:
                    W = W + labelArr[j] * dataArr[j]
                    changedFlag = True
                    iter += 1
            if not changedFlag : break
    print "Average Iteration :", float(iter) / 2000

def PLA3(dataArrIn, classLabels):
    dataArr = array(dataArrIn); labelArr = array(classLabels)
    m, n = shape(dataArr)
    alpha = 0.5
    iter = 0
    for j in range(2000):
        random.seed()
        index = range(m)
        random.shuffle(index)
        W = zeros(n)
        while True:
            changedFlag = False
            for j in index:
                if sign(dot(W, dataArr[j])) != labelArr[j]:
                    W = W + alpha * labelArr[j] * dataArr[j]
                    changedFlag = True
                    iter += 1
            if not changedFlag : break
    print "Average Iteration with Alpha = 0.5:", float(iter) / 2000

def PLA_Pocket(dataArrIn, classLabels, testData, testLabels):
    dataArr = array(dataArrIn); labelArr = array(classLabels)
    m, n = shape(dataArr)
    totalError = 0
    for i in range(2000):
        random.seed()
        Wg = zeros(n); W = zeros(n)
        error = Test(Wg, testData, testLabels)
        for j in range(100):
            index = random.sample(range(m), m)
            for idx in index:
                if sign(dot(W, dataArr[idx])) != labelArr[idx]:
                    W = W + labelArr[idx] * dataArr[idx]
                    err = Test(W, testData, testLabels)
                    if err < error:
                        error = err; Wg = W
                    break
        error = Test(Wg, testData, testLabels)
        totalError += error
    print "Average Error :", float(totalError) / (2000 * len(testData))

def Test(W, dataArrIn, classLabels):
    dataArr = array(dataArrIn); labelArr = array(classLabels)
    m, n = shape(dataArr)
    error = 0
    for i in range(m):
        if sign(dot(W, dataArr[i])) != labelArr[i]:
            error += 1
    return error

if __name__ == "__main__":
    dataArr, labelArr = loadDataSet('/home/muye/code/python/data/coursera/pla_packet.txt')
    testData, testLabels = loadDataSet('/home/muye/code/python/data/coursera/pla_test.txt')
    PLA_Pocket(dataArr, labelArr, testData, testLabels)
    """
    PLA(dataArr, labelArr)
    PLA2(dataArr, labelArr)
    PLA3(dataArr, labelArr)
    """
