#!/usr/bin/env python
from numpy import *
from copy import deepcopy

def createDataSet(n):
    dataArr = sorted(random.uniform(-1.0, 1.0, n))
    labelArr = ones(n)
    for i in range(len(dataArr)):
        labelArr[i] = sign(dataArr[i])
        if random.randint(1, 10) < 3:
            labelArr[i] = -labelArr[i]
    return dataArr, labelArr

def loadDataSet(filename):
    dataArr = []
    fr = open(filename)
    for line in fr.readlines():
        lineArr = line.strip().split('\t')
        dataArr.append([float(x) for x in lineArr])
    return dataArr

def decisionStump(dataArr, labelArr, symbol = True):
    n = len(dataArr)
    sumy = deepcopy(labelArr)
    for i in range(1, len(labelArr), 1):
        sumy[i] += sumy[i-1]
    error = (n - sumy[-1]) / 2
    if symbol == False:
        error = n - error
    theta = -1.0
    for i in range(len(labelArr) - 1):
        err = (i + 1 + sumy[i]) / 2 + (n - i - 1 - (sumy[-1] - sumy[i])) / 2
        if symbol == False:
            err = n - err
        if err < error:
            error = err
            theta = (dataArr[i] + dataArr[i + 1]) / 2.0
    if symbol == True and (n + sumy[-1]) / 2 < error:
        error = (n + sumy[-1]) / 2
        theta = 1.0
    elif symbol == False and (n - sumy[-1]) / 2 < error:
        error = (n - sumy[-1]) / 2
        theta = 1.0
    return float(error) / n, theta, symbol

def multiDecisionStump():
    dataSet = loadDataSet('/home/muye/code/python/data/coursera/decisionStump_train.txt')
    errors = []
    n = shape(dataSet)[1]
    for i in range(n - 1):
        data = [[d[i], d[-1]] for d in dataSet]
        data.sort(key = lambda x:x[0])
        dataArr = [ x[0] for x in data ]
        labelArr = [ x[1] for x in data ]
        error, theta, symbol = decisionStump(dataArr, labelArr, True)
        errors.append([i, error, theta, symbol])
        error, theta, symbol = decisionStump(dataArr, labelArr, False)
        errors.append([i, error, theta, symbol])
    errors.sort(key = lambda x : x[1])
    return errors[0]

def test(idx, theta, symbol):
    dataSet = loadDataSet('/home/muye/code/python/data/coursera/decisionStump_test.txt')
    error = 0
    for d in dataSet:
        if symbol == True and sign(d[idx] - theta) != sign(d[-1]):
            error += 1
        if symbol == False and sign(theta - d[idx]) != sign(d[-1]):
            error += 1
    return float(error) / len(dataSet)

if __name__ == "__main__":
    """
    inErr = 0.0; outErr = 0.0
    for i in range(5000):
        dataArr, labelArr = createDataSet(20)
        error, theta = decisionStump(dataArr, labelArr)
        inErr += error
        outErr += 0.2 + 0.3 * fabs(theta)
    print inErr / 5000, outErr / 5000
    """
    idx, error, theta, symbol = multiDecisionStump()
    print "id =", idx
    print "in error =", error
    print "out error = ", test(idx, theta, symbol)
