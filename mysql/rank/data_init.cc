// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)

#include "mysql/connect/connect.h"
#include "rank/property.h"
#include <ctime>
#include <climits>

using namespace std;
using namespace RankProperty;

int main(int argc, char** argv) {
#define CNT 100000
    string url = HOST, user = USER, pass = PASS, db = DB;
    stringstream sql;
    srand((unsigned)time(NULL));

    try {
        MuyeMySQL::MuyeConnection con(url, user, pass, db);
        tr1::shared_ptr<sql::Statement> stmt = con.getStatement();
        stmt->execute("USE " + db);
        stmt->execute("TRUNCATE TABLE user_score");
        /* Populate the test table with data */
        for (int i = 0; i < CNT; ++i) {
            sql.str("");
            sql << "INSERT INTO user_score(uid, score) VALUES ("
                << (i + 1)
                << ", "
                << rand() % (CNT/10) << ")";
            stmt->execute(sql.str());
        }
        stmt.reset();
        cout << "populate data done" << endl;
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

