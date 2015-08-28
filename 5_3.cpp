// 5.3
// Brackets
// Determine whether a given string of parentheses is properly nested.
// Test Score: 100%
#include <iostream>
#include <string>
#include <stack>
using namespace std;

int solution(string &S) {
	if(S.empty())
		return 1;
	stack<char> st;
	st.push(S[0]);
	for(size_t i = 1; i < S.length(); i ++) {
		const char ch = S[i];
		switch(ch) {
			case '{':
				st.push('{');
				break;
			case '}':
				if(st.empty() || (st.top() != '{'))
					return 0;
				st.pop();
				break;
			case '(':
				st.push('(');
				break;
			case ')':
				if(st.empty() || (st.top() != '('))
					return 0;
				st.pop();
				break;
			case '[':
				st.push('[');
				break;
			case ']':
				if(st.empty() || (st.top() != '['))
					return 0;
				st.pop();
				break;
			default:
				return 0;
		}
	}
	return st.empty();
}

int main(void) {
	{ // 1
		string S("{[()()]}");
		int r = solution(S);
		if(r != 1)
			cout << "ERROR1" << endl;
	}

	{ // 2
		string S("([)()]");
		int r = solution(S);
		if(r != 0)
			cout << "ERROR2" << endl;
	}

	{ // 3
		string S("{{[()()]}");
		int r = solution(S);
		if(r != 0)
			cout << "ERROR3" << endl;
	}

	{ // 4
		string S("");
		int r = solution(S);
		if(r != 1)
			cout << "ERROR4" << endl;
	}

	{ // 5
		string S("([{}])");
		int r = solution(S);
		if(r != 1)
			cout << "ERROR5" << endl;
	}

	{ // 6
		string S("()");
		int r = solution(S);
		if(r != 1)
			cout << "ERROR6" << endl;
	}

	{ // 7
		string S("{}");
		int r = solution(S);
		if(r != 1)
			cout << "ERROR7" << endl;
	}


	{ // 8
		string S("[]");
		int r = solution(S);
		if(r != 1)
			cout << "ERROR8" << endl;
	}

	{ // 9
		string S("()[]{}");
		int r = solution(S);
		if(r != 1)
			cout << "ERROR9" << endl;
	}

	return 0;
}
