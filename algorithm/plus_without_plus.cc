//
//写一个函数,求两个整数之和,要求在函数体内不得使用＋、－、×、÷
//http://zh.wikipedia.org/wiki/%E5%8A%A0%E6%B3%95%E5%99%A8
//半加器有两个输入和两个输出,输入可以标识为 A、B,输出通常标识为和 S 和进位 C
//A 和 B 经 XOR 运算后即为 S,经 AND 运算后即为 C
//

#include <iostream>
using namespace std;

int add(int a, int b) {
	if(b==0) return a;
	int sum = a^b;
	int carry =(a&b)<<1;
	return add(sum,carry);
}

int main(int argc, char** argv) {
    cout << add(4, 7) <<endl;
    cout << add(3, 8) <<endl;
}

