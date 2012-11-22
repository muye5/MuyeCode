#!/usr/bin/env python
#coding=utf-8
###############################################
#                                             #
#         Connect MySQL By Python             #
#                                             #
###############################################

import MySQLdb

conn = MySQLdb.connect(host = 'localhost', user = 'muye', passwd = 'muye', db = 'test', port = 3306, charset = 'utf8')

cursor = conn.cursor()

count = cursor.execute("""select * from test""")

print("total lines: %s" % count)

result = cursor.fetchone();

print("id:%s   info:%s" % (result[0], result[1]))

results = cursor.fetchmany(3);
print("fetchmany line number = 3")
for r in results:
    print("%s" % str(r))

results = cursor.fetchall();
print("fetchall")
for r in results:
    print("%s" % str(r))

conn.close()
