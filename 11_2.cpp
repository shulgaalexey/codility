// 11.2
// FibFrog
// Count the minimum number of jumps required for a frog to get to the
// other side of a river.
// Test Score: 100%
// (taken from inet)
#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <climits>
using namespace std;


int solution(vector<int> &A) {
	const bool logs = false;

	const int N = int(A.size());
	A.push_back(1);


	// 2. Prepare Fibonacci numbers, likely applicable for jumping
	vector<int> fibs;
	fibs.push_back(1);
	fibs.push_back(2);
	int last_idx = 2;
	while(true) {
		const int fib = fibs[last_idx - 1] + fibs[last_idx - 2];
		if(fib > (N + 1))
			break;
		fibs.push_back(fib);
		last_idx ++;
	}

	if(logs) {
		cout << "Useful Fibonacci:" << endl;
		for(size_t i = 0; i < fibs.size(); i ++)
			cout << fibs[i] << endl;
		cout << "---------" << endl;
	}

	// this array will hold the optimal jump count that reaches this index
	vector<int> reachable(A.size(), -1);

	// get the leafs that can be reached from the starting shore
	for(size_t i = 0; i < fibs.size(); i ++) {
		const int jump = fibs[i];
		if(A[jump - 1] == 1)
			reachable[jump -1] = 1;
	}

	if(logs) {
		cout << "Reachable leafs from the first bank:" << endl;
		for(size_t i = 0; i < reachable.size(); i ++)
			if(reachable[i] == 1)
				cout << i << " ";
		cout << endl;
		cout << "---------" << endl;
	}

	// iterate all the positions until you reach the other shore
	for(int idx = 0; idx < int(A.size()); idx ++) {
		// ignore non-leafs and already found paths
		if((A[idx] == 0) || (reachable[idx] > 0))
			continue;

		if(logs)
			cout << "Analyzing leaf pos: " << idx << endl;

		// get the optimal jump count to reach this leaf
		int min_idx = -1;
		int min_value = 100000;

		for(size_t i = 0; i < fibs.size(); i ++) {
			const int jump = fibs[i];
			int previous_idx = idx - jump;

			if(logs) {
				cout << "jump = " << jump << "\t";
				cout << "previous_idx = " << previous_idx <<
					endl;
			}

			if(previous_idx < 0)
				break;


			if(logs) {
				if(reachable[previous_idx] > 0)
					cout << "\t\treachable!" << endl;
				else
					cout << "\t\tUN reachable!" << endl <<
						endl;;
			}

			if((reachable[previous_idx] > 0)
					&& (min_value > reachable[previous_idx])) {
				min_value = reachable[previous_idx];
				min_idx = previous_idx;
			}

			if(min_idx != -1)
				reachable[idx] = min_value + 1;
		}
	}

	return reachable[A.size() - 1];
}

// ----------------------------------------------------------------------------

int calc_jumps_bf(int start_pos, int N,
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
		int cur_cnt = calc_jumps_bf(leafs[i], N, _fibs, leafs, i + 1);
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
	int cnt = calc_jumps_bf(-1, N, _fibs, leafs, 0);
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
		//cout << "Test Case 2" << endl;
		int a[] = {1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != (-1))
			cout << "ERROR2" << endl;
		//cout << "Finished" << endl;
	}

	{ // 3
		//cout << "Test Case 3" << endl;
		int a[] = {1, 1, 1, 0, 1, 0, 0, 0, 0, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != (-1))
			cout << "ERROR3" << endl;
		//cout << "Finished" << endl;
	}

	{ // 4
		//cout << "Test Case 4" << endl;
		int a[] = {0, 0, 0, 0, 1, 0, 1, 0, 0, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != (-1))
			cout << "ERROR4" << endl;
		//cout << "Finished" << endl;
	}

	{ // 5
		//cout << "Test Case 4" << endl;
		int a[] = {0, 0, 0, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != 1)
			cout << "ERROR5" << endl;
		//cout << "Finished" << endl;
	}

	{ // 6
		//cout << "Test Case 6" << endl;
		int a[] = {0, 0, 0, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != 1)
			cout << "ERROR5" << endl;
		//cout << "Finished" << endl;
	}


	if(1) { // rnd
		srand(time(NULL));

		for(int test = 0; test < 10; test ++) {
			cout << endl << "test: " << test << "..." << endl;
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
			} else
				cout << "OK" << endl;
			//cout << "...finished" << endl;
		}
	}
	return 0;
}
