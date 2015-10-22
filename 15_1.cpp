// 15.1
// NumberSolitaire
// In a given array, find the subset of maximal sum in which
// the distance between consecutive elements is at most 6.
// Test Score: 100%
#include <iostream>
#include <vector>
#include <map>
#include <climits>
using namespace std;

int solution(vector<int> &A) {
	const int N = int(A.size());
	vector<int> sub_solutions(6 + N, INT_MIN);
	sub_solutions[6] = A[0];

	for(int idx = 7; idx < (N + 6); idx ++) {
		int max_prev = INT_MIN;
		for(int prev_idx = 0; prev_idx < 6; prev_idx ++) {
			max_prev = max(max_prev,
					sub_solutions[idx - prev_idx - 1]);
		}
		sub_solutions[idx] = A[idx - 6] + max_prev;
	}
	return sub_solutions[N + 6 - 1];
}

//----------------------------------------------------------------------------

map<int, int> _m;
int calc_optimal_from2(vector<int> &A, int start) {
	if(_m.count(start) > 0)
		return _m[start];

	const int N = int(A.size());

	int sum = INT_MIN;
	for(int i = 1; i <= 6; i ++) {
		const int idx = start + i;
		if(idx == N)
			break;
		const int cur_sum = A[start] + calc_optimal_from2(A, idx);
		if(cur_sum > sum)
			sum = cur_sum;
	}
	_m[start] = sum;
	return sum;
}

int calc_optimal_from_bf2(vector<int> &A, int start) {

	const int N = int(A.size());

	if(start == (N - 1))
		return A[N - 1];


	int sum = INT_MIN;
	for(int i = 1; i <= 6; i ++) {
		const int idx = start + i;
		if(idx == N)
			break;
		const int cur_sum = A[start] + calc_optimal_from_bf2(A, idx);
		if(cur_sum > sum)
			sum = cur_sum;
	}
	return sum;
}

int solution2(vector<int> &A) {
	const int N = int(A.size());
	int sum = INT_MIN;
	_m[N - 1] = A[N - 1];
	for(int i = 1; i <= 6; i ++) {
		if(i == N)
			break;
		const int cur_sum = A[0] + calc_optimal_from2(A, i);
		if(cur_sum > sum)
			sum = cur_sum;
	}
	_m.clear();
	return sum;
}

int main(void) {

	{ // 0
		int a[] = {1, -2};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != (-1))
			cout << "ERROR0" << endl;
	}

	{ // 1
		int a[] = {1, -2, 0, 9, -1, -2};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != 8)
			cout << "ERROR1" << endl;
	}

	{ // 2
		int a[] = {1, -1, -2};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != (-1))
			cout << "ERROR2" << endl;
	}

	{ // 3
		int a[] = {1, 1, -2};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != 0)
			cout << "ERROR3" << endl;
	}

	{ // 4
		int a[] = {-3, -4, 7, 9, -1, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != 14)
			cout << "ERROR4" << endl;
	}

	{ // 5
		int a[] = {2, 0, -1, -5, 8, -2};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != 8)
			cout << "ERROR5" << endl;
	}

	return 0;
}
