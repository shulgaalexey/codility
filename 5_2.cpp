// 5.2
// StoneWall
// Cover "Manhattan skyline" using the minimum number of rectangles.
// Test Score: 100%
#include <iostream>
#include <vector>
#include <stack>
#include <stdlib.h>
#include <time.h>
using namespace std;

int solution(vector<int> &H) {
	stack<int> st;
	int cnt = 0;
	for(size_t i = 0; i < H.size(); i ++) {
		if(st.empty()) {
			st.push(H[i]);
			cnt ++;
		}
		else {
			while(!st.empty() && (st.top() > H[i]))
				st.pop();
			if(st.empty() || (st.top() != H[i])) {
				st.push(H[i]);
				cnt ++;
			}
		}
	}
	return cnt;
}

int main(void) {
	{ // 1
		int h[] = {8, 8, 5, 7, 9, 8, 7, 4, 8};
		vector<int> H(h, h + sizeof(h) / sizeof(h[0]));
		int r = solution(H);
		if(r != 7)
			cout << "ERROR1" << endl;
	}

	{ // 2
		int h[] = {1, 1};
		vector<int> H(h, h + sizeof(h) / sizeof(h[0]));
		int r = solution(H);
		if(r != 1)
			cout << "ERROR2" << endl;
	}

	{ // 3
		int h[] = {1, 2, 3, 4};
		vector<int> H(h, h + sizeof(h) / sizeof(h[0]));
		int r = solution(H);
		if(r != 4)
			cout << "ERROR3" << endl;
	}

	{ // 4
		int h[] = {4, 3, 2, 1};
		vector<int> H(h, h + sizeof(h) / sizeof(h[0]));
		int r = solution(H);
		if(r != 4)
			cout << "ERROR4" << endl;
	}

	{ // 5
		int h[] = {1, 2, 3, 4, 3, 2, 1};
		vector<int> H(h, h + sizeof(h) / sizeof(h[0]));
		int r = solution(H);
		if(r != 4)
			cout << "ERROR5" << endl;
	}

	{ // Rnd
		srand(time(NULL));
		for(int test = 0; test < 1000; test ++) {
			//cout << "test " << test << "..." << endl;
			if((test % 100) == 0)
				cout << "test " << test << "..." << endl;
			//const int N = 7;
			const int N = 100000;
			vector<int> H(N);
			for(int i = 0; i < N; i ++) {
				H[i] = rand() % 1000000000 + 1;
				//H[i] = rand() % 5 + 1;
				//cout << H[i] << " ";
			}
			//cout << endl;
			//int r =
			solution(H);
			//cout << r << " blocks needed" << endl;
		}
	}

	return 0;
}
