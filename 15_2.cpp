// 15.2
// MinAbsSum
// Given array of integers, find the lowest absolute sum of elements.
// Test Score: 100% (Applied official Codility solution)
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
using namespace std;

int solution(vector<int> &A) {
	const int N = int(A.size());

	int M = 0;
	int S = 0;
	for(int i = 0; i < N; i ++) {
		/* Make all values positive (absolute) */
		if(A[i] < 0)
			A[i] *= -1;

		/* Find the maximum value in the array */
		if(A[i] > M)
			M = A[i];

		/* Find the sum of the array */
		S += A[i];
	}

	/* Find the values distribution */
	vector<int> count(M + 1, 0);
	for(int i = 0; i < N; i ++) {
		count[A[i]] += 1;
	}

	/* Array of achievable sums */
	vector<int> dp(S + 1, -1);
	dp[0] = 0;

	/* Golden solution */
	for(int a = 1; a <= M; a ++) {
		if(count[a] <= 0)
			continue;
		for(int j = 0; j <= S; j ++) {
			if(dp[j] >= 0) {
				dp[j] = count[a];
			} else if((j >= a) && (dp[j - a] > 0)) {
				dp[j] = dp[j - a] - 1;
			}
		}
	}

	int result = S;
	for(int i = 0; i < (S / 2 + 1); i ++)
		if(dp[i] >= 0)
			result = min(result, S - 2 * i);
	return result;
}

int solution3(vector<int> &A) {
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
