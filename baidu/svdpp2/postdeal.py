#!/usr/bin/env python
import sys
import os

mids = {}
uids = {}

f = open("./umap.txt", 'r')
while(True):
    line = f.readline()
    if not line : break
    items = line.strip().split('\t')
    uids[items[1]] = items[0]
f.close()

f = open("./imap.txt", 'r')
while(True):
    line = f.readline()
    if not line : break
    items = line.strip().split('\t')
    mids[items[1]] = items[0]
f.close()

idu = 0
idm = 0
f = open("./rt.txt", 'r')
out = open("./tmp.txt", 'w')
while(True):
    line = f.readline()
    if not line : break
    items = line.strip().split('\t')
    idu = uids.get(items[0], '0')
    idm = mids.get(items[1], '0')
    if idu == '0' or idm == '0':
        print "cann't find [", '\t'.join(items)
        sys.exit(-1)
    print >> out, '\t'.join([idu, idm, items[2]])
f.close()
out.close()
os.system("mv ./tmp.txt ./rt.txt")
