// 6.2
// EquiLeader
// Find the index S such that the leaders of the sequences A[0], A[1], ..., A[S]
// and A[S + 1], A[S + 2], ..., A[N - 1] are the same.
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
	if(A.size() == 1)
		return 0;

	const int N = int(A.size());
	int stack = 0;
	int size = 0;
	for(int i = 0; i < N; i ++) {
		if(size == 0) {
			stack = A[i];
			size = 1;
		} else {
			if(stack == A[i]) {
				size ++;
			} else {
				size --;
			}
		}
	}

	if(size == 0)
		return 0;

	int cnt = 0;
	for(int i = 0; i < N; i ++)
		if(A[i] == stack)
			cnt ++;

	if(cnt < int(N / 2))
		return 0;

	int el_cnt = 0;
	int cnt_left = 0;
	int cnt_right = cnt;
	for(int i = 0; i < (N - 1); i ++ ) {
		if(stack == A[i]) {
			cnt_left ++;
			cnt_right --;
		}
		int left_limit = (i + 1) / 2;
		int right_limit = (N - i - 1) / 2;
		if((cnt_left > left_limit) && (cnt_right > right_limit)) {
			//cout << "EL: " << i << endl;
			el_cnt ++;
		}

	}

	return el_cnt;
}


int solution_complex(vector<int> &A) {
	if(A.empty())
		return 0;
	if(A.size() == 1)
		return 0;

	const int N = int(A.size());
	vector<int> f(N);	// Forward leaders
	vector<int> b(N);	// Bacward leaders
	int stack = 0;
	int size = 0;
	for(int i = 0; i < N; i ++) {
		if(size == 0) {
			stack = A[i];
			size = 1;
			f[i] = stack;
		} else {
			if(stack == A[i]) {
				size ++;
				f[i] = stack;
			} else {
				size --;
				if(size == 0)
					f[i] = INT_MIN;
				else
					f[i] = stack;
			}
		}
	}

	size = 0;
	for(int i = (N - 1); i >= 0; i --) {
		if(size == 0) {
			stack = A[i];
			size = 1;
			b[i] = stack;
		} else {
			if(stack == A[i]) {
				size ++;
				b[i] = stack;
			} else {
				size --;
				if(size == 0)
					b[i] = INT_MIN;
				else
					b[i] = stack;
			}
		}
	}

	int cnt = 0;
	for(int i = 0; i < (N - 1); i ++) {
		if((f[i] != INT_MIN) && (f[i] == b[i + 1])) {
			//cout << "Equileader: " << f[i] << endl;
			int limit = 0;
			int ec = 0;
			bool flag = false;
			int el = 0;

			if(i < (N / 2)) {
				limit = (i + 1) / 2;
				ec = 0;
				flag = false;
				el = f[i];
				for(int j = 0; j <= i; j ++) {
					if(A[j] == el) {
						ec ++;
						if(ec > limit) {
							flag = true;
							break;
						}
					}
				}

				if(!flag)
					continue; // el is not an equileader

				limit = (N - i - 1) / 2;
				ec = 0;
				flag = false;
				el = b[i + 1];
				for(int j = (i + 1); j < N; j ++) {
					if(A[j] == el) {
						ec ++;
						if(ec > limit) {
							flag = true;
							break;
						}
					}
				}

				if(!flag)
					continue; // elb is not an equileader
			} else {
				limit = (N - i - 1) / 2;
				ec = 0;
				flag = false;
				el = b[i + 1];
				for(int j = (i + 1); j < N; j ++) {
					if(A[j] == el) {
						ec ++;
						if(ec > limit) {
							flag = true;
							break;
						}
					}
				}

				if(!flag)
					continue; // elb is not an equileader

				limit = (i + 1) / 2;
				ec = 0;
				flag = false;
				el = f[i];
				for(int j = 0; j <= i; j ++) {
					if(A[j] == el) {
						ec ++;
						if(ec > limit) {
							flag = true;
							break;
						}
					}
				}

				if(!flag)
					continue; // el is not an equileader
			}

			cnt ++;
		}
	}
	return cnt;
}

// This is the solution of 6.1
int el(vector<int> &A, int start, int finish) {
	int stack = 0;
	int size = 0;
	for(int i = start; i <= finish; i ++) {
		if(size == 0) {
			size = 1;
			stack = A[i];
		} else {
			if(stack == A[i])
				size ++;
			else
				size --;
		}
	}

	int cnt = 0;
	int limit = (finish - start + 1) / 2;
	for(int i = start; i <= finish; i ++) {
		if(A[i] == stack) {
			cnt ++;
			if(cnt > limit)
				return stack;
		}
	}
	return INT_MIN;
}
int solution_bf(vector<int> &A) {
	int N = int(A.size());
	int cnt = 0;
	for(int i = 0; i < (N - 1); i ++) {
		int elf = el(A, 0, i);
		if(elf == INT_MIN)
			continue;
		int elb = el(A, i + 1, N - 1);
		//cout << "elf: " << elf << " elb: " << elb << endl;
		if(elf == elb)
			cnt ++;
	}
	return cnt;
}

int main(void) {
	{ // 1
		int a[] = {4, 3, 4, 4, 4, 2};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r1 = solution(A);
		if(r1 != 2)
			cout << "ERROR1" << endl;
		int r2 = solution_bf(A);
		if(r2 != 2)
			cout << "ERROR1_bf" << endl;
	}

	{ // 2
		int a[] = {1, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r1 = solution(A);
		if(r1 != 1)
			cout << "ERROR2" << endl;
		int r2 = solution_bf(A);
		if(r2 != 1)
			cout << "ERROR2_bf" << endl;
	}

	{ // 3
		int a[] = {1, 2};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r1 = solution(A);
		if(r1 != 0)
			cout << "ERROR3" << endl;
		int r2 = solution_bf(A);
		if(r2 != 0)
			cout << "ERROR3_bf" << endl;
	}

	{ // 4
		int a[] = {1, 1, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r1 = solution(A);
		if(r1 != 2)
			cout << "ERROR4" << endl;
		int r2 = solution_bf(A);
		if(r2 != 2)
			cout << "ERROR4_bf" << endl;
	}

	{ // 5
		int a[] = {1, 1, 1, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r1 = solution(A);
		if(r1 != 3)
			cout << "ERROR5" << endl;
		int r2 = solution_bf(A);
		if(r2 != 3)
			cout << "ERROR5_bf" << endl;
	}

	{ // rnd
		for(int test = 0; test < 500; test ++ ) {
			const int N = 6;
			vector<int> A(N);
			for(int i = 0; i < N; i ++)
				A[i] = rand() % 5;
			int r1 = solution(A);
			int r2 = solution_bf(A);
			int r3 = solution_complex(A);
			if((r1 != r2) || (r1 != r3)) {
				cout << "ERROR_rnd at test " << test << endl;
				for(int i = 0; i < N; i ++)
					cout << A[i] << " ";
				cout << endl;
				cout << "r1: " << r1 << " r2: " << r2 << endl;
			}


			/*if(r1 != 0) {
			  cout << endl << endl << "test " << test << endl;

			  for(int i = 0; i < N; i ++)
			  cout << A[i] << " ";
			  cout << endl;
			  cout << "r1: " << r1 << " r2: " << r2 << endl;
			  }*/

		}
	}

	return 0;
}
