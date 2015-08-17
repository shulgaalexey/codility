// 1.2
// Test Score: 100%

#include <iostream>
#include <vector>
using namespace std;

int solution(vector<int> &A) {
	if(A.empty())
		return 1;
	const size_t N = A.size();
	long long sum = 0;
	for(size_t i = 0; i < N; i ++)
		sum += A[i];
	long long sum_exp = ((long long)(2 + N) * (N + 1)) / 2;
	return int(sum_exp - sum);
}

int main(void) {

	{ // 0
		vector<int> A;
		const int x = solution(A);
		const int e = 0;
		if(x != e)
			cout << "ERROR [1]" << x << " instead of " << e << endl;
	}

	{ // 1
		int a[] = {2, 3, 1, 5};
		vector<int> A(a,  a + sizeof(a) / sizeof(a[0]));
		const int x = solution(A);
		const int e = 4;
		if(x != e)
			cout << "ERROR [1]" << x << " instead of " << e << endl;
	}

	{ // 2
		int a[] = {2};
		vector<int> A(a,  a + sizeof(a) / sizeof(a[0]));
		const int x = solution(A);
		const int e = 1;
		if(x != e)
			cout << "ERROR [2]" << x << " instead of " << e << endl;
	}

	{ // 3
		int a[] = {1};
		vector<int> A(a,  a + sizeof(a) / sizeof(a[0]));
		const int x = solution(A);
		const int e = 2;
		if(x != e)
			cout << "ERROR [3]" << x << " instead of " << e << endl;
	}

	{ // 4
		const size_t N = 100000;
		vector<int> A(N);
		for(size_t i = 0; i < N; i ++)
			A[i] = i + 1;
		A[0] = N + 1;
		const int x = solution(A);
		const int e = 1;
		if(x != e)
			cout << "ERROR [4]" << x << " instead of " << e << endl;
	}

	{ // 5
		const size_t N = 100000;
		vector<int> A(N);
		for(size_t i = 0; i < N; i ++)
			A[i] = i + 1;
		A[N - 1] = N + 1;
		const int x = solution(A);
		const int e = N;
		if(x != e)
			cout << "ERROR [5]" << x << " instead of " << e << endl;
	}

	{ // 6
		const size_t N = 100000;
		vector<int> A(N);
		for(size_t i = 0; i < N; i ++)
			A[i] = i + 1;
		A[10] = N + 1;
		const int x = solution(A);
		const int e = 11;
		if(x != e)
			cout << "ERROR [6]" << x << " instead of " << e << endl;
	}

	return 0;
}
