// 9.2
// CountNonDivisible
// Calculate the number of elements of an array that are not divisors of each element.
// Test Score: 100%
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

vector<int> solution(vector<int> &A) {
	if(A.empty())
		return vector<int>();

	const int N = int(A.size());
	vector<int> ret(N, 0);
	if(N == 1)
		return ret;

	////////////////////////////////////////////////////////////
	// Pre-processing: storing the histogram of input elements
	////////////////////////////////////////////////////////////
	const int histo_size = 2 * N + 1;
	vector<int> H(histo_size, 0);
	for(int i = 0; i < N; i ++)
		H[A[i]] ++;

	vector<int> B = A; // May be optimized: we can create B with no duplications
	std::sort(B.begin(), B.end());


	map<int, int> _m; // For DP

	// Divisors density storage
	int init_cnt = 0;
	if(B[0] == 1) { // Special case for 1, because it is a divider for every other item
		init_cnt = H[1];
		_m[1] = H[1];
	}
	vector<int> D(histo_size, init_cnt);

	for(int i = 0; i < N; i ++) {

		// Processing item B[i]
		const int b = B[i];
		if(_m.count(b) > 0) {
			continue;
		}

		int b_cnt = H[b];
		int j = b;
		while(j < histo_size) {
			D[j] += b_cnt; // Updae dividers density
			j += b;
		}
		_m[b] = b_cnt;
	}

	////////////////////////////////////////////////////////////
	// Querying
	////////////////////////////////////////////////////////////
	for(int i = 0; i < N; i ++) {
		const int a = A[i];
		const int divisors = D[a];
		ret[i] = N - divisors;
	}


	return ret;

}

int main(void) {
	{ // 1
		cout << endl << "Test 1: " << endl;
		int a[] = {3, 1, 2, 3, 6};
		int exp[] = {2, 4, 3, 2, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> R = solution(A);
		for(size_t i = 0; i < R.size(); i ++) cout << R[i] << " "; cout << endl;
		for(size_t i = 0; i < R.size(); i ++) {
			if(R[i] != exp[i])
				cout << "ERROR1" << endl;
		}
	}

	{ // 2
		cout << endl << "Test 2: " << endl;
		int a[] = {2, 3};
		int exp[] = {1, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> R = solution(A);
		for(size_t i = 0; i < R.size(); i ++) cout << R[i] << " "; cout << endl;
		for(size_t i = 0; i < R.size(); i ++) {
			if(R[i] != exp[i])
				cout << "ERROR2" << endl;
		}
	}

	{ // 3
		cout << endl << "Test 3: " << endl;
		int a[] = {2, 2};
		int exp[] = {0, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> R = solution(A);
		for(size_t i = 0; i < R.size(); i ++) cout << R[i] << " "; cout << endl;
		for(size_t i = 0; i < R.size(); i ++) {
			if(R[i] != exp[i])
				cout << "ERROR3" << endl;
		}
	}

	{ // 4
		cout << endl << "Test 4: " << endl;
		int a[] = {2, 4};
		int exp[] = {1, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> R = solution(A);
		for(size_t i = 0; i < R.size(); i ++) cout << R[i] << " "; cout << endl;
		for(size_t i = 0; i < R.size(); i ++) {
			if(R[i] != exp[i])
				cout << "ERROR4" << endl;
		}
	}


	return 0;
}
