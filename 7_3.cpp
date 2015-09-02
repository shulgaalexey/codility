// 7.3
// MaxSliceSum
// Find a maximum sum of a compact subsequence of array elements.
// Test Score: 100%
#include <iostream>
#include <vector>
#include <climits>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

int solution(vector<int> &A) {
	int max_ending = 0;
	int max_slice = 0;
	for(size_t i = 0; i < A.size(); i ++) {
		max_ending = max(0, max_ending + A[i]);
		max_slice = max(max_slice, max_ending);
	}

	if(max_slice != 0)
		return max_slice;

	max_slice = INT_MIN;
	for(size_t i = 0; i < A.size(); i ++)
		if(A[i] > max_slice)
			max_slice = A[i];

	return max_slice;
}


int calc_slice(const vector<int> &A, size_t start, size_t finish) {
	int sum = 0;
	for(size_t i = start; i <= finish; i ++)
		sum += A[i];
	return sum;
}

int solution_bf(vector<int> &A) {
	int max_slice = INT_MIN;
	for(size_t i = 0; i < A.size(); i ++) {
		for(size_t j = i; j < A.size(); j ++) {
			int slice = calc_slice(A, i, j);
			if(slice > max_slice)
				max_slice = slice;
		}
	}
	return max_slice;
}

int main(void) {
	{ // 1
		int a[] = { 3, 2, -6, 4, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r1 = solution(A);
		if(r1 != 5)
			cout << "ERROR1" << endl;

		int r2 = solution_bf(A);
		if(r2 != 5)
			cout << "ERROR1_bf" << endl;
	}

	{ // rnd
		srand(time(NULL));
		for(int test = 0; test < 10; test ++) {
			const int N = 10;
			vector<int> A(N);
			for(int i = 0; i < N; i ++)
				A[i] = -5 + rand() % 10;

			int r1 = solution(A);
			int r2 = solution_bf(A);
			if(r1 != r2)
				cout << "ERROR_rnd" << endl;
		}
	}

	{ // heavy rnd
		srand(time(NULL));
		for(int test = 0; test < 100; test ++) {
			cout << "test " << test << "..." << endl;
			const int N = 1000;
			vector<int> A(N);
			for(int i = 0; i < N; i ++)
				A[i] = -1000000 + rand() % 1000000;

			int r1 = solution(A);
			int r2 = solution_bf(A);
			if(r1 != r2)
				cout << "ERROR_rnd" << endl;
		}
	}

	return 0;
}
