//2.3
// Test Score: 100%
#include <iostream>
#include <vector>
using namespace std;

int solution(vector<int> &A) {
	if(A.empty())
		return 1;
	const size_t N = A.size();
	const size_t N1 = N + 1;
	bool e[N1];
	for(size_t i = 0; i < N1; i ++)
		e[i] = false;
	for(size_t i = 0; i < N; i ++)
		if((A[i] >= 1) && (A[i] <= int(N)))
			e[A[i]] = true;
	for(size_t i = 1; i < N1; i ++)
		if(!e[i])
			return i;
	return N1;
}

int main(void) {
	{ // 1
		int a[] = {1, 3, 6, 4, 1, 2};
		vector<int> A(a, a + 6);
		const int x = solution(A);
		if(x != 5) cout << "ERROR1!" << endl;
	}

	{ // 2
		int a[] = {-3, -5, -2, 1, 4, 2, 6};
		vector<int> A(a, a + 7);
		const int x = solution(A);
		if(x != 3) cout << "ERROR2!" << endl;
	}

	{ // 3
		int a[] = {2, 3, 4};
		vector<int> A(a, a + 3);
		const int x = solution(A);
		if(x != 1) cout << "ERROR3!" << endl;
	}

	{ // 4
		int a[] = {5, 6, 7};
		vector<int> A(a, a + 3);
		const int x = solution(A);
		if(x != 1) cout << "ERROR4!" << endl;
	}

	{ // 5
		int a[] = {-5, -6, -7};
		vector<int> A(a, a + 3);
		const int x = solution(A);
		if(x != 1) cout << "ERROR5!" << endl;
	}

	{ // 6
		int a[] = {1, 2, 3, 4};
		vector<int> A(a, a + 4);
		const int x = solution(A);
		if(x != 5) cout << "ERROR6!" << endl;
	}

	return 0;
}
