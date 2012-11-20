// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)

#include "mysql/connect/connect.h"

namespace MuyeMySQL {

    MuyeConnection::MuyeConnection(const string& url, const string& user, const string& pass, const string& database)
        : m_url(url), m_user(user), m_pass(pass), m_database(database) {
            createConnection();
            createStatement();
            cout << "#\t Connected Successfully!" << endl;
        }

    auto_ptr<sql::ResultSet> MuyeConnection::executeQuery(const string& sql) {
        try {
            if(stmt.get() == NULL) {
                throw sql::SQLException("SQLException: Statement is NULL");
            }
            auto_ptr<sql::ResultSet> res(stmt->executeQuery(sql.c_str()));
            return res;
        } catch (sql::SQLException& e) {
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
            auto_ptr<sql::ResultSet> res(NULL);
            return res;
        } catch (runtime_error& e) {
            cout << "# ERR: " << e.what() << endl;
            auto_ptr<sql::ResultSet> res(NULL);
            return res;
        }
    }

    void MuyeConnection::createConnection() {
        if(con.get() != NULL) {
            con.reset();
        }
        try {
            driver = sql::mysql::get_driver_instance();
            con.reset(driver->connect(m_url, m_user, m_pass));
        } catch (sql::SQLException& e) {
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        } catch (runtime_error& e) {
            cout << "# ERR: " << e.what() << endl;
        }
    }

    void MuyeConnection::createStatement() {
        if(stmt.get() != NULL) {
            stmt.reset();
        }
        try {
            driver = sql::mysql::get_driver_instance();
            stmt.reset(con->createStatement());
        } catch (sql::SQLException& e) {
            /*
               The MySQL Connector/C++ throws three different exceptions:

               - sql::MethodNotImplementedException (derived from sql::SQLException)
               - sql::InvalidArgumentException (derived from sql::SQLException)
               - sql::SQLException (derived from runtime_error)
               */
            /* Use what() (derived from runtime_error) to fetch the error message */
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
            cout << "not ok 1 - examples/connect.php" << endl;
        } catch (runtime_error& e) {
            cout << "# ERR: " << e.what() << endl;
            cout << "not ok 1 - examples/connect.php" << endl;
        }
    }

} // namespace MuyeMySQL

