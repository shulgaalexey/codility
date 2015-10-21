//14.2
//TieRopes
//Tie adjacent ropes to achieve the maximum number of ropes of length >= K.
#include <iostream>
#include <vector>
using namespace std;

int solution(int K, vector<int> &A) {
	int cnt = 0;
	int len = 0;
	for(size_t i = 0; i < A.size(); i ++) {
		len += A[i];
		if(len >= K) {
			cnt ++;
			len = 0;
		}
	}
	return cnt;
}

int main(void) {
	{ // 1
		int a[] = {1, 2, 3, 4, 1, 1, 3};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(4, A);
		cout << r << endl;
		if(r != 3)
			cout << "ERROR1" << endl;
	}

	{ // 2
		int a[] = {7, 7, 1, 6, 6, 8, 4, 6, 8, 3};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(4, A);
		cout << r << endl;
		if(r != 8)
			cout << "ERROR2" << endl;
	}

	{ // 3
		int a[] = {4, 4, 4, 4, 4};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(4, A);
		cout << r << endl;
		if(r != 5)
			cout << "ERROR3" << endl;
	}

	{ // 4
		int a[] = {1, 1, 1, 1, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(4, A);
		cout << r << endl;
		if(r != 1)
			cout << "ERROR4" << endl;
	}


	{ // 5
		int a[] = {1, 1, 1, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(4, A);
		cout << r << endl;
		if(r != 1)
			cout << "ERROR5" << endl;
	}

	{ // 6
		int a[] = {1, 1, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(4, A);
		cout << r << endl;
		if(r != 0)
			cout << "ERROR6" << endl;
	}
	return 0;
}
