十万用户,积分零到一万,对用户积分更新及用户排名查询
方法一:
直接由数据库统计排名:
"SELECT 1 + COUNT(t2.uid) FROM user_score t1, user_score t2 WHERE t1.uid = ? AND t2.score > t1.score"

方法二:
在数据库中创建辅助表,将积分按段划分,统计各个分段的人数;
只需计算用户所在段的排名,再查询数据库累加比他大的段中的人数和即可计算出最终排名:
"SELECT t1.score, 1 + COUNT(t2.uid) FROM user_score t1, user_score t2  WHERE t1.uid = ? AND t2.score > t1.score AND t2.score < floor((t1.score + 1000) / 1000) * 1000"

方法三:
线段树统计查询

方法四:
辅助数组统计,开辟数组[1~10000],数组对应当前积分的人数,查询时从当前位置累加至最后可得出最终排名
