// 6.1
// Dominator
// Find an index of an array such that its value occurs at more
// than half of indices in the array.
// Test Score: 100%
// Solution by codility
#include <iostream>
#include <vector>
using namespace std;

int solution(vector<int> &A) {
	int stack = 0;
	int size = 0;
	int idx = -1;
	for(size_t i = 0; i < A.size(); i ++) {
		if(size == 0) {
			size = 1;
			stack = A[i];
			idx = i;
		} else {
			if(stack == A[i])
				size ++;
			else
				size --;
		}
	}

	unsigned int cnt = 0;
	for(size_t i = 0; i < A.size(); i ++) {
		if(A[i] == stack) {
			cnt ++;
			if(cnt > (A.size() / 2))
				return idx;
		}
	}
	return -1;
}

int main(void) {
	{ // 1
		int a[] = {3, 4, 3, 2, 3, -1, 3, 3};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int idx = solution(A);
		if((idx < 0) || (A[idx] != 3))
			cout << "ERROR1" << endl;
	}

	{ // 2
		int a[] = {3, 4, 5, 2, 3, -1, 3, 3};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int idx = solution(A);
		if(idx != (-1))
			cout << "ERROR2" << endl;
	}

	{ // 3
		int a[] = {3, 3, 3, 3, 3, 1, 1, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int idx = solution(A);
		if((idx < 0) || (A[idx] != 3))
			cout << "ERROR3" << endl;
	}

	{ // 4
		int a[] = {1, 1, 1, 3, 3, 3, 3, 3};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int idx = solution(A);
		if((idx < 0) || (A[idx] != 3))
			cout << "ERROR4" << endl;
	}

	{ // 5
		int a[] = {3};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int idx = solution(A);
		if((idx < 0) || (A[idx] != 3))
			cout << "ERROR5" << endl;
	}

	{ // 6
		int a[] = {3, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int idx = solution(A);
		if(idx != (-1))
			cout << "ERROR6" << endl;
	}
	return 0;
}
