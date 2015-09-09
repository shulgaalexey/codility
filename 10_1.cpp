// 10.1
// ChocolatesByNumbers
// There are N chocolates in a circle. Count the number of chocolates
// you will eat.
// Test Score: 100%
#include <iostream>
using namespace std;

int solution(int N, int M) {
	int a = (N > M) ? N : M;
	int b = (N > M) ? M : N;
	while(true) {
		if((a % b) == 0)
			break;
		else {
			int tmp = a;
			a = b;
			b = tmp % a;
		}
	}

	return (N / b);
}

int main(void) {
	int r1 = solution(10, 4);
	cout << r1 << endl;
	if(r1 != 5)
		cout << "ERROR1" << endl;
	return 0;
}
