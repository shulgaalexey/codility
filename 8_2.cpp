// 8.2
// CountFactors
// Count factors of given number n.
// Test Score: 100%
#include <iostream>
using namespace std;

int solution(int N) {
	if(N < 0)
		return 0;
	int cnt = 0;
	unsigned int D = 1;
	while((D * D) <= (unsigned int)N) {
		if((N % D) == 0) {
			if((N / D) == D)
				cnt += 1;
			else
				cnt += 2;
		}
		D ++;
	}
	return cnt;
}

int main(void) {
	int r = solution(24);
	if(r != 8)
		cout << "ERROR" << endl;
	return 0;
}
