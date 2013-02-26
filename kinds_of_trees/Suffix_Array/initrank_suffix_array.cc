// Copyright (c) 2013
// Author: Muye (muyepiaozhou@gmail.com)
// 后缀数组:
// 倍增算法求rank和sa数组.
// 倍增数组的时间复杂度为O(nlog(n)), 算法的核心思想是对每个字符开始的长度为2^k的子串进行排序,求出排名rank数组
// 设首地址为i长度为2^k的子串排名关键字为XY:
// 1.其中X为首地址为i长度为2^k-1的子串====即次幂为k-1时的rank[i]
// 2.其中Y为首地址为i+2^k-1,长度为2^k-1的子串====即次幂为k-1时的rank[i+2^k-1]
// (注意:这两个即的含义很重要,虽然算法思想上我们排序排的是长度为2^k的子串,但真正排序时用的是rank的值
// 也就是用的只是一个排名值,是上一步长度为2^k-1的排名值,这样迭代下去,实际上的排名只是对两列正整数在排序)
// 看例子:
//
//        a         a         b         a         a         a         a         b
//        |         |         |         |         |         |         |         |
//        |         |         |         |         |         |         |         |
//1.Rank: 1         1         2         1         1         1         1         2      k = 0
//        i from len to 1:
//               SA[sum[rank[i]] = i
//        即:SA[rank[i]的名次] = rank[i]的索引(即i);是按照rank的索引来填充SA的,每个rank值求出它的名词
//    SA: 1         2         4         5         6         7         3         8
//        利用算出来的SA信息重新计算一下rank数组:这一步的含义是将原来初始的rank值(可能不是1,2,3...等正整数)变成正整数值,为了后续的基数排序.
//        当然在这里我们最初的rank值就是1,2,3的表示方法,所以这一步处理后rank数组保持不变.
// trank: 1         1         2         1         1         1         1         2      k = 0
//        |     /   |     /   |     /   |     /   |     /   |     /   |     /   |
//        |   /     |   /     |   /     |   /     |   /     |   /     |   /     |
//    XY: 1 1       1 2       2 1       1 1       1 1       1 1       1 2       2 0
//        理论上有了rank值就可以得出下一轮的XY,然后对XY重新排序,再处理,就可以得出新的SA和rank数组
//        这里涉及的一个核心过程就是对XY的排序,XY是什么,XY是新的更长子串,对新子串的排序可以利用旧的子串已有的排序信息
//        毕竟我们要的只是一个顺序.所以这里就可以将rank值当做子串的代表,而SA数组就是旧子串的排序信息.
//        利用基数排序,先对Y部分做排序,之后按Y已排好的顺序排X部分(要求使用稳定排序).
//        Y数组是在原rank数组的基础上左移和0填充,所以左移部分的相对顺序保持不变,就是原SA数组中记录的相对顺序.而0填充的部分从左到右依次增大,并小于左移部分.
//        由于原SA数组中记录的是rank的索引,所以新的YSA中会对索引做一个左移.
//    SA: 1         2         4         5         6         7         3         8
//        |         |         |         |         |         |         |         |
//        |         |         |         |         |         |         |         |
//   YSA: 8         1         3         4         5         6         2         7
//        然后再按照Y部分的顺序排序X部分,X部分就是原来的rank数组,这里按照YSA的顺序来排序rank数组.
//        i from 1 to len:
//               ++sum[rank[i]]
//        i from 2 to m:
//               sum[i] += sum[i-1]
//        i from len to 1:
//               SA[sum[rank[YSA[i]]] = YSA[i]
//        最后这一步排序就是基于Y的顺序来排X部分:rank[YSA[i]]就是Y部分排名为i的所对应的X部分的rank值
//        按照Y部分的排名由后至前(稳定)排序X:举个例子
//        39, 23, 27, 17, 13   按照Y部分先排序为 23, 13, 27, 17, 39; 再按照Y部分的顺序对X部分采用计数排序.
//        39排第5,17排第2,27第4,13第1,23第3.即结果为13, 17, 23, 27, 39
//   YSA: 8         1         3         4         5         6         2         7
//  rank: 1         1         2         1         1         1         1         2      k = 0
//        所以参照YSA采用计数排序依次排列rank中的元素,顺序为:
//        rank[YSA[i]]: i from len to 1:
//        1         1         1         1         1         2         1         2
//        |         |         |         |         |         |         |         |
//        |         |         |         |         |         |         |         |
//   XSA: 1         4         5         6         2         7         8         3
//    XY: 1 1       1 2       2 1       1 1       1 1       1 1       1 2       2 0
//        XSA的顺序正是XY的顺序,因为在每一轮迭代过程中处理的子串是不同的,也就是说它的代表rank值应该是不一样的.所以每一轮需要对rank值进行更新.
//        满足rank[XSA[i]] != rank[XSA[i-1]] OR rank[XSA[i]+j] != rank[XSA[i-1]+j]的就是新的子串
//        这里注意越界处理
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
//        这便得出了新的子串代表进入下一轮迭代,这里会更新子串种类数m和子串长度

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
    // rank数组作为字符串代表,这里求出它的初始值
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
    //计数排序(从后至前:稳定排序)
    for(int i = len - 1; i >= 0; --i) {
        sa[sum[rank[i]]-1] = i;
        --sum[rank[i]];
    }

    vector<int> trank;
    trank.resize(len);
    //求出真正用于迭代循环的字符串代表的rank数组,这里得出的和上面的rank数组相同,但是其实可以是不同的
    //也就是说用于最初计数排序求得一开始的sa的rank数组和用于倍增算法求得最终sa的rank数组可以是不一样的
    //因为求sa说白了只关心元素之间的相对顺序,可以比较即可
    int p = 0;
    trank[sa[0]] = 0;
    for(int i = 1; i < len; ++i) {
        if(rank[sa[i]] != rank[sa[i-1]]) ++p;
        trank[sa[i]] = p;
    }
    copy(trank.begin(), trank.end(), rank.begin());
    //tsa用来保存基数排序时Y部分的顺序,按照Y部分的顺序来对X部分排序
    //才满足基数排序的性质
    vector<int> tsa;
    tsa.resize(len);
    //m代表不同子串的个数,j代表子串的长度
    int m = p, j = 1;
    p = 0;
    while(p < len - 1) {
        memset(sum, 0, sizeof(sum));
        p = 0;
        //求Y部分的顺序,保存在tsa中
        for(int i = len - j; i < len; ++i) {
            tsa[p++] = i;
        }
        for(int i = 0; i < len; ++i) {
            if(sa[i] >= j) {
                tsa[p++] = sa[i] - j;
            }
        }

        copy(rank.begin(), rank.end(), trank.begin());
        //因为每一轮的子串都是新的,所以其代表rank也会更新,所以每一轮都应该重新统计不同子串的个数
        //知道最后不同字串的个数等于字符串长度(这里等于len-1时结束)
        for(int i = 0; i < len; ++i) {
            //这一步没有必要按照Y部分的顺序统计其实.
            //++sum[trank[tsa[i]]];
            ++sum[trank[i]];
        }
        for(int i = 1; i <= m; ++i) {
            sum[i] += sum[i-1];
        }
        //这一步很重要,就是按照Y部分的顺序排序X部分:基数排序
        for(int i = len - 1; i >= 0; --i) {
            sa[sum[trank[tsa[i]]]-1] = tsa[i];
            --sum[trank[tsa[i]]];
        }
        //迭代更新子串的代表rank,暂存于trank中
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
    /* 打印结果 */
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

