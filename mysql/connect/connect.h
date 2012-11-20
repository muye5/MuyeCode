// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)


#ifndef MYSQL_CONNECT_CONNECT_H_
#define MYSQL_CONNECT_CONNECT_H_

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <tr1/memory>
#include <driver/mysql_public_iface.h>

namespace MuyeMySQL {
    using namespace std;
    class MuyeConnection {
    private:
        string m_url;
        string m_user;
        string m_pass;
        string m_database;
        sql::Driver *driver;
        tr1::shared_ptr<sql::Connection> con;
        tr1::shared_ptr<sql::Statement> stmt;
    public:
        MuyeConnection(const string& url, const string& user, const string& pass, const string& database);
        auto_ptr<sql::ResultSet> executeQuery(const string& sql);
        tr1::shared_ptr<sql::Connection> getConnection() {
            return con;
        }
        tr1::shared_ptr<sql::Statement> getStatement() {
            return stmt;
        }
    private:
        void createConnection();
        void createStatement();
    };
} // namespace MuyeMySQL
#endif  // MYSQL_CONNECT_CONNECT_H_

