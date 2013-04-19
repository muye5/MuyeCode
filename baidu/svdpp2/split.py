#!/usr/bin/env python
import sys
import os
import random

f = open("./training_set.txt", 'r')
umap = open("./umap.txt", 'w')
imap = open("./imap.txt", 'w')
train = open("./train.txt", 'w')
test = open("./probe.txt", 'w')

mids = {}
uids = {}
nu = 0
nm = 0
idu = 0
idm = 0

while(True):
    line = f.readline()
    if not line : break
    items = line.strip().split('\t')
    if items[0] in uids:
        idu = uids[items[0]]
    else:
        idu = nu + 1
        nu = idu
        uids[items[0]] = idu
        print >> umap, '\t'.join([items[0], str(idu)])

    if items[1] in mids:
        idm = mids[items[1]]
    else:
        idm = nm + 1
        nm = idm
        mids[items[1]] = idm
        print >> imap, '\t'.join([items[1], str(idm)])

    if(random.randint(1, 10) == 4):
        print >> test, '\t'.join([str(idu), str(idm), items[2]])
    print >> train, '\t'.join([str(idu), str(idm), items[2]])
f.close()
imap.close()
umap.close()
train.close()
test.close()

print "number of customer is", nu
print "size of uids is", len(uids)
print "number of movie is", nm
print "size of mids is", len(mids)

f = open("./predict.txt", 'r')
out = open("./pred.txt", 'w')
num = 0
while(True):
    line = f.readline()
    num = num + 1
    if not line : break
    items = line.strip().split('\t')
    uid = uids.get(items[0], 0)
    mid = mids.get(items[1], 0)
    if uid == 0 or mid == 0:
        print "Line", num, "Not Found:", items[0], items[1]
        sys.exit(-1)
    print >> out, '\t'.join([str(uid), str(mid)])
f.close()
out.close()

f = open("./user_history.txt", 'r')
out = open("./history.txt", 'w')
while(True):
    line = f.readline()
    if not line : break
    items = line.strip().split('\t')
    if items[0] in uids:
        uid = uids[items[0]]
        mid = mids.get(items[1], 0)
        if mid == 0:
            mid = nm + 1
            nm = mid
            mids[items[1]] = mid
        print >> out, '\t'.join([str(uid), str(mid)])
f.close()
out.close()
print "feedback size is", nm
print "size of mids is", len(mids)
