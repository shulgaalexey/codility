// 4.3
// Distinct
// Compute number of distinct values in an array.
// Test Score: 100%
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <map>
using namespace std;

int solution(vector<int> &A) {
	if(A.empty())
		return 0;
	if(A.size() == 1)
		return 1;
	sort(A.begin(), A.end());
	int cnt = 1;
	int cur = A[0];
	for(size_t i = 1; i < A.size(); i ++) {
		if(A[i] != cur) {
			cur = A[i];
			cnt ++;
		}
	}
	return cnt;
}

int solution_bf(vector<int> &A) {
	if(A.empty())
		return 0;
	if(A.size() == 1)
		return 1;
	map<int, int> m;
	for(size_t i = 0; i < A.size(); i ++)
		m[A[i]] = 1;
	return m.size();
}

int main(void) {
	{ // 1
		int a[] = {2, 1, 1, 2, 3, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int c = solution(A);
		if(c != 3)
			cout << "ERROR1" << endl;
	}

	{ // 1
		vector<int> A;
		int c = solution(A);
		if(c != 0)
			cout << "ERROR2" << endl;
	}

	{ // 3
		int a[] = {1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int c = solution(A);
		if(c != 1)
			cout << "ERROR3" << endl;
	}

	{ // 4
		int a[] = {1, 2, 3};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int c = solution(A);
		if(c != 3)
			cout << "ERROR4" << endl;
	}

	{ // 5
		int a[] = {1, 1, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int c = solution(A);
		if(c != 1)
			cout << "ERROR5" << endl;
	}

	{ // 6
		srand(time(NULL));
		for(int test = 0; test < 10; test ++) {
			cout << "test " << test << endl;
			const int N = 10;
			vector<int> A(N);
			vector<int> B(N);
			for(int i = 0; i < N; i ++) {
				A[i] = rand() % 7;
				B[i] = A[i];
				//cout << A[i] << " ";
			}
			//cout << endl;

			int c = solution(A);
			int bf = solution_bf(B);
			if(c != bf)
				cout << "ERROR6" << endl;
			//cout << c << endl;
		}
	}
	return 0;
}
