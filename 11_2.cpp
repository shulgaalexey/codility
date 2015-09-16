// 11.2
#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <climits>
using namespace std;

int get_fib_sum(int N, const map<int, int> &_fibs, const vector<int> &fibs) {
	// Apply DP
	if(_fibs.count(N) > 0)
		return 1;
	for(int i = int(fibs.size() - 1); i >= 0; i --) {
		if(N < fibs[i])
			continue;
		int cnt = get_fib_sum(N - fibs[i], _fibs, fibs);
		if(cnt > 0)
			return (cnt + 1);
	}
	return 0;
}

int get_far_leaf_candidate(int farest_idx, int starting_idx,
		int cur_pos,
		const vector<int> &leafs,
		const map<int, int> &_fibs,
		const vector<int> &fibs) {

	const int N = leafs[leafs.size() -1];
	for(int i = farest_idx; i >= starting_idx; i --) {
		int left = leafs[i] - cur_pos;
		if(_fibs.count(left) == 0)
			continue; // this leaf can not be achieved with Fibonacci jump

		int right = N - left + 1;
		if((right == 0) || (_fibs.count(right) > 0))
			return i; // This leaf is a good candidate for the first jump

		if(get_fib_sum(right, _fibs, fibs) == 0)
			continue; // the right part can not be present with Fibonacci jumps
	}
	return -1;
}

int get_jump_way(int farest_idx, int starting_idx,
		int cur_pos,
		const vector<int> &leafs,
		const map<int, int> &_fibs,
		const vector<int> &fibs) {

	const int N = leafs[leafs.size() -1];
	int cnt = INT_MAX;
	for(int i = farest_idx; i >= starting_idx; i --) {
		int cur_cnt = 0;

		// Lets start analysis with the farest candidate, found in [starting_idx ... i]
		int far_idx = get_far_leaf_candidate(i, starting_idx, cur_pos, leafs, _fibs, fibs);
		if(far_idx == -1)
			continue; // No candidate for the first jump

		cur_cnt ++; // Can make at least this first jump

		if(leafs[far_idx] == N) { // This jump moves us to the finish
			if(cur_cnt < cnt)
				cnt = cur_cnt;
			continue; // we have a cur result; goto next test
		}

		// Check if the right part can be present with a single Fib jump
		int right = N - leafs[far_idx] + 1;
		if(_fibs.count(right) > 0) {
			cur_cnt ++; // We can get to the finish
			if(cur_cnt < cnt)
				cnt = cur_cnt;
			continue; // we have a cur result; goto next test
		}

		// Find min number of jumps in the right part
		cur_cnt += get_jump_way(farest_idx, far_idx + 1, leafs[far_idx], leafs, _fibs, fibs);
		if(cur_cnt < cnt)
			cnt = cur_cnt;
	}

	if(cnt == INT_MAX)
		return (-1);
	return cnt;

}

int solution(vector<int> &A) {
	const bool logs = false;

	const int N = int(A.size());
	// 1. Prepare array of leafs
	vector<int> leafs;
	for(int i = 0; i < N; i ++)
		if(A[i])
			leafs.push_back(i);
	leafs.push_back(N); // opposite bank of the river

	if(logs) {
		for(size_t i = 0; i < leafs.size(); i ++)
			cout << leafs[i] << " ";
		cout << endl;
	}

	// 2. Prepare Fibonacci numbers, likely applicable for jumping
	map<int, int> _fibs;
	_fibs[1] = 1;
	vector<int> fibs(1, 1);
	int fib_1 = 0;
	int fib_2 = 1;
	while(true) {
		const int fib = fib_1 + fib_2;
		if(fib > (N + 1))
			break;
		if(logs)
			cout << "fib: " << fib << endl;
		_fibs[fib] = fib;
		fibs.push_back(fib);
		fib_1 = fib_2;
		fib_2 = fib;
	}


	// 3. Find the left and right part, of the river,
	// so both are summs of Fibonacci
	return get_jump_way(leafs.size() -1, 0, -1, leafs, _fibs, fibs);


#if 0
	// 3. Greedy approach to find a min number of jumps
	int cur_pos = -1;
	int cnt = 0;
	while(true) {
		bool found = false;
		for(int i = int(leafs.size() - 1); i >= 0; i --) {
			if(_fibs.count(leafs[i] - cur_pos) > 0) {
				// This jump can be done with Fibonacci number
				cnt ++;
				cur_pos = leafs[i];
				found = true;
				break;
			}
		}
		if(!found)
			return -1;
		if(cur_pos == N)
			return cnt;
	}
	return -1;
#endif
}

int calc_jumps(int start_pos, int N,
		const map<int, int> &_fibs,
		const vector<int> &leafs,
		int start_idx) {

	if(start_pos == N)
		return 0; // Reached the end of the recursion

	int min_cnt = INT_MAX;
	for(size_t i = start_idx; i < leafs.size(); i ++) {
		if(_fibs.count(leafs[i] - start_pos) <= 0)
			continue; // can not jump on this leaf

		// Try to jump on this leaf and see what would happen
		int cur_cnt = calc_jumps(leafs[i], N, _fibs, leafs, i + 1);
		if(cur_cnt < min_cnt)
			min_cnt = cur_cnt;
	}
	if(min_cnt == INT_MAX)
		return INT_MAX;
	return (min_cnt + 1);
}

int solution_bf(vector<int> &A) {
	const bool logs = false;

	const int N = int(A.size());
	// 1. Prepare array of leafs
	vector<int> leafs;
	for(int i = 0; i < N; i ++)
		if(A[i])
			leafs.push_back(i);
	leafs.push_back(N); // opposite bank of the river

	if(logs) {
		for(size_t i = 0; i < leafs.size(); i ++)
			cout << leafs[i] << " ";
		cout << endl;
	}

	// 2. Prepare Fibonacci numbers, likely applicable for jumping
	map<int, int> _fibs;
	_fibs[1] = 1;
	int fib_1 = 0;
	int fib_2 = 1;
	while(true) {
		const int fib = fib_1 + fib_2;
		if(fib > (N + 1))
			break;
		if(logs)
			cout << "fib: " << fib << endl;
		_fibs[fib] = fib;
		fib_1 = fib_2;
		fib_2 = fib;
	}

	// 3. Brute-force recursive algorithm
	int cnt = calc_jumps(-1, N, _fibs, leafs, 0);
	if(cnt == INT_MAX)
		cnt = -1;
	return cnt;
}

int main(void) {
	{ // 1
		int a[] = {0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != 3)
			cout << "ERROR1" << endl;
	}

	{ // 2
		cout << "Test Case 2" << endl;
		int a[] = {1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != (-1))
			cout << "ERROR2" << endl;
		cout << "Finished" << endl;
	}

	{ // 3
		cout << "Test Case 3" << endl;
		int a[] = {1, 1, 1, 0, 1, 0, 0, 0, 0, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != (-1))
			cout << "ERROR3" << endl;
		cout << "Finished" << endl;
	}

	{ // 4
		cout << "Test Case 4" << endl;
		int a[] = {0, 0, 0, 0, 1, 0, 1, 0, 0, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != (-1))
			cout << "ERROR4" << endl;
		cout << "Finished" << endl;
	}

	{ // 5
		cout << "Test Case 4" << endl;
		int a[] = {0, 0, 0, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != 1)
			cout << "ERROR5" << endl;
		cout << "Finished" << endl;
	}

	{ // 6
		cout << "Test Case 6" << endl;
		int a[] = {0, 0, 0, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != 1)
			cout << "ERROR5" << endl;
		cout << "Finished" << endl;
	}


	if(1) { // rnd
		srand(time(NULL));

		for(int test = 0; test < 10; test ++) {
			cout << "test: " << test << "..." << endl;
			const int N = 10;
			vector<int> A(10, 0);
			for(int i = 0; i < N; i ++)
				if(rand() > (RAND_MAX / 2))
					A[i] = 1;

			//cout << "started..." << endl;
			//for(size_t i = 0; i < A.size(); i ++)
			//	cout << A[i] << ", ";
			//cout << endl;

			int r1 = solution(A);
			int r2 = solution_bf(A);
			if(r1 != r2) {
				cout << "ERROR_rnd" << endl;
				for(size_t i = 0; i < A.size(); i ++)
					cout << A[i] << ", ";
				cout << endl;
				cout << "r1 = " << r1 << endl;
				cout << "r2 = " << r2 << endl;
			}
			//cout << "...finished" << endl;
		}
	}
	return 0;
}
