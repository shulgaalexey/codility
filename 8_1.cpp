// 8.1
// MinPerimeterRectangle
// Find the minimal perimeter of any rectangle whose area equals N.
// Test Score: 100%
#include <iostream>
#include <climits>
using namespace std;

int solution(int N) {
	long long A = 1;
	unsigned int p_min = UINT_MAX;
	while((A * A) <= N) {
		if((N % A) == 0) { /* Check if B also is integer */
			int B = N / A;
			unsigned int p = 2 * (A + B);
			if(p < p_min)
				p_min = p;
		}
		A ++;
	}
	return p_min;
}

int main(void) {
	{ // 1
		int r = solution(30);
		if(r != 22)
			cout << "ERROR1" << endl;
	}

	return 0;
}
