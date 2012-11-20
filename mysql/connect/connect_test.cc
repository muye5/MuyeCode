// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)

#include "mysql/connect/connect.h"
#include "mysql/connect/property.h"

using namespace std;
using namespace MuyeProperty;

int main(int argc, char** argv) {
    string url = EXAMPLE_HOST;
    string user = EXAMPLE_USER;
    string pass = EXAMPLE_PASS;
    string db = EXAMPLE_DB;
    stringstream sql;
    stringstream msg;

    try {
        MuyeMySQL::MuyeConnection con(url, user, pass, db);
        tr1::shared_ptr<sql::Statement> stmt = con.getStatement();
        /* create new table */
        {
            stmt->execute("USE " + db);
            stmt->execute("DROP TABLE IF EXISTS test");
            stmt->execute("CREATE TABLE test(id INT, label CHAR(1))");
            cout << "#\t Test table created" << endl;
        }

        /* Populate the test table with data */
        {
            for (int i = 0; i < EXAMPLE_NUM_TEST_ROWS; ++i) {
                sql.str("");
                sql << "INSERT INTO test(id, label) VALUES (";
                sql << test_data[i].id << ", '" << test_data[i].label << "')";
                stmt->execute(sql.str());
            }
            cout << "#\t Test table populated" << endl;
        }

        /* Run a query */
        {
            int row = 0;
            sql.str("");
            sql << "SELECT id, label FROM test ORDER BY id ASC";
            auto_ptr<sql::ResultSet> res = con.executeQuery(sql.str());
            cout << "#\t Running 'SELECT id, label FROM test ORDER BY id ASC'" << endl;
            /* Number of rows in the result set */
            cout << "#\t\t Number of rows\t";
            cout << "res->rowsCount() = " << res->rowsCount() << endl;
            if (res->rowsCount() != EXAMPLE_NUM_TEST_ROWS) {
                msg.str("");
                msg << "Expecting " << EXAMPLE_NUM_TEST_ROWS << "rows, found " << res->rowsCount();
                throw runtime_error(msg.str());
            }
            /* Fetching data */
            while(res->next()) {
                cout << "#\t\t Fetching row " << row << "\t";
                cout << "id = " << res->getInt(1);
                cout << ", label = '" << res->getString("label") << "'" << endl;
                row++;
            }
            res.reset(NULL);
        }

        /* Usage of UPDATE */
        {
            stmt->execute("INSERT INTO test(id, label) VALUES (100, 'z')");
            int affected_rows = stmt->executeUpdate("UPDATE test SET label = 'y' WHERE id = 100");
            cout << "#\t UPDATE indicates " << affected_rows << " affected rows" << endl;
            if (affected_rows != 1) {
                msg.str("");
                msg << "Expecting one row to be changed, but " << affected_rows << "change(s) reported";
                throw runtime_error(msg.str());
            }
            stmt.reset();
        }
    } catch (sql::SQLException& e) {
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        cout << "not ok 1 - examples/connect.php" << endl;
        return EXIT_FAILURE;

    } catch (runtime_error& e) {
        cout << "# ERR: " << e.what() << endl;
        cout << "not ok 1 - examples/connect.php" << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

