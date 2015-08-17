// 2.1
// Test Score: 100%
#include <iostream>
#include <vector>
using namespace std;

int solution(int X, vector<int> &A) {
	if(A.empty())
		return (-1);

	long long sum_exp = (long long)X + 1;
	sum_exp *= X;
	sum_exp /= 2;

	const size_t X_const = X + 1;
	size_t l[X_const];
	for(size_t i = 0; i < X_const; i ++) l[i] = 0;

	long long sum = 0;
	for(size_t i = 0; i < A.size(); i ++) {
		const int pos = A[i];
		if(pos > X) continue;
		if(!l[pos]) {
			l[pos] = 1;
			sum += pos;
			if(sum == sum_exp)
				return i;
		}
	}
	return (-1);
}

int main(void) {
	{ //1
		int a[] = {1, 3, 1, 4, 2, 3, 5, 4};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));

		int t = solution(5, A);
		if(t != 6) cout << "ERROR 0!" << endl;
		//cout << t << endl;

		t = solution(1, A);
		if(t != 0) cout << "ERROR 1!" << endl;
		//cout << t << endl;

		t = solution(2, A);
		if(t != 4) cout << "ERROR 2!" << endl;
		//cout << t << endl;

		t = solution(3, A);
		if(t != 4) cout << "ERROR 3!" << endl;
		//cout << t << endl;

		t = solution(6, A);
		if(t != (-1)) cout << "ERROR 4!" << endl;
	}

	{ //2
		//cout << "test 100" << endl;
		vector<int> A(100);
		for(int i = 0; i < 100; i ++) A[i] = i + 1;
		int t = solution(100, A);
		if(t != 99) cout << "ERROR 5!" << endl;
	}

	{ //3
		//cout << "test 100 000" << endl;
		vector<int> A(100000);
		for(int i = 0; i < 100000; i ++) A[i] = i + 1;
		int t = solution(100000, A);
		if(t != (100000 - 1)) cout << "ERROR 6!" << endl;
	}

	return 0;
}
