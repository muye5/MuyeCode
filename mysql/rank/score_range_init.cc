// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)

#include "mysql/connect/connect.h"
#include "rank/property.h"

using namespace std;
using namespace RankProperty;

int main(int argc, char **argv) {
    string url = HOST, user = USER, pass = PASS, db = DB;
    stringstream sql;
    try {
#define CNT 100000
        MuyeMySQL::MuyeConnection con(url, user, pass, db);
        tr1::shared_ptr<sql::Statement> stmt = con.getStatement();
        stmt->execute("USE " + db);
        stmt->execute("TRUNCATE TABLE score_range");
        int num = (CNT / 10) / 1000;
        for (int i = 0; i < num; ++i) {
            int from = i * 1000;
            int to = from + 1000;
            sql.str("");
            sql << "INSERT INTO score_range(from_score, to_score) VALUES ("
                << from << "," << to << ")";
            stmt->execute(sql.str());
        }
        sql.str("");
        sql << "UPDATE score_range r, ( "
            << "SELECT s.from_score f, COUNT(*) cnt "
            << "FROM user_score u, score_range s "
            << "WHERE u.score BETWEEN s.from_score AND (s.to_score - 1) "
            << "GROUP BY s.from_score) AS t "
            << "SET r.count = t.cnt "
            << "WHERE r.from_score = t.f";
        stmt->execute(sql.str());
        stmt.reset();
    } catch (sql::SQLException& e) {
        cout << "# ERR: " << e.what() << endl;
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        return EXIT_FAILURE;
    } catch (runtime_error& e) {
        cout << "# ERR: " << e.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

