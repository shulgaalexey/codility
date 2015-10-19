//13.4
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;


bool mysort(int a, int b) {
	return (abs(a) < abs(b));
}

int solution(vector<int> &A) {
	sort(A.begin(), A.end(), mysort);
	int min = abs(A[0] * 2);
	for(size_t i = 1; i < A.size(); i ++) {
		int s1 = A[i - 1] / abs(A[i - 1]);
		int s2 = A[i] / abs(A[i]);
		if((s1 * s2) > 0)
			// Those values have the same sign,
			// so it is not a good idea to analyze them:
			// The summ will be too high
			continue;

		int candidate = abs(A[i - 1] + A[i]);
		if(candidate < min)
			min = candidate;
	}
	return min;
}

int solution_bf(vector<int> &A) {
	int min = abs(A[0] * 2);
	for(size_t i = 0; i < A.size(); i ++) {
		for(size_t j = 0; j < A.size(); j ++) {
			int candidate = abs(A[i] + A[j]);
			if(candidate < min)
				min = candidate;
		}
	}
	return min;
}

int main(void) {
	{ // 1
		int a[] = {1, 4, -3};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		int r2 = solution_bf(A);
		cout << r << endl;
		cout << r2 << endl;
		if((r != 1) && (r != r2))
			cout << "ERROR1" << endl;
	}

	{ // 2
		int a[] = {-8, 4, 5, -10, 3};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		int r2 = solution_bf(A);
		cout << r << endl;
		cout << r2 << endl;
		if((r != 3) && (r != r2))
			cout << "ERROR3" << endl;
	}

	{ // 3
		int a[] = {-1000000000, 1000000000};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		int r2 = solution_bf(A);
		cout << r << endl;
		cout << r2 << endl;
		if((r != 0) && (r != r2))
			cout << "ERROR3" << endl;
	}


	{ // rnd
		for(int test = 0; test < 50; test ++) {
			cout << "test: " << test << "..." << endl;
			const int N = 10;
			vector<int> A(N, 0);
			for(int i = 0; i < N; i ++)
				A[i] = -10 + rand() % 10;

			int r1 = solution(A);
			int r2 = solution_bf(A);
			if(r1 != r2) {
				cout << "ERRORRND" << endl;
				for(int i = 0; i < N; i ++)
					cout << A[i] << " ";
				cout << endl;
			}
		}
	}
	return 0;
}
