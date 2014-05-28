#!/usr/bin/env python
import numpy as np
import matplotlib
matplotlib.use('Agg')
from matplotlib.mlab import prepca
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from mpl_toolkits.mplot3d import proj3d

def createDataSet():
    np.random.seed()
    mu_vec1 = np.array([0, 0, 0])
    cov_mat1 = np.array([[1, 0, 0], [0, 1, 0], [0, 0, 1]])
    data1 = np.random.multivariate_normal(mu_vec1, cov_mat1, 20)

    mu_vec2 = np.array([1, 1, 1])
    cov_mat2 = np.array([[1, 0, 0], [0, 1, 0], [0, 0, 1]])
    data2 = np.random.multivariate_normal(mu_vec2, cov_mat2, 20)

    data = np.concatenate((data1, data2), axis = 0)
    return data

def plotData3D(data, imagename):
    fig = plt.figure(figsize = (8, 8))
    ax = Axes3D(fig)
    plt.rcParams['legend.fontsize'] = 10
    ax.plot(data[0:20,0], data[0:20,1], data[0:20,2], 'o', markersize = 8, color = 'blue', alpha = 0.5, label = 'class1')
    ax.plot(data[20:40,0], data[20:40,1], data[20:40,2], '^', markersize = 8, color = 'red', alpha = 0.5, label = 'class2')
    plt.title('Samples for class 1 and class 2')
    ax.legend(loc = 'upper right')
    plt.draw()
    plt.savefig(imagename);
    plt.close()

def plotData2D(data, imagename):
    plt.plot(data[0:20,0], data[0:20,1], 'o', markersize = 8, color = 'blue', alpha = 0.5, label = 'class1')
    plt.plot(data[20:40,0], data[20:40,1], '^', markersize = 8, color = 'red', alpha = 0.5, label = 'class2')
    plt.savefig(imagename);
    plt.close()

def MyPCA(data, imagename):
    data = matplotlib.mlab.prepca(data.T)[0].T
    plotData2D(data, imagename)

if __name__ == '__main__':
    data = createDataSet()
    plotData3D(data, 'data_3d.png')
    plotData2D(data, 'data_2d.png')
    MyPCA(data, 'pca_2d.png')


