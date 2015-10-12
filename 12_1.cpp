// 12.1
// MinMaxDivision
// Divide array A into K blocks and minimize the largest sum of any block.
// Test Score: 100%
// (taken from inet)
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

bool valid_block_sum(const vector<int> &A,
		int max_block_cnt,
		int max_block_size) {
	int block_sum = 0;
	int block_cnt = 0;
	for(size_t i = 0; i < A.size(); i ++) {
		if((block_sum + A[i]) > max_block_size) {
			block_sum = A[i];
			block_cnt ++;
		} else
			block_sum += A[i];
		if(block_cnt >= max_block_cnt)
			return false;
	}
	return true;
}

int solution(int K, int M, vector<int> &A) {
	int max_item = INT_MIN; // Max item of the array
	for(size_t i = 0; i < A.size(); i ++)
		if(A[i] > max_item)
			max_item = A[i];

	int item_sum = 0; // Sum of all array items
	for(size_t i = 0; i < A.size(); i ++)
		item_sum += A[i];

	int lower_bound = max_item;
	int upper_bound = item_sum;

	const int max_block_cnt = K;

	// Checking border conditions
	if(max_block_cnt == 1)
		return upper_bound;
	if(max_block_cnt >= int(A.size()))
		return lower_bound;


	// Binary searching for the minimal block sum
	while(lower_bound <= upper_bound) {
		int candidate_mid = (lower_bound + upper_bound) / 2;
		//cout << "low:" << lower_bound << "\t";
		//cout << "up:" << upper_bound << "\t";
		//cout << "avg:" << candidate_mid << "\n";
		if(valid_block_sum(A, max_block_cnt, candidate_mid))
			upper_bound = candidate_mid - 1;
		else
			lower_bound = candidate_mid + 1;
	}
	return lower_bound;
}

int main(void) {
	{ // 1
		int a[] = {2, 1, 5, 1, 2, 2, 2};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(3, 5, A);
		cout << r << endl;
		if(r != 6)
			cout << "ERROR1" << endl;
	}

	{ // 2
		int a[] = {3, 2, 2, 2, 5, 2, 3, 2, 1, 4, 5, 2, 5};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r = solution(3, 5, A);
		cout << r << endl;
		if(r != 13)
			cout << "ERROR2" << endl;
	}

	return 0;
}
