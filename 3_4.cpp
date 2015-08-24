// 3.4
// GenomicRangeQuery
// Find the minimal nucleotide from a range of sequence DNA.
// Test Score: 100%
#include <iostream>
#include <vector>
#include <math.h>
#include <climits>
#include <stdlib.h>
#include <time.h>
using namespace std;

vector<int> solution(string &S, vector<int> &P, vector<int> &Q) {
	if(S.empty() || P.empty() || Q.empty())
		return vector<int>();

	/* Calculate the amounts of nucleotides */
	const size_t N = S.length();
	vector<int> A(N), C(N), G(N);
	int a_cnt = 0, c_cnt = 0, g_cnt = 0;
	for(size_t i = 0; i < N; i ++) {
		switch(S[i]) {
			case 'A': a_cnt ++; break;
			case 'C': c_cnt ++; break;
			case 'G': g_cnt ++; break;
			default: break;
		}
		A[i] = a_cnt;
		C[i] = c_cnt;
		G[i] = g_cnt;
	}

	const size_t M = P.size();
	vector<int> ret(M);
	for(size_t K = 0; K < M; K ++) {
		size_t i1 = P[K];
		size_t i2 = Q[K];
		int impact = 0;
		if(i1 == 0) {
			/*
			 *  When starting from the beginning of the array
			 *  it is enough to check the presence of the
			 *  nucleotide
			 */
			if(A[i2] > 0)
				impact = 1;
			else if(C[i2] > 0)
				impact = 2;
			else if(G[i2] > 0)
				impact = 3;
			else
				impact = 4;
		} else {
			/* When starting from the arbitrary index
			 *  it iis needed to check if the amount
			 *  of nucleotides changed
			 */
			if(i1 > 0)
				i1 --;
			if(A[i1] != A[i2])
				impact = 1;
			else if(C[i1] != C[i2])
				impact = 2;
			else if(G[i1] != G[i2])
				impact = 3;
			else
				impact = 4;
		}
		ret[K] = impact;
	}
	return ret;
}

vector<int> solution_bf(string &S, vector<int> &P, vector<int> &Q) {
	if(S.empty() || P.empty() || Q.empty())
		return vector<int>();

	vector<int> ret(P.size());
	for(size_t K = 0; K < P.size(); K ++) {
		int impact = INT_MAX;
		for(int i = P[K]; i <= Q[K]; i ++) {
			switch(S[i]) {
				case 'A': impact = min(impact, 1); break;
				case 'C': impact = min(impact, 2); break;
				case 'G': impact = min(impact, 3); break;
				default: impact = min(impact, 4); break;
			}
		}
		ret[K] = impact;
	}
	return ret;
}

static bool equal(const vector<int> &r1, const vector<int> &r2) {
	if(r1.size() != r2.size())
		return false;
	for(size_t i = 0; i < r1.size(); i ++)
		if(r1[i] != r2[i])
			return false;
	return true;
}

static void print(const vector<int> &r, const string &tag) {
	cout << tag << ": ";
	for(size_t i = 0; i < r.size(); i ++)
		cout << r[i] << " ";
	cout << endl;
}

int main(void) {
	{ // 1
		string S = "CAGCCTA";
		int p[] = {2, 5, 0};
		int q[] = {4, 5, 6};
		int exp[] = {2, 4, 1};
		vector<int> P(p, p + sizeof(p) / sizeof(p[0]));
		vector<int> Q(q, q + sizeof(q) / sizeof(q[0]));
		vector<int> Exp(exp, exp + sizeof(exp) / sizeof(exp[0]));

		vector<int> r1 = solution(S, P, Q);
		if(!equal(r1, Exp)) {
			print(r1, "result");
			print(Exp, "expected");
			cout << "ERROR1" << endl;
		}

		vector<int> r2 = solution_bf(S, P, Q);
		if(!equal(r2, Exp)) {
			print(r2, "BF result");
			print(Exp, "expected");
			cout << "ERROR1BF" << endl;
		}
	}

	{ // 2
		srand(time(NULL));
		for(int test = 0; test < 100; test ++) {
			cout << "Test " << test << "..." << endl;
			const int N = 12;
			const int M = 50;

			string S;
			for(int i = 0; i < N; i ++) {
				int ch = rand() % 4;
				switch(ch) {
					case 0: S += 'A'; break;
					case 1: S += 'C'; break;
					case 2: S += 'G'; break;
					case 3: S += 'T'; break;
				}
			}

			vector<int> P(M), Q(M);
			for(int i = 0; i < M; i ++) {
				int p = rand() % N;
				int q = rand() % N;
				P[i] = min(p, q);
				Q[i] = max(p, q);
			}

			vector<int> r1 = solution(S, P, Q);
			vector<int> r2 = solution_bf(S, P, Q);
			if(!equal(r1, r2)) {
				cout << "S: " << S << endl;
				print(P, "P");
				print(Q, "Q");
				print(r1, "result");
				print(r2, "BF result");
				cout << "ERROR2" << endl;
			} else
				cout << "OK" << endl;
		}
	}

	return 0;
}
