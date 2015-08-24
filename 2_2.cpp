// 2.2
// PermCheck
// Check whether array A is a permutation.
// Test Score: 100%
#include <iostream>
#include <vector>
using namespace std;

int solution(vector<int> &A) {
	if(A.empty()) return 0;
	const size_t N = A.size();
	const size_t N1 = N + 1;
	unsigned char e[N1];
	for(size_t i = 0; i < N1; i ++)
		e[i] = 0;
	for(size_t i = 0; i < N; i ++) {
		if(A[i] > int(N))
			return 0;
		e[A[i]] = 1;
	}
	for(size_t i = 1; i < N1; i ++)
		if(!e[i])
			return 0;
	return 1;
}

int main(void) {
	{ // 1
		int a[] = {4, 1, 3, 2};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int f = solution(A);
		if(f != 1) cout << "ERROR1!" << endl;
	}

	{ // 2
		int a[] = {4, 1, 3};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int f = solution(A);
		if(f != 0) cout << "ERROR2!" << endl;
	}

	{ // 3
		vector<int> A(1);
		A[0] = 1;
		int f = solution(A);
		if(f != 1) cout << "ERROR3!" << endl;

		A[0] = 0;
		f = solution(A);
		if(f != 0) cout << "ERROR4!" << endl;

		A[2] = 0;
		f = solution(A);
		if(f != 0) cout << "ERROR5!" << endl;
	}

	{ // 4
		vector<int> A(100000);
		for(size_t i = 0; i < 100000; i ++)
			A[i] = i + 1;
		int f = solution(A);
		if(f != 1) cout << "ERROR6!" << endl;

		A[0] = 100000 + 1;
		f = solution(A);
		if(f != 0) cout << "ERROR67" << endl;
		A[0] = 1;

		A[13] = 100000 + 1;
		f = solution(A);
		if(f != 0) cout << "ERROR68" << endl;
		A[13] = 14;

		A[100000 - 1] = 100000 + 1;
		f = solution(A);
		if(f != 0) cout << "ERROR69" << endl;
	}

	return 0;
}
