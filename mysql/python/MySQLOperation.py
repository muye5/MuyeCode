#!/usr/bin/env python
#coding=utf-8
###############################################
#                                             #
#               MySQL By Python               #
#                                             #
###############################################

import MySQLConnection

dbconn = MySQLConnection.MySQLConn()

def process():
    dbconn.connect(m_host = 'localhost', m_user = 'muye', m_passwd = 'muye', m_db = 'test')
    conn = dbconn.cursor()

    sql = "DROP TABLE IF EXISTS test"
    conn.execute(sql)
    sql = """create table test
    (id int,
    label varchar(255)
    )"""
    conn.execute(sql)

    sql = "insert into test(id, label) values(%s, %s)"
    values = ((1, 'this is inserted through python'), (2, 'python insert once many lines'), (3, 'last inserted line'))
    rows = conn.executemany(sql, values);
    print "inserted ", rows

    sql = "select * from test"
    print sql
    conn.execute(sql)
    results = conn.fetchall()
    for r in results:
        print str(r)

    dbconn.close()

if __name__ == '__main__':
    process()



