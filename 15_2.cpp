// 15.2
// MinAbsSum
// Given array of integers, find the lowest absolute sum of elements.
// Test Score: 72% (Correctness 100%, Performance 40%)
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
using namespace std;

int solution(vector<int> &A) {
	if(A.empty())
		return 0;
	map<int, int> m1;
	map<int, int> m2;
	map<int, int> *m = &m1;
	map<int, int> *m_next = &m2;
	(*m)[A[0]] = A[0];
	(*m)[-A[0]] = -A[0];
	for(size_t i = 1; i < A.size(); i ++) {
		for(map<int, int>::iterator it = m->begin();
				it != m->end(); ++it) {
			const int prev_tmp_sum = it->second;
			const int next_tmp_sum_pos = prev_tmp_sum + A[i];
			const int next_tmp_sum_neg = prev_tmp_sum - A[i];
			(*m_next)[next_tmp_sum_pos] = next_tmp_sum_pos;
			(*m_next)[next_tmp_sum_neg] = next_tmp_sum_neg;
		}
		map<int, int> *m_tmp = m;
		m->clear();
		m = m_next;
		m_next = m_tmp;
	}

	int min_sum = INT_MAX;
	for(map<int, int>::iterator it = m->begin(); it != m->end(); ++it) {
		if(abs(it->second) < min_sum)
			min_sum = abs(it->second);
	}

	return min_sum;
}

int main(void) {
	{ // 0
		int a[] = {1, -1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != 0)
			cout << "ERROR0" << endl;
	}

	{ // 1
		int a[] = {1, 5, 2, -2};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != 0)
			cout << "ERROR1" << endl;
	}

	{ // 2
		int a[] = {1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != 1)
			cout << "ERROR2" << endl;
	}

	{ // 3
		int a[] = {-1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != 1)
			cout << "ERROR3" << endl;
	}

	{ // 4
		int a[] = {-3, 3, -3, 0, -2};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != 1)
			cout << "ERROR4" << endl;
	}

	{ // 5
		int a[] = {-3, 5, -1, -4, -1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != 0)
			cout << "ERROR5" << endl;
	}

	return 0;
}
