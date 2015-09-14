// 10.2
// CommonPrimeDivisors
// Check whether two numbers have the same prime divisors.
// Test Score: 100%
// Solution taken on http://codesays.com/2014/solution-to-common-prime-divisors-by-codility/
#include <iostream>
#include <vector>
using namespace std;


int gcd(int x, int y) {
	// Compute the greatest common divisor
	if((x % y) == 0)
		return y;
	else
		return gcd(y, x % y);
}

bool hasSamePrimeDivisors(int x, int y) {
	int gcd_value = gcd(x, y);  //  The gcd contains all the common prime divisors

	while(x != 1) {
		int x_gcd = gcd(x, gcd_value);
		if(x_gcd == 1) {
			// x does not contain any more common prime divisors
			break;
		}
		x /= x_gcd;
	}

	if(x != 1) {
		// If x and y have exactly the same common prime divisors, x must be composed by
		// the prime divisors in gcd_value. So after previous loop, x must be one.
		return false;
	}

	while(y != 1) {
		int y_gcd = gcd(y, gcd_value);
		if(y_gcd == 1) {
			// y does not contain any more common prime divisors
			break;
		}
		y /= y_gcd;
	}

	return (y == 1);
}

int solution(vector<int> &A, vector<int> &B) {
	int count = 0;
	for(size_t i = 0; i < A.size(); i ++) {
		if(hasSamePrimeDivisors(A[i],B[i]))
			count += 1;
	}
	return count;
}


int main(void) {
	{ // 1
		int a[] = {15, 10, 9};
		int b[] = {75, 30, 5};

		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> B(b, b + sizeof(b) / sizeof(b[0]));

		int r = solution(A, B);
		if(r != 1)
			cout << "ERROR1" << endl;

	}

	return 0;
}
