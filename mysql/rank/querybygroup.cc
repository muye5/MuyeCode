// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)

#include "rank/querybygroup.h"

namespace Query {
    QueryByGroup::QueryByGroup() : con(HOST, USER, PASS, DB), connect(con.getConnection()) {
        connect->setAutoCommit(false);
        stmt.reset(connect->createStatement());
    }
    int QueryByGroup::query(int uid) {
        int score = 0, rank = 0;
        try {
            sql.str("");
            sql << "SELECT t1.score, 1 + COUNT(t2.uid)"
                << "FROM user_score t1, user_score t2 "
                << "WHERE t1.uid = "
                << uid
                << " AND t2.score > t1.score AND t2.score < floor((t1.score + 1000) / 1000) * 1000";
            stmt->execute(sql.str());
            auto_ptr<sql::ResultSet> res(stmt->getResultSet());
            while(res->next()) {
                score = res->getInt(1);
                rank = res->getInt(2);
            }
            sql.str("");
            sql << "SELECT sum(count) "
                << "FROM score_range "
                << "WHERE from_score > "
                << score;
            stmt->execute(sql.str());
            res.reset(stmt->getResultSet());
            while(res->next()) {
                rank += res->getInt(1);
            }
            res.reset(NULL);
            return rank;
        } catch (sql::SQLException& e) {
            cout << "# ERR: " << e.what() << endl;
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
            return EXIT_FAILURE;
        } catch (runtime_error& e) {
            cout << "# ERR: " << e.what() << endl;
            return EXIT_FAILURE;
        }
    }

    bool QueryByGroup::update(int uid, int offset) {
        int score = 0;
        try {
            sql.str("");
            sql << "SELECT score FROM user_score WHERE uid = " << uid;
            auto_ptr<sql::ResultSet> res(stmt->executeQuery(sql.str()));
            while(res->next()) {
                score = res->getInt(1);
            }
            res.reset(NULL);
        } catch (sql::SQLException& e) {
            cout << "# ERR: " << e.what() << endl;
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
            return false;
        } catch (runtime_error& e) {
            cout << "# ERR: " << e.what() << endl;
            return false;
        }
        int newscore = score + offset;
        if(newscore < 0) {
            newscore = 0;
        } else if(newscore > MAX_SCORE) {
            newscore = MAX_SCORE;
        }
        int rng = score / 1000 * 1000;
        int newrng = newscore / 1000 * 1000;

        try {
            sql.str("");
            sql << "UPDATE user_score SET score = "
                << newscore
                << " WHERE uid = "
                << uid;
            stmt->execute(sql.str());
            sql.str("");
            if(rng != newrng) {
                sql.str("");
                sql << "UPDATE score_range SET count = count - 1 WHERE from_score = " << rng;
                stmt->execute(sql.str());
                sql.str("");
                sql << "UPDATE score_range SET count = count + 1 WHERE from_score = " << newrng;
                stmt->execute(sql.str());
            }
            connect->commit();
            return true;
        } catch (sql::SQLException& e) {
            cout << "# ERR: " << e.what() << endl;
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
            return false;
        } catch (runtime_error& e) {
            cout << "# ERR: " << e.what() << endl;
            return false;
        }
    }
} // namespace Query
