// 7.1
// MaxDoubleSliceSum
// Find the maximal sum of any double slice.
// Test Score: 100% (taken from the inet
// https://codesolutiony.wordpress.com/2015/01/05/codility-7-1-max-double-slice-sum/)
#include <iostream>
#include <vector>
#include <math.h>
#include <climits>
#include <stdlib.h>
#include <time.h>
using namespace std;


int solution(vector<int> &A) {
	if(A.size() < 3)
		return 0;

	const int N = int(A.size());

	/* Calculate the most possible summ, moving left-to-right */
	vector<int> fromLeft(N);
        for(int i = 2; i < N; i++)
            fromLeft[i] = max(0, fromLeft[i - 1] + A[i - 1]);

	/* Calculate the most possible summ, moving right-to-left */
	vector<int> fromRight(N);
        for(int i = (N - 3); i >= 0; i--)
            fromRight[i] = max(0, fromRight[i + 1] + A[i + 1]);

	/* Calculate the most possible summ of the array */
        int max_slice = 0;
        for(int i = 1; i < (N - 1); i++)
            max_slice = max(max_slice, fromLeft[i] + fromRight[i]);

        return max_slice;
}

// Test Score: 76% (Correctness 83%, Performance 71%)
int solution2(vector<int> &A) {
	if(A.size() < 3)
		return 0;
	const int N = int(A.size());
	int max_ending = 0;
	int max_slice = 0;
	int max_slice_start = 0;
	int max_slice_finish = 0;
	for(int i = 1; i < (N - 1); i ++ ) {
		int cur_ending = max_ending + A[i];
		if(cur_ending > 0) {
			if(max_ending == 0)
				max_slice_start = i;
			max_ending = cur_ending;
		} else {
			max_ending = 0;
		}

		if(max_ending > max_slice) {
			max_slice = max_ending;
			max_slice_finish = i;
		}
	}

	int min_val = INT_MAX;
	max_slice_finish = min(max_slice_finish + 1, N - 1);
	max_slice_start = max(0, max_slice_start - 1);
	for(int i = (max_slice_start + 1); i < max_slice_finish; i ++) {
		if( A[i] < min_val)
			min_val = A[i];
	}

	if(min_val < 0) {
		max_slice -= min_val;
		return max_slice;
	} else {
		if((max_slice_start > 0) || (max_slice_finish < (N-1)))
			return max_slice;
		max_slice -= min_val;
		return max_slice;
	}
}

int find_max_slice(vector<int> &A, int start, int finish, int &slice_end) {
	int max_ending = 0;
	int max_slice = 0;
	for(int i = start; i <= finish; i ++) {
		max_ending = max(0, max_ending + A[i]);
		if(max_ending > max_slice) {
			slice_end = i;
			max_slice = max_ending;
		}
	}
	return max_slice;
}

int calc_slice_exclusive(vector<int> &A, int start, int finish, int excl) {
	int slice = 0;
	for(int i = start; i <= finish; i ++)
		if(i != excl)
			slice += A[i];
	return slice;
}

int solution_bf(vector<int> &A) {
	if(A.size() < 3)
		return 0;

	const int N = int(A.size());
	int max_slice = INT_MIN;
	for(int start = 1; start < (N - 3); start ++) {
		for(int finish = (start + 2); finish < (N - 1); finish ++) {
			for(int i = start; i <= finish; i ++) {
				int cur_slice = calc_slice_exclusive(A,
						start,
						finish,
						i);
				if(cur_slice > max_slice)
					max_slice = cur_slice;
			}
		}
	}
	return max_slice;
}

int main(void) {
	{ // 1
		int a[] = {3, 2, 6, -1, 4, 5, -1, 2};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		int r1 = solution(A);
		if(r1 != 17)
			cout << "ERROR1" << endl;
		int r2 = solution_bf(A);
		if(r2 != 17)
			cout << "ERROR1_bf" << endl;
	}

	{ // rnd
		srand(time(NULL));
		for(int test = 0; test < 10; test ++) {
			cout << endl << endl;
			const int N = 8;
			vector<int> A(N);
			for(int i = 0; i < N; i ++)
				A[i] = -5 + rand() % 10;
			int r1 = solution(A);
			int r2 = solution_bf(A);
			if(r1 != r2) {
				cout << "ERROR_rnd at test " << test << endl;
				for(int i = 0; i < N; i ++)
					cout << A[i] << " ";
				cout << endl;
				cout << "r1: " << r1 << endl;
				cout << "r2: " << r2 << endl;
			}
		}
	}
	return 0;
}

/*int max_slize_finish = 0;
  for(int i = 1; i < (N - 1); i ++ ) {
  max_ending = max(0, max_ending + A[i]);
  if(max_ending > max_slice) {
  max_slice = max_ending;
  max_slice_finish = i;
  }
  }
  max_slice_finish = min(max_slice_finish + 1, N - 1);

  max_ending = 0;
  max_slice = 0;
  int max_slice_start = 0;
  for(int i = (max_slice_finish - 1); i > 0; i --) {
  max_ending = max(0, max_ending + A[i]);
  if(max_ending > max_slice) {
  max_slice = max_ending;
  max_slice_start = i;
  }
  }
  max_slice_start = max(0, max_slice_start - 1);
  if((max_slice_finish - max_slice_start) <= 1)
  return A[max_slice_start + 1];


  int min = INT_MAX;
  for(int i = (max_slice_start + 1); i < max_slice_finish; i ++) {
  if( A[i] < min)
  min = A[i];
  }
  if(min < 0)*/
