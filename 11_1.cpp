// 11.1
// Ladder
// Count the number of different ways of climbing to the top of a ladder.
// Test Score: 100%
#include <iostream>
#include <vector>
#include <climits>
#include <math.h>
using namespace std;

vector<int> solution(vector<int> &A, vector<int> &B) {
	if(A.empty())
		return vector<int>();

	// 1. Find the longest ladder
	int max_val = INT_MIN;
	for(size_t i = 0; i < A.size(); i++) {
		if(A[i] > max_val)
			max_val = A[i];
	}
	max_val = max(max_val, 2);

	// 2. Pre-calculate the ways for different ladders
	// including the longest one
	vector<unsigned long long> ways(max_val + 1, 0);
	ways[1] = 1; // For a ladder with one rung there is only one way
	ways[2] = 2; // For a ladder with two rungs there are only two ways
	for(int i = 3; i <= max_val; i ++) {
		// i means the number of remaining rungs
		ways[i] = ways[i - 1] + ways[i - 2];
		// Total number of ways equal to
		// ways if we stand by one rung plus
		// ways if we stand by two rungs
	}

	// 3. Processing input tasks
	vector<int> ret(A.size(), 0);
	for(size_t test = 0; test < A.size(); test ++) {
		const int a = A[test];
		const int modulo = 1 << B[test];
		int cur_cnt = ways[a] % modulo;
		ret[test] = cur_cnt;
	}

	return ret;
}

int main(void) {
	int a[] = {4, 4, 5, 5, 1};
	int b[] = {3, 2, 4, 3, 1};
	int e[] = {5, 1, 8, 0, 1};

	vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
	vector<int> B(b, b + sizeof(b) / sizeof(b[0]));
	vector<int> E(e, e + sizeof(e) / sizeof(e[0]));

	vector<int> r = solution(A, B);
	for(size_t i = 0; i < r.size(); i ++) cout << r[i] << " "; cout << endl;
	for(size_t i = 0; i < r.size(); i ++) {
		if(r[i] != E[i])
			cout << "ERROR" << endl;
	}
	return 0;
}
