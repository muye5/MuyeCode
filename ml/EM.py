#!/usr/bin/env python
import numpy as np

class Coin:
    def __init__(self):
        self.data = []
        self.label = []
        self.thetaA = 0.0
        self.thetaB = 0.0

    def CreateDataSet(self):
        self.thetaA = np.random.random()
        self.thetaB = np.random.random()
        for t in range(50):
            theta = self.thetaA
            label = 'A'
            if np.random.random() >= 0.5:
                theta = self.thetaB
                label = 'B'
            samples = []
            # 1:head; 0:tail
            for i in range(10):
                if np.random.random() >= theta: samples.append(0)
                else: samples.append(1)
            self.data.append(samples)
            self.label.append(label)

    def Expect(self, thetas):
        thetaA, thetaB = thetas
        expection = []
        for t in range(len(self.label)):
            numH = sum(self.data[t])
            numT = len(self.data[t]) - numH
            pA = (thetaA ** numH) * ((1-thetaA) ** numT)
            pB = (thetaB ** numH) * ((1-thetaB) ** numT)
            pA /= (pA + pB); pB = 1 - pA
            expection.append([pA, pB])
        return expection

    def Maximum(self, expection):
        numAH = 0.0; numAT = 0.0
        numBH = 0.0; numBT = 0.0
        for t in range(len(self.label)):
            numH = sum(self.data[t])
            numT = len(self.data[t]) - numH
            pA, pB = expection[t]
            numAH += pA * numH
            numAT += pA * numT
            numBH += pB * numH
            numBT += pB * numT
        newThetas = []
        newThetas.append(numAH / (numAH + numAT))
        newThetas.append(numBH / (numBH + numBT))
        return newThetas

    def Train(self, iters):
        self.CreateDataSet()
        thetas = np.array([self.thetaA - 0.1, self.thetaB + 0.1])
        print '-' * 20
        print 'initial thetas:[', thetas[0], thetas[1], ']'
        for i in range(iters):
            expection = self.Expect(thetas.tolist())
            newThetas = np.array(self.Maximum(expection))
            if max(np.abs(newThetas - thetas)) < 0.00001: break
            thetas = newThetas
            # print ' ' * 5, '[', thetas[0], thetas[1], ']'
        print 'train thetas:[', thetas[0], thetas[1], ']'
        print 'original thetas:[', self.thetaA, self.thetaB, ']'

if __name__ == '__main__':
    coin = Coin()
    coin.CreateDataSet()
    coin.Train(50)
