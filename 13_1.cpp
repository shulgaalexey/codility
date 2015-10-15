// 13.1
// AbsDistinct
// Compute number of distinct absolute values of sorted array elements.
// Test Score: 100%
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int solution(vector<int> &A) {
	int adc = 0;
	map<int, int> m;
	for(size_t i = 0; i < A.size(); i ++) {
		int a = A[i];
		if( a < 0)
			a *= -1;
		if(m.count(a) > 0)
			continue;
		m[a] = a;
		adc ++;
	}
	return adc;
}

int main(void) {
	{ // 1
		int a[] = {-5, -3, -1, 0, 3, 6};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != 5)
			cout << "ERROR1" << endl;
	}
	return 0;
}
