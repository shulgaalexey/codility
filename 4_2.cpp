// 4.2
// Test Score: 100%
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> &A) {
	const size_t N = A.size();
	if(N < 3)
		return 0;
	sort(A.begin(), A.end());
	for(size_t i = 0; i < (N - 2); i ++) {
		long long dif =	A[i+2] - A[i+1];
		if((A[i] >= 0) && (A[i] > dif))
			return 1;
	}
	return 0;
}

int main(void) {

	{ // 1
		int a[] = {10, 2, 5, 1, 8, 20};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int e = solution(A);
		if(e != 1)
			cout << "ERROR1" << endl;
	}

	{ // 2
		int a[] = {10, 50, 5, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int e = solution(A);
		if(e != 0)
			cout << "ERROR2" << endl;
	}

	{ // 3
		int a[] = {10, 2, 5, 1, 8, 20, 100, 200};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int e = solution(A);
		if(e != 1)
			cout << "ERROR3" << endl;
	}

	return 0;
}
