// 14.1
// MaxNonoverlappingSegments
// Find a maximal set of non-overlapping segments.
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;

int solution(vector<int> &A, vector<int> &B) {
	if(A.size() < 1)
		return 0;

	int cnt = 1;
	int right = B[0];

	for(size_t i = 0; i < A.size(); i ++) {
		if(A[i] > right) {
			cnt ++;
			right  = B[i];
		}
	}

	return cnt;
}

vector<vector<int> > make_sets(vector<int> IDXS) {
	vector<vector<int> > ret;
	if(IDXS.size() == 1) {
		vector<int> single;
		single.push_back(IDXS[0]);
		ret.push_back(single);
		return ret;
	}

	ret.push_back(IDXS);
	for(size_t i = 0; i < IDXS.size(); i ++) {
		const int val = IDXS[i];
		IDXS.erase(IDXS.begin() + i);
		vector<vector<int> > vars = make_sets(IDXS);
		for(size_t j = 0; j < vars.size(); j ++)
			ret.push_back(vars[j]);
		IDXS.insert(IDXS.begin() + i, val);
	}
	return ret;
}

bool has_intersection(const vector<int> &idxs,
		const vector<int> &A,
		const vector<int> &B) {
	if(idxs.size() == 1)
		return false;

	for(size_t i = 0; i < idxs.size(); i ++) {
		int base_idx = idxs[i];
		const int l = A[base_idx];
		const int r = B[base_idx];
		for(size_t j = (i + 1); j < idxs.size(); j ++) {
			int cur_idx = idxs[j];
			const int l_cur = A[cur_idx];
			const int r_cur = B[cur_idx];
			if((l_cur >= l) && (l_cur <= r))
				return true;
			if((r_cur >= l) && (r_cur <= r))
				return true;
		}
	}

	/*cout << "variant: \t";
	  for(size_t i = 0; i < idxs.size(); i ++)
	  cout << idxs[i] << " ";
	  cout << "\thas NO intersections" << endl;*/
	return false;
}

int solution_bf(vector<int> &A, vector<int> &B) {
	if(A.empty() || B.empty())
		return 0;

	/* Generate all possible sub-sets */
	const int N = int(A.size());
	vector<int> idxs(N);
	for(int i = 0; i < N; i ++)
		idxs[i] = i;
	vector<vector<int> > sets = make_sets(idxs);

	/* Find the longest sub-set with no intersections */
	int longest = 0;
	for(size_t i = 0; i < sets.size(); i ++) {
		vector<int> vars = sets[i];
		if(int(vars.size()) <= longest)
			continue;
		for(size_t j = 0; j < vars.size(); j ++) {
			if(has_intersection(vars, A, B))
				continue;
			if(int(vars.size()) > longest)
				longest = int(vars.size());
			//cout << vars[j] << " ";
		}
		//cout << endl;
	}

	return longest;
}

int main(void) {
	{ // 1
		int a[] = {1, 3, 7, 9, 9};
		int b[] = {5, 6, 8, 9, 10};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> B(b, b + sizeof(b) / sizeof(b[0]));
		int r = solution(A, B);
		int r2 = solution_bf(A, B);
		cout << r << endl;
		cout << r2 << endl;
		if((r != 3) || (r != r2))
			cout << "ERROR1" << endl;
	}

	{ // RND
		srand(time(NULL));
		for(int test = 0; test < 50; test ++) {
			cout << "test: " << test << "..." << endl;
			const int N = 8;

			vector<int> A(N);
			vector<int> B(N);
			for(int i = 0; i < N; i ++) {
				int a = 1 + abs(rand() % 10);
				int b = 1 + abs(rand() % 10);
				if(a < b) {
					A[i] = a;
					B[i] = b;
				} else {
					A[i] = b;
					B[i] = a;
				}
			}
			sort(A.begin(), A.end());
			sort(B.begin(), B.end());

			int r1 = solution(A, B);
			int r2 = solution_bf(A, B);
			if(r1 != r2) {
				cout << "ERROR RND" << endl;
				for(int i = 0; i < N; i ++)
					cout << A[i] << " ";
				cout << endl;
				for(int i = 0; i < N; i ++)
					cout << B[i] << " ";
				cout << endl;
				cout << "\tr1 = " << r1;
				cout << "\tr2 = " << r2 << endl;
			}
		}
	}

	return 0;
}
