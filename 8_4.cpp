// 8.4
// Flags
// Find the maximum number of flags that can be set on mountain peaks.
// Test Score: 93% (Correctness 100%, Performance 85%)
// With help from Ishaq, http://codesays.com/2014/solution-to-boron2013-flags-by-codility/
#include <iostream>
#include <vector>
using namespace std;

int solution(vector<int> &A) {
	if(A.empty())
		return 0;

	vector<int> P;
	for(size_t i = 1; i < (A.size() - 1); i ++)
		if((A[i] > A[i - 1]) && (A[i] > A[i + 1]))
			P.push_back(i);

	const int peaks_count = int(P.size());
	if(peaks_count <= 1)
		return peaks_count;

	// The distance for k flags requires k(k-1) distance between first and last flag
	int max_flags_possible = peaks_count;
	const int dist = P[P.size() - 1] - P[0];
	while((max_flags_possible * (max_flags_possible - 1)) > dist)
		        max_flags_possible --;

	for(int K = max_flags_possible; K >= 0; K --) {
		int flags_set = 1;
		int distance = 0;
		for(int i = 1; i < peaks_count; i ++) {
			distance += P[i] - P[i - 1];
			if(distance >= K) {
				flags_set += 1;
				distance = 0;
			}
		}
		if(flags_set >= K)
			return K;
	}
	return 0;
}

int main(void) {
	int a[] = {1, 5, 3, 4, 3, 4, 1, 2, 3, 4, 6, 2};
	vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
	int r = solution(A);
	cout << r << endl;
	if(r != 3)
		cout << "ERROR" << endl;

	return 0;
}
