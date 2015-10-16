// 13.2
// CountDistinctSlices
// Count the number of distinct slices (containing only unique numbers).
// Test Score: 100%
#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <time.h>
using namespace std;

void print_caterpillar(const map<int, int> &m) {
	for(map<int, int>::const_iterator it = m.begin(); it != m.end(); ++it)
		cout << it->first << " ";
	cout << endl;
}

int solution(int M, vector<int> &A) {
	int cnt = 0;
	map<int, int> m;
	size_t head = 0;
	size_t tail = 0;
	while(head < A.size()) {
		const int a = A[head];
		if(m.count(a) == 0) {
			// Caterpillar moves forward
			head ++;
			m[a] = a;
			cnt ++;
			//cout << "cnt = " << cnt << "\t| ";
			//print_caterpillar(m);
		} else {
			// Caterpillar shrinks
			if(!m.empty()) {
				m.erase(A[tail]);
				tail ++;
				cnt += head - tail;
				//cout << "cnt = " << cnt << "\t| ";
				//print_caterpillar(m);
			}
		}

		if(cnt > 1000000000)
			return 1000000000;
	}

	// Caterpillar shrinks until disappears
	while(!m.empty()) {
		m.erase(A[tail]);
		tail ++;
		cnt += head - tail;
		//cout << "cnt = " << cnt << "\t| ";
		//print_caterpillar(m);

		if(cnt > 1000000000)
			return 1000000000;
	}
	return cnt;
}

int solution_bf(int M, vector<int> &A) {
	int cnt = 0;
	for(size_t i = 0; i < A.size(); i ++) {
		map<int, int> m;
		for(size_t j = i; j < A.size(); j ++) {
			if(m.count(A[j]) > 0)
				break;
			cnt ++;
			m[A[j]] = A[j];

			//print_caterpilar(m);
		}
	}
	return cnt;
}

int main(void) {
	{ // 1
		int a[] = {3, 4, 5, 5, 2};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(6, A);
		int r2 = solution_bf(6, A);
		//cout << r << endl;
		//cout << r2 << endl;
		if((r != 9) || (r2 != 9))
			cout << "ERROR1" << endl;
	}
	{ // 2
		int a[] = {6, 7, 4, 2, 1, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(7, A);
		int r2 = solution_bf(7, A);
		//cout << r << endl;
		//cout << r2 << endl;
		if((r != 16) || (r2 != 16))
			cout << "ERROR2" << endl;
	}
	{ // rnd
		srand(time(NULL));
		for(int test = 0; test < 50; test ++) {
			cout << "Test: " << test << "..." << endl;
			const int N = 50;
			const int M = 10;
			vector<int> A(N);
			for(int i = 0; i < N; i ++)
				A[i] = 1 + rand() % M;
			int r1 = solution(M, A);
			int r2 = solution_bf(M, A);
			if(r1 != r2) {
				cout << "ERRORRND" << endl;
				for(size_t i = 0; i < A.size(); i ++)
					cout << A[i] << " ";
				cout << endl;
			}
		}
	}

	return 0;
}
