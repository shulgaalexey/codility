//13.3
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> &A) {
	const int n = int(A.size());
	if(n < 3)
		return 0;
	sort(A.begin(), A.end());
	int result = 0;
	for(int x = 0; x < n; x ++) {
		int z = 0;
		for(int y = (x + 1); y < n; y ++) {
			while((z < n) && ((A[x] + A[y]) > A[z]))
				z ++;
			result += z - y - 1;
		}
	}
	return result;
}

int main(void) {
	{ //
		int a[] = {10, 2, 5, 1, 8, 12};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(A);
		cout << r << endl;
		if(r != 4)
			cout << "ERROR1" << endl;
	}

	return 0;
}
