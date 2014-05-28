#!/usr/bin/env python
"""
Newton Search Direction
with the second-order Taylor's expansion
http://www.math.unl.edu/~s-bbockel1/833-notes/node9.html
"""
from numpy import *
u = 0; v = 0
for i in range(5):
    fu = exp(u) + v * exp(u * v) + 2 * u - 2 * v - 3
    fv = 2 * exp(2 * v) + u * exp(u * v) - 2 * u + 4 * v - 2
    fuu = exp(2) + v * v * exp(u * v) + 2
    fvv = 4 * exp(2 * v) + u * u * exp(u * v) + 4
    fuv = exp(u * v) * (1 + u * v) - 2

    m2 = matrix(array([[fuu, fuv], [fuv, fvv]]))
    m1 = matrix(array([fu, fv]))
    du, dv = asarray((m2.I * m1.T).T)[0]
    print asarray((m2.I * m1.T).T)[0]
    u -= du; v -= dv
e = exp(u) + exp(2 * v) + exp(u * v) + u * u - 2 * u * v + 2 * v * v - 3 * u - 2 * v
print e
"""
u = 0; v = 0
for i in range(5):
    fu = exp(u) + v * exp(u * v) + 2 * u - 2 * v - 3
    fv = 2 * exp(2 * v) + u * exp(u * v) - 2 * u + 4 * v - 2
    u -= 0.01 * fu; v -= 0.01 * fv
e = exp(u) + exp(2 * v) + exp(u * v) + u * u - 2 * u * v + 2 * v * v - 3 * u - 2 * v
print e
"""
