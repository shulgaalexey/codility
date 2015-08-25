// 4.4
// NumberOfDiscIntersections
// Compute the number of intersections in a sequence of discs.
// Not my solution, taken from the internet
// Test Score: 93% (87%/100%)
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int solution(vector<int> &A) {
	size_t disc_count = A.size();
	vector<int> range_upper(disc_count);
	vector<int> range_lower(disc_count);

	for(size_t i = 0; i < disc_count; i ++) {
		range_upper[i] = i + A[i];
		range_lower[i] = i - A[i];
	}

	sort(range_upper.begin(), range_upper.end());
	sort(range_lower.begin(), range_lower.end());

	size_t range_lower_index = 0;
	int intersect_count = 0;
	for(size_t range_upper_index = 0; range_upper_index < disc_count;
			range_upper_index ++) {
		while((range_lower_index < disc_count)
				&& (range_upper[range_upper_index] >=
					range_lower[range_lower_index]))
			range_lower_index ++;

		intersect_count += range_lower_index - range_upper_index - 1;
		if(intersect_count > 10000000)
			return -1;
	}
	return intersect_count;
}

int main(void) {
	{ // 1
		int a[] = {1, 5, 2, 1, 4, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int c = solution(A);
		if(c != 11)
			cout << "ERROR1" << endl;
	}
	return 0;
}
