// 2.4
// Test Score: 100%
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

vector<int> solution(int N, vector<int> &A) {
	vector<int> ctrs(N);
	for(int i = 0; i < N; i ++)
		ctrs[i] = 0;
	if(A.empty())
		return ctrs;

	int cur_max = 0;
	int applyable_max = 0;
	const int N1 = N + 1;
	for(size_t i = 0; i < A. size(); i++) {
		if(A[i] != N1) {
			const int idx = A[i] - 1;
			ctrs[idx] = max(ctrs[idx], applyable_max);
			ctrs[idx] ++;
			if(ctrs[idx] > cur_max)
				cur_max = ctrs[idx];
		} else
			applyable_max = cur_max;
	}

	for(size_t i = 0; i < ctrs.size(); i ++)
		ctrs[i] = max(ctrs[i], applyable_max);

	return ctrs;
}

int main(void) {
	{ // 1
		int a[] = {3, 4, 4, 6, 1, 4, 4};
		vector<int> A(a, a + 7);
		vector<int> ctrs = solution(5, A);
		int exp[] = {3, 2, 2, 4, 2};
		vector<int> Exp(exp, exp + 5);
		if(ctrs.size() == Exp.size()) {
			for(size_t i = 0; i < ctrs.size(); i ++)
				if(ctrs[i] != Exp[i])
					cout << "ERROR1" << endl;
		} else
			cout << "ERROR1_1" << endl;
	}

	{ // 2
		int a[] = {4, 4, 4, 4, 4};
		vector<int> A(a, a + 5);
		vector<int> ctrs = solution(3, A);
		int exp[] = {0, 0, 0};
		vector<int> Exp(exp, exp + 3);
		if(ctrs.size() == Exp.size()) {
			for(size_t i = 0; i < ctrs.size(); i ++)
				if(ctrs[i] != Exp[i])
					cout << "ERROR2" << endl;
		} else
			cout << "ERROR2_1" << endl;
	}

	{ // 3
		int a[] = {1, 4, 2, 4, 3, 4};
		vector<int> A(a, a + 6);
		vector<int> ctrs = solution(3, A);
		int exp[] = {3, 3, 3};
		vector<int> Exp(exp, exp + 3);
		if(ctrs.size() == Exp.size()) {
			for(size_t i = 0; i < ctrs.size(); i ++)
				if(ctrs[i] != Exp[i])
					cout << "ERROR3" << endl;
		} else
			cout << "ERROR3_1" << endl;
	}

	{ // 4
		int a[] = {1, 2, 3};
		vector<int> A(a, a + 3);
		vector<int> ctrs = solution(3, A);
		int exp[] = {1, 1, 1};
		vector<int> Exp(exp, exp + 3);
		if(ctrs.size() == Exp.size()) {
			for(size_t i = 0; i < ctrs.size(); i ++)
				if(ctrs[i] != Exp[i])
					cout << "ERROR4" << endl;
		} else
			cout << "ERROR4_1" << endl;
	}

	return 0;
}
