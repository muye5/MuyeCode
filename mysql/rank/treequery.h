// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)


#ifndef RANK_TREEQUERY_H_
#define RANK_TREEQUERY_H_

#include "mysql/connect/connect.h"
#include "rank/property.h"

namespace Query {
    using namespace std;
    using namespace RankProperty;

    class QueryTree {
    private:
#define CNT 100000
#define MAX_SCORE (CNT/10 - 1)
        class Node;
        bool flag;
        stringstream sql;
        MuyeMySQL::MuyeConnection con;
        tr1::shared_ptr<sql::Statement> stmt;
        Node* tree;
        int* uids;
    public:
        QueryTree();
        ~QueryTree();
    public:
        int query(int uid);
        bool update(int uid, int offset);
    private:
        void build(int index, int l, int r);
        bool add(int v, int index, int offset);
        // int cntnum(int l, int r, int index);
        int query(int score, int index);
    private:
        class Node {
        public:
            int l, r;
            int cnt;
        public:
            Node(int ll = -1, int rr = -1) : l(ll), r(rr), cnt(0) {}
        public:
            int middle() {
                return (l + r) >> 1;
            }
        };
    };
} // namespace Query
#endif  // RANK_TREEQUERY_H_

