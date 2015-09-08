// 9.1
// CountSemiprimes
// Count the semiprime numbers in the given range [a..b]
// Test Score: 100%
#include <iostream>
#include <vector>
using namespace std;

vector<int> solution(int N, vector<int> &P, vector<int> &Q) {
	if(P.empty())
		return vector<int>();

	// 0. Check if we can have semiprimes with input params
	const int M = int(P.size());
	vector<int> ret(M, 0);
	if(N <= 3) {
		// There are no semiprimes there
		for(int i = 0; i < M; i ++)
			ret[i] = 0;
		return ret;
	}


	//
	// PRE-PROCESSING
	//

	// 1. Prepare Primes array
	// 1.a Prepare the sieve
	vector<bool> sieve(N + 1, true);
	{
		sieve[0] = false;
		sieve[1] = false;
		int i = 2;
		while((i * i) <= N) {
			if(sieve[i]) {
				int k = i * i;
				while(k <= N) {
					sieve[k] = false;
					k += i;
				}
			}
			i ++;
		}
	}

	//cout << "Sieve:" << endl;
	//for(size_t i = 0; i < sieve.size(); i ++) cout << sieve[i] << " ";
	//cout << endl << endl;


	// 1.b Prepare the primes array
	vector<int> primes;
	{
		for(int i = 2; i <= N; i ++)
			if(sieve[i])
				primes.push_back(i);
	}

	// 1.c Check if we have primes (we must have, actually)
	if(primes.empty())
		return ret;

	//cout << "Primes:" << endl;
	//for(size_t i = 0; i < primes.size(); i ++) cout << primes[i] << " ";
	//cout << endl << endl;

	// 2. Prepare the semi-sieve
	vector<bool> semi_sieve(N + 1, false);
	{
		const int primes_cnt = int(primes.size());
		for(int p1_idx = 0; p1_idx < (primes_cnt - 1); p1_idx ++) {
			int p1 = primes[p1_idx];
			//cout << "For prime: " << p1 << endl;
			if((p1 * p1) > N)
				break;
			for(int p2_idx = p1_idx; p2_idx < primes_cnt; p2_idx ++) {
				int p2 = primes[p2_idx];
				int semi_prime = p1 * p2;

				//cout << "Candidate Semi-sieve: "
				//	<< semi_prime << endl;

				if(semi_prime > N)
					break;

				//cout << "Update Semi-sieve: "
				//	<< semi_prime << endl;
				semi_sieve[semi_prime] = true;
			}
		}
	}


	//cout << "Semi-sieve:" << endl;
	//for(size_t i = 0; i < semi_sieve.size(); i ++) cout << semi_sieve[i] << " ";
	//cout << endl;
	//for(size_t i = 0; i < semi_sieve.size(); i ++) if(semi_sieve[i]) cout << i << " ";
	//cout << endl << endl;


	// 3. Find semiprime trend
	vector<int> semi_trend(N + 1, 0);
	{
		int semi_cnt = 0;
		for(int i = 4; i <= N; i ++) {
			if(semi_sieve[i])
				semi_cnt ++;
			semi_trend[i] = semi_cnt;
		}
	}

	//cout << "Semi-sieve trend:" << endl;
	//for(size_t i = 0; i < semi_trend.size(); i ++) cout << semi_trend[i] << " ";
	//cout << endl << endl;

	//
	// SERVING QUERIES
	//

	// 4. Find semiprime counts within queries
	{
		for(int i = 0; i < M; i ++) {
			int start = P[i] - 1;
			int finish = Q[i];
			int cnt = semi_trend[finish] - semi_trend[start];
			ret[i] = cnt;
		}
	}

	return ret;
}

int main(void) {

	{ // 1
		int p[] = { 1,  4, 16};
		int q[] = {26, 10, 20};
		vector<int> P(p, p + sizeof(p) / sizeof(p[0]));
		vector<int> Q(q, q + sizeof(q) / sizeof(q[0]));
		vector<int> R = solution(26, P, Q);

		cout << "Result: " << endl;
		for(size_t i = 0; i < R.size(); i ++)
			cout << R[i] << " ";
		cout << endl;

		if((R[0] != 10)
				|| (R[1] != 4)
				|| (R[2] != 0))
			cout << "ERROR" << endl;
	}

	return 0;
}
