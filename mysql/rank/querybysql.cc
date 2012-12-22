// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)

#include "rank/querybysql.h"

namespace Query {
    QueryBySQL::QueryBySQL() : con(HOST, USER, PASS, DB), stmt(con.getStatement()) {
    }
    int QueryBySQL::query(int uid) {
        try {
            sql.str("");
            sql << "SELECT 1 + COUNT(t2.uid) "
                << "FROM user_score t1, user_score t2 "
                << "WHERE t1.uid = " << uid << " AND t2.score > t1.score";
            stmt->execute(sql.str());
            auto_ptr<sql::ResultSet> res(stmt->getResultSet());
            int rank = 0;
            while(res->next()) {
                rank = res->getInt(1);
            }
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
} // namespace Query
