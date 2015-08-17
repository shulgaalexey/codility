// 1.1
// Test Score: 100%

#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

int solution(vector<int> &A) {
    const size_t N = A.size();
    vector<int> sfw(N), sbw(N);

    sfw[0] = A[0];
    sbw[N - 1] = A[N - 1];

    for(size_t i = 1; i < N; i ++)
        sfw[i] = sfw[i - 1] + A[i];

    for(int i = int(N - 2); i >= 0; i --)
        sbw[i] = sbw[i + 1] + A[i];

    int min = INT_MAX;
    for(size_t i = 0; i < (N - 1); i ++) {
        const int cur_min = abs(sfw[i] - sbw[i + 1]);
        if(cur_min < min) {
            min = cur_min;
        }
    }

    return min;
}

//////////////////////////////////////////////////////
#include <iostream>
int main(void) {
	int a[] = {3, 1, 2, 4, 3};
	vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
	const int min = solution(A);
	if(min != 1)
		cout << "ERROR" << endl;
	else
		cout << "OK" << endl;
	return 0;
}
