// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)

#include "rank/treequery.h"

namespace Query {
    QueryTree::QueryTree() : flag(false), con(HOST, USER, PASS, DB), stmt(con.getStatement()),
    tree(new Node[(CNT/10) << 2]()), uids(new int[CNT+1]()) {
        build(0, 0, CNT/10);
        try {
            sql.str("");
            sql << "SELECT * FROM user_score";
            stmt->execute(sql.str());
            auto_ptr<sql::ResultSet> res(stmt->getResultSet());
            int cnt = 0;
            while(res->next()) {
                int id = res->getInt(1);
                int score = res->getInt(2);
                uids[id] = score;
                ++cnt;
                if(cnt != id) {
                    uids[cnt] = -1;
                }
                if(!add(score, 0, 1)) {
                    cerr << "Add [" << id << ":" << score << "] failed!" << endl;
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

    QueryTree::~QueryTree() {
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
        delete[] tree;
        delete[] uids;
    }

    int QueryTree::query(int uid) {
        if(uid < 1 || uid > CNT ) {
            cerr << uid << " should between 1 and " << CNT << endl;
            return -1;
        }
        int score = uids[uid];
        return (1 + query(++score, 0));
    }

    void QueryTree::build(int index, int l, int r) {
        tree[index].l = l;
        tree[index].r = r;
        if(l + 1 == r) {
            return;
        }
        int m = tree[index].middle();
        build((index << 1) + 1, l, m);
        build((index << 1) + 2, m, r);
    }

    bool QueryTree::add(int v, int index, int offset) {
        if(v < tree[index].l || v >= tree[index].r) {
            cerr << v << " is not between " << tree[index].l << " and " << tree[index].r << endl;
            return false;
        }
        if(tree[index].l + 1 == tree[index].r) {
            if(tree[index].l != v) {
                cerr << v << " not between " << tree[index].l << " and " << tree[index].r << endl;
                return false;
            }
            tree[index].cnt += offset;
            return true;
        }
        int m = tree[index].middle();
        if(v < m) {
            return add(v, (index << 1) + 1, offset) && (tree[index].cnt += offset);
        } else {
            return add(v, (index << 1) + 2, offset) && (tree[index].cnt += offset);
        }
    }

    /*
    int cntnum(int l, int r, int index) {
        if(l < tree[index].l || r > tree[index].r) {
            cerr << v << " is not between " << tree[index].l << " and " << tree[index].r << endl;
            return 0;
        }
        if(tree[index].l == l && tree[index].r == r) {
            return tree[index].cnt;
        }
        int m = tree[index].middle();
        int num = 0;
        if(r <= m) {
            num += cntnum(l, r, (index << 1) + 1);
        } else if(l >= m){
            num += cntnum(l, r, (index << 1) + 2);
        } else {
            num += cntnum(l, m, (index << 1) + 1);
            num += cntnum(m, r, (index << 1) + 2);
        }
        return num;
    }
    */

    int QueryTree::query(int score, int index) {
        if(tree[index].l + 1 == tree[index].r) {
            if(score != tree[index].l) {
                return 0;
            }
            return tree[index].cnt;
        }
        int m = tree[index].middle();
        if(score < m) {
            int rnk = 0;
            rnk += tree[(index << 1) + 2].cnt;
            rnk += query(score, (index << 1) + 1);
            return rnk;
        } else {
            return query(score, (index << 1) + 2);
        }
    }

    bool QueryTree::update(int uid, int offset) {
        flag = true;
        int score = uids[uid];
        int newscore = score + offset;
        if(newscore < 0) {
            newscore = 0;
        } else if(newscore > MAX_SCORE) {
            newscore = MAX_SCORE;
        }
        uids[uid] = newscore;
        add(score, 0, -1);
        add(newscore, 0, 1);
        return true;
    }
}
