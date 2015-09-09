// 5.4
// Fish
// N voracious fish are moving along a river. Calculate how many fish are alive.
// Test Score: 100%
#include <iostream>
#include <vector>
#include <stack>
#include <stdlib.h>
#include <time.h>
using namespace std;

int solution(vector<int> &A, vector<int> &B) {
	stack<int> st;
	int eaten = 0;
	for(size_t i = 0; i < A.size(); i ++) {
		if(B[i] == 1)
			st.push(A[i]);
		else {
			while(!st.empty()) {
				if(A[i] > st.top()) {
					st.pop();
					// The fish going upstream is bigger
					// and it eats another one
					eaten ++;
				} else
					break;
			}
			if(!st.empty())
				// The fish going downstream is bigger
				// and it eats another one
				eaten ++;
		}
	}
	return (A.size() - eaten);
}

#if 0
BF solution is incorrect
int solution_bf(vector<int> &A, vector<int> &B) {
	int eaten = 0;

	for(int t = 0; t < int(A.size(); t ++) {
			// Scaning left-to-right
			for(size_t i = 0; i < A.size(); i ++) {
			if(A[i] == (-1))
			continue; // Already eaten
			if(B[i] != 1)
			continue; // Considering only fish going downstream

			for(size_t j = (i + 1); j < A.size(); j ++) {
			if(A[j] == (-1))
			continue; // Already eaten
			if(B[j] != 0)
			continue; // It is not the opposite fish
			if(A[j] > A[i]) {
			// The fish going upstream is bigger
			// and it eats another one
			A[i] = -1;
			eaten ++;
			break;
			} else {
			// The fish going downstream is bigger
			// and it eats another one
				eaten ++;
				A[j] = -1;
			}
			}
			}
	}
	/*
	// Scanning right-to-left
	for(int i = int(A.size() - 1); i >= 0; i --) {
	if(A[i] == (-1))
	continue; // Already eaten
	if(B[i] != 0)
	continue; // Considering only fish going downstream

	for(int j = (i - 1); j >= 0; j --) {
	if(A[j] == (-1))
	continue; // Already eaten
	if(B[j] != 1)
	continue; // It is not the opposite fish
	if(A[j] > A[i]) {
// The fish going downstream is bigger
// and it eats another one
eaten ++;
break;
} else {
// The fish going upstream is bigger
// and it eats another one
eaten ++;
A[j] = -1;
}
}
}*/
return (A.size() - eaten);
}
#endif

int main(void) {
	{ // 1
		int a[] = {4, 3, 2, 1, 5};
		int b[] = {0, 1, 0, 0, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> B(b, b + sizeof(b) / sizeof(b[0]));
		int r1 = solution(A, B);
		if(r1 != 2)
			cout << "ERROR1" << endl;
		/*int r2 = solution_bf(A, B);
		  if(r2 != 2)
		  cout << "ERROR1_bf" << endl;*/
	}

	{ // 2
		int a[] = {4, 3, 2, 1, 5};
		int b[] = {0, 1, 1, 0, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> B(b, b + sizeof(b) / sizeof(b[0]));
		int r1 = solution(A, B);
		if(r1 != 2)
			cout << "ERROR2" << endl;
		/*int r2 = solution_bf(A, B);
		  if(r2 != 2)
		  cout << "ERROR2_bf" << endl;*/
	}

	{ // 3
		int a[] = {4, 5};
		int b[] = {0, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> B(b, b + sizeof(b) / sizeof(b[0]));
		int r1 = solution(A, B);
		if(r1 != 2)
			cout << "ERROR3" << endl;
		/*int r2 = solution_bf(A, B);
		  if(r2 != 2)
		  cout << "ERROR3_bf" << endl;*/
	}

	{ // 4
		int a[] = {1, 2, 3};
		int b[] = {1, 1, 1};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> B(b, b + sizeof(b) / sizeof(b[0]));
		int r1 = solution(A, B);
		if(r1 != 3)
			cout << "ERROR4" << endl;
		/*int r2 = solution_bf(A, B);
		  if(r2 != 3)
		  cout << "ERROR4_bf" << endl;*/
	}

	{ // 5
		int a[] = {1, 2, 3};
		int b[] = {0, 0, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> B(b, b + sizeof(b) / sizeof(b[0]));
		int r1 = solution(A, B);
		if(r1 != 3)
			cout << "ERROR5" << endl;
		/*int r2 = solution_bf(A, B);
		  if(r2 != 3)
		  cout << "ERROR5_bf" << endl;*/
	}

	{ // 6
		int a[] = {4, 2, 1, 3};
		int b[] = {1, 1, 1, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> B(b, b + sizeof(b) / sizeof(b[0]));
		int r1 = solution(A, B);
		if(r1 != 1)
			cout << "ERROR6" << endl;
		/*int r2 = solution_bf(A, B);
		  if(r2 != 1)
		  cout << "ERROR6_bf" << endl;
		  cout << r2 << endl;*/
	}

	{ // 7
		int a[] = {4, 3, 2, 1, 5};
		int b[] = {0, 0, 1, 0, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> B(b, b + sizeof(b) / sizeof(b[0]));
		int r1 = solution(A, B);
		if(r1 != 3)
			cout << "ERROR7" << endl;
		/*int r2 = solution_bf(A, B);
		  if(r2 != 3)
		  cout << "ERROR5_bf" << endl;*/
	}

	return 0;
}
