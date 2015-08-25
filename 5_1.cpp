// 5.1
// Nesting
// Determine whether given string of parentheses is properly nested.
// Test Score: 100%
#include <iostream>
#include <string>
#include <stack> // for brute force solution
#include <stdlib.h>
#include <time.h>
using namespace std;

int solution(string &S) {
	if(S.empty())
		return 1;
	if(S.length() % 2)
		return 0;
	int cnt = 0;
	for(size_t i = 0; i <  S.length(); i ++) {
		if(S[i] == '(')
			cnt ++;
		else if(S[i] == ')')
			cnt --;
		if(cnt < 0)
			return 0;
	}
	return ((cnt == 0) ? 1 : 0);
}

int solution_bf(string &S) {
	if(S.empty())
		return 1;
	if(S[0] != '(')
		return 0;
	stack<char> st;
	st.push(S[0]);
	for(size_t i = 1; i < S.length(); i ++) {
		if(S[i] == '(')
			st.push('(');
		else if(S[i] == ')') {
			if(st.empty())
				return 0;
			else
				st.pop();
		}
	}
	return ((st.empty()) ? 1 : 0);
}

int main(void) {
	{ // 1
		string S("(()(())())");
		if(solution(S) != 1)
			cout << "ERROR1" << endl;
		if(solution_bf(S) != 1)
			cout << "ERROR1_bf" << endl;
	}

	{ // 2
		string S("())");
		if(solution(S) != 0)
			cout << "ERROR2" << endl;
		if(solution_bf(S) != 0)
			cout << "ERROR2_bf" << endl;
	}

	{ // 3
		string S(")(");
		if(solution(S) != 0)
			cout << "ERROR3" << endl;
		if(solution_bf(S) != 0)
			cout << "ERROR3_bf" << endl;
	}

	{ // 4
		string S("())()(");
		if(solution(S) != 0)
			cout << "ERROR4" << endl;
		if(solution_bf(S) != 0)
			cout << "ERROR4_bf" << endl;
	}

	{ // Rnd
		srand(time(NULL));
		for(int test = 0; test < 1000; test ++) {
			string S;
			for(int i = 0; i < 20; i ++)
				S += (rand() > (RAND_MAX / 2)) ? '(' : ')';
			int r1 = solution(S);
			int r2 = solution_bf(S);
			if(r1 == 1) {
				cout << "test " << test << "..." << endl;
				cout << S << endl;
				cout << "r1: " << r1 << " r2: " << r2 << endl;
			}
			if(r1 != r2)
				cout << "ERROR_rnd" << endl;
		}
	}

	return 0;
}
