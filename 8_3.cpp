// 8.3
// Peaks
// Divide an array into the maximum number of same-sized blocks,
// each of which should contain an index P such that A[P - 1] < A[P] > A[P + 1].
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;

int solution(vector<int> &A) {
	if(A.empty())
		return 0;
	int N = int(A.size());
	//cout << "N = " << N << endl;

	//cout << "Input array" << endl;
	//for(size_t i = 0; i < A.size(); i ++) cout << A[i] << " "; cout << endl;

	// Find peaks and mark it in the dedicated array
	vector<int> P(N);
	int p_cnt = 0;
	P[0] = 0;
	for(int i = 1; i < (N - 1); i ++) {
		if((A[i] > A[i - 1]) && (A[i] > A[i + 1]))
			p_cnt ++;
		P[i] = p_cnt;
	}
	P[N - 1] = p_cnt;

	//cout << "Peaks count" << endl;
	//for(size_t i = 0; i < P.size(); i ++) cout << P[i] << " "; cout << endl;
	//for(size_t i = 0; i < P.size(); i ++) cout << i << " "; cout << endl;

	if(p_cnt == 0)
		return 0; // No peaks detected

	// Find divider variants
	vector<int> D;
	long long d = 1;
	while((d * d) <= N) {
		if((N % d) == 0) {
			D.push_back(d);
			if((N / d) != d)
				D.push_back(N / d);
		}
		d ++;
	}
	sort(D.begin(), D.end());

	//cout << "Dividers: " << endl;
	//for(size_t i = 0; i < D.size(); i ++) cout << D[i] << " "; cout << endl;

	// Search for the max K
	int candidate_d = 1;	// at-least one block should be there;
	for(size_t i = 1; i < D.size(); i ++) {
		int cur_d = D[i];
		int cur_step = N / cur_d;
		//cout << "cur_d = " << cur_d << ", cur_step = " << cur_step << endl;
		//cout << endl;
		//cout << "idx to check: " << 0 << endl;

		int prev_p = P[0];
		bool no_new_peaks = false;
		for(int j = 1; j <= cur_d; j ++) {
			int cur_p = P[j * cur_step - 1];
			//cout << "idx to check: " << j * cur_step - 1 << endl;
			//cout << "prev_p = " << prev_p << ", cur_p = " << cur_p << endl;
			if(prev_p == cur_p) {
				// found a block with no peaks
				no_new_peaks = true;
				break;
			}
			prev_p = cur_p;
		}
		if(no_new_peaks)
			break;
		candidate_d = cur_d;
	}
	return candidate_d;
}


vector<int> make_interval(const vector<int> &A, int start, int finish) {
	vector<int> ret;

	if(start == 0)
		ret.push_back(A[0]);
	else
		ret.push_back(A[start - 1]);

	for(int i = start; i <= finish; i ++)
		ret.push_back(A[i]);

	if(finish == int(A.size() - 1))
		ret.push_back(A[A.size() - 1]);
	else
		ret.push_back(A[finish + 1]);

	return ret;

}

bool has_peaks(const vector<int> &A) {
	const int N = int(A.size());
	for(int i = 1; i < (N - 1); i ++)
		if((A[i] > A[i - 1]) && (A[i] > A[i + 1]))
			return true;
	return false;
}

// Even this brute-force approach got 100% on performance tests (-:
int solution_bf(vector<int> &A) {

	//cout << "input:" << endl;
	//for(size_t k = 0; k < A.size(); k ++) cout << A[k] << " ";
	//cout << endl << endl;

	// Check if there are any peaks
	if(!has_peaks(A))
		return 0;


	// Find divider variants
	const int N = int(A.size());
	vector<int> D;
	long long d = 1;
	while((d * d) <= N) {
		if((N % d) == 0) {
			D.push_back(d);
			if((N / d) != d)
				D.push_back(N / d);
		}
		d ++;
	}
	sort(D.begin(), D.end());

	// Search for the max K
	int candidate = 1;	// at-least one block should be there;
	for(size_t i = 1; i < D.size(); i ++) {
		int cur_d = D[i];
		//cout <<  endl << "cur_d = " << cur_d << endl;
		int cur_step = N / cur_d;
		for(int j = 0; j < cur_d; j ++) {
			int finish = (j + 1) * cur_step - 1;
			int start = finish - cur_step + 1;
			vector<int> interval = make_interval(A, start, finish);

			//cout << "search interval:" << endl;
			//for(size_t k = 0; k < interval.size(); k ++) cout << interval[k] << " ";
			//cout << "  --  ";
			//if(has_peaks(interval))
			//	cout << "PEAKS found" << endl;
			//else
			//	cout << "no peaks" << endl;

			if(!has_peaks(interval)) {
				return candidate;
			}
		}
		candidate = cur_d;
	}
	return candidate;
}

int main(void) {
	{ // 1
		int a[] = {1, 2, 3, 4, 3, 4, 1, 2, 3, 4, 6, 2};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r1 = solution(A);
		int r2 = solution_bf(A);
		//cout << r1 << endl;
		if(r1 != 3)
			cout << "ERROR1" << endl;
		if(r2 != 3)
			cout << "ERROR1_bf" << endl;
	}

	{ // 2
		int a[] = {1, 5, 1, 1, 4, 1, 1, 3, 1, 1, 2, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r1 = solution(A);
		int r2 = solution_bf(A);
		//cout << r1 << endl;
		if(r1 != 4)
			cout << "ERROR2" << endl;
		if(r2 != 4)
			cout << "ERROR2_bf" << endl;
	}


	{ // 2.1
		int a[] = {1, 1, 5, 1, 4, 1, 3, 1, 1, 2, 1, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r1 = solution(A);
		int r2 = solution_bf(A);
		//cout << r1 << endl;
		if(r1 != 4)
			cout << "ERROR2.1" << endl;
		if(r2 != 4)
			cout << "ERROR2.1_bf" << endl;
	}

	{ // 3.1
		srand(time(NULL));
		for(int test = 0; test < 10000; test ++) {
			//cout << "test " << test << "..." << endl;
			int N = 12;
			//cout << "N: " << N << endl;
			vector<int> A(N);
			for(int i = 0; i < N; i ++)
				A[i] = 1 + rand() % 10;

			int r1 = solution(A);
			int r2 = solution_bf(A);

			if(r1 != r2) {
				cout << "ERROR_rnd" << endl;
				for(size_t i = 0; i < A.size(); i ++) cout << A[i] << " ";
				cout << endl;
				cout << "r1: " << r1 << " r2: " << r2 << endl;
			}
		}
	}

	{ // 3.2
		srand(time(NULL));
		for(int iteration = 0; iteration < 10; iteration ++) {
			cout << "iteration: " << iteration << "..." << endl;
			int N = 1;
			for(int test = 0; test < 8; test ++) {
				//cout << "test " << test << "..." << endl;
				//cout << "N: " << N << endl;
				N *= (test + 1);
				vector<int> A(N);
				for(int i = 0; i < N; i ++)
					A[i] = 1 + rand() % 10;

				int r1 = solution(A);
				int r2 = solution_bf(A);

				if(r1 != r2) {
					cout << "ERROR_rnd" << endl;
					for(size_t i = 0; i < A.size(); i ++) cout << A[i] << " ";
					cout << endl;
					cout << "r1: " << r1 << " r2: " << r2 << endl;
				}
			}
		}
	}
	return 0;
}
