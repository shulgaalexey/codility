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

int solution3(vector<int> &A) {
	int abs_sum = 0;
	for(size_t i = 0; i < A.size(); i ++)
		abs_sum += abs(A[i]);

	vector<int> buf(2 * abs_sum + 1, 0);
	const size_t zero_idx = abs_sum;
	buf[A[0] + zero_idx] = 1;
	buf[-A[0] + zero_idx] = 1;
	for(size_t i = 1; i < A.size(); i ++) {
		vector<int> buf_tmp = buf;
		buf.assign(2 * abs_sum + 1, 0);
		for(size_t j = 0; j < buf_tmp.size(); j ++) {
			if(buf_tmp[j] == 1) {
				int prev_tmp_sum = j - zero_idx;
				int new_tmp_sum_pos = prev_tmp_sum + A[i];
				int new_tmp_sum_neg = prev_tmp_sum - A[i];
				buf_tmp[new_tmp_sum_pos + zero_idx] = 1;
				buf_tmp[new_tmp_sum_neg + zero_idx] = 1;
			}
		}
		buf = buf_tmp;
	}

	if(buf[zero_idx] == 1)
		return 0;

	int min_sum = INT_MAX;
	for(int i = 0; i < abs_sum; i ++) {
		if(buf[zero_idx + i ] == 1) {
			min_sum = i;
			break;
		}
		if(buf[zero_idx - i] == 1) {
			min_sum = i;
			break;
		}
	}
	return min_sum;
}

int solution2(vector<int> &A) {
	if(A.empty())
		return 0;

	map<int, map<int, int> > hyper_map;
	map<int, int> zero_level;
	zero_level[A[0]] = A[0];
	hyper_map[0] = zero_level;
	for(size_t i = 1; i < A.size(); i ++) {
		map<int, int> &prev_level = hyper_map[i - 1];
		map<int, int> cur_level;
		for(map<int, int>::iterator it = prev_level.begin();
				it != prev_level.end(); ++it) {
			cur_level[it->first + A[i]] = it->first + A[i];
			cur_level[it->first - A[i]] = it->first - A[i];
		}
		hyper_map[i] = cur_level;
	}

	int min_sum = INT_MAX;
	map<int, int> &last_level = hyper_map[int(A.size()) - 1];
	for(map<int, int>::iterator it = last_level.begin();
			it != last_level.end(); ++it) {
		if(abs(it->second) < min_sum)
			min_sum = abs(it->second);
	}

	return min_sum;
}


int solution2a(vector<int> &A) {
	if(A.empty())
		return 0;

	map<int, int> m;
	m[A[0]] = 0;
	int level = 0;

	for(size_t i = 1; i < A.size(); i ++) {
		map<int, int> candidates;
		for(map<int, int>::iterator it = m.begin();
				it != m.end(); ++it) {
			if(it->second != level)
				continue;
			candidates[it->first] = level;
		}

		for(map<int, int>::iterator it = candidates.begin();
				it != candidates.end(); ++it) {

			if(it->second != level)
				continue;

			const int prev_tmp_sum = it->first;
			const int next_tmp_sum_pos = prev_tmp_sum + A[i];
			const int next_tmp_sum_neg = prev_tmp_sum - A[i];

			m[next_tmp_sum_pos] = level + 1;
			m[next_tmp_sum_neg] = level + 1;

			//m[-next_tmp_sum_pos] = level + 1;
			//m[-next_tmp_sum_neg] = level + 1;

			cout << next_tmp_sum_pos << "\t"
				<< next_tmp_sum_neg << endl;
		}
		level ++;
	}

	int min_sum = INT_MAX;
	const int last_level = int(A.size()) - 1;
	for(map<int, int>::iterator it = m.begin(); it != m.end(); ++it) {
		if((it->second == last_level) && (abs(it->first) < min_sum))
			min_sum = abs(it->first);
	}

	return min_sum;
}

int main(void) {
	{ // 0
		int a[] = {1, -1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		int r2 = solution2(A);
		int r2a = solution2a(A);
		cout << r << endl;
		cout << r2 << endl;
		if((r != 0) || (r != r2) || (r != r2a))

			cout << "ERROR0" << endl;
	}

	{ // 1
		int a[] = {1, 5, 2, -2};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		int r2 = solution2(A);
		int r2a = solution2a(A);
		cout << r << endl;
		cout << r2 << endl;
		if((r != 0) || (r != r2) || (r != r2a))
			cout << "ERROR1" << endl;
	}

	{ // 2
		int a[] = {1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		int r2 = solution2(A);
		int r2a = solution2a(A);
		cout << r << endl;
		cout << r2 << endl;
		if((r != 1) || (r != r2) || (r != r2a))
			cout << "ERROR2" << endl;
	}

	{ // 3
		int a[] = {-1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		int r2 = solution2(A);
		int r2a = solution2a(A);
		cout << r << endl;
		cout << r2 << endl;
		if((r != 1) || (r != r2) || (r != r2a))
			cout << "ERROR3" << endl;
	}

	{ // 4
		int a[] = {-3, 3, -3, 0, -2};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		int r2 = solution2(A);
		int r2a = solution2a(A);
		cout << r << endl;
		cout << r2 << endl;
		if((r != 1) || (r != r2) || (r != r2a))
			cout << "ERROR4" << endl;
	}

	{ // 5
		int a[] = {-3, 5, -1, -4, -1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		int r2 = solution2(A);
		int r2a = solution2a(A);
		cout << r << endl;
		cout << r2 << endl;
		if((r != 0) || (r != r2) || (r != r2a))
			cout << "ERROR5" << endl;
	}

	return 0;
}
