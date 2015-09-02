// 7.2
// MaxProfit
// Given a log of stock prices compute the maximum possible earning.
// Test Score: 100%
#include <iostream>
#include <vector>
using namespace std;

int solution(vector<int> &A) {
	if(A.size() <= 1)
		return 0;

	const int N = int(A.size());
	int tmp = A[0];
	for(int i = 1; i < N; i ++) {
		int tmp2 = A[i];
		A[i] -= tmp;
		tmp = tmp2;
	}
	A[0] = 0;

	int max_ending = 0;
	int max_slice = 0;
	for(int i = 0; i < N; i ++) {
		max_ending = max(0, max_ending + A[i]);
		max_slice = max(max_slice, max_ending);
	}

	return max(0, max_slice);
}

int main(void) {
	{ // 1
		int a[] = {23171, 21011, 21123, 21366, 21013, 21367};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		if(r != 356)
			cout << "ERROR" << endl;
	}

	return 0;
}
