// 10.2
// CommonPrimeDivisors
// Check whether two numbers have the same prime divisors.
#include <iostream>
#include <vector>
using namespace std;

int gcd(int a, int b) {
	if((a % b) == 0)
		return b;
	else
		return gcd(b, a % b);
}

int prime(int n) {
	if(n == 1)
		return true;
	int i = 2;
	while((i * i) <= n) {
		if((n %i) == 0)
			return false;
	}
	return true;
}

int solution(vector<int> &A, vector<int> &B) {
	int cnt = 0;
	for(size_t i = 0; i < A.size(); i ++) {
		if(A[i] == B[i]) {
			cnt ++;
			continue;
		}

		const int a = A[i];
		const int b = B[i];
		int n = gcd(a, b);
		if(n == 1)
			continue;

		n = 2;

		bool dif_divs = false;
		while(true) {
			if((n * n) > a)
				break;
			if((n * n) > b)
				break;

			if(!prime(n)) {
				n ++;
				continue;
			}

			bool a_prime_div = (a % n) == 0;
			bool b_prime_div = (b % n) == 0;
			if(a_prime_div == b_prime_div) {
				n ++;
				continue;
			}

			dif_divs = true;
			break;
		}

		if(!dif_divs) {
			//cout << "a = " << a << ", b = " << b << endl;
			cnt ++;
		}
	}
	return cnt;
}

int main(void) {
	{ // 1
		int a[] = {15, 10, 9};
		int b[] = {75, 30, 5};

		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> B(b, b + sizeof(b) / sizeof(b[0]));

		int r = solution(A, B);
		cout << r << endl;
		if(r != 1)
			cout << "ERROR1" << endl;

	}

	return 0;
}
