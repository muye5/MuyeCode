// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)
// ��׺����:
// �����㷨��rank��sa����.
// ���������ʱ�临�Ӷ�ΪO(nlog(n)), �㷨�ĺ���˼���Ƕ�ÿ���ַ���ʼ�ĳ���Ϊ2^k���Ӵ���������,�������rank����
// ���׵�ַΪi����Ϊ2^k���Ӵ������ؼ���ΪXY:
// 1.����XΪ�׵�ַΪi����Ϊ2^k-1���Ӵ�====������Ϊk-1ʱ��rank[i]
// 2.����YΪ�׵�ַΪi+2^k-1,����Ϊ2^k-1���Ӵ�====������Ϊk-1ʱ��rank[i+2^k-1]
// (ע��:���������ĺ������Ҫ,��Ȼ�㷨˼�������������ŵ��ǳ���Ϊ2^k���Ӵ�,����������ʱ�õ���rank��ֵ
// Ҳ�����õ�ֻ��һ������ֵ,����һ������Ϊ2^k-1������ֵ,����������ȥ,ʵ���ϵ�����ֻ�Ƕ�����������������)
// ������:
//
//        a         a         b         a         a         a         a         b
//        |         |         |         |         |         |         |         |
//        |         |         |         |         |         |         |         |
//1.Rank: 1         1         2         1         1         1         1         2      k = 0
//        i from len to 1:
//               SA[sum[rank[i]] = i
//        ��:SA[rank[i]������] = rank[i]������(��i);�ǰ���rank�����������SA��,ÿ��rankֵ�����������
//    SA: 1         2         4         5         6         7         3         8
//        �����������SA��Ϣ���¼���һ��rank����:��һ���ĺ����ǽ�ԭ����ʼ��rankֵ(���ܲ���1,2,3...��������)���������ֵ,Ϊ�˺����Ļ�������.
//        ��Ȼ���������������rankֵ����1,2,3�ı�ʾ����,������һ�������rank���鱣�ֲ���.
// trank: 1         1         2         1         1         1         1         2      k = 0
//        |     /   |     /   |     /   |     /   |     /   |     /   |     /   |
//        |   /     |   /     |   /     |   /     |   /     |   /     |   /     |
//    XY: 1 1       1 2       2 1       1 1       1 1       1 1       1 2       2 0
//        ����������rankֵ�Ϳ��Եó���һ�ֵ�XY,Ȼ���XY��������,�ٴ���,�Ϳ��Եó��µ�SA��rank����
//        �����漰��һ�����Ĺ��̾��Ƕ�XY������,XY��ʲô,XY���µĸ����Ӵ�,�����Ӵ�������������þɵ��Ӵ����е�������Ϣ
//        �Ͼ�����Ҫ��ֻ��һ��˳��.��������Ϳ��Խ�rankֵ�����Ӵ��Ĵ���,��SA������Ǿ��Ӵ���������Ϣ.
//        ���û�������,�ȶ�Y����������,֮��Y���źõ�˳����X����(Ҫ��ʹ���ȶ�����).
//        Y��������ԭrank����Ļ��������ƺ�0���,�������Ʋ��ֵ����˳�򱣳ֲ���,����ԭSA�����м�¼�����˳��.��0���Ĳ��ִ�������������,��С�����Ʋ���.
//        ����ԭSA�����м�¼����rank������,�����µ�YSA�л��������һ������.
//    SA: 1         2         4         5         6         7         3         8
//        |         |         |         |         |         |         |         |
//        |         |         |         |         |         |         |         |
//   YSA: 8         1         3         4         5         6         2         7
//        Ȼ���ٰ���Y���ֵ�˳������X����,X���־���ԭ����rank����,���ﰴ��YSA��˳��������rank����.
//        i from 1 to len:
//               ++sum[rank[i]]
//        i from 2 to m:
//               sum[i] += sum[i-1]
//        i from len to 1:
//               SA[sum[rank[YSA[i]]] = YSA[i]
//        �����һ��������ǻ���Y��˳������X����:rank[YSA[i]]����Y��������Ϊi������Ӧ��X���ֵ�rankֵ
//        ����Y���ֵ������ɺ���ǰ(�ȶ�)����X:�ٸ�����
//        39, 23, 27, 17, 13   ����Y����������Ϊ 23, 13, 27, 17, 39; �ٰ���Y���ֵ�˳���X���ֲ��ü�������.
//        39�ŵ�5,17�ŵ�2,27��4,13��1,23��3.�����Ϊ13, 17, 23, 27, 39
//   YSA: 8         1         3         4         5         6         2         7
//  rank: 1         1         2         1         1         1         1         2      k = 0
//        ���Բ���YSA���ü���������������rank�е�Ԫ��,˳��Ϊ:
//        rank[YSA[i]]: i from len to 1:
//        1         1         1         1         1         2         1         2
//        |         |         |         |         |         |         |         |
//        |         |         |         |         |         |         |         |
//   XSA: 1         4         5         6         2         7         8         3
//    XY: 1 1       1 2       2 1       1 1       1 1       1 1       1 2       2 0
//        XSA��˳������XY��˳��,��Ϊ��ÿһ�ֵ��������д�����Ӵ��ǲ�ͬ��,Ҳ����˵���Ĵ���rankֵӦ���ǲ�һ����.����ÿһ����Ҫ��rankֵ���и���.
//        ����rank[XSA[i]] != rank[XSA[i-1]] OR rank[XSA[i]+j] != rank[XSA[i-1]+j]�ľ����µ��Ӵ�
//        ����ע��Խ�紦��
//        for(int i = 1; i < len; ++i) {
//            if(rank[sa[i]] != rank[sa[i-1]] || (sa[i]+j - len) * (sa[i-1]+j - len) < 0)
//                ++p;
//            else if(sa[i]+j < len && sa[i-1]+j < len && rank[sa[i]+j] != rank[sa[i-1]+j])
//                ++p;
//            else if((sa[i]+j - len) * (sa[i-1]+j - len) == 0 && max(sa[i]+j, sa[i-1]+j) == len)
//                ++p;
//            trank[sa[i]] = p;
//        }
//2.Rank: 1         2         4         1         1         1         2         3      k = 1
//        ���ó����µ��Ӵ����������һ�ֵ���,���������Ӵ�������m���Ӵ�����

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

void suffix_init(string s) {
    int sum[26];
    memset(sum, 0, sizeof(sum));

    int len = s.length();
    vector<int> rank;
    rank.resize(len);
    // rank������Ϊ�ַ�������,����������ĳ�ʼֵ
    for(int i = 0; i < len; ++i) {
        rank[i] = s[i] - 'a';
    }
    for(int i = 0; i < len; ++i) {
        ++sum[rank[i]];
    }
    for(int i = 1; i < 26; ++i) {
        sum[i] += sum[i-1];
    }
    vector<int> sa;
    sa.resize(len);
    //��������(�Ӻ���ǰ:�ȶ�����)
    for(int i = len - 1; i >= 0; --i) {
        sa[sum[rank[i]]-1] = i;
        --sum[rank[i]];
    }

    vector<int> trank;
    trank.resize(len);
    //����������ڵ���ѭ�����ַ��������rank����,����ó��ĺ������rank������ͬ,������ʵ�����ǲ�ͬ��
    //Ҳ����˵������������������һ��ʼ��sa��rank��������ڱ����㷨�������sa��rank��������ǲ�һ����
    //��Ϊ��sa˵����ֻ����Ԫ��֮������˳��,���ԱȽϼ���
    int p = 0;
    trank[sa[0]] = 0;
    for(int i = 1; i < len; ++i) {
        if(rank[sa[i]] != rank[sa[i-1]]) ++p;
        trank[sa[i]] = p;
    }
    copy(trank.begin(), trank.end(), rank.begin());
    //tsa���������������ʱY���ֵ�˳��,����Y���ֵ�˳������X��������
    //������������������
    vector<int> tsa;
    tsa.resize(len);
    //m����ͬ�Ӵ��ĸ���,j�����Ӵ��ĳ���
    int m = p, j = 1;
    p = 0;
    while(p < len - 1) {
        memset(sum, 0, sizeof(sum));
        p = 0;
        //��Y���ֵ�˳��,������tsa��
        for(int i = len - j; i < len; ++i) {
            tsa[p++] = i;
        }
        for(int i = 0; i < len; ++i) {
            if(sa[i] >= j) {
                tsa[p++] = sa[i] - j;
            }
        }

        copy(rank.begin(), rank.end(), trank.begin());
        //��Ϊÿһ�ֵ��Ӵ������µ�,���������rankҲ�����,����ÿһ�ֶ�Ӧ������ͳ�Ʋ�ͬ�Ӵ��ĸ���
        //֪�����ͬ�ִ��ĸ��������ַ�������(�������len-1ʱ����)
        for(int i = 0; i < len; ++i) {
            //��һ��û�б�Ҫ����Y���ֵ�˳��ͳ����ʵ.
            //++sum[trank[tsa[i]]];
            ++sum[trank[i]];
        }
        for(int i = 1; i <= m; ++i) {
            sum[i] += sum[i-1];
        }
        //��һ������Ҫ,���ǰ���Y���ֵ�˳������X����:��������
        for(int i = len - 1; i >= 0; --i) {
            sa[sum[trank[tsa[i]]]-1] = tsa[i];
            --sum[trank[tsa[i]]];
        }
        //���������Ӵ��Ĵ���rank,�ݴ���trank��
        trank[sa[0]] = 0;
        p = 0;
        for(int i = 1; i < len; ++i) {
            if(rank[sa[i]] != rank[sa[i-1]] || (sa[i]+j - len) * (sa[i-1]+j - len) < 0)
                ++p;
            else if(sa[i]+j < len && sa[i-1]+j < len && rank[sa[i]+j] != rank[sa[i-1]+j])
                ++p;
            else if((sa[i]+j - len) * (sa[i-1]+j - len) == 0 && max(sa[i]+j, sa[i-1]+j) == len)
                ++p;
            trank[sa[i]] = p;
        }
        copy(trank.begin(), trank.end(), rank.begin());
        j <<= 1;
        m = p;
    }
    /* ��ӡ��� */
    cout << s << endl;
    for(int i = 0; i < len; ++i) {
        cout << i << " : " << s.substr(sa[i]) << endl;
    }
    cout << endl;
    for(int i = 0; i < len; ++i) {
        cout << rank[i] << " = " << s.substr(i) << endl;
    }
    cout << endl;
    /*  */
}

int main(int argc, char **argv) {
    string s("aabbccaa");
    suffix_init(s);
    return 0;
}

