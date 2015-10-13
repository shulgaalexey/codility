// 12.2
// NailingPlanks
// Count the minimum number of nails that allow a series of planks to be nailed.
// Test Score: 1000% (thanks, internet)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool all_nailed(vector<int> &A, vector<int> &B, vector<int> &C, const int nails) {
	/* Nail planks */
	vector<unsigned char> nailed_planks(A.size(), 0);
	for(size_t i = 0; i < size_t(nails); i ++)
		for(size_t k = 0; k < A.size(); k ++)
			if((C[i] >= A[k]) && (C[i] <= B[k]))
				nailed_planks[k] = 1;
	/* Check if all planks are nailed */
	for(size_t k = 0; k < A.size(); k ++)
		if(nailed_planks[k] != 1)
			return false;
	return true;
}

int solution2(vector<int> &A, vector<int> &B, vector<int> &C) {
	const int max_nails_cnt = int(C.size());
	int upper_nails_cnt = max_nails_cnt;
	int lower_nails_cnt = 1;
	int nails_cnt_candidate = upper_nails_cnt;
	int last_successfull = -1;

	while(lower_nails_cnt <= upper_nails_cnt) {
		nails_cnt_candidate =
			(upper_nails_cnt + lower_nails_cnt) / 2;
		//cout << "Nails cnt candidate: " << nails_cnt_candidate << endl;
		if(all_nailed(A, B, C, nails_cnt_candidate)) {
			//cout << "All Nailed" << endl;
			last_successfull = nails_cnt_candidate;
			upper_nails_cnt = nails_cnt_candidate - 1;
		} else {
			//cout << "Not nailed" << endl;
			lower_nails_cnt = nails_cnt_candidate + 1;
		}
	}
	return last_successfull;
}

////////////////////////////////////////////////////////////////////////////////

bool nails_enough(int j, vector<int> &A, vector<int> &B, vector<int> &C);

int solution(vector<int> &A, vector<int> &B, vector<int> &C) {
	int last = (int)C.size();
	int bgn = 0;
	int mid = 0;
	int result = -1;
	while(bgn <= last) {
		mid = (last + bgn) / 2;
		if(nails_enough(mid, A, B, C)) {
			last = mid - 1;
			result = mid;
		} else
			bgn = mid + 1;
	}
	return result;
}

bool nails_enough(int j, vector<int> &A, vector<int> &B, vector<int> &C)
{
	std::vector<int> used_nails(C.begin(), C.begin() + j);
	sort(used_nails.begin(), used_nails.end());
	// binary search again for fitted nail
	for(int j = 0; j < (int)A.size(); j++) {
		int last = (int)used_nails.size() - 1;
		int mid = 0;
		int bgn = 0;
		bool found = false;
		while(bgn <= last) {
			mid = (last + bgn) / 2;
			if(used_nails[mid] >= A[j] && used_nails[mid] <= B[j]) {
				// fit
				found = true;
				break;
			}
			if(used_nails[mid] < A[j]) {
				bgn = mid + 1;
			}else if(used_nails[mid] > B[j]) {
				last = mid - 1;
			}
		}
		if (found == false)
			return false;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////

int main(void) {
	{ // 1
		int a[] = {1, 4, 5, 8};
		int b[] = {4, 5, 9, 10};
		int c[] = {4, 6, 7, 10, 2};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> B(b, b + sizeof(b) / sizeof(b[0]));
		vector<int> C(c, c + sizeof(c) / sizeof(c[0]));
		int r = solution(A, B, C);
		int r2 = solution2(A, B, C);
		cout << r << endl;
		cout << r2 << endl;
		if(r != 4)
			cout << "ERROR1" << endl;
	}

	{ // 2
		int a[] = {6, 7, 10, 5, 2, 1, 6, 3, 5, 2, 10, 7};
		int b[] = {10, 3, 3, 7, 3, 9, 4, 7, 2, 5, 5, 3};
		int c[] = {8, 8, 10, 8, 3, 8, 3, 6, 10, 1, 2, 8, 9, 9, 5, 7, 7,
			7, 7};
		vector<int> A(sizeof(a) / sizeof(a[0]), 0);
		vector<int> B(sizeof(b) / sizeof(b[0]), 0);
		for(size_t i = 0; i < A.size(); i ++) {
			if(a[i] < b[i]) {
				A[i] = a[i];
				B[i] = b[i];
			} else {
				A[i] = b[i];
				B[i] = a[i];
			}
		}
		//for(size_t i = 0; i < A.size(); i ++) cout << A[i] << "\t";
		//cout << endl;
		//for(size_t i = 0; i < B.size(); i ++) cout << B[i] << "\t";
		//cout << endl;
		vector<int> C(c, c + sizeof(c) / sizeof(c[0]));
		int r = solution(A, B, C);
		int r2 = solution2(A, B, C);
		cout << r << endl;
		cout << r2 << endl;
		if(r != 8)
			cout << "ERROR2" << endl;
	}
	return 0;
}
