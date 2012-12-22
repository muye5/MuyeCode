// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)

#include "rank/arrayquery.h"

namespace Query {
    QueryArray::QueryArray() : flag(false), con(HOST, USER, PASS, DB), stmt(con.getStatement()),
    uids(new int[CNT+1]()), ranks(new int[CNT/10]()) {
        try {
            int cnt = 0;
            sql.str("");
            sql << "SELECT * FROM user_score";
            stmt->execute(sql.str());
            auto_ptr<sql::ResultSet> res(stmt->getResultSet());
            while(res->next()) {
                ++cnt;
                int id = res->getInt(1);
                int score = res->getInt(2);
                uids[id] = score;
                ++ranks[score];
                if(cnt != id) {
                    uids[cnt] = -1;
                }
            }
        } catch (sql::SQLException& e) {
            cerr << "# ERR: " << e.what() << endl;
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << " )" << endl;
        } catch (runtime_error& e) {
            cerr << "# ERR: " << e.what() << endl;
        }
    }

    QueryArray::~QueryArray() {
        if(flag) {
            try {
                tr1::shared_ptr<sql::Connection> connect(con.getConnection());
                connect->setAutoCommit(false);
                tr1::shared_ptr<sql::Statement> st(connect->createStatement());
                for(int i = 1; i <= CNT; ++i) {
                    if(uids[i] == -1) {
                        continue;
                    }
                    sql.str("");
                    sql << "UPDATE user_score SET score = "
                        << uids[i]
                        << " WHERE uid = "
                        << i;
                    st->executeUpdate(sql.str());
                }
                sql.str("");
                sql << "UPDATE score_range r, ( "
                    << "SELECT s.from_score f, COUNT(*) cnt "
                    << "FROM user_score u, score_range s "
                    << "WHERE u.score BETWEEN s.from_score AND (s.to_score - 1) "
                    << "GROUP BY s.from_score) AS t "
                    << "SET r.count = t.cnt "
                    << "WHERE r.from_score = t.f";
                st->execute(sql.str());
                connect->commit();
            } catch (sql::SQLException& e) {
                cout << "# ERR: " << e.what() << endl;
                cout << " (MySQL error code: " << e.getErrorCode();
                cout << ", SQLState: " << e.getSQLState() << " )" << endl;
            } catch (runtime_error& e) {
                cout << "# ERR: " << e.what() << endl;
            }
        }
        delete[] uids;
        delete[] ranks;
    }

    int QueryArray::query(int uid) {
        int rnk = 1;
        for(int score = uids[uid] + 1; score < CNT/10; ++score) {
            rnk += ranks[score];
        }
        return rnk;
    }

    bool QueryArray::update(int uid, int offset) {
        flag = true;
        int score = uids[uid];
        int newscore = score + offset;
        if(newscore < 0) {
            newscore = 0;
        } else if(newscore > MAX_SCORE) {
            newscore = MAX_SCORE;
        }
        uids[uid] = newscore;
        --ranks[score];
        ++ranks[newscore];
        return true;
    }
}

