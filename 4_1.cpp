// 4.1
// MaxProductOfThree
// Maximize A[P] * A[Q] * A[R] for any triplet (P, Q, R).
// Test Score: 100%
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> &A) {
	if(A.size() < 3)
		return 0;
	sort(A.begin(), A.end());
	const size_t N = A.size();
	int p1 = A[0] * A[1] * A[N - 1];
	int p2 = A[N - 1] * A[N - 2] * A[N -3];
	if(p1 > p2)
		return p1;
	else
		return p2;
}

int main(void) {
	{ // 1
		int a[] = {-3, 1, 2, -2, 5, 6};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int p = solution(A);
		if(p != 60)
			cout << "ERROR1" << endl;
	}

	{ // 2
		int a[] = {-30, 1, 2, -2, 5, 6};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int p = solution(A);
		if(p != 360)
			cout << "ERROR2" << endl;
	}

	return 0;
}
