// 3.3
// Test Score: 100%
#include <iostream>
#include <vector>
#include <climits>
#include <stdlib.h>
#include <time.h>
using namespace std;

int solution(vector<int> &A) {
	if(A.empty())
		return 0;

	double min_avg = INT_MAX;
	int min_idx = -1;

	/* Checking all intervals with size 2 */
	for(size_t i = 0; i < (A.size() - 1); i ++) {
		double avg = 1.0 * (A[i] + A[i + 1]) / 2;
		if(avg < min_avg) {
			min_avg = avg;
			min_idx = i;
		}
	}
	//cout << "min_avg for size 2: " << min_avg << " idx: " << min_idx << endl;

	/* Checking all intervals with size 3 */
	for(size_t i = 0; i < (A.size() - 2); i ++) {
		double avg = 1.0 * (A[i] + A[i + 1] + A[i + 2]) / 3;
		if(avg < min_avg) {
			min_avg = avg;
			min_idx = i;
		}
	}

	//cout << "min_avg for size 3: " << min_avg << " idx: " << min_idx << endl;

	return min_idx;
}

int solution_bf(vector<int> &A) {
	if(A.empty())
		return 0;
	double min_avg = INT_MAX;
	int min_idx = -1;
	for(int size = 2; size < int(A.size()); size ++) {
		for(size_t i = 0; i < (A.size() - size + 1); i ++) {
			int sum = 0;
			const int P = i;
			const int Q = P + size - 1;
			for(int j = P; j <= Q; j ++)
				sum += A[j];
			double avg = 1.0 * sum / (Q - P + 1);
			if(avg < min_avg) {
				min_avg = avg;
				min_idx = i;
			}
		}
	}
	return min_idx;
}

int main(void) {
	{ // 1
		int a[] = {4, 2, 2, 5, 1, 5, 8};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		const int i1 = solution(A);
		if(i1 != 1) cout << "ERROR1" << endl;
		const int i2 = solution_bf(A);
		if(i2 != 1) cout << "ERROR1_bf" << endl;
	}

	{ // 2
		int a[] = {-4, -2, -2, -5, -1, -5, -8};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		const int i1 = solution(A);
		if(i1 != 5) cout << "ERROR2" << endl;
		const int i2 = solution_bf(A);
		if(i2 != 5) cout << "ERROR2_bf" << endl;
	}

	{ // random
		srand(time(NULL));
		for(int test = 0; test < 10; test ++) {
			cout << "test " << test << "..." << endl;
			const int N = 15;
			vector<int> A(N);
			for(int i = 0; i < N; i ++) {
				A[i] = -10 + rand() % 20;
				cout << A[i] << " ";
			}
			cout << endl;
			const int i1 = solution(A);
			const int i2 = solution_bf(A);
			cout << "i1: " << i1 << " i2: " << i2 << endl;
			if(i1 != i2)
				cout << "ERROR_rand" << endl;
			else
				cout << "OK" << endl;
			cout << endl;
		}
	}

	return 0;
}
