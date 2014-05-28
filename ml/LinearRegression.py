#!/usr/bin/env python
from numpy import *

def loadDataSet(n):
    X = random.uniform(-1.0, 1.0, size = n)
    Y = random.uniform(-1.0, 1.0, size = n)
    dataArr = []; labelArr = []
    for i in range(len(X)):
        dataArr.append([1.0, X[i], Y[i]])
        if sign(X[i] ** 2 + Y[i] ** 2 - 0.6) == 1:
            labelArr.append(1)
        else:
            labelArr.append(-1)
        if random.randint(1, 10) < 2:
            labelArr[i] = -labelArr[i]
    return dataArr, labelArr

def LinearRegression(dataArr, labelArr):
    X = matrix(array(dataArr))
    Y = matrix(array(labelArr)).T
    W = (X.T * X).I * X.T * Y
    error = 0.0
    n, d = shape(X)
    for i in range(n):
        if sign(sum(X[i] * W)) != labelArr[i]:
            error += 1.0
    error = error / n
    #error = sum(asarray(X * W - Y) ** 2) / len(dataArr)
    return error

def LinearRegression2(dataArr, labelArr):
    for x in dataArr:
        x.extend([x[1] * x[2], x[1] ** 2, x[2] ** 2])
    X = matrix(array(dataArr))
    Y = matrix(array(labelArr)).T
    W = (X.T * X).I * X.T * Y
    return asarray(W)

def test(W, dataArr, labelArr):
    for x in dataArr:
        x.extend([x[1] * x[2], x[1] ** 2, x[2] ** 2])
    X = matrix(array(dataArr))
    Y = matrix(array(labelArr)).T
    error = 0.0
    n, d = shape(X)
    for i in range(n):
        if sign(sum(X[i] * W)) != labelArr[i]:
            error += 1.0
    error = error / n
    #error = sum(asarray(X * W - Y) ** 2) / len(dataArr)
    return error

if __name__ == "__main__":
    """
    error = 0.0
    for i in range(1000):
        dataArr, labelArr = loadDataSet(1000)
        error += LinearRegression(dataArr, labelArr)
    print error / 1000
    """
    W = zeros((6, 1))
    for i in range(100):
        dataArr, labelArr = loadDataSet(1000)
        W = W + LinearRegression2(dataArr, labelArr)
    W = W / 100
    print W
    error = 0.0
    for i in range(100):
        dataArr, labelArr = loadDataSet(1000)
        error += test(matrix(W), dataArr, labelArr)
    print error / 100

