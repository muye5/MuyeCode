#!/usr/bin/env python
#coding=utf8

import URLFilter

if __name__ == '__main__':
    urlbf = URLFilter.URLBloomFilter()
    urlbf.initdb()
    urlbf.initfilter()
    urlbf.initsql(m_sql = 'insert into test (url) values(%s)')
    if urlbf.add('www.sina.com.cn'):
        print 'add success'
    else:
        print 'add failed'
    if urlbf.add('www.sina.com.cn'):
        print 'add success'
    else:
        print 'add failed'

    urlbf.close()
