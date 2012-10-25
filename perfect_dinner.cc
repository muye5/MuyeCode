// Copyright (c) 2012 Tencent Inc.
// Author: Muye (muyepiaozhou@gmail.com)
//
// Jack的完美点餐方案
// Jack最近喜欢到学校餐厅吃饭,好吃干净还便宜.
// 在学校餐厅,有a种汤,b种饭,c种面条,d种荤菜,e种素菜.
// 为了保证膳食搭配,Jack每顿饭都会点1~2样荤菜,1~2样素菜(不重复).
// 同时,在Jack心情好的时候,会点一样饭,再配上一种汤.
// 在心情不好的时候,就只吃一种面条.
// 因为经济有限,Jack每次点餐的总价在min~max之间.Jack想知道,总共有多少种不同的点餐方案.
// Input
// 输入数据第一行包含一个整数T,表示测试数据的组数,对于每组测试数据：
// 第一行为整数a,b,c,d,e(a,b,c,d,e>0 且 10>=a,b,c,d,e)
// 第二行为a个大于零的整数,表示a种汤的价格
// 第三行为b个大于零的整数,表示b种饭的价格
// 第四行为c个大于零的整数,表示c种面条的价格
// 第五行为d个大于零的整数,表示d种荤菜的价格
// 第六行为e个大于零的整数,表示e种素菜的价格
// 第七行为两个整数min max,表示每次点餐的价格范围
// Output
// 对于每组测试数据,输出一行,包含一个整数,表示点餐方案数.
// Sample Input
// 1
// 2 2 2 2 2
// 2 3
// 3 1
// 5 2
// 1 4
// 3 6
// 5 8
// Sample Output
// 3
//



#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> double_food(vector<int>& one) {
	vector<int>::size_type len = one.size();
	vector<int> v;
	for(vector<int>::size_type i = 0; i < len - 1; ++i) {
		for(vector<int>::size_type j = i + 1; j < len; ++j) {
			v.push_back(one[i] + one[j]);
		}
	}
	sort(v.begin(), v.end());
	return v;
}

vector<int> two_kinds_food(vector<int>& a, vector<int>& b, int up) {
	vector<int> price;
	for(vector<int>::iterator ita = a.begin(); ita != a.end(); ++ita) {
		for(vector<int>::iterator itb = b.begin(); itb != b.end(); ++itb) {
			if(*ita + *itb <= up) {
				price.push_back(*ita + *itb);
			} else {
				break;
			}
		}
	}
	sort(price.begin(), price.end());
	return price;
}

void read_data(vector<int>& v, int n) {
	int temp = 0;
	for(int i = 0; i < n; ++i) {
		cin >> temp;
		v.push_back(temp);
	}
	sort(v.begin(), v.end());
}

int perfect_dinner(vector<int>& a, vector<int>& b, int up, int low) {
	vector<int> price = two_kinds_food(a, b, up);
	int kinds = 0;
	for(vector<int>::iterator it = price.begin(); it != price.end(); ++it) {
		if(*it >= low) {
			++kinds;
		}
	}
	return kinds;
}

int main(int argc, char **argv) {
	freopen("./data/022.data", "r", stdin);
	int g;
	cin >> g;
	for(int i = 0; i < g; ++i) {
		int na, nb, nc, nd, ne, maxprice, minprice;
		vector<int> va, vb, vc, vd, ve, vd2, ve2;

		cin >> na >> nb >> nc >> nd >>ne;

		read_data(va, na);
		read_data(vb, nb);
		read_data(vc, nc);
		read_data(vd, nd);
		read_data(ve, ne);

		cin >> minprice >> maxprice;

		vd2 = double_food(vd);
		ve2 = double_food(ve);

		int min_a_b = va[0] + vb[0], min_c = vc[0], min_d_e = vd[0] + ve[0];
		int max_a_b = maxprice - min_d_e;
		int max_d_e = maxprice - min(min_a_b, min_c);

		vector<int> vab = two_kinds_food(va, vb, max_a_b);

		vector<int> vde = two_kinds_food(vd, ve, max_d_e);
		vector<int> vd2e = two_kinds_food(vd2, ve, max_d_e);
		vector<int> vde2 = two_kinds_food(vd, ve2, max_d_e);
		vector<int> vd2e2 = two_kinds_food(vd2, ve2, max_d_e);

		int kinds = 0;
		kinds += perfect_dinner(vab, vde, maxprice, minprice);
		kinds += perfect_dinner(vab, vd2e, maxprice, minprice);
		kinds += perfect_dinner(vab, vde2, maxprice, minprice);
		kinds += perfect_dinner(vab, vd2e2, maxprice, minprice);
		kinds += perfect_dinner(vc, vde, maxprice, minprice);
		kinds += perfect_dinner(vc, vd2e, maxprice, minprice);
		kinds += perfect_dinner(vc, vde2, maxprice, minprice);
		kinds += perfect_dinner(vc, vd2e2, maxprice, minprice);
		cout << kinds << endl;
	}
	return 0;
}

