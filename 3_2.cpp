// 3.2
// PassingCars
// Count the number of passing cars on the road.
// Test Score: 100%
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

int solution(vector<int> &A) {
	if(A.empty())
		return 0;
	int cnt = 0;
	for(int i = int(A.size() - 1); i >= 0; i --) {
		if(A[i] == 1)
			A[i] = ++cnt;
		else
			A[i] = (-1) * cnt;
	}

	int pairs = 0;
	for(size_t i = 0; i < A.size(); i ++) {
		if(A[i] < 0) {
			pairs += (-1) * A[i];
			if(pairs > 1000000000)
				return (-1);
		}
	}
	return pairs;
}

int solution_bf(vector<int> &A) {
	int pairs = 0;
	for(size_t i = 0; i < A.size(); i ++) {
		if(A[i] == 0) {
			int ones = 0;
			for(size_t j = (i + 1); j < A.size(); j++)
				ones += A[j];
			pairs += ones;
			if(pairs > 1000000000)
				return (-1);
		}
	}
	return pairs;
}

int main(void) {
	{ // 1
		int a[] = {0, 1, 0, 1, 1};
		vector<int> A1(a, a + sizeof(a) / sizeof(a[0]));
		int p1 = solution(A1);
		if(p1 != 5) cout << "ERROR1" << endl;
		vector<int> A2(a, a + sizeof(a) / sizeof(a[0]));
		int p2 = solution_bf(A2);
		if(p2 != 5) cout << "ERROR1_bf" << endl;
	}

	{ // 2
		int a[] = {0, 1, 0, 1, 0};
		vector<int> A1(a, a + sizeof(a) / sizeof(a[0]));
		int p1 = solution(A1);
		if(p1 != 3) cout << "ERROR2" << endl;
		vector<int> A2(a, a + sizeof(a) / sizeof(a[0]));
		int p2 = solution_bf(A2);
		if(p2 != 3) cout << "ERROR2_bf" << endl;
	}

	{ // 3
		int a[] = {0, 1};
		vector<int> A1(a, a + sizeof(a) / sizeof(a[0]));
		int p1 = solution(A1);
		if(p1 != 1) cout << "ERROR3" << endl;
		vector<int> A2(a, a + sizeof(a) / sizeof(a[0]));
		int p2 = solution_bf(A2);
		if(p2 != 1) cout << "ERROR3_bf" << endl;
	}

	{ // 4
		int a[] = {1, 0};
		vector<int> A1(a, a + sizeof(a) / sizeof(a[0]));
		int p1 = solution(A1);
		if(p1 != 0) cout << "ERROR4" << endl;
		vector<int> A2(a, a + sizeof(a) / sizeof(a[0]));
		int p2 = solution_bf(A2);
		if(p2 != 0) cout << "ERROR4_bf" << endl;
	}

	{ // 5
		int a[] = {1, 1, 1, 1};
		vector<int> A1(a, a + sizeof(a) / sizeof(a[0]));
		int p1 = solution(A1);
		if(p1 != 0) cout << "ERROR5" << endl;
		vector<int> A2(a, a + sizeof(a) / sizeof(a[0]));
		int p2 = solution_bf(A2);
		if(p2 != 0) cout << "ERROR5_bf" << endl;
	}

	{ // 6
		int a[] = {1, 1, 1, 1, 0};
		vector<int> A1(a, a + sizeof(a) / sizeof(a[0]));
		int p1 = solution(A1);
		if(p1 != 0) cout << "ERROR6" << endl;
		vector<int> A2(a, a + sizeof(a) / sizeof(a[0]));
		int p2 = solution_bf(A2);
		if(p2 != 0) cout << "ERROR6_bf" << endl;
	}

	{ // 7
		int a[] = {0, 0, 0, 0, 0};
		vector<int> A1(a, a + sizeof(a) / sizeof(a[0]));
		int p1 = solution(A1);
		if(p1 != 0) cout << "ERROR7" << endl;
		vector<int> A2(a, a + sizeof(a) / sizeof(a[0]));
		int p2 = solution_bf(A2);
		if(p2 != 0) cout << "ERROR7_bf" << endl;
	}

	{ // 8
		int a[] = {0, 1, 1, 1, 1};
		vector<int> A1(a, a + sizeof(a) / sizeof(a[0]));
		int p1 = solution(A1);
		if(p1 != 4) cout << "ERROR8" << endl;
		vector<int> A2(a, a + sizeof(a) / sizeof(a[0]));
		int p2 = solution_bf(A2);
		if(p2 != 4) cout << "ERROR8_bf" << endl;
	}

	{ // load
		cout << "Load test..." << endl;
		srand(time(NULL));
		const int N = 100000;
		vector<int> A1(N);
		vector<int> A2(N);

		for(int i = 0; i < N; i ++) {
			int car = rand() > (RAND_MAX / 2);
			A1[i] = car;
			A2[i] = car;
		}
		int p1 = solution(A1);
		int p2 = solution_bf(A2);
		if(p1 == p2) cout << "OK" << endl;
		cout << "p1: " << p1 << " p2: " << p2 << endl;
		if(p1 != p2) cout << "ERROR_load" << endl;
	}

	{ // random
		srand(time(NULL));
		for(int test = 0; test < 10; test ++) {
			cout << "test " << test << "..." << endl;
			const int N = 10000;
			vector<int> A1(N);
			vector<int> A2(N);

			for(int i = 0; i < N; i ++) {
				int car = rand() > (RAND_MAX / 2);
				A1[i] = car;
				A2[i] = car;
			}
			int p1 = solution(A1);
			int p2 = solution_bf(A2);
			if(p1 == p2) cout << "OK" << endl;
			cout << "p1: " << p1 << " p2: " << p2 << endl;
			if(p1 != p2) cout << "ERROR_random" << endl;
		}
	}

	return 0;
}
