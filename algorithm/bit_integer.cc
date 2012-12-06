// Copyright (c) 2012 default
// Author: Muye (muyepiaozhou@gmail.com)
// ����һ��ѭ�򽥽�������,����дһ����intת������ĺ���,����ÿ���ڵ��һ��digit,Ҫע���ʾ���������:
// ������֮��,дһ����������ʾ��������������ӷ�����,ͬʱҲҪ���ǵ��������.(ע��:ÿ���ڵ��һ������)
// ģ������Ƽӷ�ʵ��һ��,�������ͦ�����,ԽдԽ��������...
// �ò����ʾ����:(4 bits) 1 == 0001, -1 == 1999
// ��һλ�Ƿ���λ,0��ʾ����,1��ʾ����

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Node {
private:
    static bool carry;
    int v;
public:
    Node() : v(0) {}
    Node(int n) {
        v = n % 10;
    }
    Node(const Node& node) {
        v = node.v;
    }
public:
    Node operator+(const Node& node) const {
        int tmp = v + node.v;
        if(carry) {
            ++tmp;
        }
        if(tmp / 10) {
            carry = true;
        } else {
            carry = false;
        }
        return Node(tmp % 10);
    }
    Node& operator=(const Node& node) {
        if(this == &node) {
            return *this;
        }
        v = node.v;
        return *this;
    }
    Node& operator+=(const Node& node) {
        v += node.v;
        if(carry) {
            ++v;
        }
        if(v / 10) {
            carry = true;
            v %= 10;
        } else {
            carry = false;
        }
        return *this;
    }
    Node operator++(int) {
        Node node = *this;
        if(++v / 10) {
            carry = true;
            v %= 10;
        } else {
            carry = false;
        }
        return node;
    }
    Node& operator++() {
        if(++v / 10) {
            carry = true;
            v %= 10;
        } else {
            carry = false;
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Node& node) {
        out << node.v;
        return out;
    }
    friend class Integer;
};

bool Node::carry = false;

class Integer {
private:
    static const int len;
    int flag;
    vector<Node> bits;
public:
    Integer() : flag(+1), bits(len - 1, Node(0)) {}
    Integer(int n) : flag(+1), bits(len - 1, Node(0)) {
        if(n < 0) {
            flag = -1;
            n *= -1;
        }
        vector<Node>::iterator it = bits.begin();
        if(flag == -1) {
            // negative situation: 9 - n
            while(it != bits.end()) {
                it->v = 9 - n % 10;
                n /= 10;
                ++it;
            }
        } else {
            while(it != bits.end()) {
                it->v = n % 10;
                n /= 10;
                ++it;
            }
        }
        // negative situation: + 1
        if(flag == -1) {
            it = bits.begin();
            ++*it;
            while(Node::carry && ++it != bits.end()) {
                ++*it;
            }
            Node::carry = false;
        }
        reverse(bits.begin(), bits.end());
    }

    Integer(const Integer& n) {
        if(this == &n) {
            return;
        }
        flag = n.flag;
        copy(n.bits.begin(), n.bits.end(), bits.begin());
    }

public:
    Integer operator+(const Integer& n) {
        Integer sum;
        vector<Node>::const_reverse_iterator rit1 = bits.rbegin();
        vector<Node>::const_reverse_iterator rit2 = n.bits.rbegin();
        vector<Node>::reverse_iterator rit3 = sum.bits.rbegin();

        while(rit1 != bits.rend()) {
            if(Node::carry) {
                Node::carry = false;
                *rit3 = *rit1 + *rit2;
                if(Node::carry) {
                    ++*rit3;
                    Node::carry = true;
                } else {
                    ++*rit3;
                }
            } else {
                *rit3 = *rit1 + *rit2;
            }
            ++rit1;
            ++rit2;
            ++rit3;
        }
        sum.flag = flag * n.flag;
        if(Node::carry) {
            sum.flag *= -1;
        }
        Node::carry = false;
        return sum;
    }

    int value() {
        int tmp = 0;
        cout << "flag = " << flag << endl;
        if(flag == -1) {
            for(vector<Node>::iterator it = bits.begin(); it != bits.end(); ++it) {
                tmp *= 10;
                tmp += 9 - it->v;
            }
            return ++tmp * flag;
        } else {
            for(vector<Node>::iterator it = bits.begin(); it != bits.end(); ++it) {
                tmp *= 10;
                tmp += it->v;
            }
            return tmp;
        }
    }

    friend ostream& operator<<(ostream& out, const Integer& n) {
        vector<Node>::const_iterator it = n.bits.begin();
        while(it != n.bits.end()) {
            out << *(it++);
        }
        return out;
    }

};

const int Integer::len = 4;

int main(int argc, char **argv) {
    Integer a(+999), b(-1000);
    Integer c = a + b;
    cout << a.value() << endl;
    cout << a << endl;
    cout << b.value() << endl;
    cout << b << endl;
    cout << c.value() << endl;
    cout << c << endl;
    return 0;
}

